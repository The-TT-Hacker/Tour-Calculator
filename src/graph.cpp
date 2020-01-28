#include "graph.h"

#include <iterator>
#include <iostream>

int    date_cmp(const char *d1, const char *d2);
double haversine_distance(const double lat1, const double lon1, const double lat2, const double lon2);

// Graph

Graph::~Graph() {

	std::cout << "Deleted Graph\n";

	nodes.clear();

}

void Graph::add_node(const Tournament *tournament) {

	Node node = Node(tournament);

	nodes.push_back(node);

}

void Graph::add_region_distance_edges() {

	int i = 0;

	std::list<Node>::iterator it;

	for (it = nodes.begin(); it != nodes.end(); ++it, ++i) {

		Node* currNode = &(*it);
    
    	std::list<Node>::iterator it2 = nodes.begin();
		
		for (advance(it2, i); it2 != nodes.end(); ++it2) {

			Node* childNode = &(*it2);

			const char *date1 = currNode->end_date.c_str();
			const char *date2 = childNode->start_date.c_str();

			if (date_cmp(date1, date2) < 0) {

				double distance = haversine_distance(currNode->lat, currNode->lon, childNode->lat, childNode->lon);

				currNode->add_edge(childNode, distance);

			}

		}

	}

}

void Graph::add_return_home_distance_edges(Home* home) {

  int i = 0;

  std::list<Node>::iterator it;

  for (it = nodes.begin(); it != nodes.end(); ++it, ++i) {

    Node currNode = *it;
    
    std::list<Node>::iterator it2 = nodes.begin();
    
    for (advance(it2, i); it2 != nodes.end(); ++it2) {

      Node childNode = *it2;

      const char *date1 = currNode.end_date.c_str();
      const char *date2 = childNode.start_date.c_str();

      if (date_cmp(date1, date2) < 0) {

        double distance = haversine_distance(home->lat, home->lon, childNode.lat, childNode.lon);

        currNode.add_edge(&childNode, distance);
      
      }
      
    }

  }

}

// Node

Node::Node(const Tournament *tournament)
: name(tournament->name), start_date(tournament->start_date), end_date(tournament->end_date), lat(tournament->lat), lon(tournament->lon) {}

Node::~Node() {

	std::cout << "Deleted Node\n";

	edges.clear();

}

void Node::add_edge(Node *node, double weight) {

	Edge edge = Edge(node, weight);

	edges.push_back(edge);

}

// Edge

Edge::Edge(Node *node, double weight) 
: node(node), weight(weight) {}