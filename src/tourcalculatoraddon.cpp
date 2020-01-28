#include "tourcalculator.h"
#include "functions.h"

#include <node.h>
#include <uv.h>
#include <iostream>
#include <list>
#include <unistd.h>

using v8::Context;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;

using v8::Function;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Array;
using v8::Integer;
using v8::Maybe;
using v8::MaybeLocal;
using v8::Persistent;
using v8::HandleScope;

void            build_tournament_list(Isolate* isolate, Local<Array> tournaments_array, std::list<Tournament>* tournaments);
TourCalculator* build_tour_calculator(Isolate* isolate, Local<Array> tournaments_array);
TourCalculator* build_tour_calculator_with_home(Isolate* isolate, Local<Array> tournaments_array, double home_lat = (double) NULL, double home_lon = (double) NULL);
Local<Array>    build_tour_array(Isolate* isolate, Tour* tour);
Local<String>   get_string(const char* str, Isolate* isolate);
Local<Object>   get_object_from_array(Local<Array> array, int i, Local<Context> context);
std::string     get_string_from_object(Local<Object> obj, const char* str, Isolate* isolate);
double          get_double_from_object(Local<Object> obj, const char* str, Isolate* isolate);
int             get_int_from_integer(Local<Integer> num, Local<Context> context);

struct worker_data {
  int                  num_tournaments;
  TourCalculator*      tourcalculator;
  Tour*                tour;
  Persistent<Function> callback;
};

void calculate_region_tour_min_distance_max_tournaments_worker(uv_work_t* req) {
  worker_data* request = (worker_data*)req->data;
  request->tour = request->tourcalculator->calculate_region_tour_min_distance_max_tournaments();

  sleep(2);
}

void calculate_region_tour_min_distance_num_tournaments_worker(uv_work_t* req) {
  worker_data* request = (worker_data*)req->data;
  request->tour = request->tourcalculator->calculate_region_tour_min_distance_num_tournaments(request->num_tournaments);

  sleep(2);
}

void calculate_region_tour_min_distance_max_tournaments_from_home_worker(uv_work_t* req) {
  worker_data* request = (worker_data*)req->data;
  request->tour = request->tourcalculator->calculate_region_tour_min_distance_max_tournaments();

  sleep(2);
}

void calculate_region_tour_min_distance_num_tournaments_from_home_worker(uv_work_t* req) {
  worker_data* request = (worker_data*)req->data;
  request->tour = request->tourcalculator->calculate_region_tour_min_distance_num_tournaments(request->num_tournaments);

  sleep(2);
}

void post_calculation(uv_work_t* req, int status) {

  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  worker_data* request = (worker_data*)req->data;
  delete req;

  Local<Array> best_tour = build_tour_array(isolate, request->tour);

  Local<Value> argv[1];

  argv[0] = best_tour;

  Local<Function>::New(isolate, request->callback)->Call(isolate->GetCurrentContext(), Null(isolate), 1, argv);

  // Cleanup

  delete request->tourcalculator;
  delete request->tour;
  request->callback.~Persistent();
  delete request;

}

// Tour Calculator Wrappers

void calculate_region_tour_min_distance_max_tournaments(const FunctionCallbackInfo<Value>& args) {

	// Preamble - JS Environment

  Isolate*        isolate = args.GetIsolate();
  Local<Context>  context = isolate->GetCurrentContext();

  // JS Arguments

  Local<Array>    array    = Local<Array>::Cast(args[0]);
  Local<Function> callback = Local<Function>::Cast(args[1]);

  // Thread Pool Setup

  worker_data*   request = new worker_data;
  uv_work_t* req     = new uv_work_t();

  request->tourcalculator  = build_tour_calculator(isolate, array);
  request->callback.Reset(isolate, callback);
  
  req->data = request;

  // Push To Thread Pool

  uv_queue_work(uv_default_loop(), req, calculate_region_tour_min_distance_max_tournaments_worker, post_calculation);

}

void calculate_region_tour_min_distance_num_tournaments(const FunctionCallbackInfo<Value>& args) {

  // Preamble - JS Environment

  Isolate*        isolate = args.GetIsolate();
  Local<Context>  context = isolate->GetCurrentContext();

  // JS Arguments

  Local<Array>    array    = Local<Array>::Cast(args[0]);
  Local<Integer>  num      = Local<Integer>::Cast(args[1]);
  Local<Function> callback = Local<Function>::Cast(args[2]);

  // Convert Arguments

  int num_tournaments = get_int_from_integer(num, context);

  // Thread Pool Setup

  worker_data*   request = new worker_data;
  uv_work_t* req     = new uv_work_t();

  request->num_tournaments = num_tournaments;
  request->tourcalculator  = build_tour_calculator(isolate, array);
  request->callback.Reset(isolate, callback);

  req->data = request;

  // Push To Thread Pool

  uv_queue_work(uv_default_loop(), req, calculate_region_tour_min_distance_num_tournaments_worker, post_calculation);

}

