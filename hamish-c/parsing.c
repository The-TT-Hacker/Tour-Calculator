#include "tourCalculator.h"

#define MAXLINE 1000

/* todo: get tours from CSV */

/* copy tournament name (first CSV field) from line to name */
/* return pointer to name, or NULL if no comma found        */
char *getName( char *name, char *line )
{
    memset( name, '\0', NAMESIZE );
    char *comma = strchr( line, ',' );
    if ( comma == NULL ) {
        return NULL;
    }
    strncpy( name, line, (comma-line) );
    return name;
}

unsigned long getDate( char *line )
{
    char *comma;
    char numstring[16];
    comma = strchr( line, ',' );
    if ( comma == NULL ) {
        return 0;
    }
    comma++;
    while ( isspace(*comma) ) {
        comma++;
    }
    strncpy( numstring, comma, ( strchr( comma, ',' ) - comma ) );
    return strtoul( numstring, NULL, 10 );
}

unsigned int getDuration( char *line )
{
    char *comma;
    for ( int i = 0 ; i < 2 ; i++ ) {
        comma = strchr( line, ',' );
        if ( comma == NULL ) {
            return 0;
        }
        comma++;
    }
}

Tournament *getTournamentsFromCSV( char *filename )
{
    FILE *datafile = fopen( filename, "r" );
    char line[MAXLINE];
    Tournament *start;

    char name[NAMESIZE];
    unsigned long date;
    unsigned int duration;

    while ( fgets( line, MAXLINE, datafile ) != NULL ) {
        printf( "%s", line );
        getName( name, line );
        printf( "Tournament name: %s\n", name );
        date = getDate( line );
        printf( "Tournament date: %u\n", date );
    }
}
