const fs = require("fs");
var tournaments = JSON.parse(fs.readFileSync("test_tournaments.js", "utf8"));

for (var i = 0; i < tournaments.length; i++) {
    var line = `	Tournament tournament${i} = Tournament("${tournaments[i].tournamentName}", "${tournaments[i].startDate}", "${tournaments[i].endDate}", ${tournaments[i].latitude}, ${tournaments[i].longitude});`;
    var line2 = `	tournaments.push_back(tournament${i});`;
    console.log(line2);
}
