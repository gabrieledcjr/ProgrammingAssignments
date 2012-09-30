/*************************************************************************
 * Filename: equation.h                                                  *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012  ; Lab Section 7                           *
 * Programming Assignment 2: A Modular Approach to the Equation          *
 *                           Evaluator                                   *
 * Date: September 8, 2012                                               *
 *                                                                       *
 * Description: This file stores all the #includes, #defines, and        *
 *              function prototypes required to evaluate each equation   *
 *              listed below. There are detailed description on how each *
 *              function works documented on there respective function   *
 *              definitions located in the file <equation.c>             *
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

#ifndef EQUATION
#define EQUATION

#include <stdio.h>
#include <math.h>

#define PI						3.141592	/* Defines PI as a constant variable */
#define NUMERATOR_Y				113		    /* Numerator used in the General Equation whose */
#define DENOMINATOR_Y			115			/* Denominator used in the General Equation */
#define MOD_OPERAND             2           /* Modulus operand used in the General Equation */
#define CODE_NUMBER				2			/* Pre-defined number used to encode a character */
#define CODE_UPPERCASE_LETTER	'A'			/* Pre-defined uppercase letter used to encode a character */
#define CODE_LOWERCASE_LETTER	'a'			/* Pre-defined lowercase letter used to encode a character */


/*************************************************************
 * These function prototypes are described in detail at      *
 * there respective function definitions located in the file *
 * <equation.c>                                              * 
 *************************************************************/

double getMass (void);
double getAcceleration (void);
double computeNewtons2ndLaw (double mass, double acceleration);

double getRadius (void);
double getHeight (void);
double computeVolumeOfCylinder(double radius, double height);

char getPlaintextCharacter (void);
char encodeCharacter (char plaintextCharacter);

double getPointX (int point);
double getPointY (int point);
double computeDistanceOfTwoPoints (double x1, double y1, double x2, double y2);

double getTheta (void);
double computeSineOfTheta (double theta);

int getResistor (int resistorNumber);
double computeParallelResistance (int resistor1, int resistor2, int resistor3);

int getA (void);
double getX (void);
double getZ (void);
double computeGeneralEquation (int a, double x, double z);

#endif