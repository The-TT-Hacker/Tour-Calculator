#!/usr/bin/env python

"""
Algorithm to calcuate the ideal tournaments someone should play
"""

from datetime   import datetime
from functions import haversine 
import sys

class Tour:

    def __init__(self):
        # Number of tournaments in the tour
        tour_length = 0

        # List of tournaments in chronological order
        tournaments = []
        
        # Weight between the tournament with the corrosponding index in tournaments list and the next tournament in the list
        weights = []

    def get_weight(self):
        return sum( weights ) 

    def add_tournament(self, tournament):
        
        # if it's the first tournament, append weight 0
        if tour_length == 0:
            weights.insert(0, 0)
        else:
            weights.insert(0, cost(tournament, self.tournaments[1]))

        tour_length += 1
        tournaments.insert(0, tournament)

    def get_sub_weight(self, current_tournament, length):
        tour = Tour()

        tour.tournaments.append(current_tournament)

        for tournament in tournaments:

NUM_TOURNAMENTS = 2

tour_length = 2

home = {"lat": -33.823685, "lon": 151.193543}
#home = {"lat": 51.433558,  "lon": -0.215512}

tournaments = [
    { "name": "Wimbledon",       "lat":  51.433558, "lon":  -0.215512, "start_date": datetime(2019, 12, 29), "end_date": datetime(2019, 12, 30), "best_tour": Tour() },
    { "name": "Sydney Open",     "lat": -33.854980, "lon": 151.072281, "start_date": datetime(2020, 1,   1), "end_date": datetime(2020, 1,   4), "best_tour": Tour() },
	{ "name": "Newcastle Open",  "lat": -32.923188, "lon": 151.729923, "start_date": datetime(2020, 1,   6), "end_date": datetime(2020, 1,  10), "best_tour": Tour() },
	{ "name": "Wollongong Open", "lat": -34.418964, "lon": 150.886659, "start_date": datetime(2020, 1,  12), "end_date": datetime(2020, 1,  16), "best_tour": Tour() },
	{ "name": "Bathurst Open",   "lat": -33.407295, "lon": 149.576608, "start_date": datetime(2020, 1,  18), "end_date": datetime(2020, 1,  22), "best_tour": Tour() },
	{ "name": "Manly Open",      "lat": -33.796415, "lon": 151.285392, "start_date": datetime(2020, 1,  24), "end_date": datetime(2020, 1,  28), "best_tour": Tour() }
]

def cost(tournament1, tournament2):
    return haversine(tournament1["lat"], tournament1["lon"], tournament2["lat"], tournament2["lon"])

def main(home, tournaments, tour_length=None):

    # Sort tournaments in reverse chronological order by their end date
    tournaments_sorted = sorted( tournaments, key = lambda x : x["end_date"], reverse = True )

    # Stores the current best tour
    best_tour = Tour()

    # Traverse list of tournaments once
    for current_tournament in tournaments_sorted:

	    tour1 = calculate_region_tour_min_distance_num_tournaments(graph, NUM_TOURNAMENTS)
	    #tour2 = calculate_tour_min_distance_max_tournaments(graph, home2)
        ## Get current_tournament's best tour

        # Set best tour as a tour with only the current_tournament
        current_tournament["best_tour"].add_tournament(current_tournament)

        # Get the list of tournaments which start after the current_tournament's end date
        remaining_tournaments = filter( lambda x : x["start_date"] > current_tournament["end_date"], tournaments_sorted )
        
        # Check each tournament occuring after the current_tournament
        for remaining_tournament in remaining_tournaments:
            
            # If the subsequent_tournament's best tour is the requested tour length
            # Should not run if no tour length is given
            if ( remaining_tournament["best_tour"].tour_length == tour_length ):
                 raise Exception("This should never be run")
                 # Tour starting at current_tournament and then first tour_length - 1 tournaments in the remaining_tournament's best tour
                 new_tour = remaining_tournament["best_tour"].
            
            # If we have not reached the number of tournaments requested in the tour
            elif ( remaining__tournament["best_tour"].get_weight() + cost( current_tournament, remaining_tournament ) > current_tournament["best_tour"].get_weight()):
                # Replace current_tournament's best tour with the current_tournament plus the remaining_tournament's best tour
                current_tournament["best_tour"]

        # Check if current_tournament's best tour is the overall best so far
        if current_tournament["best_tour"].tour_length + 1 >= best_tour.tour_length:
            
            # Add home to the current_tournament's best tour
            

            if current_tournament["best_tour"].get_weight() > best_tour.get_weight()):
                best_tour = current_tournament["best_tour"]

if __name__ == "__main__":
    sys.exit(main(home, tournaments))
