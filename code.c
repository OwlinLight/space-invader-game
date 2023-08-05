

/* code.c Copyright 2022 Neil Kirby, not for disclosure */


#include "code.h"

/* the bits database */
#define COLOR_SHIFT 4
#define TYPE_SHIFT 12
#define POINTS_SHIFT 20

/* avoid magic number */
#define COLOR_BITS 3
#define TYPE_BITS 3
#define POINTS_BITS 9


/* the debug prints are a three-part series */

static int bits(int shift, int many, unsigned int source)
{
    int temp, mask = 0;
	int rval;

	if(DEBUG)printf("isolating %d bits after shifting %d on %08X gives ",
		many, shift, source );

        temp = source >> shift;
		/* NSTD: need comment to explain */
        while (many > 0)
        {
            mask = (mask << 1) + 1;
            many--;
        }
        rval = (temp & mask);

	if(DEBUG)printf("%d\n", rval);

	return rval;
}


int color_from_code(unsigned int code)
{
	if(DEBUG)printf("color_from_code: ");
	return  bits(COLOR_SHIFT, COLOR_BITS, code);
}

int type_from_code(unsigned int code)
{
	if(DEBUG)printf("type_from_code: ");
	return  bits(TYPE_SHIFT, TYPE_BITS, code);
}

int points_from_code(unsigned int code)
{
	if(DEBUG)printf("points_from_code: ");
	return  bits(POINTS_SHIFT, POINTS_BITS, code);
}
