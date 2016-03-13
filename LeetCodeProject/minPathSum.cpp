#include<vector>
#include<iostream>
using namespace std;
class Solution64 {
public:
	int minPathSum(vector<vector<int>>& grid) {
		vector<vector<int>> minPath = grid;
		int row = grid.size();
		int range =grid[0].size();
		int sum = grid[0][0];
		for (int i = 1; i < row; i++) {
			sum += grid[i][0];
			minPath[i][0] = sum;
		}
		sum = grid[0][0];
		for (int i = 1; i < range; i++) {
			sum += grid[0][i];
			minPath[0][i] = sum;
		}
		for (int i = 1; i < row; i++) {
			for (int j = 1; j < range; j++) {
				minPath[i][j] = minPath[i - 1][j] < minPath[i][j - 1] ? (minPath[i - 1][j] + grid[i][j]) : (minPath[i][j - 1] + grid[i][j]);
			}
		}

		return minPath[row - 1][range - 1];

	}
};

int t64_main()
{
	vector<int> t = { 1,2,3 };
	vector<vector<int>> test;
	test.push_back(t);
	t = { 4,5,6 };
	test.push_back(t);
	Solution64 s = Solution64();
	cout << s.minPathSum(test);


	cin.get();
	return 0;
}

