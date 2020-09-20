
/* 

This algorithm assumes that the optimal tour of length n from
Tournament t is guaranteed to be 
bestTourOfLength(n, t->start) -> start, followed by
bestTourofLength( n-1, bestTourOfLength(n, t->start) -> start) -> start

TODO:
- implement maxUtility. It should take two BestTour object (pointers)
  as one can be an automatic variable created for the sake of comparison,
  with its pointer never recorded anywhere
  - implement a BestTour creating function

- Define and implement a function to read tournament data in from a text file,
  and generate the linked list in chronological order from this data, with 
  sane initialisations for pointers.

- Implement findBestTour()

- Break this file up, hiding functionality that is unimportant

*/



#include <stdio.h>
#include <time.h>


typedef struct Tournament {
    char name[50];
    unsigned long date; /* unix timestamp */
    unsigned int duration;
    struct Tournament *next; /* traverse linked list chronologically from the start */
    struct BestTour *best;
} Tournament;

typedef struct BestTour {
    int length;
    double utility;
    Tournament *this; /* allows us to print and pass tours around without needing their starting tournament */
    Tournament *next; 
    struct BestTour *longer; /* traverse linked list of BestTours from *this */
} BestTour;


/* get best tour of length length, starting anywhere from *start onwards */
BestTour *findBestTour( int length, Tournament *start );

/* find the next tournament chronologically that the player could play */
Tournament *nextValidTournament( Tournament *start );

/* determine whether a player could physically play *second after *first */
int validSuccessor( Tournament *first, Tournament *second );

/* traverse linked list of BestTours up to desired length */
BestTour *bestTourOfLength( int n, Tournament *tournament );

/* recursively print an optimal tour */
void printBestTour( BestTour *tour );


double maxUtility( BestTour *tourA, BestTour* tourB );


Tournament *nextValidTournament( Tournament *start )
{
    Tournament *current = start;
    while ( current != NULL ) {
        if ( validSuccessor( start, current ) ) {
            break;
        }
        current = current->next;
    }
    return current;
}

int validSuccessor( Tournament *first, Tournament *second )
{
    if ( first->date + first->duration < second->date ) {
        return 1;
    } else {
        return 0;
    }
}

BestTour *bestTourOfLength( int n, Tournament *tournament )
{
    BestTour *currentBest = tournament->best;
    while ( currentBest != NULL ) {
        if ( currentBest->length < n ) {
            currentBest = currentBest->longer;
        } else {
            break;
        }
    }
    return currentBest;
}

/* print the best tour possible starting at tour->this */
void printBestTour( BestTour *tour )
{
    if ( tour == NULL ) {
        return;
    }
    printf( "Tournament no. %d: %s\n", tour->length, tour->this->name );
    if ( tour->length > 2 ) {
        printBestTour( bestTourOfLength( tour->length - 1, tour->next ) );
    } else {
        printf( "Tournament no. %d: %s\n", 1, tour->next->name );
        return;
    }
}


int main()
{
    printf( "Current time is %lu\n", (unsigned long)time(NULL) );
}

    
