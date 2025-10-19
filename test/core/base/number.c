#include "../../code/impl/base/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    paxi8  sign0 = pax_sign_f32(-1.56);
    paxf32 magn0 = pax_magn_f32(-1.56);

    printf("sign, magn = %i, %f\n", sign0, magn0);

    paxi8  sign1 = pax_sign_f32(+1.56);
    paxf32 magn1 = pax_magn_f32(+1.56);

    printf("sign, magn = %i, %f\n", sign1, magn1);

    paxi8  sign2 = pax_sign_f32(0);
    paxf32 magn2 = pax_magn_f32(0);

    printf("sign, magn = %i, %f\n", sign2, magn2);
}
