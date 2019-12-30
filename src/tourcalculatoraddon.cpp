#include "tourcalculator.h"

#include <node.h>
#include <iostream>
#include <list>

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

TourCalculator* build_tour_calculator(Isolate* isolate, Local<Array> tournaments_array);
Local<Array>    build_tour_array(Isolate* isolate, Tour* tour);
Local<String>   get_string(const char* str, Isolate* isolate);
Local<Object>   get_object_from_array(Local<Array> array, int i, Local<Context> context);
std::string     get_string_from_object(Local<Object> obj, char* str, Isolate* isolate);
double          get_double_from_object(Local<Object> obj, char* str, Isolate* isolate);

// Tour Calculator Wrappers

void calculate_region_tour_min_distance_max_tournaments(const FunctionCallbackInfo<Value>& args) {

	// Preamble - JS Environment

  Isolate*        isolate = args.GetIsolate();
  Local<Context>  context = isolate->GetCurrentContext();

  // Arguments

  Local<Array>    array = Local<Array>::Cast(args[0]);
  Local<Function> cb    = Local<Function>::Cast(args[1]);

  // Calculate Tour

  TourCalculator* tourcalculator = build_tour_calculator(isolate, array);
	Tour*           tour           = tourcalculator->calculate_region_tour_min_distance_max_tournaments();
	Local<Array>    best_tour      = build_tour_array(isolate, tour);

	// Run Callback 

  const unsigned argc       = 1;
  Local<Value>   argv[argc] = { best_tour };
  
  cb->Call(context, Null(isolate), argc, argv);

}

void calculate_region_tour_min_distance_num_tournaments(const FunctionCallbackInfo<Value>& args) {

	// Preamble - JS Environment

  Isolate*        isolate = args.GetIsolate();
  Local<Context>  context = isolate->GetCurrentContext();

  // JS Arguments

  Local<Array>    array = Local<Array>::Cast(args[0]);
  Local<Integer>  num   = Local<Integer>::Cast(args[1]);
  Local<Function> cb    = Local<Function>::Cast(args[2]);

  // Calculate Tour

  Maybe<long int> maybe_num_tournaments = num->IntegerValue(context);
  int             num_tournaments       = maybe_num_tournaments.FromJust();
  TourCalculator* tourcalculator        = build_tour_calculator(isolate, array);
	Tour*           tour                  = tourcalculator->calculate_region_tour_min_distance_num_tournaments(num_tournaments);
	Local<Array>    best_tour             = build_tour_array(isolate, tour);

	// Run Callback 

  const unsigned argc       = 1;
  Local<Value>   argv[argc] = { best_tour };
  
  cb->Call(context, Null(isolate), argc, argv);

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

}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

// Helper Functions

/*

Takes a JavaScript array and builds a list of tournament objects.
Initialises TourCalculator object with the list of tournaments and returns a pointer to it.

*/

TourCalculator* build_tour_calculator(Isolate* isolate, Local<Array> tournaments_array) {

  Local<Context> context = isolate->GetCurrentContext();

  // Build list of tournaments

  std::list<Tournament*> tournaments;

	for (uint32_t i = 0; i < tournaments_array->Length(); ++i) {

    //MaybeLocal<Value> test = tournaments_array->Get(context, i);
    //Local<Object> tournament_obj;
    //test.ToLocal(&tournament_obj);

    Local<Object> tournament_obj = get_object_from_array(tournaments_array, i, context);

    //MaybeLocal<String> maybe_key = String::NewFromUtf8(isolate, "name");
    //Local<String> key;
	  //maybe_key.ToLocal(&key);

	  //Local<Value> value_name = tournament_obj->Get(context, key);
		//String::Utf8Value str_name(isolate, value_name);
		//std::string       name(*str_name);

    std::string name       = get_string_from_object(tournament_obj, "name", isolate);
    std::string start_date = get_string_from_object(tournament_obj, "start_date", isolate);
    std::string end_date   = get_string_from_object(tournament_obj, "end_date", isolate);

    double lat = get_double_from_object(tournament_obj, "lat", isolate);
    double lon = get_double_from_object(tournament_obj, "lon", isolate);

    /*

		Local<Value> value_start_date = tournament_obj->Get(String::NewFromUtf8(isolate, "start_date"));
		String::Utf8Value str_start_date(isolate, value_start_date);
		std::string       start_date(*str_start_date);

		Local<Value> value_end_date = tournament_obj->Get(String::NewFromUtf8(isolate, "end_date"));
		String::Utf8Value str_end_date(isolate, value_end_date);
		std::string       end_date(*str_end_date);

	  Local<Value> value_lat = tournament_obj->Get(String::NewFromUtf8(isolate, "lat"));
	  double lat = value_lat->NumberValue();

	  Local<Value> value_lon = tournament_obj->Get(String::NewFromUtf8(isolate, "lon"));
	  double lon = value_lon->NumberValue();

    */

	  Tournament *tournament = new Tournament(name, start_date, end_date, lat, lon);

	  tournaments.push_back(tournament);

	}

	// Calculate tour

	TourCalculator* tourcalculator = new TourCalculator(tournaments);

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

	std::list<Node*>::iterator it;

	int i = 0;

  for (it = tour->nodes.begin(); it != tour->nodes.end(); ++it) {

  	Node *node = *it;

  	Local<Object> tour_obj = Object::New(isolate);

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

std::string get_string_from_object(Local<Object> obj, char* str, Isolate* isolate) {

  Local<Context> context = isolate->GetCurrentContext();

  Local<String> key = get_string(str, isolate);

  MaybeLocal<Value> maybe_value = obj->Get(context, key);
  Local<Value> value;
  maybe_value.ToLocal(&value);

  String::Utf8Value str_value(isolate, value);
  std::string       ret_str(*str_value);

  return ret_str;

}

double get_double_from_object(Local<Object> obj, char* str, Isolate* isolate) {

  Local<Context> context = isolate->GetCurrentContext();

  Local<String> key = get_string(str, isolate);

  MaybeLocal<Value> maybe_value = obj->Get(context, key);
  Local<Value> value;
  maybe_value.ToLocal(&value);

  Maybe<double> maybe_double = value->NumberValue(context);
  double        double_value = maybe_double.FromJust();

  return double_value;

}