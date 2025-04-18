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
		inputFile >> x2 >> x1 >> y2 >> y1;
		arr1[i] = x2 - x1;
		arr2[i] = y2 - y1;
	}
}
void inputdata_processing(float arr1[], float arr2[], double n)
{
	for (int i = 0; i < n; i++) {
		int exponent1 = static_cast<int>(std::floor(std::log10(std::abs(arr1[i]))));
		double scale1 = std::pow(10, 1 - exponent1);
		arr1[i] = round(arr1[i] * scale1) / scale1;
		int exponent2 = static_cast<int>(std::floor(std::log10(std::abs(arr2[i]))));
		double scale2 = std::pow(10, 1 - exponent2);
		arr2[i] = round(arr2[i] * scale2) / scale2;
	}
}
void a_i(float arr1[], float arr2[], float arr3[], double n)
{
	for (int i = 0; i < n; i++) {
		int exponent = static_cast<int>(std::floor(std::log10(std::abs(arr2[i] / arr1[i]))));
		double scale = std::pow(10, 1 - exponent);
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
	double scale = std::pow(10, 1 - exponent);
	float temp = round(sum / n * scale) / scale;
	return temp;
}
float a_error(float arr3[], double n, float sum)
{
	float t = 2.4;
	float delta_a = sqrt(sum / (n - 1)) / sqrt(n) * t;
	int exponent = static_cast<int>(std::floor(std::log10(std::abs(delta_a))));
	double scale = std::pow(10, 1 - exponent);
	float temp = round(delta_a * scale) / scale;
	return temp;
}
float e_k(float a)
{
	float T = 296.15;
	float temp = T * a;
	return temp;
}
float e_k_error(float a, float delta_a)
{
	float T = 296.15;
	float delta_T = 0.5;
	float temp = sqrt(pow(a, 2) * pow(delta_T / 3, 2) + pow(T, 2) * pow(delta_a, 2));
	return temp;
}
void outputdata(float arr1[], float arr2[], float arr3[], double n)
{
	std::ofstream outputFile("OutputData.csv");
	inputdata_processing(arr1, arr2, n);
	a_i(arr1, arr2, arr3, n);
	float sum1 = 0;
	float sum2 = 0;
	float temp1 = 0;
	float temp2 = 0;
	outputFile << "x2-x1" << " " << "y2-y1" << " " << "a_i" << " " << "a_i-a" << " " << "(a_i-a)^2" << std::endl;
	for (int i = 0; i < n; i++) {
		if (arr3[i] != arithmetic_mean(arr3, n))
		{
			int exponent1 = static_cast<int>(std::floor(std::log10(std::abs(arr3[i] - arithmetic_mean(arr3, n)))));
			double scale1 = std::pow(10, 1 - exponent1);
			temp1 = round((arr3[i] - arithmetic_mean(arr3, n)) * scale1) / scale1;
			int exponent2 = static_cast<int>(std::floor(std::log10(std::abs(pow(temp1, 2)))));
			double scale2 = std::pow(10, 1 - exponent2);
			temp2 = round(pow(temp1, 2) * scale2) / scale2;
		}
		else
		{
			temp1 = 0;
			temp2 = 0;
		}
		sum1 += arr3[i];
		sum2 += temp2;
		outputFile << std::setprecision(2) << arr1[i] << "  " << std::setprecision(2) << arr2[i] << "   " << std::setprecision(2) << arr3[i] << "   " << std::setprecision(2) << temp1 << "   " << std::setprecision(2) << temp2 << std::endl;
	}
	outputFile << "--------------------------------------------" << std::endl;
	outputFile << "Sum(a_i-a)= " << std::setprecision(2) << sum1 << " Sum(a_i-a)^2=" << std::setprecision(2) << sum2 << std::endl;

	outputFile << "Среднее арифитическое " << std::setprecision(2) << arithmetic_mean(arr3, n) << std::endl;
	outputFile << "Погрешность a " << std::setprecision(2) << a_error(arr3, n, sum2) << std::endl;
	outputFile << "e/k= " << std::setprecision(2) << e_k(arithmetic_mean(arr3, n)) << std::endl;
	outputFile << "e/k Погрешность, как погрешность косвенных измерений " << std::setprecision(2) << e_k_error(arithmetic_mean(arr3, n), a_error(arr3, n, sum2)) << std::endl;
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
