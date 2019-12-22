#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <string>

// Tournament

class Tournament {

	public:

		std::string name;
		std::string start_date;
		std::string end_date;

		double lat;
		double lon;

		Tournament(std::string name, std::string start_date, std::string end_date, double lat, double lon);

};

#endif