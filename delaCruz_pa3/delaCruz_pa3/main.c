/*************************************************************************
 * Filename: main.c                                                      *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012  ; Lab Section 7                           *
 * Programming Assignment 3: Statistical Analysis of Student Records     *
 * Date: September 17, 2012                                              *
 *                                                                       *
 * Description: This program processes numbers corresponding to student  *
 *              records read from a file and writes the required results *
 *              to an output file. This program assumes five student     *
 *              records and it will calculate for the sum of GPAs, class *
 *              standings and ages. It will also calculate for mean of   *
 *              GPAs, class standings and ages. It will also calculate   *
 *              for the deviation of each GPA from the mean, variance,   *
 *              standard deviation, mininum GPA and maximum GPA.         *
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

#include "GPA.h"

int main (void)
{
	FILE *inputStream = NULL,			/* File pointer for input file */
		 *outputStream = NULL;			/* File pointer for output file */

	int studentId1 = 0,
		studentId2 = 0,
		studentId3 = 0,
		studentId4 = 0,
		studentId5 = 0;					/* 5 student IDs */

	int studentClassStanding1 = 0,
		studentClassStanding2 = 0,
		studentClassStanding3 = 0,
		studentClassStanding4 = 0,
		studentClassStanding5 = 0;		/* 5 student class standings */

	double studentGpa1 = 0.0,
		   studentGpa2 = 0.0,
		   studentGpa3 = 0.0,
		   studentGpa4 = 0.0,
		   studentGpa5 = 0.0;			/* 5 student GPAs */

	double studentAge1 = 0.0,
		   studentAge2 = 0.0,
		   studentAge3 = 0.0,
		   studentAge4 = 0.0,
		   studentAge5 = 0.0;			/* 5 student ages */

	double sumGpa = 0.0,				/* sum of the 5 student's GPA */
		   sumClassStanding = 0.0,		/* sum of the 5 student's class standing */
		   sumAge = 0.0;				/* sum of the 5 student's ages */

	double meanGpa = 0.0,				/* mean of the 5 student's GPA */
		   meanClassStanding = 0.0,		/* mean of the 5 student's class standing */
		   meanAge = 0.0;				/* mean of the 5 student's ages */

	double deviationGpa1 = 0.0,		
		   deviationGpa2 = 0.0,
		   deviationGpa3 = 0.0,
		   deviationGpa4 = 0.0,
		   deviationGpa5 = 0.0;			/* deviation of each student's GPA */

	double varianceGpa = 0.0,			/* variance of the 5 student's GPA */
		   standardDeviationGpa = 0.0,	/* standard variance of the 5 student's GPA */
		   maxStudentGpa = 0.0,			/* maximum number out of the 5 student's GPA */
		   minStudentGpa = 0.0;			/* minimum number out of the 5 student's GPA */


	/* Opens an input file "input.dat" for reading; */
	inputStream = openFileStream (INPUT_FILE, INPUT_FILE_MODE);

    /* Opens an output file "output.dat" for writing; */
	outputStream = openFileStream (OUTPUT_FILE, OUTPUT_FILE_MODE);

	/* Checks the condition if files were successfully opened.
	 * If either file didn't open, then an error message is prompted,
	 * otherwise program will continue to execute other operations. */
	if (inputStream == NULL || outputStream == NULL)
	{
		/* Files were not successfully opened and prompts user of the error.
		 * Program will not continue to execute the rest of the program. */
		printf ("Error: Not able to open files!\n");
	}
	else
	{
		/* Reads five records from the input file (input.dat); */
	
		/* Student 1 */
		studentId1 = readInteger (inputStream);
		studentGpa1 = readDouble (inputStream);
		studentClassStanding1 = readInteger (inputStream);
		studentAge1 = readDouble (inputStream);

		/* Student 2 */
		studentId2 = readInteger (inputStream);
		studentGpa2 = readDouble (inputStream);
		studentClassStanding2 = readInteger (inputStream);
		studentAge2 = readDouble (inputStream);

		/* Student 3 */
		studentId3 = readInteger (inputStream);
		studentGpa3 = readDouble (inputStream);
		studentClassStanding3 = readInteger (inputStream);
		studentAge3 = readDouble (inputStream);

		/* Student 4 */
		studentId4 = readInteger (inputStream);
		studentGpa4 = readDouble (inputStream);
		studentClassStanding4 = readInteger (inputStream);
		studentAge4 = readDouble (inputStream);

		/* Student 5 */
		studentId5 = readInteger (inputStream);
		studentGpa5 = readDouble (inputStream);
		studentClassStanding5 = readInteger (inputStream);
		studentAge5 = readDouble (inputStream);

		/* Calculates the sum of the GPAs; */
		sumGpa = calculateSum (studentGpa1, studentGpa2, 
							   studentGpa3, studentGpa4, 
							   studentGpa5);

		/* Calculates the sum of the class standings; */
		sumClassStanding = calculateSum (studentClassStanding1, studentClassStanding2, 
										 studentClassStanding3, studentClassStanding4, 
										 studentClassStanding5);

		/* Calculates the sum of the ages; */
		sumAge = calculateSum (studentAge1, studentAge2,
								studentAge3, studentAge4,
								studentAge5);

		/* Calculates the mean of the GPAs; */
		meanGpa = calculateMean (sumGpa, NUMBER_OF_STUDENTS);

		/* Calculates the mean of the class standings; */
		meanClassStanding = calculateMean (sumClassStanding, NUMBER_OF_STUDENTS);

		/* Calculates the mean of the ages; */
		meanAge = calculateMean (sumAge, NUMBER_OF_STUDENTS);
 
		/* Calculates the deviation of each GPA from the mean */
		deviationGpa1 = calculateDeviation (studentGpa1, meanGpa);
		deviationGpa2 = calculateDeviation (studentGpa2, meanGpa);
		deviationGpa3 = calculateDeviation (studentGpa3, meanGpa);
		deviationGpa4 = calculateDeviation (studentGpa4, meanGpa);
		deviationGpa5 = calculateDeviation (studentGpa5, meanGpa);

		/* Calculates the variance of the GPAs */
		varianceGpa = calculateVariance (deviationGpa1, deviationGpa2,
										 deviationGpa3, deviationGpa4,
										 deviationGpa5, NUMBER_OF_STUDENTS);

		/* Calculates the standard deviation of the GPAs; */
		standardDeviationGpa = calculateStandardDeviation (varianceGpa);
	
		/* Determines the min of the GPAs; */
		minStudentGpa = findMin (studentGpa1, studentGpa2, 
								 studentGpa3, studentGpa4, 
								 studentGpa5);	

		/* Determines the max of the GPAs; */
		maxStudentGpa = findMax (studentGpa1, studentGpa2, 
								 studentGpa3, studentGpa4, 
								 studentGpa5);

		/* Writing the result to the output file (output.dat) */
		printDouble (outputStream, meanGpa);
		printDouble (outputStream, meanClassStanding);
		printDouble (outputStream, meanAge);
		printDouble (outputStream, standardDeviationGpa);
		printDouble (outputStream, minStudentGpa);
		printDouble (outputStream, maxStudentGpa);

		/* Closes the input and output files (i.e. input.dat and output.dat) */
		closeFileStream (inputStream);
		closeFileStream (outputStream);
	}

	return 0;
}