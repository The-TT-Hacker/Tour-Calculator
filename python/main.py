"""
Algorithm to calcuate the ideal tournaments someone should play
"""

from graph      import *
from calculator import *
from datetime   import datetime

NUM_TOURNAMENTS = 2

home1 = {"lat": -33.823685, "lon": 151.193543}
home2 = {"lat": 51.433558,  "lon": -0.215512}

tournaments = [
	{"name": "Wimbledon",       "lat": 51.433558,  "lon": -0.215512,  "start_date": datetime(2019, 12, 29), "end_date": datetime(2019, 12, 30)},
	{"name": "Sydney Open",     "lat": -33.854980, "lon": 151.072281, "start_date": datetime(2020, 1, 1), "end_date": datetime(2020, 1, 4)},
	{"name": "Newcastle Open",  "lat": -32.923188, "lon": 151.729923, "start_date": datetime(2020, 1, 6), "end_date": datetime(2020, 1, 10)},
	{"name": "Wollongong Open", "lat": -34.418964, "lon": 150.886659, "start_date": datetime(2020, 1, 12), "end_date": datetime(2020, 1, 16)},
	{"name": "Bathurst Open",   "lat": -33.407295, "lon": 149.576608, "start_date": datetime(2020, 1, 18), "end_date": datetime(2020, 1, 22)}
	#{"name": "Manly Open",      "lat": -33.796415, "lon": 151.285392, "start_date": datetime(2020, 1, 24), "end_date": datetime(2020, 1, 28)}
]

if __name__ == "__main__":
	graph = build_region_graph(tournaments)

	#print(graph)

	tour1 = calculate_return_home_tour_min_distance_num_tournaments(graph, NUM_TOURNAMENTS)
	#tour2 = calculate_tour_min_distance_max_tournaments(graph, home2)

	print(tour1)
	#print(tour2)