#include<stdio.h>
#include<string.h>

struct MyPoint
{
	int x;
	int y;
};

struct MyPointProperties
{
	int quadrant;
	char axis_location[10];
};

int main(void)
{
	struct MyPoint point;
	struct MyPointProperties pproperties;
	
	printf("\n\n Enter X-Coordinates for A point : ");
	scanf("%d",&point.x);
	printf("\n\n Enter Y-Coordinates for A point : ");
	scanf("%d",&point.y);
	
	printf("\n\n Point-Coordinates (x,y) Are : (%d , %d) \n", point.x,point.y);
	
	if(point.x==0 && point.y)
	{
		printf("\n\n The Point is the Origin (%d, %d) \n",point.x,point.y);
	}
	else
	{
		if(point.x==0)
		{ 
		    if(point.y<0)
		    {
		    	strcpy(pproperties.axis_location,"Negative Y");
			}
			if(point.y>0)
			{
				strcpy(pproperties.axis_location,"Positive Y");
			}
			pproperties.quadrant=0;
			printf("\n\n The Point lies on the %s Axis \n",pproperties.axis_location);
		}
		else if(point.y==0)
		{
  			if(point.x<0)
			{
		    	strcpy(pproperties.axis_location,"Negative X");
			}
			if(point.x>0)
			{
				strcpy(pproperties.axis_location,"Positive X");
			}
			pproperties.quadrant=0;	
				printf("\n\n The Point lies on the %s Axis \n",pproperties.axis_location);		
		}
		else
		{
			pproperties.axis_location[0]='\0';
			
			if(point.x>0 && point.y>0)
			{
				pproperties.quadrant=1;
			}
			else if(point.x < 0 && point.y > 0)
			{
				pproperties.quadrant=2;
			}
			else if(point.x<0 && point.y<0)
			{
				pproperties.quadrant=3;
			}
			else
			{
				pproperties.quadrant=4;
			}
			printf("\n\n The Point Lies in Quadrant Number %d !!!\n",pproperties.quadrant);
		}
	
	
	}

	return(0);

}

