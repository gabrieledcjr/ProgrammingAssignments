/*************************************************************************
 * Filename: GPA.h                                                       *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012  ; Lab Section 7                           *
 * Programming Assignment 3: Statistical Analysis of Student Records     *
 * Date: September 17, 2012                                              *
 *                                                                       *
 * Description: This is header file the houses the function prototypes   *
 *              all functions required to run the project delaCruz_pa3.  *
 *              Individual functions are more defined at their function  *
 *              definitions located in GPA.c                             *
 *                                                                       *
 * Relevant Formulas:													 *
 *   1) Sum of 5 numbers:                                                *
 *      sum = n1 + n2 + n3 + n4 + n5, where n1 is number 1,              *
 *                                          n2 is number 2,              *
 *									        n3 is number 3,              *
 *									        n4 is number 4,              *
 *									        n5 is number 5,              *
 *   2) Mean:											                 *
 *      mean = sum / count, where sum is result of formula 1             *
 *                                count is number of student records     *
 *   3) Deviation:												         *
 *      d = n# - mean, where d is deviation of a specific number         *
 *							 n# where # is the specific student record   *
 *                           mean is result of formula 2                 *
 *   4) Variance:                                                        *
 *      v = ((d1)^2 + (d2)^2 + (d3)^2 + (d4)^2 + (d5)^2) / count         *
 *                          , where v is variance                        *
 *                                  d1 is deviation of student record 1  *
 *                                  d2 is deviation of student record 2  *
 *                                  d3 is deviation of student record 3  *
 *                                  d4 is deviation of student record 4  *
 *									d5 is deviation of student record 5  *
 *									count is number of student records   *
 *   5) Standard deviation:											     *
 *      s = sqrt (v), where s is standard deviation                      *
 *                          v is result of formula 4                     *
 *************************************************************************/

#ifndef GPA_H
#define GPA_H

#include <stdio.h>
#include <math.h>

#define NUMBER_OF_STUDENTS	5				/* Number of student records */
#define INPUT_FILE			"input.dat"     /* Filename of the file where the inputs are to be retrieved */
#define INPUT_FILE_MODE		"r"             /* File mode of the input file */
#define OUTPUT_FILE			"output.dat"    /* Filename of the file where the output is to be stored */
#define OUTPUT_FILE_MODE	"w"             /* File mode of the output file */

FILE * openFileStream (char fileName[], char mode[]);

int readInteger (FILE *fileStream);
double readDouble (FILE *fileStream);

double calculateSum (double number1, double number2, 
					 double number3, double number4, 
				     double number5);
double calculateMean (double sum, int count);
double calculateDeviation (double number, double mean);
double calculateVariance (double deviation1, double deviation2,
						  double deviation3, double deviation4,
						  double deviation5, int count);
double calculateStandardDeviation (double variance);

double findMin (double number1, double number2, 
			    double number3, double number4, 
			    double number5);
double findMax (double number1, double number2, 
			    double number3, double number4, 
			    double number5);

void printDouble (FILE *fileStream, double number);

void closeFileStream (FILE *fileStream);

#endif