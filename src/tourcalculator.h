#ifndef TOURCALCULATOR_H
#define TOURCALCULATOR_H

#include "tournament.h"
#include "graph.h"

#include <list>
#include <string>

class TourCalculator;
class Tour;

// TourCalculator

class TourCalculator {

	private:

		Graph                 *graph;
		std::list<Tournament*> tournaments;

	public:

		TourCalculator(std::list<Tournament*> tournaments);

		// Calculator algorithms

		Tour* calculate_region_tour_min_distance_num_tournaments(int num_tournaments);
		Tour* calculate_region_tour_min_distance_max_tournaments();
		//Tour* calculate_return_home_tour_min_distance_num_tournaments();
		//Tour* calculate_return_home_tour_min_distance_max_tournaments();
		//Tour* calculate_point_to_point_tour_min_distance_num_tournaments();
		//Tour* calculate_point_to_point_tour_min_distance_max_tournaments();

	private:

		// Graph builders

		void build_region_graph();
		//void build_return_home_graph();
		//void build_point_to_point_graph();

		// Helper functions

		void  initialise_tours_list(std::list<Tour*> *tours);
		void  get_next_tour_iteration(std::list<Tour*> *prev_tours, std::list<Tour*> *curr_tours);
		Tour* get_minimum_tour(std::list<Tour*> tours);

};

// Tour

class Tour {

	public:

	  std::list<Node*> nodes;
	  double           total_weight = 0;

	  void  add_node(Node *node, double weight);
	  Tour* copy();

};

#endif