/*************************************************************************
 * Filename: main.c                                                      *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012  ; Lab Section 7                           *
 * Programming Assignment 2: A Modular Approach to the Equation          *
 *                           Evaluator                                   *
 * Date: September 8, 2012                                               *
 *                                                                       *
 * Description: This program evaluates the equations provided below.     *
 *              The program must prompt user for inputs to the equations *
 * 			    and evaluate them based on the inputs.                   *
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

int main (void) 
{
	char plaintextCharacter = '\0';				/* character to be encoded */
	double mass = 0.0, acceleration = 0.0;		/* variables used to compute for force */
	double radius = 0.0, height = 0.0;          /* variables used to compute for volume of cylinder */
	double x1 = 0.0, x2 = 0.0, 
		   y1 = 0.0, y2 = 0.0;	                /* variables used to compute for distance between two points */
	double theta = 0.0;							/* variable used to compute for sine of theta */
	int	resistor1 = 0, 
		resistor2 = 0, 
		resistor3 = 0;					        /* variables used to compute for equivalent parallel resistance */
	int a = 0;									/* variable used to compute for general equation */
	double x = 0.0, z = 0.0;                    /* variables used to compute for general equation */


	/* Compute for Newton's Second Law of Motion */
	printf ("Newton's Second Law of Motion:\n");
	mass = getMass ();
	acceleration = getAcceleration ();

	printf ("force = mass * acceleration\n");
	printf ("      = %lf * %lf\n", mass, acceleration);
	printf ("      = %.2lf\n\n", computeNewtons2ndLaw (mass, acceleration));	

	/* Compute for volume of cylinder */
	printf ("Volume of Cylinder:\n");
	radius = getRadius ();
	height = getHeight ();

	printf ("volume_cylinder = PI * radius^2 * height\n");
	printf ("                = %f * %lf^2 * %lf\n", PI, radius, height);
	printf ("                = %.2lf\n\n", computeVolumeOfCylinder (radius, height));

	/* Encode a character */
	printf ("Character encoding:\n");
	plaintextCharacter = getPlaintextCharacter ();

	printf ("encoded_character = (plaintext_character + %d) - '%c' + '%c'\n", CODE_NUMBER, CODE_UPPERCASE_LETTER, CODE_LOWERCASE_LETTER);
	printf ("                  = (%c + %d) - '%c' + '%c'\n", plaintextCharacter, CODE_NUMBER, CODE_UPPERCASE_LETTER, CODE_LOWERCASE_LETTER);
	printf ("                  = %c\n\n", encodeCharacter (plaintextCharacter));

	/* Compute for distance between two points */
	printf ("Distance between two points:\n");
	x1 = getPointX (1);
	y1 = getPointY (1);
	x2 = getPointX (2);
	y2 = getPointY (2);

	printf ("distance = square root of ((x1 - x2)^2 + (y1 - y2)^2)\n");
	printf ("         = square root of ((%lf - %lf)^2 + (%lf - %lf)^2)\n", x1, x2, y1, y2);
	printf ("         = %.2lf\n\n", computeDistanceOfTwoPoints (x1, y1, x2, y2));

	/* Compute for sine of theta */
	printf ("Sine of theta:\n");
	theta = getTheta ();

	printf ("sine_theta = tan (theta) * cos (theta)\n");
	printf ("           = tan (%lf) * cos (%lf)\n", theta, theta);
	printf ("           = %.2lf\n\n", computeSineOfTheta (theta));

	/* Compute for equivalent parallel resistance */
	printf ("Equivalent parallel resistance:\n");
	resistor1 = getResistor (1);
	resistor2 = getResistor (2);
	resistor3 = getResistor (3);

	printf ("parallel_resistance = 1 / ((1 / R1) + (1 / R2) + (1 / R3))\n");
	printf ("                    = 1 / ((1 / %d) + (1 / %d) + (1 / %d))\n", resistor1, resistor2, resistor3);
	printf ("                    = %.2lf\n\n", computeParallelResistance (resistor1, resistor2, resistor3));

	/* Find the value of y in a general equation */
	printf ("General equation (Finding unknown value of y):\n");
	a = getA ();
	x = getX ();
	z = getZ ();

	printf ("y = (%d / %d) / x * z / (a %% %d) - PI + a\n", NUMERATOR_Y, DENOMINATOR_Y, MOD_OPERAND);
	printf ("  = (%d / %d) / %lf * %lf / (%d %% %d) - %f + %d\n", NUMERATOR_Y, DENOMINATOR_Y, x, z, a, MOD_OPERAND, PI, a);
	printf ("  = %.2lf\n", computeGeneralEquation (a, x, z));

	return 0;
}

