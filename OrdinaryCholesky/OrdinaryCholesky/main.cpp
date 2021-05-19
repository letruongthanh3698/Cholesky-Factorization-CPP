// OrdinaryCholesky.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "main.h"
#include "OrdinaryCholesky.h"
#include "OrdinaryCholesky_terminate.h"
#include "coder_array.h"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <sstream>

using namespace std;

// Function Declarations
static coder::array<double, 2U> argInit_UnboundedxUnbounded_real_T(string filename);

static double argInit_real_T();

static void main_OrdinaryCholesky();

uint64_t precision = 15;

uint64_t rows, cols;
string filename = "s3rmt3m1.mtx";

// Function Definitions
static coder::array<double, 2U> argInit_UnboundedxUnbounded_real_T(string filename)
{
	ifstream input_file(filename);
	if (!input_file.is_open())
		throw "Can not open file!";

	uint64_t numberelement;
	input_file >> rows >> cols;
	input_file >> numberelement;

	coder::array<double, 2U> result;
	// Set the size of the array.
	// Change this size to the value that the application requires.
	result.set_size(rows, cols);
	// Loop over the array to initialize each element.
	for (int idx0{ 0 }; idx0 < result.size(0); idx0++) {
		for (int idx1{ 0 }; idx1 < result.size(1); idx1++) {
			// Set the value of the array element.
			// Change this value to the value that the application requires.
			result[idx0 + result.size(0) * idx1] = argInit_real_T();
		}
	}

	uint64_t rowindex_U64, colindex_U64;
	double value_D;
	for (uint64_t index = 0; index < numberelement; index++)
	{
		input_file >> rowindex_U64 >> colindex_U64 >> value_D;
		result[rowindex_U64 + colindex_U64*cols] = value_D;
	}

	return result;
}

static double argInit_real_T()
{
	return 0.0;
}

static void main_OrdinaryCholesky()
{
	coder::array<double, 2U> input;
	coder::array<double, 2U> res;
	// Initialize function 'getchol' input arguments.
	// Initialize function input argument 'input'.
	cout << "Data loading!\n";
	input = argInit_UnboundedxUnbounded_real_T(filename + ".txt");
	// Call the entry-point 'getchol'.
	cout << "Load Data Successfully!\n";
	cout << "Calculating!\n";
	clock_t start, stop;
	start = clock();
	OrdinaryCholesky(input, res);
	stop = clock();
	cout << "Execution time: " << (double)(stop - start) / CLOCKS_PER_SEC << "\n";

	/*cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(5);
	for (uint64_t i = 0; i < rows; i++)
	{
	for (uint64_t j = 0; j < cols; j++)
	cout << res[i + cols*j] << " ";
	cout << "\n";
	}*/

	ofstream output_file(filename + ".result.txt");
	output_file.setf(ios::fixed);
	output_file.setf(ios::showpoint);
	output_file.precision(precision);

	output_file << rows << " " << cols << "\n";

	uint64_t cnt = 0;
	std::ostringstream res_str;
	res_str.setf(ios::fixed);
	res_str.setf(ios::showpoint);
	res_str.precision(precision);
	for (uint64_t i = 0; i < rows; i++)
		for (uint64_t j = 0; j < cols; j++)
			if (res[i + cols*j] != 0)
			{
				res_str << i << " " << j << " " << res[i + cols*j] << "\n";
				cnt++;
			}

	output_file << cnt << "\n";
	output_file << res_str.str();

	output_file.close();
}

int main(int, char **)
{
	cout << "Enter Data filename (without \"txt\"):";
	cin >> filename;
	// The initialize function is being called automatically from your entry-point
	// function. So, a call to initialize is not included here. Invoke the
	// entry-point functions.
	// You can call entry-point functions multiple times.
	main_OrdinaryCholesky();
	// Terminate the application.
	// You do not need to do this more than one time.
	OrdinaryCholesky_terminate();
	cout << "Save Done! Press Enter to continue!";
	cin.get();
	cin.get();
	return 0;
}

// End of code generation (main.cpp)
