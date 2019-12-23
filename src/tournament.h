#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <string>

class Tournament;
class Home;

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

// Home

class Home {

  public:

		double lat;
		double lon;

		Home(double lat, double lon);

};

#endif