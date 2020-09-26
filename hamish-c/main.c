#include "tourCalculator.h"


Tournament *first;
BestTour *best;

int main()
{
    first = getTournamentsFromCSV( "fakeTournaments.csv" );
    best = highestUtility( first, 2 );
    if ( best == NULL ) {
        printf( "No tour possible with these parameters :(\n" );
    }
    printBestTour( best, 0 );
    destroyTournaments( first );
}
