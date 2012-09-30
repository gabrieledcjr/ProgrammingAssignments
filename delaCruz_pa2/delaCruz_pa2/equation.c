/*************************************************************************
 * Filename: equation.c                                                  *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012  ; Lab Section 7                           *
 * Programming Assignment 2: A Modular Approach to the Equation          *
 *                           Evaluator                                   *
 * Date: September 8, 2012                                               *
 *                                                                       *
 * Description: This file shows function definitions needed to perform   *
 *              the different equations listed below. There are detailed *
 *              description on how each function works documented above  *
 *              the function headers.                                    *
 *              (NOTE: This program DOES NOT DO ERROR CHECKING. User can * 
 *               have a faulty input or equations can divide zero.)      * 
 *                                                                       *
 * Relevant Formulas:													 *
 *   1) Newton's Second Law of Motion:                                   *
 *      f = m * a, where f is force,                                     *
 *                       m is mass,                                      *
 *                       a is acceleration                               *
 *                       t is time interval                              *
 *   2) Volume of a cylinder:											 *
 *      v = PI * r^2 * h, where v is volume of cylinder                  *
 *                              PI is the constant pi                    *
 *                              r is radius		   			             *
 *                              h is height                              *
 *   3) Character encoding:												 *
 *      e = (p + 2) - 'A' + 'a', where e is encoded character            *
 *									   p is plaintext character          *
 *   4) Distance between two points:                                     *
 *      d = sqrt((x1 - x2)^2 + (y1 - y2)^2)                              *
 *                             , where d is distance                     *
 *                                     x1 is x-coordinate of point 1     *
 *                                     y1 is y-coordinate of point 1     *
 *                                     x2 is x-ccordinate of point 2     *
 *                                     y2 is y-coordinate of point 2     *
 *   5) Sine:															 *
 *      sin t = tan (t) * cos (t), where t is degrees in radian          *
 *   6) Equivalent parallel resistance:                                  *
 *      p = 1 / (1 / R1 + 1 / R2 + 1 / R3),                              *
 *                             , where p is parallel resistance          *
 *                                     R1 is resistor 1                  *
 *                                     R2 is resistor 2                  *
 *                                     R3 is resistor 3                  *
 *   7) General equation:												 *
 *      y = (113 / 115) / x * z / (a % 2) - PI + a                       *
 *                             , where y is unknown variable y           *
 *                                     x,z,a are user-defined variables  *
 *                                     PI is the constant pi             *
 *************************************************************************/

#include "equation.h"


/*************************************************************
 * Function: getMass ()                                      *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              value of mass.                               *
 * Input parameters: None                                    *
 * Returns: The value of mass in type double                 *
 * Preconditions: Requires a user to input value for mass    *
 * Postconditions: The value of mass is returned.            *
 *************************************************************/
double getMass (void)
{
	double mass = 0.0;

	printf ("Enter value of mass [floating-point value] > ");
	scanf ("%lf", &mass);

	return mass;
}

/*************************************************************
 * Function: getAcceleration ()                              *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              value of acceleration.                       *
 * Input parameters: None                                    *
 * Returns: The value of acceleration in type double         *
 * Preconditions: Requires a user to input value for         *
 *                acceleration.                              *
 * Postconditions: The value of acceleration is returned.    *
 *************************************************************/
double getAcceleration (void)
{
	double acceleration = 0.0;

	printf ("Enter value of acceleration [floating-point value] > ");
	scanf ("%lf", &acceleration);

	return acceleration;
}


/*************************************************************
 * Function: computeNewtons2ndLaw  ()                        *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function computes for the value of      *
 *              using Newton's Second Law of Motion.         *
 * Input parameters: mass and acceleration                   *
 * Returns: The value of force                               *
 * Preconditions: The mass and acceleration has values       *
 *                inputted by user, and values are valid     *
 *                inputs.                                    *
 * Postconditions: The value of force is returned            *
 *************************************************************/
double computeNewtons2ndLaw (double mass, double acceleration)
{
	return mass * acceleration;
}

/*************************************************************
 * Function: getRadius ()                                    *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              value of radius.                             *
 * Input parameters: None                                    *
 * Returns: The value of radius in type double               *
 * Preconditions: Requires a user to input value for radius  *
 * Postconditions: The value of radius is returned.          *
 *************************************************************/
