#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>


void inputdata(float arr1[], float arr2[], double n)
{
	std::ifstream inputFile("InputData.csv");
	float x2 = 0;
	float x1 = 0;
	float y2 = 0;
	float y1 = 0;
	for (int i = 0; i < n; i++) {
		inputFile >> x2 >> x1>>y2>>y1;
		arr1[i] = x2-x1;
		arr2[i] = y2 - y1;
	}
}
void inputdata_processing(float arr1[], float arr2[], double n)
{
	for (int i = 0; i < n; i++) {
		int exponent1 = static_cast<int>(std::floor(std::log10(std::abs(arr1[i]))));
		double scale1 = std::pow(10, 1 - exponent1);
		arr1[i] = round(arr1[i] * scale1) / scale1;
		int exponent2 = static_cast<int>(std::floor(std::log10(std::abs(arr1[i]))));
		double scale2 = std::pow(10, 1 - exponent2);
		arr2[i] = round(arr1[i] * scale2) / scale2;
	}
}
void a_i(float arr1[], float arr2[], float arr3[], double n)
{
	for (int i = 0; i < n; i++) {
		int exponent = static_cast<int>(std::floor(std::log10(std::abs(arr2[i] / arr1[i]))));
		double scale = std::pow(10, 2 - exponent);
		arr3[i] = round(arr2[i] / arr1[i] * scale) / scale;
	}
}
float arithmetic_mean(float arr3[], double n)
{
	float sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr3[i];
	}
	int exponent = static_cast<int>(std::floor(std::log10(std::abs(sum / n))));
	double scale = std::pow(10, 3 - exponent);
	float temp = round(sum/n * scale) / scale;
	return temp;
}

void outputdata(float arr1[], float arr2[], float arr3[], double n)
{
	std::ofstream outputFile("OutputData.csv");
	a_i(arr1, arr2, arr3, n);
	outputFile << "x2-x1" << " " << "y2-y1" << " " << "a_i" << std::endl;
	for (int i = 0; i < n; i++) {
		outputFile << arr1[i] << " " << arr2[i] << " " << arr3[i]<< std::endl;
	}
	outputFile << arithmetic_mean(arr3, n);

}
int main() {
	double n = 8;
	float data1[8];
	float data2[8];
	float data3[8];
	inputdata(data1, data2, n);
	outputdata(data1, data2, data3, n);

	return 0;
}
