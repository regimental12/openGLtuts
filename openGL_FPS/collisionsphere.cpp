#include "collisionsphere.h"

collisionsphere::collisionsphere()
{
    r = 0;
}

collisionsphere::collisionsphere(const vector3d& vec , float rad)
{
    centre.change(vec);
    r = rad;
}