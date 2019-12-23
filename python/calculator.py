from graph     import Tour
from functions import *

"""
Given a tournaments graph and number of tournaments,
return the path in a region with the shortest distance and
the number of tournaments specified. If home is specified,
start the tour from there.

Assumptions
===========

Node edges only contain child nodes which start after the current nodes finish date

num_tournaments > 0

home = {"lat": lat, "lon": lon}

Algorithm
=========

1. Calculate all tours of length 1 by making one for each of the nodes in the graph.nodes list

2. Calculate all tours of length 2 by looping through all tours of length 1 and for each tour
make a new one with each of the nodes child nodes.

3. Repeat step 2 until all tours of length num_tournaments are calculated

4. Loop through all tours of length num_tournaments to find the one with the least combined weight/distance
"""

def calculate_region_tour_min_distance_num_tournaments(graph, num_tournaments, home = None):
  
  prev_tours = [] # tours of length n
  curr_tours = [] # tours of length n + 1
    
  # Add all the tournaments as potential start tournaments
  for node in graph.nodes:

    # If a starting point is defined, add the initial from the start as the inital weight
    if home:
      initial_weight = haversine(home["lon"], home["lat"], node.lon, node.lat)
    else:
      initial_weight = 0

    tour = Tour(node, initial_weight)

    prev_tours.append(tour)
  
  # Find all potential multi-tournament tours
  for i in range(num_tournaments - 1):

    for tour in prev_tours:

      # Get the last node in the tour
      last_node = tour.nodes[-1]

      # Make a new tour with each of the child nodes
      for edge in last_node.edges:

        new_tour = tour.copy()
        new_tour.add_node(edge.node, edge.weight)
        curr_tours.append(new_tour)

    if len(curr_tours) == 0:
      best_tour = get_minimum_tour(prev_tours)
      return best_tour

    prev_tours = curr_tours
    curr_tours = []

  best_tour = get_minimum_tour(prev_tours)

  return best_tour

"""
Given a tournaments graph, return the path with the shortest distance and
the maximum number of tournaments possible

Assumptions
===========

Node edges only contain child nodes which start after the current nodes finish date

num_tournaments > 0

home = {"lat": lat, "lon": lon}

Algorithm
=========

1. Calculate all tours of length 1 by making one for each of the nodes in the graph.nodes list

2. Calculate all tours of length 2 by looping through all tours of length 1 and for each tour
make a new one with each of the nodes child nodes.

3. Repeat step 2 until all the current list of tours is empty

4. Loop through all tours in the previous tours list to find the one with the least combined weight/distance
"""

def calculate_region_tour_min_distance_max_tournaments(graph, home = None):
  
  prev_tours = [] # tours of length n
  curr_tours = [] # tours of length n + 1
    
  # Add all the tournaments as potential start tournaments
  for node in graph.nodes:

    # If a starting point is defined, add the initial from the start as the inital weight
    if home is not None:
      initial_weight = haversine(home["lon"], home["lat"], node.lon, node.lat)
    else:
      initial_weight = 0

    tour = Tour(node, initial_weight)

    prev_tours.append(tour)
  
  # Find all potential multi-tournament tours
  while True:

    for tour in prev_tours:

      # Get the last node in the tour
      last_node = tour.nodes[-1]

      # Make a new tour with each of the child nodes
      for edge in last_node.edges:

        new_tour = tour.copy()
        new_tour.add_node(edge.node, edge.weight)
        curr_tours.append(new_tour)

    if len(curr_tours) == 0:
      break

    prev_tours = curr_tours
    curr_tours = []

  best_tour = get_minimum_tour(prev_tours)

  return best_tour

def calculate_return_home_tour_min_distance_num_tournaments(graph, num_tournaments, home = None):
  prev_tours = [] # tours of length n
  curr_tours = [] # tours of length n + 1

  # Add all the tournaments as potential start tournaments
  for node in graph.nodes:

    initial_weight = 0

    tour = Tour(node, initial_weight)

    prev_tours.append(tour)

  # Find all potential multi-tournament tours
  for i in range(num_tournaments - 1):

    for tour in prev_tours:

      # Get the last node in the tour
      last_node = tour.nodes[-1]

      # Make a new tour with each of the child nodes
      for edge in last_node.edges:

        new_tour = tour.copy()
        new_tour.add_node(edge.node, edge.weight)
        curr_tours.append(new_tour)

    if len(curr_tours) == 0:
      best_tour = get_minimum_tour(prev_tours)
      return best_tour

    prev_tours = curr_tours
    curr_tours = []

  best_tour = get_minimum_tour(prev_tours)

  return best_tour

def calculate_return_home_tour_min_distance_max_tournaments():
  pass

def calculate_point_to_point_tour_min_distance_num_tournaments():
  pass

def calculate_point_to_point_tour_min_distance_max_tournaments():
  pass