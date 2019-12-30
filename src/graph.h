#ifndef GRAPH_H
#define GRAPH_H

#include "tournament.h"

#include <list>
#include <string>

class Graph;
class Node;
class Edge;

// Graph

class Graph {

	public:
		std::list<Node*> nodes;

		~Graph();

		void add_node(Tournament *tournament);
		void add_region_distance_edges(std::list<Tournament*> tournaments);
		void add_return_home_distance_edges(std::list<Tournament*> tournaments, Home* home);

};

// Node

class Node {

	public:
		std::string name;
		std::string start_date;
		std::string end_date;

		double  lat;
		double  lon;

		std::list<Edge*> edges;

	  Node(Tournament *tournament);
	  ~Node();
  
  	void add_edge(Node *node, double weight);
};

// Edge

class Edge {

	public:

	  Node *node;
	  float weight;

	  Edge(Node *node, double weight);
	  ~Edge();
};

#endif