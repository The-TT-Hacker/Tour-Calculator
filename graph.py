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

class Graph:
	def __init__(self):
		self.nodes = []

	def add_node(self, tournament):
		edges = []

		node = Node(tournament["name"], tournament["start_date"], tournament["end_date"], edges)

		self.nodes.append(node)

	def find_node(self, tournament):
		for node in self.nodes:
			if node.name == tournament["name"] and node.start_date == tournament["start_date"]:
				return node

	def add_distance_edges(self, tournaments):
		for i, node in enumerate(self.nodes):
			j = i + 1

			for child_node in self.nodes[i + 1:]:

				if child_node.start_date > node.end_date:
				
					distance = haversine(tournaments[i]["lon"], tournaments[i]["lat"], tournaments[j]["lon"], tournaments[j]["lat"])

					node.add_edge(child_node, distance)

				j += 1

	def __str__(self):
		string = "Graph:\n"

		for node in self.nodes:
			string += "\t" + node.name + "\n"

			for edge in node.edges:
				string += "\t\t" + edge.node.name + "\n"

			string += "\n"

		return string

class Node:
	def __init__(self, name, start_date, end_date, edges):
		self.name       = name
		self.start_date = start_date
		self.end_date   = end_date

		# Only nodes with events that occur after
		self.edges = edges

	def add_edge(self, node, weight):
		edge = Edge(node, weight)

		self.edges.append(edge)

class Edge:
	def __init__(self, node, weight):
		self.node   = node
		self.weight = weight

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
            string += "\t" + node.name + "\n"

    return string

"""
Assumes tournaments are in chronological order
"""

def build_graph(tournaments):

	graph = Graph()

	for tournament in tournaments:
		graph.add_node(tournament)

	graph.add_distance_edges(tournaments)

	return graph

if __name__ == "__main__":
	pass