double getRadius (void)
{
	double radius = 0.0;

	printf ("Enter value of radius [floating-point value] > ");
	scanf ("%lf", &radius);

	return radius;
}

/*************************************************************
 * Function: getHeight ()                                    *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              value of height.                             *
 * Input parameters: None                                    *
 * Returns: The value of height in type double               *
 * Preconditions: Requires a user to input value for height  *
 * Postconditions: The value of height is returned.          *
 *************************************************************/
double getHeight (void)
{
	double height = 0.0;

	printf ("Enter value of height [floating-point value] > ");
	scanf ("%lf", &height);
	
	return height;
}

/*************************************************************
 * Function: computeVolumeOfCylinder ()                      *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function computes for the volume of     *
 *              cylinder.                                    *
 * Input parameters: radius and height                       *
 * Returns: The volume of cylinder                           *
 * Preconditions: The radius and height has valid values     *
 *                inputted by user. Also, a constant value   *
 *                for PI has been defined.                   *
 * Postconditions: The volume of cylinder is returned        *
 *************************************************************/
double computeVolumeOfCylinder(double radius, double height)
{
	return PI * radius * radius * height;
}

/*************************************************************
 * Function: getPlaintextCharacter ()                        *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              character.                                   *
 * Input parameters: None                                    *
 * Returns: The character                                    *
 * Preconditions: Requires a user to input a character       *
 * Postconditions: The character is returned.                *
 *************************************************************/
char getPlaintextCharacter (void)
{
	char plaintextCharacter = '\0';

	printf ("Enter a character > ");
	scanf (" %c", &plaintextCharacter);

	return plaintextCharacter;
}

/*************************************************************
 * Function: encodeCharacter ()                              *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function encodes a character.           *
 * Input parameters: character                               *
 * Returns: An encoded character                             *
 * Preconditions: The plaintextCharacter has a valid value   *
 *                inputted by user. Also, constant values    *
 *                for the CODE_NUMBER, CODE_UPPERCASE_LETTER *
 *                and CODE_LOWERCASE_LETTER has been defined *
 * Postconditions: The encoded character is returned         *
 *************************************************************/
char encodeCharacter (char plaintextCharacter)
{
	return (plaintextCharacter + CODE_NUMBER) - 
		    CODE_UPPERCASE_LETTER + CODE_LOWERCASE_LETTER;
}

/*************************************************************
 * Function: getPointX ()                                    *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              value of x.                                  *
 * Input parameters: Point number for x                      *
 * Returns: The value of x in type double                    *
 * Preconditions: Requires a user to input value for x       *
 * Postconditions: The value of x is returned.               *
 *************************************************************/
double getPointX (int point)
{
	double x = 0.0;

	printf ("Enter value of x%d [floating-point value] > ", point);
	scanf ("%lf", &x);

	return x;
}

/*************************************************************
 * Function: getPointY ()                                    *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              value of y.                                  *
 * Input parameters: Point number for y                      *
 * Returns: The value of y in type double                    *
 * Preconditions: Requires a user to input value for y       *
 * Postconditions: The value of y is returned.               *
 *************************************************************/
double getPointY (int point)
{
	double y = 0.0;

	printf ("Enter value of y%d [floating-point value] > ", point);
	scanf ("%lf", &y);

	return y;
}

/*************************************************************
 * Function: computeDistanceOfTwoPoints ()                   *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function computes for the distance of   *
 *              two points.                                  *
 * Input parameters: point (x1, y1) and point (x2, y2)       *
 * Returns: The distance of two points                       *
 * Preconditions: Two valid points with x and y values has   *
 *                been inputted by user. Also math.h needs   *
 *                to be included.                            *
 * Postconditions: The distance of two points is returned    *
 *************************************************************/
double computeDistanceOfTwoPoints (double x1, double y1, double x2, double y2)
{
	return 	sqrt (pow ((x1 - x2), 2) + 
		          pow ((y1 - y2), 2));
}

/*************************************************************
 * Function: getTheta ()                                     *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              value of theta.                              *
 * Input parameters: None                                    *
 * Returns: The value of theta in type double                *
 * Preconditions: Requires a user to input value for theta   *
 * Postconditions: The value of radius is returned.          *
 *************************************************************/
