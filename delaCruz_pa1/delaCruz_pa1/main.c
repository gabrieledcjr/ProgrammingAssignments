/*
 * Programmer:	Gabriel V. de la Cruz Jr.
 * Class:		CptS 121, Fall 2012
 * Date:		25 Aug 2012
 *
 * Programming Assignment #1
 * Description: This program computes for the following:
 *				- Newton's Second Law of Motion
 *				- Volume of a cylinder
 *				- Character encoding
 *				- Distance between two points
 *				- Sine
 *				- Equivalent parallel resistance
 *				- General equation
 *
 * NOTE: This program does not do error checking. User can 
 *       have a faulty input or equations can divide zero. 
 */

#include <stdio.h>
#include <math.h>

#define PI		3.14159		// Defines PI as a constant variable
#define NUM		113		    // Numerator used in General Equation whose value is constant
#define DENOM	115			// Denominator used in the General Equation whose value is constant

int main (void) 
{											
	char plaintext_character = '\0', encoded_character = '\0';      // Variables for Character encoding
	int	R1 = 0, R2 = 0, R3 = 0;					                    // Variables for Equivalent parallel resistance
	int a = 0;									                    // Variable for General equation
	double mass = 0.0, acceleration = 0.0, force = 0.0;				// Variables for Newton's Second Law of Motion
	double radius = 0.0, height = 0.0, volume_cylinder = 0.0;		// Variables for Volume of a cylinder
	double x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0, distance = 0.0;	// Variables for Distance between two points
	double theta = 0.0, sin_theta = 0.0;							// Variables for Sine
	double parallel_resistance = 0.0;								// Variable for Equivalent parallel resistance
	double x = 0.0, y = 0.0, z = 0.0;								// Variables for General equation


	/******** Newton's Second Law of Motion ********/

	// Gets the value for mass and acceleration
	
	printf ("Please enter the mass and acceleration (both floating-point values): ");
	scanf ("%lf%lf", &mass, &acceleration);

	// Computes for the value of force 
	force = mass * acceleration;

	// Displays the equation used in finding the force and the result 
	printf ("force = mass * acceleration\n");
	printf ("      = %.3lf * %.3lf\n", mass, acceleration);
	printf ("      = %.3lf\n\n", force);


	/******** Volume of a cylinder ********/

	// Gets the value for radius and height 
	printf ("Volume of Cylinder:\n");
	printf ("Please enter the radius and height (both floating-point values): ");
	scanf ("%lf%lf", &radius, &height);

	// Computes for the volume of a cylinder 
	volume_cylinder = PI * (radius * radius) * height;
	
	// This equation also works
	// volume_cylinder = PI * pow (radius, 2) * height;

	// Displays the equation used in finding the volume of the cylinder and the result 
	printf ("volume_cylinder = PI * radius^2 * height\n");
	printf ("                = %.5f * %.3lf^2 * %.3lf\n", PI, radius, height);
	printf ("                = %.3lf\n\n", volume_cylinder);


	/******** Character encoding ********/

	// Gets the value for plaintext_character
	printf ("Character encoding:\n");
	printf ("Please enter any character: ");
	scanf ("\n%c", &plaintext_character);

	// Encodes character
	encoded_character = (plaintext_character + 2) - 'A' + 'a';

	// Displays the equation used in character encoding and the result
	printf ("encoded_character = (plaintext_character + 2) - 'A' + 'a'\n");
	printf ("                  = (%c + 2) - 'A' + 'a'\n", plaintext_character);
	printf ("                  = %c\n\n", encoded_character);


	/******** Distance between two points ********/

	// Gets the value for x1, y1 as Point 1
	printf ("Distance between two points:\n");
	printf ("Please enter value of x1 and y1 (both floating-point values): ");
	scanf ("%lf%lf", &x1, &y1);
	// Get the value for x2, y2 as Point 2
	printf ("Please enter value of x2 and y2 (both floating-point values): ");
	scanf ("%lf%lf", &x2, &y2);

	// Computes for the distance between (x1, y1) to (x2, y2) 
	distance = sqrt (pow ((x1 - x2), 2) + pow ((y1 - y2), 2));

	// This equation also works
	// distance = sqrt (((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));

	// Displays the equation used in finding the distance between two points
	printf ("distance = square root of ((x1 - x2)^2 + (y1 - y2)^2)\n");
	printf ("         = square root of ((%.3lf - %.3lf)^2 + (%.3lf - %.3lf)^2)\n", x1, x2, y1, y2);
	printf ("         = %.3lf\n\n", distance);


	/******** Computes for Sine ********/

	// Get the value for theta
	printf ("Sine of theta:\n");
	printf ("Please enter value of theta (floating-point value): ");
	scanf ("%lf", &theta);

	// Computes for the sine of theta
	sin_theta = tan (theta) * cos (theta);

	// Displays the equation used in finding sine of theta and result
	printf ("sine_theta = tan (theta) * cos (theta)\n");
	printf ("           = tan (%.3lf) * cos (%.3lf)\n", theta, theta);
	printf ("           = %.3lf\n\n", sin_theta);


	/******** Computes for Equivalent parallel resistance ********/

	// Get the value R1, R2 and R3
	printf ("Equivalent parallel resistance:\n");
	printf ("Please enter values of R1, R2 and R3 (all in integer value): ");
	scanf ("%d%d%d", &R1, &R2, &R3);

	// Computes for the equivalent parallel resistance of 3 resistors
	parallel_resistance = 1.0 / ((1.0 / R1) + (1.0 / R2) + (1.0 / R3));

	// Displays the equation used in finding the equivalent parallel resistance and result
	printf ("parallel_resistance = 1 / ((1 / R1) + (1 / R2) + (1 / R3))\n");
	printf ("                    = 1 / ((1 / %d) + (1 / %d) + (1 / %d))\n", R1, R2, R3);
	printf ("                    = %.3lf\n\n", parallel_resistance);


	/******** General equation ********/

	printf ("General equation (Finding unknown value of y):\n");
	
	// Get the value for x, z
	printf ("Please enter values of x and z (both floating-point values): ");
	scanf ("%lf%lf", &x, &z);

	// Get the value a
	printf ("Please enter value of a (integer value): ");
	scanf ("%d", &a);

	// Computes for the value of y
	// If a is even, y gets a value of undefined
	y = ((double) NUM / DENOM) / x * z / (a % 2) - PI + a;

	// Displays the equation used in finding the value for y and result
	printf ("y = (%d / %d) / x * z / (a %% 2) - PI + a\n", NUM, DENOM);
	printf ("  = (%d / %d) / %.3lf * %.3lf / (%d %% 2) - %.5f + %d\n", NUM, DENOM, x, z, a, PI, a);
	printf ("  = %.3lf\n", y);

	return 0;
}