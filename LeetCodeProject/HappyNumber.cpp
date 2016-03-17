#include<unordered_set>
#include<unordered_map>
#include<string>
#include<sstream>
#include<vector>
#include<math.h>
#include<iostream>
using namespace std;

class Solution202 {
public:
	bool isHappy(int n) {
		std::unordered_set<std::string> setStr;
		std::stringstream intConvertion;
		intConvertion << n;
		std::string str = intConvertion.str();
		setStr.insert(str);

		intConvertion.str("");
		bool isLoop = false;
		int cnt = -1;
		do {
			cnt = 0;
			for (int i = 0; i < str.length(); i++) {
				cnt += (str[i] - '0')*(str[i] - '0');
			}
			intConvertion << cnt;
			str = intConvertion.str();
			intConvertion.str("");
			if (setStr.find(str) == setStr.end()) {
				setStr.insert(str);
			}
			else {
				isLoop = true;
			}

		} while (cnt==1||isLoop);
		return isLoop ? false : true;
	}
	int Hindex(vector<int>& citations) {
		int* table = new int[citations.size()];
		for (int i = 0; i < citations.size(); i++) {
			table[i] = 0;
		}
		for (int i = 0; i < citations.size(); i++) {
			for (int j = 0; j<citations.size(); j++) {
				if (citations[i] >= (j+1)) {
					table[j] += 1;
				}
			}
		}
		for (int i = citations.size() - 1; i >= 0; i--) {
			if (table[i] >= (i + 1)) {
				return (i + 1);
			}
		}
		return 0;

	}

	int countPrimes(int n) {
		if (n <= 2)return 0;

		int cnt = 0;
		for (int i = 2; i < n; i++) {
			if (isPrime(i)) { 
				cout << i<<" ";
				cnt++; 

			}
		}
		return cnt;
	}
	bool isPrime(int s) {
		if (s < 2)return  false;
		if (s == 2||s==3) return true;
		int half = s/2;
		for (int i = 2; i <= half; i++) {
			if (s%i == 0)return false;
		}
		return true;
	}

	int effectiveCountPrime(int n) {
		bool* primeTable = new bool[n + 1];
		primeTable[1] = false;
		for (int i = 2; i <= n; i++)primeTable[i] = true;
		int cnt = 0;
		for (int i = 1; i <= sqrt(n); i++) {
			if (primeTable[i]) {
				int it = i + i;;
				while (it <= n) {
					primeTable[it] = false;
					it += i;
				}
			}
		}
		for (int i = 1; i<n; i++)if (primeTable[i])cnt++;
		return cnt;
	}

	string fractionToDecimal(int numerator, int denumerator) {
		int shang, yushu;
		string res = "";
		stringstream sstream;
		unordered_set<char> chset;
		char circularChar;
		if (numerator == 0)return "0";
		bool zheng = true;
		if (numerator<0)
		{
			zheng = !zheng;
			numerator = -1 * numerator;
		}
		if (denumerator<0)
		{
			zheng = !zheng;
			denumerator = -1 * denumerator;
		}
		if (!zheng)
		{
			res += "-";
		}
		if (numerator >= denumerator) {
			shang = numerator / denumerator;
			yushu = numerator%denumerator;
			sstream << shang;
			string tmp = sstream.str();
			res += tmp;
			sstream.str("");

			if (yushu == 0)return res;
			else {
				numerator = yushu * 10;
				res += ".";
			}
		}
		else {
			res += "0.";
			numerator = numerator * 10;
			while (numerator<denumerator) {
				numerator = numerator * 10;
				res += "0";
			}
		}
		while (numerator > denumerator) {
			shang = numerator / denumerator;
			yushu = numerator%denumerator;
			sstream << shang;
			circularChar = shang + '0';
			if (chset.find(circularChar) == chset.end()) {
				chset.insert(circularChar);
			}
			else {
				break;
			}
			string tmp = sstream.str();
			res += tmp;
			sstream.str("");

			if (yushu == 0)return res;
			else {
				numerator = yushu * 10;
			}

		}
		//找到上个循环的char
		int i = res.size() - 1;
		for (; i >= 0; i--) {
			if (res[i] == circularChar)break;
		}
		return res.substr(0, i).append("(").append(res.substr(i, res.size() - i + 1)).append(")");
	}
};

int t202_main() {
	Solution202 s = Solution202();




	cout<<s.fractionToDecimal(-2147483648,1);
	cin.get();
}