double getTheta (void)
{
	double theta = 0.0;

	printf ("Enter value of theta [floating-point value] > ");
	scanf ("%lf", &theta);
	
	return theta;
}

/*************************************************************
 * Function: computeSineOfTheta ()                           *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function computes for the value of      *
 *              sine of theta.                               *
 * Input parameters: theta                                   *
 * Returns: The value of sine of theta                       *
 * Preconditions: Theta has a valid value inputted by user,  *
 *                and it is in radian. Also, math.h needs to *
 *                be included.                               *
 * Postconditions: The sine of theta is returned             *
 *************************************************************/
double computeSineOfTheta (double theta)
{
	return tan (theta) * cos (theta);
}

/*************************************************************
 * Function: getResistor ()                                  *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              value of a resistor.                         *
 * Input parameters: The number of the resistor              *
 * Returns: The value of resistor in type integer            *
 * Preconditions: Requires a user to input value for         *
 *                resistor.                                  *
 * Postconditions: The value of resistor is returned.        *
 *************************************************************/
int getResistor (int resistorNumber)
{
	int resistor = 0;

	printf ("Enter values of resistor %d [integer value] > ", resistorNumber);
	scanf ("%d", &resistor);

	return resistor;
}

/*************************************************************
 * Function: computeParllelResistance ()                     *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function computes for the value of      *
 *              equivalent parallel resistance.              *
 * Input parameters: Three resistors                         *
 * Returns: The value of equivalent parallel resistance      *
 * Preconditions: The three resistors has valid values       *
 *                inputted by user.                          *
 * Postconditions: The equivalent parallel resistance  is    *
 *                 returned.                                 *
 *************************************************************/
double computeParallelResistance (int resistor1, int resistor2, int resistor3)
{
	return 1.0 / ((1.0 / resistor1) + 
		          (1.0 / resistor2) + 
				  (1.0 / resistor3));
}

/*************************************************************
 * Function: getA ()                                         *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              value of a.                                  *
 * Input parameters: None                                    *
 * Returns: The value of a in type integer                   *
 * Preconditions: Requires a user to input value for a       *
 * Postconditions: The value of a is returned.               *
 *************************************************************/
int getA (void)
{
	int a = 0;

	printf ("Enter value of a [integer value] > ");
	scanf ("%d", &a);

	return a;
}

/*************************************************************
 * Function: getX ()                                         *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              value of x.                                  *
 * Input parameters: None                                    *
 * Returns: The value of x in type double                    *
 * Preconditions: Requires a user to input value for x       *
 * Postconditions: The value of x is returned.               *
 *************************************************************/
double getX (void)
{
	double x = 0.0;

	printf ("Enter value of x [floating-point value] > ");
	scanf ("%lf", &x);

	return x;
}

/*************************************************************
 * Function: getZ ()                                         *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function prompts the user for the       *
 *              value of z.                                  *
 * Input parameters: None                                    *
 * Returns: The value of z in type double                    *
 * Preconditions: Requires a user to input value for z       *
 * Postconditions: The value of z is returned.               *
 *************************************************************/
double getZ (void)
{
	double z = 0.0;

	printf ("Enter value of z [floating-point value] > ");
	scanf ("%lf", &z);

	return z;
}

/*************************************************************
 * Function: computeGeneralEqueation ()                      *
 * Date Created: September 8, 2012                           *
 * Date Last Modified: September 8, 2012                     *
 * Description: This function finds the value of y using a   *
 *              general equation.                            *
 * Input parameters: User-defined values for the variables   *
 *                   a, x and z.                             *
 * Returns: The result of the general equation               *
 * Preconditions: The a, x and z has valid values inputted   *
 *                by user. Also, NUMERATOR_Y, DENOMINATOR_Y, *
 *                MOD_OPERAND and PI are all defined.        *
 * Postconditions: The result of the general equation  is    *
 *                 returned.                                 *
 *************************************************************/
double computeGeneralEquation (int a, double x, double z)
{
	return ((double) NUMERATOR_Y /(double) DENOMINATOR_Y) / 
		     x * z / (a % MOD_OPERAND) - PI + a;
}
