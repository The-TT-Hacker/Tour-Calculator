#include "tourCalculator.h"


double calcUtility( BestTour *start )
{
    ;
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
