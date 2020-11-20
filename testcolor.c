#include <stdio.h>
#include <stdlib.h>


int		create_trgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

int main ()
{
    int s = 0xCB8F8F;
   // printf("color: %d\n",create_trgb(203,143,143));



}