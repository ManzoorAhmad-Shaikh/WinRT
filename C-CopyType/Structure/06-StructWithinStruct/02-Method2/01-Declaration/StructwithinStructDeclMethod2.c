#include<stdio.h>

struct MyPoint
{
		int x;
		int y;
};

struct Rectangle
{
   struct MyPoint point1,point2;
};


int main(void)
{
	int length,breadth,area;

    struct Rectangle rect;
		
	printf("\n\n Enter Leftmost X-coordinate of Rectangle : ");
	scanf("%d",&rect.point1.x);
	
	printf("\n\n Enter Bottommost Y-coordinate of Rectangle : ");
	scanf("%d",&rect.point1.y);
	
	printf("\n\n Enter Rightmost X-coordinate of Rectangle : ");
	scanf("%d",&rect.point2.x);
	
	printf("\n\n Enter Topmost Y-coordinate of Rectangle : ");
	scanf("%d",&rect.point2.y);
	
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
