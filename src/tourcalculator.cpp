#include "tourcalculator.h"
#include "functions.h"

#include <iostream>
#include <list>
#include <string>

void print_tours_list(std::list<Tour*> *tours);

//// Tour Calculator

TourCalculator::TourCalculator(std::list<Tournament*> tournaments)
: tournaments(tournaments) {

  graph      = new Graph();
  homeExists = false;

}

TourCalculator::TourCalculator(std::list<Tournament*> tournaments, double home_lat, double home_lon)
: tournaments(tournaments) {

  graph      = new Graph();
  home       = new Home(home_lat, home_lon);
  homeExists = true;

}

TourCalculator::~TourCalculator() {

  delete graph;

  std::list<Tournament*>::iterator it;

  for (it = tournaments.begin(); it != tournaments.end(); ++it) {

    Tournament *tournament = *it;

    delete tournament;

  }

  if (homeExists) delete home;

}

// Calculators

/*

Given a number of tournaments,
return the path in a region with the shortest total distance and
the number of tournaments specified.

Assumptions
===========

Node edges only contain child nodes which start after the current nodes finish date

Algorithm
=========

1. Calculate all tours of length 1 by making one for each of the nodes in the graph.nodes list

2. Calculate all tours of length 2 by looping through all tours of length 1 and for each tour
make a new one with each of the nodes child nodes.

3. Repeat step 2 until all tours of length num_tournaments are calculated

4. Loop through all tours of length num_tournaments to find the one with the least combined weight/distance

*/

Tour* TourCalculator::calculate_region_tour_min_distance_num_tournaments(int num_tournaments, bool start_from_home) {

  build_region_graph();

  std::list<Tour*> prev_tours; // tours of length n
  std::list<Tour*> curr_tours; // tours of length n + 1

  // Add all the tournaments as potential start tournaments

  if (start_from_home) initialise_tours_list_from_home(&prev_tours);
  else                 initialise_tours_list(&prev_tours);
  
  // Find all potential multi-tournament tours

  for (int i = 1; i < num_tournaments; ++i) {

    get_next_tour_iteration(&prev_tours, &curr_tours);

    if (curr_tours.size() == 0) {

      break;
    
    } else {
      
      free_tours(&prev_tours);
      prev_tours = curr_tours;
      curr_tours.clear();
    
    }

  }

  Tour *best_tour = get_minimum_tour(prev_tours);

  //print_tours_list(&prev_tours);

  return best_tour;

}

/*

Given a tournaments graph, return the path with the shortest distance and
the maximum number of tournaments possible

Assumptions
===========

Node edges only contain child nodes which start after the current nodes finish date

Algorithm
=========

1. Calculate all tours of length 1 by making one for each of the nodes in the graph.nodes list

2. Calculate all tours of length 2 by looping through all tours of length 1 and for each tour
make a new one with each of the nodes child nodes.

3. Repeat step 2 until all the current list of tours is empty

4. Loop through all tours in the previous tours list to find the one with the least combined weight/distance

*/

Tour* TourCalculator::calculate_region_tour_min_distance_max_tournaments(bool start_from_home) {

  build_region_graph();

  std::list<Tour*> prev_tours; // tours of length n
  std::list<Tour*> curr_tours; // tours of length n + 1

  // Add all the tournaments as potential start tournaments

  if (start_from_home) initialise_tours_list_from_home(&prev_tours);
  else                 initialise_tours_list(&prev_tours);
  
  // Find all potential multi-tournament tours

  while (true) {

    get_next_tour_iteration(&prev_tours, &curr_tours);

    if (curr_tours.size() == 0) {

      break;
    
    } else {
    
      free_tours(&prev_tours);
      prev_tours = curr_tours;
      curr_tours.clear();
    
    }

  }

  Tour *best_tour = get_minimum_tour(prev_tours);

  //print_tours_list(&prev_tours);

  return best_tour;

}

Tour* TourCalculator::calculate_return_home_tour_min_distance_num_tournaments(int num_tournaments) {

  build_return_home_graph();

  std::list<Tour*> prev_tours; // tours of length n
  std::list<Tour*> curr_tours; // tours of length n + 1

  // Add all the tournaments as potential start tournaments

  initialise_tours_list(&prev_tours);
  
  // Find all potential multi-tournament tours

  for (int i = 1; i < num_tournaments; ++i) {

    get_next_tour_iteration(&prev_tours, &curr_tours);

    if (curr_tours.size() == 0) {

      break;
    
    } else {
      
      free_tours(&prev_tours);
      prev_tours = curr_tours;
      curr_tours.clear();
    
    }

  }

  Tour *best_tour = get_minimum_tour(prev_tours);

  //print_tours_list(&prev_tours);

  return best_tour;

}

