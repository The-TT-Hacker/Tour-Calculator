#include "tourCalculator.h"

#define MAXLINE 1000


/* copy the nth comma separated field of line to field, add '\0' */
char *getField( char *field, char *line, int n )
{
    char *startField = line;
    char *endField;
    
    for ( int i = 0 ; i < n ; i++ ) {
        startField = strchr( startField, ',' );
        if ( startField == NULL ) {
            return NULL;
        }
        startField++;
    }
    while ( isspace(*startField) ) {
        startField++;  /* skip whitespace */
    }

    endField = startField;
    while ( isprint(*endField) && *endField != ',' ) {
        endField++;
    }

    if ( endField == startField ) { /*  */
        return NULL;
    }

    strncpy( field, startField, (endField-startField) );
    field[endField-startField] = '\0';
    return field;
}

/* copy tournament name (first CSV field) from line to name 
   return pointer to name, or NULL if no comma found        */
char *getName( char *name, char *line )
{
    getField( name, line, 0 );
    return name;
}

unsigned long getDate( char *line )
{
    char numstring[16];
    getField( numstring, line, 1 );
    return strtoul( numstring, NULL, 10 );
}

unsigned int getDuration( char *line )
{
    char numstring[16];
    getField( numstring, line, 2 );
    return (unsigned int) atoi( numstring );
}

Tournament *getTournamentsFromCSV( char *filename )
{
    FILE *datafile = fopen( filename, "r" );
    char line[MAXLINE];
    Tournament *start = NULL;
    Tournament *current = NULL;

    char name[NAMESIZE];
    unsigned long date;
    unsigned int duration;

    while ( fgets( line, MAXLINE, datafile ) != NULL ) {
        if ( getName( name, line ) == NULL ) {
            return NULL;
        }
        date = getDate( line );
        duration = getDuration( line );

        /* printf( "%s", line ); */
        /* printf( "Tournament name: %s\n", name ); */
        /* printf( "Tournament date: %u\n", date ); */
        /* printf( "Tournament duration: %u\n\n", duration ); */

        if ( start == NULL ) {
            start = createTournament( name, date, duration );
            current = start;
        } else {
            current->next = createTournament( name, date, duration );
            current = current->next;
        }
    }

    return start;
}
