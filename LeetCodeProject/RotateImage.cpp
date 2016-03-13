#include<vector>
#include<iostream>
using namespace std;

class Solution48 {
public:

	int missingNumber(vector<int>& nums) {
		int sum = 0;
		for (int i = 0; i<nums.size(); i++)
		{
			sum += nums[i];
		}
		int n = nums.size();
		int res = (n *n + n) / 2;
		return res - sum;

	}
	void rotate(vector<vector<int>>& matrix) {

		int n = matrix.size();
		int j = 0;
		int tmp;
		while (n > 1) {
			
			for (int i = j; i <= j + n - 1 - 1; i++) {
				tmp = matrix[j][i];
				matrix[j][i] = matrix[i][n + j - 2];
				matrix[i][n + j - 2] = matrix[n + j - 2][n + j - 2 +j- i];
				matrix[n + j - 2][n + j - 2 +j- i] = matrix[n + j - 2 +j- i][j];
				matrix[n + j - 2 +j- i][j] = tmp;
			}
			j++;
			n = n - 2;
		}



	}
};

int t48_main() {
	Solution48 s = Solution48();
	int arr[] = { 0,1,2 };
	vector<int> test(arr, arr + 3);
	s.missingNumber(test);

	cin.get();
	return 0;
}