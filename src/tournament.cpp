#include "tournament.h"

// Tournament

Tournament::Tournament(std::string name, std::string start_date, std::string end_date, double lat, double lon)
: name(name), start_date(start_date), end_date(end_date), lat(lat), lon(lon) {

}

Home::Home(double lat, double lon)
: lat(lat), lon(lon) {
	
}