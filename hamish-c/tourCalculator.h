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

cost.c
- implement a cost function
- implement maxUtility. It should take two BestTour object (pointers)
  as one can be an automatic variable created for the sake of comparison,
  with its pointer never recorded anywhere

tour.c
- implement a BestTour generator
- implement a recursive BestTour destructor
- make the tournament struct more space efficient (use single bytes for flags)

tournament.c
- implement a Tournament generator 
- implement a recursive tournament destructor


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
    struct BestTour *next;    /* next step in this tour */
    short viaHome;            /* 1 if best to go home before *next */
    short longerImpossible;   /* 1 if it is not possible for a longer tour to exist */
    struct BestTour *longer;  /* traverse linked list of BestTours from *this */
} BestTour;



/* tournament.c */
void destroyTournaments( Tournament *start );
Tournament *nextValidTournament( Tournament *start );

/* tour.c */
BestTour *newTour( Tournament *this, BestTour *next );
BestTour *bestTourFromTounament( int length, Tournament *tournament );
BestTour *findBestTour( int length, Tournament *start );
void printBestTour( BestTour *tour );
void destroyTours( BestTour *tour );

/* utility.c */
double calcUtility( BestTour *start );
void returnHome( BestTour *b );
