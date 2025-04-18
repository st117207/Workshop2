#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>


void inputdata(float arr1[], float arr2[], double n)
{
	std::ifstream inputFile("InputData.csv");
	float firstCol = 0;
	float secondCol = 0;
	for (int i = 0; i < n; i++) {
		inputFile >> firstCol >> secondCol;
		arr1[i] = firstCol;
		arr2[i] = secondCol;
	}
}
float Ln_i(float arr1[], float arr2[], double n)
{
	float sum1 = 0;
	float sum2 = 0;
	float a = 32.5;
	for (int i = 0; i < n; i++)
	{
		sum1 += arr1[i];
		sum2 += arr2[i];
	}
	int exponent1 = static_cast<int>(std::floor(std::log10(std::abs(sum1 / n))));
	double scale1 = std::pow(10, 1 - exponent1);
	float temp1 = round(sum1 / n * scale1) / scale1;
	int exponent2 = static_cast<int>(std::floor(std::log10(std::abs(sum2 / n))));
	double scale2 = std::pow(10, 1 - exponent2);
	float temp2 = round(sum2 / n * scale2) / scale2;
	return temp2 - a * temp1;
}

void outputdata(float arr1[], float arr2[], double n)
{
	int exponent = static_cast<int>(std::floor(std::log10(std::abs(Ln_i(arr1, arr2, n)))));
	double scale = std::pow(10, 1 - exponent);
	float temp = round(Ln_i(arr1, arr2, n) * scale) / scale;
	std::ofstream outputFile("OutputData.csv");
	outputFile << std::setprecision(2) << Ln_i(arr1, arr2, n) << " " << std::setprecision(2) << exp(temp);

}
int main() {
	double n = 16;
	float data1[16];
	float data2[16];
	inputdata(data1, data2, n);
	outputdata(data1, data2, n);

	return 0;
}
