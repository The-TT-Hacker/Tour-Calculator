#include "tourCalculator.h"


/* create a new BestTour object */
BestTour *newTour( Tournament *this, BestTour *next )
{
    BestTour *b = malloc( sizeof( BestTour ) );
    b->length = next->length + 1;
    b->utility = -1;
}

/* traverse linked list of BestTours starting at *tournament, up to desired length */
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

/* recursive routine. Expects *start to be linked in chronologial order */
BestTour *findBestTour( int length, Tournament *start )
{
    ;
}

/* return the tour with  */
BestTour *maxUtility( BestTour *tourA, BestTour *tourB )
{
    ;
}
