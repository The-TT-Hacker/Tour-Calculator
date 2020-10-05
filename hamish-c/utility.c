#include "tourCalculator.h"


double calcUtility( BestTour *start )
{
    /* for now we just say utility = duration */
    if ( start == NULL ) {
        return 0.0;
    } else if ( start->utility == -1.0 ) {
        return (double) start->this->duration + calcUtility( start->next );
    } else {
        return start->utility;
    }
}

/* decide whether or not to return home after b->this */
/* populate b->viaHome and b->utility accordingly */
void returnHome( BestTour *b )
{
    double utilViaHome, utilDirect;

    b->viaHome = 1;
    utilViaHome = calcUtility(b);

    b->viaHome = 0;
    utilDirect = calcUtility(b);

    if ( utilViaHome > utilDirect ) {
        b->utility = utilViaHome;
        b->viaHome = 1;
    } else {
        b->utility = utilDirect;
        b->viaHome = 0;
    }

    return;
}
