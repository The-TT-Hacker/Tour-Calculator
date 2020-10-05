const tourcalculator = require('./build/Release/tourcalculator');
const fs = require("fs");

var tournaments = JSON.parse(fs.readFileSync("test_tournaments.js", "utf8"));

console.log(tournaments.length);

var home = {
	lat: -33.868839,
	lon: 151.208936
}

/*
var tournaments = [
	{ "name": "Wimbledon",  lat: 51.433558,  lon: -0.215512,  start_date: "01/01/2020", end_date: "02/01/2020" },
	{ "name": "Sydney",     lat: -33.854980, lon: 151.072281, start_date: "02/01/2020", end_date: "03/01/2020" },
	{ "name": "Newcastle",  lat: -32.923188, lon: 151.729923, start_date: "04/01/2020", end_date: "05/01/2020" },
	{ "name": "Wollongong", lat: -34.418964, lon: 150.886659, start_date: "06/01/2020", end_date: "07/01/2020" },
	{ "name": "Bathurst",   lat: -33.407295, lon: 149.576608, start_date: "08/01/2020", end_date: "09/01/2020" }
];
*/

var num_tournaments = 3;

console.log("1");

/*
tourcalculator.calculate_region_tour_min_distance_num_tournaments(tournaments, num_tournaments, function (tour) {
	console.log("calculate_region_tour_min_distance_num_tournaments");
  console.log(tour);
});

tourcalculator.calculate_region_tour_min_distance_max_tournaments(tournaments, function(tour) {
	console.log("test_calculate_region_tour_min_distance_max_tournaments");
	console.log(tour);
});

var tour = tourcalculator.calculate_region_tour_min_distance_max_tournaments_from_home(tournaments, home, function (tour) {
	console.log("calculate_region_tour_min_distance_max_tournaments_from_home");
	console.log(tour);
});

console.log(tour);
*/

var i = 0;

tourcalculator.calculate_region_tour_min_distance_num_tournaments_from_home(tournaments, num_tournaments, home, function (tour) {
	console.log("calculate_region_tour_min_distance_num_tournaments_from_home");
	console.log(tour);

	console.log(i);
});

i = 1

console.log("2");