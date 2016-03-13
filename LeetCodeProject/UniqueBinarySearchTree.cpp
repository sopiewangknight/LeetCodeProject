#include<vector>

using namespace std;
class Solution {
public:
	int numTrees(int n) {
		vector<int> fn(n + 1, 0);
		fn[0] = 1;
		fn[1] = 1;
		fn[2] = 2;
		for (int i = 3; i <= n; i++) {
			int sum = 0;
			for (int j = 0; j <= i - 1; j++) {
				sum += fn[j] * fn[i - 1 - j];
			}
			fn[i] = sum;
		}
		return fn[n];
	}
};