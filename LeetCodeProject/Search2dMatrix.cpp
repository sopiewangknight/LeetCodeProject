#include<vector>

using namespace std;

class Solution74 {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.size() == 0)return false;

		int row = matrix.size();
		int range = matrix[0].size();

		if (target > matrix[row - 1][range - 1])return false;
		int begin = 0;
		int end = row - 1;
		int mid;
		while (begin <= end) {
			mid = (begin + end) / 2;
			if (matrix[mid][range - 1] == target)return true;
			if (matrix[mid][range - 1] > target && (mid - 1 < 0 || target > matrix[mid - 1][range - 1]))
				break;
			if (matrix[mid][range - 1] > target) {
				end = mid - 1;
			}
			else {
				begin = mid + 1;
			}
		}

		begin = 0;
		end = range - 1;
		int rmid;
		while (begin <= end) 
		{
			rmid = (begin + end) / 2;
			if (matrix[mid][rmid] == target)return true;
			if (matrix[mid][rmid] < target) {
				begin = rmid + 1;
			}
			else {
				end = rmid - 1;
			}
		}
		return false;
	}
};
