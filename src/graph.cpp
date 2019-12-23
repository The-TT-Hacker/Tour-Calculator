#include "graph.h"

#include <iterator>
#include <math.h>
#include <cmath>
#include <cstring>

int    date_cmp(const char *d1, const char *d2);
double haversine_distance(Node *node1, Node *node2);

// Graph

void Graph::add_node(Tournament *tournament) {

	Node *node = new Node(tournament);

	nodes.push_back(node);

}

void Graph::add_region_distance_edges(std::list<Tournament*> tournaments) {

	int i = 0;

	std::list<Node*>::iterator it;

	for (it = nodes.begin(); it != nodes.end(); ++it, ++i) {

		Node *currNode = *it;
    
    std::list<Node*>::iterator it2 = nodes.begin();
		
		for (advance(it2, i); it2 != nodes.end(); ++it2) {

			Node *childNode = *it2;

			const char *date1 = currNode->end_date.c_str();
			const char *date2 = childNode->start_date.c_str();

			if (date_cmp(date1, date2) < 0) {

				double distance = haversine_distance(currNode, childNode);

				currNode->add_edge(childNode, distance);
			}
		}
	}
}

// Node

Node::Node(Tournament *tournament)
: name(tournament->name), start_date(tournament->start_date), end_date(tournament->end_date), lat(tournament->lat), lon(tournament->lon) {}

void Node::add_edge(Node *node, double weight) {

	Edge *edge = new Edge(node, weight);

	edges.push_back(edge);

}

// Edge

Edge::Edge(Node *node, double weight) 
: node(node), weight(weight) {}


// Helper Functions

int date_cmp(const char *d1, const char *d2) {

  int rc;
  
  // compare years
  rc = strncmp(d1 + 6, d2 + 6, 4);

  if (rc != 0)
    return rc;

  // compare months
  rc = strncmp(d1 + 3, d2 + 3, 2);
  
  if (rc != 0)
    return rc;

  // compare days
  return strncmp(d1, d2, 2);

}

#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {

  return (deg * M_PI / 180);

}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {

  return (rad * 180 / M_PI);

}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */

double haversine_distance(Node *node1, Node *node2) {

  double lat1r, lon1r, lat2r, lon2r, u, v;
  
  lat1r = deg2rad(node1->lat);
  lon1r = deg2rad(node1->lon);
  lat2r = deg2rad(node2->lat);
  lon2r = deg2rad(node2->lon);

  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

}