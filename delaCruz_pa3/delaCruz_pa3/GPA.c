/*************************************************************************
 * Filename: GPA.c                                                       *
 * Programmer: Gabriel V. de a Cruz Jr.                                  *
 * Class: CptS 121, Fall 2012  ; Lab Section 7                           *
 * Programming Assignment 3: Statistical Analysis of Student Records     *
 * Date: September 17, 2012                                              *
 *                                                                       *
 * Description: This file houses all of the function definitions         *
 *				declared in GPA.h. Each functions has a well-defined     *
 *              comments that identifies what the program does, what     *
 *              arguments it requires and it's return type and values    *
 *              as well pre and post conditions.                         *
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


/*************************************************************
 * Function: openFileStream ()                               *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: This function opens a file with specified    *
 *              with mode.                                   *
 * Input parameters: filename and mode                       *
 * Returns: Pointer to a FILE type                           *
 * Preconditions: Filename specified exists in the directory *
 *                with proper permissions                    *
 * Postconditions: Specified file is opened and a pointer to *
 *                 that file is returned.                    *
 *************************************************************/
FILE * openFileStream (char fileName[], char mode[])
{
	FILE *fileStream = NULL;

	fileStream = fopen (fileName, mode);

	return fileStream;
}

/*************************************************************
 * Function: readInteger ()                                  *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: Reads one integer number from the input file *
 * Input parameters: pointer to a file stream                *
 * Returns: integer read from the file                       *
 * Preconditions: File has already been successfully opened  *
 *                and assumes that data it's retrieving from *
 *                the file is an integer                     *
 * Postconditions: A number that is an integer is returned   *
 *************************************************************/
int readInteger (FILE *fileStream)
{
	int number = 0;

	fscanf (fileStream, "%d", &number);

	return number;
}

/*************************************************************
 * Function: readDouble ()                                   *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: Reads one double precision number from the   *
 *              input file.                                  *
 * Input parameters: pointer to a file stream                *
 * Returns: double read from the file                        *
 * Preconditions: File has already been successfully opened  *
 *                and assumes that data it's retrieving from *
 *                the file is a real number                  *
 * Postconditions: A number that is an double is returned    *
 *************************************************************/
double readDouble (FILE *fileStream)
{
	double number = 0.0;

	fscanf (fileStream, "%lf", &number);

	return number;
}

/*************************************************************
 * Function: calculateSum ()                                *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: Finds the sume of 5 numbers                  *
 * Input parameters: 5 double precision numbers              *
 * Returns: sum of 5 double preicision numbers               *
 * Preconditions: Assume that all numbers are positive real  *
 *                numbers. Also assume that all arguments    *
 *                has the right values and data type.        *
 * Postconditions: Sum of 5 numbers is returned              *
 *************************************************************/
double calculateSum (double number1, double number2, 
					 double number3, double number4, 
				     double number5)
{
	return number1 + number2 + number3 + number4 + number5;
}

/*************************************************************
 * Function: calculateMean ()                                *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: Determines the mean throught the calculation *
 *              sum / count and returns the result. It also  *
 *              checks if the count is not 0. If it is 0 the *
 *              function returns -1.0. Otherwise it returns  *
 *              the mean.                                    *
 * Input parameters: sum and number of addends               *
 * Returns: mean (average)                                   *
 * Preconditions: Assume that it is a sum of positive        *
 *                numbers                                    *
 * Postconditions: Mean is returned				             *
 *************************************************************/
double calculateMean (double sum, int count)
{
	double mean = -1.0;

	if (count != 0)
	{
		mean = sum / count;
	}

	return mean;
}

/*************************************************************
 * Function: calculateDeviation ()                           *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: Determines the deviation of number from the  *
 *              mean and returns the result. The deviation   *
 *              may be calculated as number - mean.          *
 * Input parameters: specific number, mean of the numbers    *
 * Returns: deviation of a specific number                   *
 * Preconditions: Assume that number is part of the group    *
 *                whose mean is also pass to this function   *
 * Postconditions: deviation of a specific number is         *
 *                 returned	         			             *
 *************************************************************/
double calculateDeviation (double number, double mean)
{
	return number - mean;
}

/*************************************************************
 * Function: calculateVariance ()                            *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: Determines the variance through the          *
 *              calculation ((deviation1)^2 + (deviation2)^2 *
 *              + (deviation3)^2 + (deviation4)^2 +          *
 *              (deviation5)^2) / count                      *
 * Input parameters: deviation of 5 numbers and hows many    *
 *                   numbers                                 *
 * Returns: variance of numbers                              *
 * Preconditions: Assume that deviations of each number were *
 *                already calculated and were accurately     *
 *                done                                       *
 * Postconditions: variance is returned        			     *
 *************************************************************/
