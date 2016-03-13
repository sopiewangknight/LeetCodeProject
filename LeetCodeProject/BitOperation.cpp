#include<iostream>

using namespace std;


int numberOfOne(int n)
{
	int cnt = 0;
	if (n < 0) {
		n = n*(-1);
	}
	while (n > 0) {
		if (n & 1 == 1)cnt++;
		n = n >> 1;
	}
	return cnt;
}

int numberOfOne2(int n) {
	int cnt = 0;
	int flag = 1;
	if (n < 0)n = -n;
	while (flag<n) {
		if ((flag&n) == flag)cnt++;
		flag = flag << 1;
	}
	return cnt;
}

int numberOfOne3(int n) {
	int cnt = 0;
	if (n < 0)n = -n;
	while (n) {
		cnt++;
		n = n&(n - 1);
	}
	return cnt;
}
int bit_main() {
	int n = 1024;
	cout << ((n&(n - 1))==0);
	//cout << numberOfOne3(-102)<<endl;
	cin.get();
	return 0;
}

