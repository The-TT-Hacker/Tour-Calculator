"""

Algorithm to calcuate the ideal tournaments someone should play

"""

from filter     import *
from graph      import *
from calculator import *

NUM_TOURNAMENTS = 2

tournaments = [
	{"name": "Sydney Open", "lat": , "lon": , "start_date": "", "end_date": ""}
]

if __name__ == "__main__":
	graph = build_graph()

	tour = calculate_region_tour_num_tournaments(graph, NUM_TOURNAMENTS)

	print(tour)