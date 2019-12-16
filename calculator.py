from graph import Tour

"""
Given a tournaments graph and number of tournaments,
return the path with the shortest distance and
the number of tournaments specified
"""

def calculate_region_tour_num_tournaments(graph, num_tournaments):
  tours_list = []

  # Initialise nested lists
  for i in range(num_tournaments):
    tours_list.append([])
    
  # Add all the tournaments as potential start tournaments
  for node in graph.nodes:
    tours_list[0].append(Tour(node,0))
  
  # Find all potential multi-tournament tours
  for i in range(num_tournaments - 1):
    for tour in tours_list[i]:
      for edge in tour.nodes[i].edges:
        new_tour = tour.copy()
        new_tour.add_node(edge.node, edge.weight)

        tours_list[i+1].append(new_tour)
  
  # Get the best tour out of all possible solutions
  tour = select_tour_least_distance(tours_list, num_tournaments)
  
  return tour

def calculate_region_tour_max_tournaments(graph):
  pass

def calculate_from_home_tour_num_tournaments():
  pass

def calculate_from_home_tour_max_tournaments():
  pass

"""
Given a list of all possible tours,
return the one with shortest travel distance
"""

def select_tour_least_distance(tours_list, num_tournaments):
  # If there are no suitable tours generated with the desired number of
  # tournaments, find the tour with the greatest number of tournaments
  while num_tournaments > 0:
    if tours_list[num_tournaments-1] == []:
      num_tournaments -= 1
    else:
      break
  
  if num_tournaments == 0:
    print('No tours possible')
    return []

  # Find the tour with the lowest collective weight
  best_tour = None
  lowest_weight = float("inf")

  for tour in tours_list[num_tournaments - 1]:
    if tour.weight < lowest_weight:
      best_tour = tour
      lowest_weight = tour.weight

  return best_tour