void calculate_region_tour_min_distance_max_tournaments_from_home(const FunctionCallbackInfo<Value>& args) {

  // Preamble - JS Environment

  Isolate*        isolate = args.GetIsolate();
  Local<Context>  context = isolate->GetCurrentContext();

  // JS Arguments

  Local<Array>    array    = Local<Array>::Cast(args[0]);
  Local<Object>   home_obj = Local<Object>::Cast(args[1]);
  Local<Function> callback = Local<Function>::Cast(args[2]);

  // Convert Arguments

  double home_lat = get_double_from_object(home_obj, "lat", isolate);
  double home_lon = get_double_from_object(home_obj, "lon", isolate);

  // Thread Pool Setup

  worker_data* request = new worker_data;
  uv_work_t*   req     = new uv_work_t();

  request->tourcalculator = build_tour_calculator_with_home(isolate, array, home_lat, home_lon);
  request->callback.Reset(isolate, callback);

  req->data = request;

  // Push To Thread Pool

  uv_queue_work(uv_default_loop(), req, calculate_region_tour_min_distance_max_tournaments_from_home_worker, post_calculation);

}

void calculate_region_tour_min_distance_num_tournaments_from_home(const FunctionCallbackInfo<Value>& args) {

  // Preamble - JS Environment

  Isolate*        isolate = args.GetIsolate();
  Local<Context>  context = isolate->GetCurrentContext();

  // JS Arguments

  Local<Array>    array    = Local<Array>::Cast(args[0]);
  Local<Integer>  num      = Local<Integer>::Cast(args[1]);
  Local<Object>   home_obj = Local<Object>::Cast(args[2]);
  Local<Function> callback = Local<Function>::Cast(args[3]);

  // Convert Arguments

  double home_lat        = get_double_from_object(home_obj, "lat", isolate);
  double home_lon        = get_double_from_object(home_obj, "lon", isolate);
  int    num_tournaments = get_int_from_integer(num, context);

  // Thread Pool Setup

  worker_data* request = new worker_data;
  uv_work_t*   req     = new uv_work_t();

  request->num_tournaments = num_tournaments;
  request->tourcalculator  = build_tour_calculator_with_home(isolate, array, home_lat, home_lon);
  request->callback.Reset(isolate, callback);

  req->data = request;

  // Push To Thread Pool

  uv_queue_work(uv_default_loop(), req, calculate_region_tour_min_distance_num_tournaments_from_home_worker, post_calculation);

}

// Define functions and objects to be exported to JavaScript

void Init(Local<Object> exports) {

  NODE_SET_METHOD(
  	exports,
  	"calculate_region_tour_min_distance_max_tournaments",
  	calculate_region_tour_min_distance_max_tournaments
  );

  NODE_SET_METHOD(
  	exports,
  	"calculate_region_tour_min_distance_num_tournaments",
  	calculate_region_tour_min_distance_num_tournaments
  );

  NODE_SET_METHOD(
    exports,
    "calculate_region_tour_min_distance_max_tournaments_from_home",
    calculate_region_tour_min_distance_max_tournaments_from_home
  );

  NODE_SET_METHOD(
    exports,
    "calculate_region_tour_min_distance_num_tournaments_from_home",
    calculate_region_tour_min_distance_num_tournaments_from_home
  );

}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

// Helper Functions

/*

Takes a JavaScript array and builds a list of tournament objects.
Initialises TourCalculator object with the list of tournaments and returns a pointer to it.

*/

void build_tournament_list(Isolate* isolate, Local<Array> tournaments_array, std::list<Tournament>* tournaments) {

  Local<Context> context = isolate->GetCurrentContext();

  // Build list of tournaments

  for (uint32_t i = 0; i < tournaments_array->Length(); ++i) {

    Local<Object> tournament_obj = get_object_from_array(tournaments_array, i, context);

    std::string name       = get_string_from_object(tournament_obj, "tournamentName", isolate);
    std::string start_date = get_string_from_object(tournament_obj, "startDate", isolate);
    std::string end_date   = get_string_from_object(tournament_obj, "endDate", isolate);

    double lat = get_double_from_object(tournament_obj, "latitude", isolate);
    double lon = get_double_from_object(tournament_obj, "longitude", isolate);

    Tournament tournament = Tournament(name, start_date, end_date, lat, lon);

    tournaments->push_back(tournament);

  }

}

