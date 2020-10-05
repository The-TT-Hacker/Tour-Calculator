#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NAMESIZE 50

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

*/

typedef struct Tournament {
    char name[NAMESIZE];
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
Tournament *createTournament( char *name, unsigned long date, unsigned int duration );
void destroyTournaments( Tournament *start );
void printAllTournaments( Tournament *this, int index );
Tournament *nextValidTournament( Tournament *start );

/* tour.c */
BestTour *newTour( Tournament *this, BestTour *next );
BestTour *getTourOfLength( Tournament *tournament, int length );
void printBestTour( BestTour *tour, int index );
BestTour *highestUtility( Tournament *start, int length );
void destroyTours( BestTour *tour );

/* utility.c */
double calcUtility( BestTour *start );
void returnHome( BestTour *b );

/* parsing.c */
Tournament *getTournamentsFromCSV( char *filename );

