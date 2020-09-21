#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* 

This algorithm assumes that the optimal tour of length n from
Tournament *t is guaranteed to be 
*t,                                                   followed by
nextStep = bestTourOfLength( n, t ) -> next,          followed by
nextStep = bestTourofLength( n-1, nextStep ) -> next, and so on 

TODO:
- implement maxUtility. It should take two BestTour object (pointers)
  as one can be an automatic variable created for the sake of comparison,
  with its pointer never recorded anywhere

- implement a BestTour generator

- implement a Tournament generator 

- Define and implement a function to read tournament data in from a text file,
  and generate the linked list in chronological order from this data, with 
  sane initialisations for pointers.

- Implement findBestTour()

*/

typedef struct Tournament {
    char name[50];
    unsigned long date;      /* unix timestamp */
    unsigned int duration;
    struct Tournament *next; /* traverse linked list chronologically from the start */
    struct BestTour *best;   
} Tournament;

typedef struct BestTour {
    int length;               /* number of tournaments */
    double utility;
    struct Tournament *this; 
    struct Tournament *next; 
    struct BestTour *longer;  /* traverse linked list of BestTours from *this */
} BestTour;


/* get best tour of length length, starting anywhere from *start onwards */
BestTour *findBestTour( int length, Tournament *start );

/* find the next tournament chronologically that the player could play */
Tournament *nextValidTournament( Tournament *start );

/* traverse linked list of BestTours up to desired length */
BestTour *bestTourOfLength( int n, Tournament *tournament );

/* recursively print an optimal tour */
void printBestTour( BestTour *tour );


BestTour *maxUtility( BestTour *tourA, BestTour* tourB );
