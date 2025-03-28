#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>


void inputdata(float arr[], double n)
{
	std::ifstream inputFile("InputData.csv");
	float firstCol = 0;
	float secondCol = 0;
	for (int i = 0; i < n; i++) {
		inputFile >> firstCol >> secondCol;
		arr[i] = secondCol;
	}
}
void collector_current(float arr[], double n, float r)
{
	for (int i = 0; i < n; i++) {
		arr[i] = arr[i] / r * 1000;
	}
}
void outputdata(float arr[], double n, float r)
{
	std::ofstream outputFile("OutputData.csv");
	collector_current(arr, n, r);
	double temp = 0;
	for (int i = 0; i < n; i++) {
		int exponent = static_cast<int>(std::floor(std::log10(std::abs(arr[i]))));
		double scale = std::pow(10, 1 - exponent);
		temp = round(arr[i] * scale) / scale;;
		outputFile << temp << " " <<std::setprecision(2)<< log(temp) << std::endl;
	}

}
int main() {
	float R = 12;
	double n = 16;
	float data[16];
	inputdata(data, n);
	outputdata(data, n, R);

	return 0;
}
