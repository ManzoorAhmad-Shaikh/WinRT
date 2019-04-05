#include<stdio.h>

int main(void)
{
	
struct Rectangle
{
	struct MyPoint
	{
		int x;
		int y;
	}point1,point2;
	
}rect={{2,5},{4,9}};

	
	int length,breadth,area;
	
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
