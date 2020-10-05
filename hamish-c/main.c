#include "tourCalculator.h"


Tournament *first;
BestTour *best;

int main( int argc, char *argv[] )
{
    int numTournaments = -1;
    int inputFileIndex = -1;
    for ( int i = 0 ; i < argc ; i++ ) {
        if ( strcmp(argv[i], "--input-file") == 0 ) {
            inputFileIndex = i+1;
            continue;
        }
        if ( strcmp(argv[i], "--num-tournaments") == 0 ) {
            numTournaments = atoi( argv[i+1] );
            continue;
        }
    }
    if ( numTournaments == -1 ) {
        fprintf( stderr, "error: --num-tournaments not given" );
        exit(1);
    }
    if ( inputFileIndex == -1 ) {
        fprintf( stderr, "error: --input-file not given" );
        exit(1);
    }

    first = getTournamentsFromCSV( argv[inputFileIndex] );
    best = highestUtility( first, numTournaments );
    if ( best == NULL ) {
        printf( "No tour possible with these parameters :(\n" );
    }
    printBestTour( best, 0 );
    destroyTournaments( first );
}
