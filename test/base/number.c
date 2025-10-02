#include "../../code/impl/base/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    paxi8  sgn0 = pax_sgn_f32(-1.56);
    paxf32 mag0 = pax_mag_f32(-1.56);

    printf("sgn, mag = %i, %f\n", sgn0, mag0);

    paxi8  sgn1 = pax_sgn_f32(+1.56);
    paxf32 mag1 = pax_mag_f32(+1.56);

    printf("sgn, mag = %i, %f\n", sgn1, mag1);

    paxi8  sgn2 = pax_sgn_f32(0);
    paxf32 mag2 = pax_mag_f32(0);

    printf("sgn, mag = %i, %f\n", sgn2, mag2);
}