/*

Takes a JavaScript array and builds a list of tournament objects.
Initialises TourCalculator object with the list of tournaments and returns a pointer to it.

*/

TourCalculator* build_tour_calculator(Isolate* isolate, Local<Array> tournaments_array) {
  
  // Build list of tournaments

  std::list<Tournament> tournaments;

  build_tournament_list(isolate, tournaments_array, &tournaments);

  // Calculate tour

  TourCalculator* tourcalculator = new TourCalculator(tournaments);

  return tourcalculator;

}

/*

Takes a JavaScript array and builds a list of tournament objects.
Initialises TourCalculator object with the list of tournaments and returns a pointer to it.

*/

TourCalculator* build_tour_calculator_with_home(Isolate* isolate, Local<Array> tournaments_array, double home_lat, double home_lon) {

  // Build list of tournaments

  std::list<Tournament> tournaments;

  build_tournament_list(isolate, tournaments_array, &tournaments);

	// Calculate tour

  TourCalculator* tourcalculator = new TourCalculator(tournaments, home_lat, home_lon);

	return tourcalculator;

}

/*

Converts a tour object into a JavaScript list with an object for each tournament

best_tour = [
	{ name: "name", start_date: "start_date", end_date: "end_date", lat: 12.3456789, lon: 12.3456789 },
	{ name: "name", start_date: "start_date", end_date: "end_date", lat: 12.3456789, lon: 12.3456789 },
	...
];

*/

Local<Array> build_tour_array(Isolate* isolate, Tour* tour) {

  Local<Context> context = isolate->GetCurrentContext();

	Local<Array> best_tour = Array::New(isolate);

	std::list<Node>::iterator it;

	int i = 0;

  for (it = tour->nodes.begin(); it != tour->nodes.end(); ++it) {

  	Node* node = &(*it);

  	Local<Object> tour_obj = Object::New(isolate);

    //std::cout << node->name << "\n";

  	tour_obj->Set(context, get_string("name", isolate),       get_string(node->name.c_str(), isolate));
  	tour_obj->Set(context, get_string("start_date", isolate), get_string(node->start_date.c_str(), isolate));
  	tour_obj->Set(context, get_string("end_date", isolate),   get_string(node->end_date.c_str(), isolate));
  	tour_obj->Set(context, get_string("lat", isolate),        Number::New(isolate, node->lat));
  	tour_obj->Set(context, get_string("lon", isolate),        Number::New(isolate, node->lon));

  	best_tour->Set(context, i, tour_obj);

  	++i;

	}

	return best_tour;

}

Local<String> get_string(const char* str, Isolate* isolate) {

  MaybeLocal<String> maybe_key = String::NewFromUtf8(isolate, str);
  Local<String> key;
  maybe_key.ToLocal(&key);

  return key;

}

Local<Object> get_object_from_array(Local<Array> array, int i, Local<Context> context) {

  MaybeLocal<Value> maybe_value = array->Get(context, i);
  Local<Value> value;
  maybe_value.ToLocal(&value);

  Local<Object> obj = Local<Object>::Cast(value);

  return obj;

}

std::string get_string_from_object(Local<Object> obj, const char* str, Isolate* isolate) {

  Local<Context> context = isolate->GetCurrentContext();

  Local<String> key = get_string(str, isolate);

  MaybeLocal<Value> maybe_value = obj->Get(context, key);
  Local<Value> value;
  maybe_value.ToLocal(&value);

  String::Utf8Value str_value(isolate, value);
  std::string       ret_str(*str_value);

  return ret_str;

}

double get_double_from_object(Local<Object> obj, const char* str, Isolate* isolate) {

  Local<Context> context = isolate->GetCurrentContext();

  Local<String> key = get_string(str, isolate);

  MaybeLocal<Value> maybe_value = obj->Get(context, key);
  Local<Value> value;
  maybe_value.ToLocal(&value);

  Maybe<double> maybe_double = value->NumberValue(context);
  double        double_value = maybe_double.FromJust();

  return double_value;

}

int get_int_from_integer(Local<Integer> num, Local<Context> context) {

  Maybe<long int> maybe_num = num->IntegerValue(context);

  int integer = maybe_num.FromJust();

  return integer;
}