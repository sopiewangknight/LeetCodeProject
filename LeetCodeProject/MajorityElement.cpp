#include<vector>
#include<iostream>

using namespace std;
class Solution169 {
public:
	int majorityElement(vector<int>& nums) {
		
		int res = middlenum(nums, 0, nums.size() - 1, nums.size() / 2);
		
		return res;
	}
	vector<int> majorityElement2(vector<int>& nums) {
		vector<int> res;
		if (nums.size() == 0)return res;
		if (nums.size() <= 2) {
			for (int i = 0; i < nums.size(); i++) {
				res.push_back(nums[i]);
			}
			return res;
		}
		int num1 = nums[0];
		int num2 = 0;

		int c1 = 1;
		int c2 = 0;

		for (int i = 1; i < nums.size(); i++) {
			int x = nums[i];
			if (x == num1)c1++;
			else if (x == num2)c2++;
			else if (c1 == 0) {
				num1 = x;
				c1++;
			}
			else if (c2 == 0) {
				num2 = x;
				c2++;
			}
			else {
				c1--;
				c2--;
			}
		}

		c1 = 0;
		c2 = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] == num1)c1++;
			else if (nums[i] == num2)c2++;
		}
		if (c1 > nums.size() / 3)res.push_back(num1);
		if (c2 > nums.size() / 3)res.push_back(num2);
		return res;


	}


	int moreThanHalf(vector<int>& nums) {
		int res, count;
		res = nums[0];
		count = 1;
		for (int i = 1; i < nums.size(); i++) {
			if (nums[i]==res)
			{
				count++;
			}
			else {
				if (count>1)
				{
					count--;

				}
				else {
					res = nums[i];
					count = 1;
				}
			}
		}
		return res;

	}

	int middlenum(vector<int>& arr, int begin,int end,int k) {
		int q = partition(arr, begin, end);
		if (q == k)return arr[k];
		if (q < k) {
			middlenum(arr, q+1, end, k );
		}
		else {
			middlenum(arr, begin, q, k);
		}
	}
	void quicksort(vector<int>& arr,int begin,int end) {

		if (begin<end)
		{
			int q = partition(arr, begin,end);
				quicksort(arr, begin, q - 1);
				quicksort(arr, q + 1, end);
		}
		

	}

	int partition(vector<int>& arr,int begin,int end) {

		int tmp ;
		int i = begin + 1;
		int first = arr[begin];
		int flag = i;
		for (; i <= end; i++)
		{
			if (arr[i] <= first) 
			{
				tmp = arr[i];
				arr[i] = arr[flag];
				arr[flag] = tmp;
				flag++;
			}
		}
		tmp = first;
		arr[begin] = arr[flag-1];
		arr[flag-1 ] = tmp;
		return flag-1 ;
	}
};

int t6_main()
{
	int arraynums[] = { 
		
2,2,		47,47,72,47,72,47,79,47,12,92,13,47,47,83,33,15,18,47,47,47,47,64,47,65,47,47,47,47,70,47,47,55,47,15,60,47,47,47,47,47,46,30,58,59,47,47,47,47,47,90,64,37,20,47,100,84,47,47,47,47,47,89,47,36,47,60,47,18,47,34,47,47,47,47,47,22,47,54,30,11,47,47,86,47,55,40,49,34,19,67,16,47,36,47,41,19,80,47,47,27
	};
	size_t count = sizeof(arraynums) / sizeof(int);
	vector<int> nums(arraynums, arraynums+ count);

	Solution169 s = Solution169();
/*	cout<<s.partition(nums, 0, 1)<<endl;

	s.quicksort(nums, 0, nums.size()-1);
	for (int i = 0; i < nums.size(); i++) {
		cout << nums[i] << "  ";
	}*/
	//cout << s.majorityElement(nums);
	cout << s.moreThanHalf(nums);


	
	cin.get();
	return 0;
}