#include<stdio.h>



int main(void)
{
	int length,breadth,area;

	struct MyPoint
{
		int x;
		int y;
};

struct Rectangle
{
   struct MyPoint point1;
   struct MyPoint point2;
};


    struct Rectangle rect={{7,1},{3,9}};
	
	length=rect.point2.y-rect.point1.y;
	if(length<0)
		length=length * -1;
		
	breadth=rect.point2.x - rect.point1.x;
	if(breadth<0)
		breadth=breadth * -1;
		
	area = length * breadth;
	
	printf("\n\n Length of Rectangle = %d \n",length);
	printf("\n\n Breadth of Rectangle = %d \n",breadth);		
	printf("\n\n Area of Rectangle = %d \n",area);
	
	return(0);
}
