#include "tourCalculator.h"


/* functions that handle tournaments */


void printAllTournaments( Tournament *this, int index )
{
    if ( this == NULL ) {
        return;
    }
    printf( "Tournament no. %d: (%s) has start date: %d and duration %d \n",
            index, this->name, this->date, this->duration );
    printAllTournaments( this->next, (index+1) );
    return;
}

/* determine whether a player could physically play *second after *first */
int validSuccessor( Tournament *first, Tournament *second )
{
    if ( first->date + first->duration < second->date ) {
        return 1;
    } else {
        return 0;
    }
}


/* find the next tournament chronologically that the player could play */
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

/* return a pointer to a new tournament object */
Tournament *createTournament( char *name, unsigned long date, unsigned int duration )
{
    Tournament *t = malloc( sizeof( Tournament ) );
    strcpy( t->name, name );
    t->date = date;
    t->duration = duration;
    t->next = NULL;
    t->best = newTour( t, NULL );
    return t;
}

/* detroy all tournaments after *start */
void destroyTournaments( Tournament *start )
{
    if ( start->next != NULL ) {
        destroyTournaments( start->next );
    }
    destroyTours( start->best );
    free( start );
    return;
}
                              
