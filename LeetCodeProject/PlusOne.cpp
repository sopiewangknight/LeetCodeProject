#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;
class Solution66 {
public:
	vector<int> plusone(vector<int>& digits) {
		int length = digits.size();
		digits[length - 1] = digits[length - 1] + 1;
		for (int i = length - 1; i > 0; i--) {
			if (digits[i] >= 10) {
				digits[i] = 0;
				digits[i - 1] = digits[i - 1] + 1;
			}
			else {
				break;
			}

		}
		if (digits[0]>=10)
		{
			digits[0] = 0;
			digits.push_back(1);
			length = digits.size();
			reverse(digits.begin(), digits.end());
			reverse(digits.begin()+1, digits.end());
		}
		return digits;
	}
};

int t3_main() {

	int arraynums[] = { 9,9,9,9,9,9,9,4};
	size_t count = sizeof(arraynums) / sizeof(int);
	vector<int> nums(arraynums, arraynums + count);
	Solution66 s = Solution66();

	vector<int> res = s.plusone(nums);

	vector<int>::iterator i;
	for (i = nums.begin(); i != nums.end(); i++) {
		cout << *i << "  ";
	}


	cin.get();

	return 0;
}