#include "functions.h"

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

double haversine_distance(const double lat1, const double lon1, const double lat2, const double lon2) {

  double lat1r, lon1r, lat2r, lon2r, u, v;
  
  lat1r = deg2rad(lat1);
  lon1r = deg2rad(lon1);
  lat2r = deg2rad(lat2);
  lon2r = deg2rad(lon2);

  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

}

void print_tours_list(std::list<Tour*> *tours) {

  std::cout << "Tours List\n";

  std::list<Tour*>::iterator it;

  for (it = tours->begin(); it != tours->end(); ++it) {

    Tour *curr_tour = *it;

    print_tour(curr_tour);

  }

  std::cout << "\n";

}

void print_tour(Tour* tour) {

  std::cout << ""   << "Tour:"    << "\n";
  std::cout << "\t" << "Weight: " << tour->total_weight << "\n";
  std::cout << "\t" << "Path: "   << tour->path << "\n";
  std::cout << "\t" << "Nodes:"   << "\n";

  std::list<Node*>::iterator it;

  for (it = tour->nodes.begin(); it != tour->nodes.end(); ++it) {
    
    Node *node = *it;

    std::cout << "\t\t" << node->name << "\n";

  }

}