#include "TourCalculator.h"
#include "Graph.h"

#include <iostream>

void print_tour(Tour *tour);

int main () {

	std::list<Tournament*> tournaments;

	Tournament *tournament1 = new Tournament("Wimbledon",  "01/01/2020", "03/01/2020", 51.433558,  -0.215512);
	Tournament *tournament2 = new Tournament("Sydney",     "03/01/2020", "06/01/2020", -33.854980, 151.072281);
	Tournament *tournament3 = new Tournament("Newcastle",  "07/01/2020", "09/01/2020", -32.923188, 151.729923);
	Tournament *tournament4 = new Tournament("Wollongong", "10/01/2020", "12/01/2020", -34.418964, 150.886659);
	Tournament *tournament5 = new Tournament("Bathurst",   "13/01/2020", "15/01/2020", -33.407295, 149.576608);

	tournaments.push_back(tournament1);
	tournaments.push_back(tournament2);
	tournaments.push_back(tournament3);
	tournaments.push_back(tournament4);
	tournaments.push_back(tournament5);

  TourCalculator tourcalculator = TourCalculator(tournaments);

  Tour* tour = tourcalculator.calculate_region_tour_min_distance_max_tournaments();

  print_tour(tour);

  return 0;

}

void print_tour(Tour *tour) {

	std::cout << "Best Tour:" << "\n";

  std::cout << "\t" << "Weight: " << tour->total_weight << "\n";
  std::cout << "\t" << "Nodes:"   << "\n";

  std::list<Node*>::iterator it;

  for (it = tour->nodes.begin(); it != tour->nodes.end(); ++it) {

  	Node *node = *it;

  	std::cout << "\t\t" << node->name << "\n";

	}

}