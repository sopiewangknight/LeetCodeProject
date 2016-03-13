#include<iostream>
#include<ctime>

using namespace std;
long long fabonacci(int n) {
	if (n == 1)return 1;
	if (n <= 0)return 0;
	return fabonacci(n - 1) + fabonacci(n - 2);
}

long long circularFabonacci(int n) {
	long long onebefore = 1;
	long long twobefore = 0;
	long long on,res;
	for (int j = 2; j <= n; j++) {
		on = onebefore + twobefore;
		res = on;
		twobefore = onebefore;
		onebefore = on;
	}
	return res;
}



int fabonacci_main() {
	clock_t start, finish;
	start = clock();
	cout << circularFabonacci(100) << endl;
	finish = clock();

	cout << (finish - start) / 1000 << "seconds" << endl;
	cin.get();
	return 0;
}