#include "tourCalculator.h"




int main()
{
    Tournament *testTournament = malloc( sizeof( Tournament ) );
    strcpy( testTournament->name, "Very Cool Tournament" );
    printf( "This tournament's name is %s\n", testTournament->name );
    free( testTournament );
    
    printf( "Current time is %lu\n", (unsigned long)time(NULL) );
}
