#include<vector>
#include<iostream>

using namespace std;
class Solution54 {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> res;
		if (matrix.size() == 0)return res;

		int row = matrix.size();
		int range = matrix[0].size();

		int m = row;
		int n = range;

		int i = 0;
		while (m > 0 && n > 0) {
			if (m > 1 && n > 1) {
				for (int j = i; j <= i + n - 1; j++) {
					res.push_back(matrix[i][j]);
				}
				for (int j = i + 1; j <= i + m - 1 - 1; j++) {
					res.push_back(matrix[j][i + n - 1]);
				}
				for (int j = i + n - 1; j >= i; j--) {
					res.push_back(matrix[i + m - 1][j]);
				}
				for (int j = i + m - 1 - 1; j >= i + 1; j--) {
					res.push_back(matrix[j][i]);
				}
				m -= 2;
				n -= 2;
			}
			else if (m == 1 && n == 1) {

				res.push_back(matrix[i][i]);

				m -= 1;
				n -= 1;
			}
			else if (m == 1 && n > 1) {

				for (int j = i; j <= i + n - 1; j++) {
					res.push_back(matrix[i][j]);
				}

				m -= 1;
				n -= n;
			}
			else {

				for (int j = i; j <= i + m - 1; j++) {
					res.push_back(matrix[j][i]);
				}

				n -= 1;
				m -= m;
			}

			i++;
		}
		return res;

	}

	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> res(n);
		for (int i = 0; i < n; i++) {
			res[i].resize(n);
		}


		int count = 1;
		int m = n;

		int i = 0;
		while (m > 0 && n > 0) {
			if (m > 1 && n > 1) {
				for (int j = i; j <= i + n - 1; j++) {
					res[i][j]=count++;
				}
				for (int j = i + 1; j <= i + m - 1 - 1; j++) {
					res[j][i + n - 1]=count++;
				}
				for (int j = i + n - 1; j >= i; j--) {
					res[i + m - 1][j]=count++;
				}
				for (int j = i + m - 1 - 1; j >= i + 1; j--) {
					res[j][i]=count++;
				}
				m -= 2;
				n -= 2;
			}
			else if (m == 1 && n == 1) {

				res[i][i]=count++;

				m -= 1;
				n -= 1;
			}
			else if (m == 1 && n > 1) {

				for (int j = i; j <= i + n - 1; j++) {
					res[i][j]=count++;
				}

				m -= 1;
				n -= n;
			}
			else {

				for (int j = i; j <= i + m - 1; j++) {
					res[j][i]=count++;
				}

				n -= 1;
				m -= m;
			}

			i++;
		}
		return res;

	}


};