double calculateVariance (double deviation1, double deviation2,
						  double deviation3, double deviation4,
						  double deviation5, int count)
{
	return (pow (deviation1, 2) + pow (deviation2, 2) +
		    pow (deviation3, 2) + pow (deviation4, 2) + 
			pow (deviation5, 2)) / count;
}

/*************************************************************
 * Function: calculateStandardDeviation ()                   *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: Calculates the standard deviation as         *
 *              sqrt (variance) and returns the result.      *
 * Input parameters: variance                                *
 * Returns: standard deviation                               *
 * Preconditions: Assume that variance was accurately        *
 *                calculated. Also, that math.h is included  *
 * Postconditions: standard deviation is returned            *
 *************************************************************/
double calculateStandardDeviation (double variance)
{
	return sqrt (variance);
}

/*************************************************************
 * Function: findMin ()                                      *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: Determines the minimum number out of the     *
 *              five input parameters passed into the        *
 *              function, returning the min.                 *
 * Input parameters: 5 double precision numbers              *
 * Returns: minimum number out of the 5 numbers              *
 * Preconditions: Assume that numbers has correct values     *
 * Postconditions: minimum number out of the 5 numbers is    *
 *                 returned                                  *
 *************************************************************/
double findMin (double number1, double number2, 
			    double number3, double number4, 
			    double number5)
{
	double min = 0;

	if (number1 <= number2 && number1 <= number3 && 
		number1 <= number4 && number1 <= number5)
	{
		min = number1;
	}
	else if (number2 <= number1 && number2 <= number3 && 
		     number2 <= number4 && number2 <= number5)
	{
		min = number2;
	}
	else if (number3 <= number1 && number3 <= number2 && 
		     number3 <= number4 && number3 <= number5)
	{
		min = number3;
	}
	else if (number4 <= number1 && number4 <= number2 && 
		     number4 <= number3 && number4 <= number5)
	{
		min = number4;
	} 
	else
	{
		min = number5;
	}

	return min;
}

/*************************************************************
 * Function: findMax ()                                      *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: Determines the maximum number out of the     *
 *              five input parameters passed into the        *
 *              function, returning the max.                 *
 * Input parameters: 5 double precision numbers              *
 * Returns: maximum number out of the 5 numbers              *
 * Preconditions: Assume that numbers has correct values     *
 * Postconditions: maximum number out of the 5 numbers is    *
 *                 returned                                  *
 *************************************************************/
double findMax (double number1, double number2, 
			    double number3, double number4, 
			    double number5)
{
	double max = 0;

	if (number1 >= number2 && number1 >= number3 && 
		number1 >= number4 && number1 >= number5)
	{
		max = number1;
	}
	else if (number2 >= number1 && number2 >= number3 && 
		     number2 >= number4 && number2 >= number5)
	{
		max = number2;
	}
	else if (number3 >= number1 && number3 >= number2 && 
		     number3 >= number4 && number3 >= number5)
	{
		max = number3;
	}
	else if (number4 >= number1 && number4 >= number2 && 
		     number4 >= number3 && number4 >= number5)
	{
		max = number4;
	} 
	else
	{
		max = number5;
	}

	return max;
}

/*************************************************************
 * Function: printDouble ()                                  *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: Prints a double precision number (to the     *
 *              hundredths place) to an output file.         *
 * Input parameters: FILE pointer & double precision number  *
 * Returns: none                                             *
 * Preconditions: Assume the stream to file was successfully *
 *                opened and number passed the correct value *
 * Postconditions: a double precision number on it's         *
 *                 hundredths place is printed on an output  *
 *                 file specified                            *
 *************************************************************/
void printDouble (FILE *fileStream, double number)
{
	fprintf (fileStream, "%.2lf\n", number);
}

/*************************************************************
 * Function: closeFileStream ()                              *
 * Date Created: September 17, 2012                          *
 * Date Last Modified: September 17, 2012                    *
 * Description: Closes open files                            *
 * Input parameters: FILE pointer to an open file stream     *
 * Returns: none                                             *
 * Preconditions: Assume the stream to file was successfully *
 *                opened and are still open                  *
 * Postconditions: stream to specific is closed and file     *
 *                 stream points to NULL                     *
 *************************************************************/
void closeFileStream (FILE *fileStream)
{
	fclose (fileStream);
}