Dependencies
============

Node.js
npm

Node.js Addon Version
=====================

Compile:

npm install
node-gyp rebuild

Run:

node test.js

Command Line Version
====================

Compile:

cd src
g++ main.cpp tourcalculator.cpp graph.cpp tournament.cpp -o calc

Run:

./calc

# Tour-Calculator
Algorithm to calcuate the ideal events someone should participate in

Algorithm Inputs
================

Graph Builder
 - Value for the Weight
   - Maximise Estimated Ranking Points
   - Maximise Estimated Prize Money
   - Minimise Travel    Time
   - Minimise Travel    Distance
   - Minimise Travel    Cost
   - Minimise Accom     Cost

Dynamic Program Parameters
 - Tournaments Graph
 - Number of tournaments / Max num

Final tour selection algorithm arguments
 - Number of tournaments in the tour
 - List of all possible tours of that length

TODO
====

make lists with objects not pointers