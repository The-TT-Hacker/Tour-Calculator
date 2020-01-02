#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "tourcalculator.h"

#include <cstring>
#include <math.h>
#include <iostream>
#include <list>

#define earthRadiusKm 6371.0

int    date_cmp(const char *d1, const char *d2);
double deg2rad(double deg);
double rad2deg(double rad);
double haversine_distance(const double lat1, const double lon1, const double lat2, const double lon2);
void   print_tours_list(std::list<Tour> *tours);
void   print_tour(Tour* tour);

#endif