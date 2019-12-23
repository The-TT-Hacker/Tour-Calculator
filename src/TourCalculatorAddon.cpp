#include <node.h>

#include <iostream>
#include <list>

#include "TourCalculator.h"
#include "Tournament.h"
#include "Graph.h"

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Exception;
using v8::Array;

TourCalculator* BuildTourCalculator(Isolate* isolate, Local<Array> tournaments_array) {

  // Build list of tournaents

  std::list<Tournament*> tournaments;

	Tournament *tournament;

	for (int i = 0; i < tournaments_array->Length(); ++i) {

	  Local<Object> tournament_obj = Local<Object>::Cast(tournaments_array->Get(i));

	  Local<Value> value_name = tournament_obj->Get(String::NewFromUtf8(isolate, "name"));
		String::Utf8Value str_name(isolate, value_name);
		std::string       name(*str_name);

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

	  Tournament *tournament = new Tournament(name,  start_date, end_date, lat,  lon);

	  tournaments.push_back(tournament);

	}

	// Calculate tour

	TourCalculator* tourcalculator = new TourCalculator(tournaments);

	return tourcalculator;

}

void BuildTour(Isolate* isolate, Tour* tour, Local<Array> best_tour) {

	std::list<Node*>::iterator it;

	int i = 0;

  for (it = tour->nodes.begin(); it != tour->nodes.end(); ++it) {

  	Node *node = *it;

  	Local<Object> tour_obj = Object::New(isolate);

  	tour_obj->Set(String::NewFromUtf8(isolate, "name"),       String::NewFromUtf8(isolate, node->name.c_str()));
  	tour_obj->Set(String::NewFromUtf8(isolate, "start_date"), String::NewFromUtf8(isolate, node->start_date.c_str()));
  	tour_obj->Set(String::NewFromUtf8(isolate, "end_date"),   String::NewFromUtf8(isolate, node->end_date.c_str()));
  	tour_obj->Set(String::NewFromUtf8(isolate, "lat"),        Number::New(isolate, node->lat));
  	tour_obj->Set(String::NewFromUtf8(isolate, "lon"),        Number::New(isolate, node->lon));

  	best_tour->Set(i, tour_obj);

  	++i;

	}

}

void CalculateTour(const FunctionCallbackInfo<Value>& args) {

	// Preamble

  Isolate*        isolate = args.GetIsolate();
  Local<Context>  context = isolate->GetCurrentContext();

  // Arguments

  Local<Array>    array = Local<Array>::Cast(args[0]);
  Local<Function> cb    = Local<Function>::Cast(args[1]);

  // Calculate Tour

  TourCalculator* tourcalculator = BuildTourCalculator(isolate, array);
	Tour*           tour           = tourcalculator->calculate_region_tour_min_distance_max_tournaments();

	Local<Array> best_tour = Array::New(isolate);

	BuildTour(isolate, tour, best_tour);

	// Initite callback with the best tour

  const unsigned argc = 1;

  Local<Value> argv[argc] = { best_tour };
  
  cb->Call(context, Null(isolate), argc, argv);

}

void Init(Local<Object> exports) {

  NODE_SET_METHOD(exports, "calc",  CalculateTour);

}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)