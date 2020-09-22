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

/* traverse linked list of BestTours starting at *tournament, up to desired length */
BestTour *bestTourFromTournament( int length, Tournament *tournament )
{
    BestTour *currentBest = tournament->best;

    while ( currentBest != NULL ) {
        if ( currentBest->length < length ) {
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

    if ( tour->length > 1 && tour->next != NULL ) {
        printBestTour( tour->next );
    } else {
        return;
    }
}

/* recursive routine. Expects *start to be linked in chronologial order */
BestTour *findBestTour( int length, Tournament *start )
{
    ;
}

void destroyTours( BestTour *tour )
{
    if ( tour->longer != NULL ) {
        destroyTours( tour->longer );
    }
    free( tour );
    return;
}
