const tourcalculator = require('./build/Release/tourcalculator');

var tournaments = [
	{ "name": "Wimbledon",  lat: 51.433558,  lon: -0.215512,  start_date: "01/01/2020", end_date: "02/01/2020" },
	{ "name": "Sydney",     lat: -33.854980, lon: 151.072281, start_date: "02/01/2020", end_date: "03/01/2020" },
	{ "name": "Newcastle",  lat: -32.923188, lon: 151.729923, start_date: "04/01/2020", end_date: "05/01/2020" },
	{ "name": "Wollongong", lat: -34.418964, lon: 150.886659, start_date: "06/01/2020", end_date: "07/01/2020" },
	{ "name": "Bathurst",   lat: -33.407295, lon: 149.576608, start_date: "08/01/2020", end_date: "09/01/2020" }
];

tourcalculator.calc(tournaments, function (tour) {
  console.log(tour);
});