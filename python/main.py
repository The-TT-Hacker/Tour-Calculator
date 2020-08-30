#!/usr/bin/env python

"""
Algorithm to calcuate the ideal tournaments someone should play
"""

from datetime   import datetime

class Tour:

    def __init__(self):
        tour_length = 0
        tournaments = []

tour_length = 2

home = {"lat": -33.823685, "lon": 151.193543}
#home = {"lat": 51.433558,  "lon": -0.215512}

tournaments = [
        { "name": "Wimbledon",       "lat": 51.433558,  "lon": -0.215512,  "start_date": datetime(2019, 12, 29), "end_date": datetime(2019, 12, 30), "best_tour": Tour() },
	{ "name": "Sydney Open",     "lat": -33.854980, "lon": 151.072281, "start_date": datetime(2020, 1,  1),  "end_date": datetime(2020, 1,  4),  "best_tour": Tour() },
	{ "name": "Newcastle Open",  "lat": -32.923188, "lon": 151.729923, "start_date": datetime(2020, 1,  6),  "end_date": datetime(2020, 1,  10), "best_tour": Tour() },
	{ "name": "Wollongong Open", "lat": -34.418964, "lon": 150.886659, "start_date": datetime(2020, 1,  12), "end_date": datetime(2020, 1,  16), "best_tour": Tour() },
	{ "name": "Bathurst Open",   "lat": -33.407295, "lon": 149.576608, "start_date": datetime(2020, 1,  18), "end_date": datetime(2020, 1,  22), "best_tour": Tour() },
	{ "name": "Manly Open",      "lat": -33.796415, "lon": 151.285392, "start_date": datetime(2020, 1,  24), "end_date": datetime(2020, 1,  28), "best_tour": Tour() }
]

if __name__ == "__main__":
    tournaments_sorted = sorted( tournaments, key = lambda x : x["end_date"], reverse = True )

    # Traverse list of tournaments once
    for current_tournament in tournaments_sorted:
        #print( t )
        remaining_tournaments = filter( lambda x : x["start_date"] > current_tournament["end_date"], tournaments_sorted )

        # Check each tournament occuring after the current_tournament
        for remaining_tournament in remaining_tournaments:
            
            if (remaining_tournament["best_tour"].tour_length == tour_length):
                remaining_tournament["best_tour"].tournaments.pop()
                remaining_tournament["best_tour"].tournaments.insert(0, current_tournament)

            
            else:
                remaining
