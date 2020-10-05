#include "tourCalculator.h"

/* create a new BestTour object */
BestTour *newTour( Tournament *this, BestTour *next )
{
    BestTour *b = malloc( sizeof( BestTour ) );

    b->this = this;
    b->next = next;
    b->longerImpossible = 0;
    b->longer = NULL;
    b->utility = -1.0;

    if ( next == NULL ) { 
        b->length = 1;
        b->viaHome = 1;
        b->utility = calcUtility(b);
    } else {
        b->length = next->length + 1;
        returnHome(b); /* decides whether to return home, populates viaHome and utility */
    }

    return b;
}

/* destroy all tours starting from tour->start */
void destroyTours( BestTour *tour )
{
    if ( tour->longer != NULL ) {
        destroyTours( tour->longer );
    }
    free( tour );
    return;
}

/* print the best tour possible starting at tour->this */
void printBestTour( BestTour *tour, int index )
{
    if ( tour == NULL ) {
        return;
    }

    printf( "Tournament no. %d: %s, starting at %d, ending at %d\n",
            index, tour->this->name, tour->this->date,
            (tour->this->date + tour->this->duration) );

    if ( tour->length > 1 && tour->next != NULL ) {
        printBestTour( tour->next, (index+1) );
    } else {
        return;
    }
}


/* traverse linked list of BestTours starting at *tournament, up to desired length 
   return longest tour if it is shorter than length                                */
BestTour *getTourOfLength( Tournament *tournament, int length )
{
    BestTour *currentBest = tournament->best;

    while ( currentBest != NULL ) {
        if ( currentBest->length == length ) {
            return currentBest;
        } else {
            if ( currentBest->longer == NULL ) {
                return currentBest;
            } else {
                currentBest = currentBest->longer;
            }
        }
    }
}

/* return best tour of desired length, starting at *start, if one exists */
/* return NULL if impossible                                             */
BestTour *calcBestTourFromHere( Tournament *start, int length )
{
    static int recursionCount;
    /* printf( "number of calls to calcBestTourFromHere: %d\n", recursionCount++ ); */
    
    BestTour *bestSoFar = getTourOfLength( start, length );
    if ( bestSoFar->length == length ) {
        return bestSoFar;
    } 
    if ( bestSoFar->longerImpossible ) {
        return NULL;
    }

    if ( bestSoFar->length < length-1 ) {
        bestSoFar = calcBestTourFromHere( start, length-1 );
        if ( bestSoFar == NULL ) {
            return NULL;
        }
    }

    static int nonTrivialCount;
    /* printf( "number of non-trivial calls to calcBestTourFromHere: %d\n", nonTrivialCount++ ); */

    BestTour *next = highestUtility( nextValidTournament(start), bestSoFar->length );
    if ( next != NULL ) {
        bestSoFar->longer = newTour( start, next );
        return bestSoFar->longer;
    } else {
        bestSoFar->longerImpossible = 1;
        return NULL;
    }
}

/*  return pointer to the tour with the highest utility of desired length from 
    start onwards                                                               */
BestTour *highestUtility( Tournament *start, int length )
{
    if ( start == NULL ) {  /* base case */
        return NULL;
    }

    BestTour *nextBest = highestUtility( start->next, length );
    BestTour *fromHere = calcBestTourFromHere( start, length );

    if ( fromHere == NULL ) { /* there is no solution possible from here onwards */
        return NULL;
    } else if ( nextBest == NULL ) {
        return fromHere;
    }

    if ( nextBest->utility > fromHere->utility ) {
        return nextBest;
    } else {
        return fromHere;
    }
}
