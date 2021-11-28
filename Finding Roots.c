#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
EMRE TUNA PEKER
040200721 
*/


float absolute_value(float abs); // since we can't use math.h library, I created my own absolute value function.

int main()
{
// PART 1----------------------------------------------------------------------------------------------------------------------
	float a;   //the number that we need the root of.
	double sec1,sec2,sec3,sec4,sec5,sec6,sec7,sec8,sec9,sec10; // sections that we will use.
	double x; //the root.
	double value1,value2,value3,value4,value5,value6,value7,value8,value9,value10; //the y values of the function for the border values of each sections.
	double counter = 1; // in order to define the sections, it is required to have a counter variable to make them all equal and valid.
	double lower_border = 0; // borders of the interval.
	printf("Emre Tuna Peker\n040200721\n\n");
	while (1) // first, to avoid negative input from the user, we check if the number is positive or not.
	{	
		printf("Part 1:\n");
		printf("Enter a positive number:");
		scanf("%f",&a);
		
		if (a < 0)
		{
			printf("You entered a negative number.\n");
		}
		else
		{
			break;
		}
	}
	
	while (1) //we use an infinite loop to make the sections smaller and smaller.
	{
		counter = counter * 10;
		if (a == 0)
		{
			x = 0;
			break;
		}
		
		sec1 = lower_border + (1 * a / counter); // the sections
		sec2 = lower_border + (2 * a / counter);
		sec3 = lower_border + (3 * a / counter);
		sec4 = lower_border + (4 * a / counter);
		sec5 = lower_border + (5 * a / counter);
		sec6 = lower_border + (6 * a / counter);
		sec7 = lower_border + (7 * a / counter);
		sec8 = lower_border + (8 * a / counter);
		sec9 = lower_border + (9 * a / counter);
		sec10 = lower_border + (10 * a / counter);
		
		value1 = (sec1 * sec1) - a; // values of each sections border
		value2 = (sec2 * sec2) - a;
		value3 = (sec3 * sec3) - a;
		value4 = (sec4 * sec4) - a;
		value5 = (sec5 * sec5) - a;
		value6 = (sec6 * sec6) - a;
		value7 = (sec7 * sec7) - a;
		value8 = (sec8 * sec8) - a;
		value9 = (sec9 * sec9) - a;
		value10 = (sec10 * sec10) - a;
		
		if (absolute_value(value1) <= 0.0001) //if one of the value variable is less than 0.0001, then we have found the root or we got really close to it.
		{
			x = sec1;
			break;
		}
		if (absolute_value(value2) <= 0.0001) 
		{
			x = sec2;
			break;
		}
		if (absolute_value(value3) <= 0.0001) 
		{
			x = sec3;
			break;
		}
		if (absolute_value(value4) <= 0.0001) 
		{
			x = sec4;
			break;
		}
		if (absolute_value(value5) <= 0.0001)
		{
			x = sec5;
			break;
		}
		if (absolute_value(value6) <= 0.0001) 
		{
			x = sec6;
			break;
		}
		if (absolute_value(value7) <= 0.0001)
		{
			x = sec7;
			break;
		}
		if (absolute_value(value8) <= 0.0001)
		{
			x = sec8;
			break;
		}
		if (absolute_value(value9) <= 0.0001)
		{
			x = sec9;
			break;
		}
		if (absolute_value(value10) <= 0.0001)
		{
			x = sec10;
			break;
		}
		
		if (value1 < 0 && value2 > 0) //if the sign of the values change, then it must be the section that the function cuts.
		{
			lower_border = sec1;
		
		}
		if (value2 < 0 && value3 > 0)
		{
			lower_border = sec2;
			
		}
		if (value3 < 0 && value4 > 0)
		{
			lower_border = sec3;
			
		}
		if (value4 < 0 && value5 > 0)
		{
			lower_border = sec4;
		
		}
		if (value5 < 0 && value6 > 0)
		{
			lower_border = sec5;
			
		}
		if (value6 < 0 && value7 > 0)
		{
			lower_border = sec6;
			
		}
		if (value7 < 0 && value8 > 0)
		{
			lower_border = sec7;
			
		}
		if (value8 < 0 && value9 > 0)
		{
			lower_border = sec8;
			
		}
		if (value9 < 0 && value10 > 0)
		{
			lower_border = sec9;
		
		}
			
	
	}
	
	printf("The root of %.1f is %.4f.\n\n",a,x);
// PART 2------------------------------------------------------------------------------------------------------------------------	
	
	float xi,xip1;
	
	printf("Part 2\n");
	
	while (1) // first, to avoid negative input from the user, we check if the number is positive or not.
	{	
		printf("Enter a positive number:");
		scanf("%f",&a);
		
		if (a < 0)
		{
			printf("You entered a negative number.\n");
		}
		else
		{
			break;
		}
	}
	
	xi = a; // first estimate of root is xi equal to a.
	
	
	while (1) // using while loop to find the root.
	{
		xip1 = xi - (xi * xi - a)/(2 * xi); // defining the variables in Newton-Raphson formula.
	
		if (absolute_value(xip1 - xi) <= 0.0001)
		{
			x = xip1;
			break;
		}
		xi = xip1;
		
	}
	
	printf("The root of %.4f is %.4f\n\n",a,x);
// PART 3-------------------------------------------------------------------------------------------------------------------------
	
	clock_t t1,t2;
	int executionTime;
	
	printf("Part 3\n");
	
	a = 0;
	
	
	t1 = clock();
	while (a <= 100000)
	{
		lower_border = 0; //in order to make the algorithm work, these two variables need to be defined again.
		counter = 1;
		a++;
		
		while (1) //we use an infinite loop to make the sections smaller and smaller.
	{
		counter = counter * 10;
		if (a == 0)
		{
			x = 0;
			break;
		}
		
		sec1 = lower_border + (1 * a / counter); // the sections
		sec2 = lower_border + (2 * a / counter);
		sec3 = lower_border + (3 * a / counter);
		sec4 = lower_border + (4 * a / counter);
		sec5 = lower_border + (5 * a / counter);
		sec6 = lower_border + (6 * a / counter);
		sec7 = lower_border + (7 * a / counter);
		sec8 = lower_border + (8 * a / counter);
		sec9 = lower_border + (9 * a / counter);
		sec10 = lower_border + (10 * a / counter);
		
		value1 = (sec1 * sec1) - a; // values of each sections border
		value2 = (sec2 * sec2) - a;
		value3 = (sec3 * sec3) - a;
		value4 = (sec4 * sec4) - a;
		value5 = (sec5 * sec5) - a;
		value6 = (sec6 * sec6) - a;
		value7 = (sec7 * sec7) - a;
		value8 = (sec8 * sec8) - a;
		value9 = (sec9 * sec9) - a;
		value10 = (sec10 * sec10) - a;
		
		if (absolute_value(value1) <= 0.0001) //if one of the value variable is less than 0.0001, then we have found the root or we got really close to it.
		{
			x = sec1;
			break;
		}
		if (absolute_value(value2) <= 0.0001) 
		{
			x = sec2;
			break;
		}
		if (absolute_value(value3) <= 0.0001) 
		{
			x = sec3;
			break;
		}
		if (absolute_value(value4) <= 0.0001) 
		{
			x = sec4;
			break;
		}
		if (absolute_value(value5) <= 0.0001)
		{
			x = sec5;
			break;
		}
		if (absolute_value(value6) <= 0.0001) 
		{
			x = sec6;
			break;
		}
		if (absolute_value(value7) <= 0.0001)
		{
			x = sec7;
			break;
		}
		if (absolute_value(value8) <= 0.0001)
		{
			x = sec8;
			break;
		}
		if (absolute_value(value9) <= 0.0001)
		{
			x = sec9;
			break;
		}
		if (absolute_value(value10) <= 0.0001)
		{
			x = sec10;
			break;
		}
		
		if (value1 < 0 && value2 > 0) //if the sign of the values change, then it must be the section that the function cuts.
		{
			lower_border = sec1;
		
		}
		if (value2 < 0 && value3 > 0)
		{
			lower_border = sec2;
			
		}
		if (value3 < 0 && value4 > 0)
		{
			lower_border = sec3;
			
		}
		if (value4 < 0 && value5 > 0)
		{
			lower_border = sec4;
		
		}
		if (value5 < 0 && value6 > 0)
		{
			lower_border = sec5;
			
		}
		if (value6 < 0 && value7 > 0)
		{
			lower_border = sec6;
			
		}
		if (value7 < 0 && value8 > 0)
		{
			lower_border = sec7;
			
		}
		if (value8 < 0 && value9 > 0)
		{
			lower_border = sec8;
			
		}
		if (value9 < 0 && value10 > 0)
		{
			lower_border = sec9;
		
		}
			
	
	}
		
	}
	t2 = clock();
	executionTime = (int)(t2 - t1);
	
	printf("Execution time of Part 1: %d\n",executionTime);
	
	a = 0;
	t1 = clock();
	
	while (a <= 100000)
	{
		a++;
		/*part 2 process starts here */
		xi = a; 
	
	
	while (1) 
	{
		xip1 = xi - (xi * xi - a)/(2 * xi); 
	
		if (absolute_value(xip1 - xi) <= 0.0001)
		{
			x = xip1;
			break;
			
		}
		xi = xip1;
		
	}
				
	}
	t2 = clock();
	
	executionTime = (int)(t2 - t1);
	
	printf("Execution time of Part 2: %d\nSecond method works a lot faster.",executionTime);
	
	return 0;
}

float absolute_value(float abs)
{
	if (abs >= 0)
	{
		return abs;
	}
	else
	{
		return 0 - abs;
	}
}
