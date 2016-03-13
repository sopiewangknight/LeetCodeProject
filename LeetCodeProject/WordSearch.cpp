#include<vector>
#include<stack>
#include<iostream>
#include<string>


using namespace std;
struct position {
	int i, j, p;

};
class Solution79 {
public:
	bool exist(vector<vector<char>>& board, string word) {
		stack<position> pstack;
		


	}

	bool findPosition(vector<vector<char>>& board, char c,stack<position>& pstack,int k) {
		bool flag = false;
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++) {
				if (board[i][j] == c)
				{
					struct position p = {i,j,k};
					pstack.push(p);
					flag = true;
				}
			}
		}
		return flag;

	}

	int recursivePath(int m, int n) {
		if (m == n&&m == 1)return 1;
		if (m == 0 || n == 0)return 0;
		return recursivePath(m - 1, n) + recursivePath(m, n - 1);
	}

	int uniquePath2(vector<vector<int>>& obstacleGrid) {
		if (obstacleGrid[0][0] == 1)return 0;

		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		int** p;
		p = new int*[m];
		for (int i = 0; i < m; i++)p[i] = new int[n];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				p[i][j] = 0;
			}

		}
		p[0][0] = 1;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (i == 0 && j == 0) continue;

				if (obstacleGrid[i][j] == 0) {
					if (i - 1 >= 0)p[i][j] +=  p[i - 1][j];
					if (j - 1 >= 0)p[i][j] += p[i][j - 1];

				}
				
			}
		}
		return p[m - 1][n - 1];

	}
	int uniquePath(int m, int n) {
		int** p;
		p = new int*[m];
		for (int i = 0; i < m; i++)p[i] = new int[n];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				p[i][j] = 0;
			}
			
		}
		for (int i = 0; i < n; i++) {
			p[0][i] = 1;

		}
		for (int i = 1; i < m; i++) {
			p[i][0] = 1;
		}
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				p[i][j] = p[i - 1][j] + p[i][j - 1] ;
			}
		}

		
		
		

		return p[m-1][n-1];

	}
};

int t_main()
{
	Solution79 s = Solution79();
	//cout<<s.uniquePath(10,3);

	cout << s.recursivePath(10, 3);
	cin.get();
	return 0;
		
}
