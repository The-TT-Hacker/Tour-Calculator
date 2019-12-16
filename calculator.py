import copy

"""
Given a tournaments graph and number of tournaments,
return the path with the shortest distance and
the number of tournaments specified
"""

class Tour:
        def __init__(self, node, weight):
                self.nodes = [node]
                self.weight = weight

        def add_node(self, node, weight):
                self.nodes.append(node)
                self.weight += weight

                return self

        def __str__(self):
                string = "Tour:\n"

                for node in self.nodes:
                        string += node.name + "\n"

                return string


def calculate_region_tour_num_tournaments(graph, num_tournaments):
        #TODO STAGE 1

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
                                tours_list[i+1].append(tour.add_node(edge.node, edge.weight))
                

                
        # Get best tour
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

        print (tours_list[num_tournaments - 1])

        for tour in tours_list[num_tournaments - 1]:
                if tour.weight < lowest_weight:
                        best_tour = tour

        return best_tour