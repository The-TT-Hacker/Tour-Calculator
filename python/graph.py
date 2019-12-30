from functions import haversine
from copy      import deepcopy

"""
Assumptions
===========

Tournaments list is sorted chronologically on start_date

Graph Structure
===============

A node's edges contain all child_nodes where child_node.start_date > node.end_date
"""

class Graph:
	def __init__(self):
		self.nodes = []

	def add_node(self, tournament):
		edges = []

		node = Node(tournament["name"], tournament["start_date"], tournament["end_date"], tournament["lat"], tournament["lon"], edges)

		self.nodes.append(node)

	def find_node(self, tournament):
		for node in self.nodes:
			if node.name == tournament["name"] and node.start_date == tournament["start_date"]:
				return node

	def add_region_distance_edges(self, tournaments):
		for i, node in enumerate(self.nodes):
			j = i + 1

			for child_node in self.nodes[i + 1:]:

				if child_node.start_date > node.end_date:
				
					distance = haversine(tournaments[i]["lon"], tournaments[i]["lat"], tournaments[j]["lon"], tournaments[j]["lat"])

					node.add_edge(child_node, distance)

				j += 1

	def add_return_home_distance_edges(self, tournaments, home):
		for i, node in enumerate(self.nodes):
			j = i + 1

			for child_node in self.nodes[i + 1:]:

				if child_node.start_date > node.end_date:
				
					distance = haversine(home["lon"], home["lat"], tournaments[j]["lon"], tournaments[j]["lat"])

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
	def __init__(self, name, start_date, end_date, lat, lon, edges):
		self.name       = name
		self.start_date = start_date
		self.end_date   = end_date
		self.lat        = lat
		self.lon        = lon

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
  def __init__(self, node, initial_weight):
    self.nodes  = [node]
    self.weight = initial_weight
    self.string = "Home - " + str(initial_weight) + " - " + node.name

  def add_node(self, node, weight):
    self.nodes.append(node)
    self.weight += weight
    self.string += " - " + str(weight) + " - " + node.name 

  def copy(self):
  	return deepcopy(self)

  def __str__(self):
    string = "Tour:\n"
    string += "Weight: " + str(self.weight) + "\n"
    string += "Path: " + self.string + "\n"

    for node in self.nodes:
      string += "\t" + node.name + "\n"

    return string

# Helper Functions

# 

def initiate_tournaments_graph(graph, tournaments):

	graph = Graph()

	for tournament in tournaments:
		graph.add_node(tournament)

	return graph

# Build graph with edge weights = distance between the node and child node

def build_region_graph(tournaments):

	graph = add_nodes(graph, tournaments)

	graph.add_region_distance_edges(tournaments)

	return graph

# Build graph with edge weights = distance between the home and child node

def build_return_home_graph(tournaments):

	graph = add_nodes(graph, tournaments)

	graph.add_return_home_distance_edges(tournaments)

	return graph

def build_point_to_point_graph():
	pass

if __name__ == "__main__":
	pass