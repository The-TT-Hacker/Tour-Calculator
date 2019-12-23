from math import radians, cos, sin, asin, sqrt

def haversine(lon1, lat1, lon2, lat2):
    """
    Calculate the great circle distance between two points 
    on the earth (specified in decimal degrees)
    """
    # convert decimal degrees to radians 
    lon1, lat1, lon2, lat2 = map(radians, [lon1, lat1, lon2, lat2])

    # haversine formula 
    dlon = lon2 - lon1
    dlat = lat2 - lat1

    a = sin(dlat / 2) ** 2 + cos(lat1) * cos(lat2) * sin(dlon / 2) ** 2
    c = 2 * asin(sqrt(a)) 
    r = 6371 # Radius of earth in kilometers

    return c * r

# Given a list of all possible tours, return the one with shortest travel distance
def get_minimum_tour(prev_tours):

  # Find the tour with the lowest collective weight
  best_tour     = None
  lowest_weight = float("inf")

  for tour in prev_tours:
    if tour.weight < lowest_weight:
      best_tour     = tour
      lowest_weight = tour.weight

  return best_tour