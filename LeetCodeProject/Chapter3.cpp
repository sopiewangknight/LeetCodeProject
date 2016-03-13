#include<iostream>
#include<math.h>
using namespace std;
void recursivelyPrint(char* number, int length, int index);
void printchar(char* number);
void printMaxN(int n) {
	char* number = new char[n + 1];
	number[n] = '\0';
	for (int i = 0; i < n; i++) {
		number[0] = i + '0';
		recursivelyPrint(number, n, 1);
	}

	delete[] number;
	
}
void recursivelyPrint(char* number, int length, int index) {
	if (index == length) {
		printchar(number);
		return;
	}
	else {
		for (int j = 0; j < 10; j++) {
			number[index] = j + '0';
			recursivelyPrint(number, length, index + 1);
		}
	}

}
void printchar(char* number) {
	int length = strlen(number);
	bool isBegin = false;

	for (int i = 0; i < length; i++) {
		if (isBegin) {
			cout << number[i];
		}
		else {
			if (number[i] != '0') {
				cout << number[i];
				isBegin = true;
			}
		}
	}
	cout << endl;
}


double mPower(double base, int exponent) {
	//ji shu
	if (exponent == 1)return base;
	if (exponent == 0)return 1;
	
	double res = mPower(base, exponent >> 1);
	res = res*res;
	if ((exponent & 1) == 1) {
		res*=base;
	}
	return res;
}
int power_main() {
	printMaxN(6);

	



	/*cout << mPower(2, 47) << endl;
	cout << pow(2, 47) << endl;*/
	cin.get();
	return 0;
}