Tour* TourCalculator::calculate_return_home_tour_min_distance_max_tournaments() {

  build_return_home_graph();

  std::list<Tour*> prev_tours; // tours of length n
  std::list<Tour*> curr_tours; // tours of length n + 1

  // Add all the tournaments as potential start tournaments

  initialise_tours_list(&prev_tours);
  
  // Find all potential multi-tournament tours

  while (true) {

    get_next_tour_iteration(&prev_tours, &curr_tours);

    if (curr_tours.size() == 0) {

      break;
    
    } else {
    
      free_tours(&prev_tours);
      prev_tours = curr_tours;
      curr_tours.clear();
    
    }

  }

  Tour *best_tour = get_minimum_tour(prev_tours);

  //print_tours_list(&prev_tours);

  return best_tour;

}

// Graph Builders

/*

Builds a graph in TourCalculator::graph where every current node has edges to
all other nodes where the start date occurs after the current node's end_date

*/

void TourCalculator::build_region_graph() {

  graph = new Graph();

  for (auto const &tournament : tournaments) {

    graph->add_node(tournament);
  
  }

  graph->add_region_distance_edges(tournaments);

}

/*

Builds a graph in TourCalculator::graph where every current node has edges to
all other nodes where the start date occurs after the current node's end_date

*/

void TourCalculator::build_return_home_graph() {

  for (auto const &tournament : tournaments) {

    graph->add_node(tournament);
  
  }

  graph->add_return_home_distance_edges(tournaments, home);

}

// Tour Calculator Helper Functions

/*



*/

void TourCalculator::initialise_tours_list(std::list<Tour*> *tours) {
  
  std::list<Node*>::iterator it;

  for (it = graph->nodes.begin(); it != graph->nodes.end(); ++it) {

    // If a starting point is defined, add the initial from the start as the inital weight

    Tour  *tour           = new Tour();
    Node  *node           = *it;
    double initial_weight = 0;

    tour->path.append("Begin");
    tour->add_node(node, initial_weight);
    tours->push_back(tour);

  }

}

void TourCalculator::initialise_tours_list_from_home(std::list<Tour*> *tours) {
  
  std::list<Node*>::iterator it;

  for (it = graph->nodes.begin(); it != graph->nodes.end(); ++it) {

    // If a starting point is defined, add the initial from the start as the inital weight

    Tour  *tour           = new Tour();
    Node  *node           = *it;

    double initial_weight = haversine_distance(home->lat, home->lon, node->lat, node->lon);

    tour->path.append("Begin - Home");
    tour->add_node(node, initial_weight);
    tours->push_back(tour);

  }

}

void TourCalculator::get_next_tour_iteration(std::list<Tour*> *prev_tours, std::list<Tour*> *curr_tours) {

  std::list<Tour*>::iterator it;

  for (it = prev_tours->begin(); it != prev_tours->end(); ++it) {

    Tour *tour      = *it;
    Node *last_node = tour->nodes.back();

    std::list<Edge*>::iterator it2;

    for (it2 = last_node->edges.begin(); it2 != last_node->edges.end(); ++it2) {
    
      Edge *edge     = *it2;
      Tour *new_tour = tour->copy();

      new_tour->add_node(edge->node, edge->weight);
      curr_tours->push_back(new_tour);

    }

  }

}

Tour* TourCalculator::get_minimum_tour(std::list<Tour*> tours) {

  std::list<Tour*>::iterator it = tours.begin();

  Tour *best_tour = *it;

  for (++it; it != tours.end(); ++it) {

    Tour *tour = *it;

    if (tour->total_weight < best_tour->total_weight) {
        best_tour = tour;
    }

  }

  return best_tour;

}

//// Tour

void Tour::add_node(Node *node, double weight) {
  
  nodes.push_back(node);

  total_weight += weight;

  std::string node_string = " - " + std::to_string(weight) + " - " + node->name;

  path += node_string;

}

Tour* Tour::copy() {
  
  Tour *new_tour = new Tour();

  for (auto const& node : nodes) {
    new_tour->nodes.push_back(node);
  }

  new_tour->total_weight = total_weight;
  new_tour->path         = path;

  return new_tour;

}