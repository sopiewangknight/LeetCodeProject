#include<vector>
#include<iostream>

using namespace std;

class Solution118 {
public:
	vector<vector<int>> generate(int numrows) {
		vector<vector<int>> res;

		vector<int> top = { 1 };

		
		res.push_back(top);
		if (numrows <= 0) {
			return res;
		}
		for (int i = 1; i < numrows; i++)
		{
			vector<int> tmp;
			int size = res.size();
			vector<int> last = res[size - 1];
			for (int j = 0; j < i+1; j++)
			{
				if (j == 0||j==i)
				{
					tmp.push_back(1);
				}
				else {
					tmp.push_back(last[j - 1] + last[j]);
				}
			}
			res.push_back(tmp);
		}
		return res;
	}
};

int t4_main() {
	Solution118 s = Solution118();
	vector<vector<int>> res = s.generate(6);

	cin.get();
	return 0;
}