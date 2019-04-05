#include<stdio.h>

struct MyPoint
{
	int x;
	int y;
};
struct MyPoint point_A,point_B,point_C,point_D,point_E;

int main(void)
{
	point_A.x=3;
	point_A.y=0;
	
	point_B.x=1;
	point_B.y=2;
	
	point_C.x=9;
	point_C.y=6;
	
	point_D.x=8;
	point_D.y=2;
	
	point_E.x=11;
	point_E.y=8;
	
	printf("\n\n Co-ordinate (x,y) of point 'A' Are : (%d,%d)\n",point_A.x,point_A.y);
	printf("\n\n Co-ordinate (x,y) of point 'B' Are : (%d,%d)\n",point_B.x,point_B.y);
	printf("\n\n Co-ordinate (x,y) of point 'C' Are : (%d,%d)\n",point_C.x,point_C.y);
	printf("\n\n Co-ordinate (x,y) of point 'D' Are : (%d,%d)\n",point_D.x,point_D.y);
	printf("\n\n Co-ordinate (x,y) of point 'E' Are : (%d,%d)\n",point_E.x,point_E.y);			

return(0);

}
