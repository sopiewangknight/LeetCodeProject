#include<vector>
#include<iostream>
using namespace std;
class Solution221 {
public:
	int maximalSquare(vector<vector<int>>& matrix) {
		
		int row = matrix.size();
		if (row == 0)return 0;
		int range = matrix[0].size();
		int max = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < range; j++) {
				if (matrix[i][j] == 1) {
					int length = 1;
					bool flag = true;
					while (flag) {
						length++;
						if ((i + length - 1)>(row-1) || (j + length - 1)>(range-1)) {
							flag = false;
							continue;
						}
						for (int k = j; k <= j + length - 1-1; k++) {
							if (k>(range-1)||matrix[i][k] == 0) {
								flag = false;
								break;
							}
						}
						for (int k = i; k <= i + length - 1 - 1; k++) {
							if (k>(row-1)||matrix[k][j + length - 1] == 0) {
								flag = false;
								break;
							}
						}
						for (int k = j + length - 1; k >= j + 1; k--) {
							if (k>(range-1)||matrix[i + length - 1][k] == 0) {
								flag = false;
								break;
							}
						}
						for (int k = i + length - 1; k >= i + 1; k--) {
							if (k>(row-1)||matrix[k][j] == 0) {
								flag = false;
								break;
							}
						}


					}
					length--;
					int area = length*length;
					max = max > area ? max : area;
				}
			}
		}
		return max;

	}
};

int t221main() {
	vector<vector<int>> test;
	vector<int> t1{1,0,1,0,0};
	vector<int> t2{ 1,0,1,1,1 };
	vector<int> t3{ 1,1,1,1,1};
	vector<int> t4{ 1,0,1,1,1 };
	test.push_back(t1);
	test.push_back(t2);
	test.push_back(t3);
	test.push_back(t4);
	Solution221 s = Solution221();
	cout << s.maximalSquare(test);


	
	
	cin.get();

	return 0;
}