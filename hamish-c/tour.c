#include "tourCalculator.h"


/* create a new BestTour object */
BestTour *newTour( Tournament *this, BestTour *next )
{
    BestTour *b = malloc( sizeof( BestTour ) );

    if ( next == NULL ) { 
        b->length = 1;
        b->viaHome = 1;
        b->utility = calcUtility(b);
    } else {
        b->length = next->length + 1;
        returnHome(b); /* decides whether to return home, populates viaHome and utility */
    }

    b->this = this;
    b->next = next;
    b->longerImpossible = 0;
    b->longer = NULL;

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
void printBestTour( BestTour *tour )
{
    if ( tour == NULL ) {
        return;
    }

    printf( "Tournament no. %d: %s\n", tour->length, tour->this->name );

    if ( tour->length > 1 && tour->next != NULL ) {
        printBestTour( tour->next );
    } else {
        return;
    }
}


/* traverse linked list of BestTours starting at *tournament, up to desired length */
BestTour *getTourOfLength( Tournament *tournament, int length )
{
    BestTour *currentBest = tournament->best;

    while ( currentBest != NULL ) {
        if ( currentBest->length < length ) {
            currentBest = currentBest->longer;
        } else {
            return currentBest;
        }
    }

    return tournament;
}

/* return best tour of desired length, starting at *start, if one exists */
/* return NULL if impossible                                             */
BestTour *calcBestTourFromHere( Tournament *start, int length )
{
    BestTour *bestSoFar = getTourOfLength( start, length );
    if ( bestSoFar->length == length ) {
        return bestSoFar;
    }
    if ( bestSoFar->longerImpossible ) {
        return NULL;
    }

    if ( bestSoFar->length < length-1 ) {
        bestSoFar = calcBestTourFromHere( start, bestSoFar->length+1 );
    }

    BestTour *next = highestUtility( nextValidTournament(start), bestSoFar->length );
    if ( next != NULL ) {
        bestSoFar->longer = newTour( start, next );
        return bestSoFar->longer;
    } else {
        bestSoFar->longerImpossible = 1;
        return NULL;
    }
    
}

/* return pointer to the tour with the highest utility of desired length from start onwards */
BestTour *highestUtility( Tournament *start, int length )
{
    if ( start->next == NULL ) {
        if ( length == 1 ) {
            return start->best;
        } else {
            return NULL;
        }
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

/* recursive routine. Expects *start to be linked in chronologial order */
BestTour *findBestTour( Tournament *start, int length )
{
    ;
}

