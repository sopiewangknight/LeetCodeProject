#include<vector>
using namespace std;


class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		vector<vector<int>> minTotal = triangle;
		
		for (int i = 1; i < triangle.size(); i++) 
		{
			for (int j = 0; j < triangle[i].size(); j++)
			{
				int left = j - 1 >= 0 && j - 1 < minTotal[i - 1].size() ? minTotal[i - 1][j - 1] : INT16_MAX;
				int right = j >= 0 && j < minTotal[i - 1].size() ? minTotal[i - 1][j] : INT16_MAX;
				int min = left < right ? left : right;
				minTotal[i][j] = min+triangle[i][j];
			}
		}
		int res = INT16_MAX;
		for (int i = 0; i < minTotal[minTotal.size() - 1].size(); i++)
		{
			if (minTotal[minTotal.size()-1][i]<res)
			{
				res = minTotal[minTotal.size() - 1][i];
			}
		}
		return res;



	}
};