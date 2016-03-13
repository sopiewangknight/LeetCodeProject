#include<string>
#include<vector>
#include<iostream>
#include<sstream>

using namespace std;
class Solution228 {
public:
	vector<string> summerrange(vector<int>& nums) {

		vector<string> result;
		stringstream strstream;
		
		vector<int>::iterator it;
		if (nums.size() == 0)return result;
		if (nums.size() == 1) {
			it = nums.begin();
			strstream << *it;
			string s = strstream.str();
			strstream.str("");
			result.push_back(s);
			return result;

		}
	
		int begin, tmp;
		begin = tmp = *nums.begin();
		for (it = nums.begin()+1; it != nums.end(); it++) {
			if (*it != tmp+1)
			{
				if (begin != tmp)
				{
					strstream << begin << "->" << tmp;
					string s = strstream.str();
					strstream.str("");

					result.push_back(s);

				}
				else {
					strstream << begin ;
					string s = strstream.str();
					strstream.str("");

					result.push_back(s);
			
				}
				begin = *it;
				tmp = *it;
			}
			else {
				tmp = *it;
			}

		}

		if (begin != tmp)
		{
			strstream << begin << "->" << tmp;
			string s = strstream.str();
			strstream.str("");

			result.push_back(s);

		}
		else {
			strstream << begin ;
			string s = strstream.str();
			strstream.str("");

			result.push_back(s);
		}

		return result;
	}
};

int tt_main() {
	Solution228 s =  Solution228();
	int arraynums[] = {0,2,3,4,6,7,8,9,22,24,26,27,28,30};
	size_t count = sizeof(arraynums) / sizeof(int);
	vector<int> nums(arraynums, arraynums + count);


	vector<string> res;
	res=s.summerrange(nums);

	vector<string>::iterator i;
	for (i = res.begin(); i != res.end(); i++) {
		cout << *i << endl;
	}
	
	cin.get();
	return 0;
}