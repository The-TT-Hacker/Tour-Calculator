"""

Algorithm to calcuate the ideal tournaments someone should play

"""

from graph      import build_graph
from calculator import calculate_region_tour_num_tournaments
from datetime   import datetime

NUM_TOURNAMENTS = 5

tournaments = [
	{"name": "Sydney Open",     "lat": -33.854980, "lon": 151.072281, "start_date": datetime(2020, 1, 1), "end_date": datetime(2020, 1, 4)},
	{"name": "Newcastle Open",  "lat": -32.923188, "lon": 151.729923, "start_date": datetime(2020, 1, 6), "end_date": datetime(2020, 1, 10)},
	{"name": "Wollongong Open", "lat": -34.418964, "lon": 150.886659, "start_date": datetime(2020, 1, 12), "end_date": datetime(2020, 1, 16)},
	{"name": "Bathurst Open",   "lat": -33.407295, "lon": 149.576608, "start_date": datetime(2020, 1, 18), "end_date": datetime(2020, 1, 22)},
	{"name": "Manly Open",      "lat": -33.796415, "lon": 151.285392, "start_date": datetime(2020, 1, 24), "end_date": datetime(2020, 1, 28)},
	{"name": "Wimbledon",       "lat": 51.433558,  "lon": -0.215512,  "start_date": datetime(2020, 1, 29), "end_date": datetime(2020, 1, 30)}
]

if __name__ == "__main__":
	graph = build_graph(tournaments)

	print(graph)

	tour = calculate_region_tour_num_tournaments(graph, NUM_TOURNAMENTS)

	print(tour)