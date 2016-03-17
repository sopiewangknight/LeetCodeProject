#include<vector>
#include<string>
#include<stack>
#include<iostream>
using namespace std;

struct state {
	char value;
	int x;
	int y;
	int next;
	state(char val, int xx, int yy, int nex) :value(val), x(xx), y(yy), next(nex) {};
};

class Solution79 {
public:
	bool exist(vector<vector<char>>& board, string word) {

		int row = board.size();
		int range = board[0].size();
		stack<state> sstack;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < range; j++) {

				if (board[i][j] == word[0]) {
					char tmpChar = word[0];
					 state first(tmpChar, i,j,0);
					sstack.push(first);
					board[sstack.top().x][sstack.top().y] = '*';
					int wordIndex = 0;

					while (!sstack.empty()) {

						if (sstack.top().next == 0) {
							if ((sstack.top().x - 1) < 0) {
								sstack.top().next = 1;
								continue;
							}


							if (board[sstack.top().x - 1][sstack.top().y] == word[wordIndex + 1]) {
								struct state top(word[wordIndex + 1], sstack.top().x - 1, sstack.top().y,  0);
								sstack.push(top);
								board[sstack.top().x][sstack.top().y] = '*';
								wordIndex++;

								if (wordIndex == (word.size()-1)) {
									return true;
								}


							}
							else {
								sstack.top().next = 1;
								continue;
							}

						}
						if (sstack.top().next == 1)
						{
							if ((sstack.top().y +1) >= range) {
								sstack.top().next = 2;
								continue;
							}


							if (board[sstack.top().x ][sstack.top().y+1] == word[wordIndex + 1]) {
								struct state top(word[wordIndex + 1], sstack.top().x , sstack.top().y+1,  0);
								sstack.push(top);
								board[sstack.top().x ][sstack.top().y] = '*';
								wordIndex++;

								if (wordIndex == (word.size()-1)) {
									return true;
								}
							}
							else {
								sstack.top().next = 2;
								continue;
							}
						}

						if (sstack.top().next == 2)
						{
							if ((sstack.top().x + 1) >=row) {
								sstack.top().next = 3;
								continue;
							}


							if (board[sstack.top().x+1][sstack.top().y ] == word[wordIndex + 1]) {
								struct state top(word[wordIndex + 1], sstack.top().x+1, sstack.top().y ,  0);
								sstack.push(top);
								board[sstack.top().x ][sstack.top().y] = '*';
								wordIndex++;


								if (wordIndex == (word.size()-1)) {
									return true;
								}
							}
							else {
								sstack.top().next = 3;
								continue;
							}
						}


						if (sstack.top().next == 3)
						{
							if ((sstack.top().x - 1) < 0) {
								sstack.top().next = 4;
								continue;
							}

							if (board[sstack.top().x - 1][sstack.top().y] == word[wordIndex + 1]) {
								struct state top(word[wordIndex + 1], sstack.top().x - 1, sstack.top().y,  0);
								sstack.push(top);
								board[sstack.top().x ][sstack.top().y] = '*';
								wordIndex++;

								if (wordIndex == word.size()) {
									return true;
								}
							}
							else {
								sstack.top().next = 4;
								continue;
							}
						}

						if (sstack.top().next == 4) {
							wordIndex--;
							board[sstack.top().x][sstack.top().y] = sstack.top().value;
							sstack.pop();
						}

					}
				
				}
			}
		}
		return false;
	};


		bool exist2(vector<vector<char>>& board, string word) {

			int row = board.size();
			int range = board[0].size();
			stack<state> sstack;
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < range; j++) {

					if (board[i][j] == word[0]) {

						state first(word[0], i, j, 0);

						sstack.push(first);
						board[sstack.top().x][sstack.top().y] = '*';
						int wordIndex = 0;  //wordIndex ��ʾ��ǰƥ��õ�λ��

						while (!sstack.empty()) {

							if (sstack.top().next == 0) {
								if ((sstack.top().x - 1) < 0) {
									sstack.top().next = 1;
									continue;
								}


								if (board[sstack.top().x - 1][sstack.top().y] == word[wordIndex + 1]) {
									struct state top(word[wordIndex + 1], sstack.top().x - 1, sstack.top().y, 0);
									//struct state top(sstack.top().x - 1, sstack.top().y, word[wordIndex + 1], 0);
									sstack.push(top);
									board[sstack.top().x][sstack.top().y] = '*';
									//board[sstack.top().x - 1][sstack.top().y] = '*';
									wordIndex++;

									if (wordIndex == word.size() - 1) {
										//if (wordIndex == word.size()) {
										return true;
									} // wordIndex == word.size() ?  ����ζ��41�е�if�����У�wordIndex ������word.size()-1��cool~~����


								}
								else {
									sstack.top().next = 1;
									continue;
								}

							}
							if (sstack.top().next == 1)
							{
								if ((sstack.top().y + 1) >= range) {
									sstack.top().next = 2;
									continue;
								}


								if (board[sstack.top().x][sstack.top().y + 1] == word[wordIndex + 1]) {
									struct state top(word[wordIndex + 1], sstack.top().x, sstack.top().y + 1, 0);
									sstack.push(top);

									board[sstack.top().x][sstack.top().y] = '*';
									//board[sstack.top().x ][sstack.top().y+1] = '*';
									wordIndex++;

									if (wordIndex == word.size() - 1) {
										//if (wordIndex == word.size()) {
										return true;
									}
								}
								else {
									sstack.top().next = 2;
									continue;
								}
							}

							if (sstack.top().next == 2)
							{
								if ((sstack.top().x + 1) >= row) {
									sstack.top().next = 3;
									continue;
								}


								if (board[sstack.top().x + 1][sstack.top().y] == word[wordIndex + 1]) {
									struct state top(word[wordIndex + 1], sstack.top().x + 1, sstack.top().y, 0);
									sstack.push(top);

									board[sstack.top().x][sstack.top().y] = '*';
									//board[sstack.top().x + 1][sstack.top().y] = '*';
									wordIndex++;


									if (wordIndex == word.size() - 1) {
										return true;
									}
								}
								else {
									sstack.top().next = 3;
									continue;
								}
							}

							if (sstack.top().next == 3)
							{
								if ((sstack.top().y - 1) < 0) {
									sstack.top().next = 4;
									continue;
								}

								if (board[sstack.top().x][sstack.top().y - 1] == word[wordIndex + 1]) {
									struct state top(word[wordIndex + 1], sstack.top().x, sstack.top().y - 1, 0);
									sstack.push(top);
									board[sstack.top().x][sstack.top().y] = '*';
									wordIndex++;

									if (wordIndex == word.size() - 1) {
										//if (wordIndex == word.size()) {
										return true;
									}
								}
								/*if ((sstack.top().x - 1) < 0) {
								sstack.top().next = 4;
								continue;
								}

								if (board[sstack.top().x - 1][sstack.top().y] == word[wordIndex + 1]) {
								struct state top(sstack.top().x - 1, sstack.top().y, word[wordIndex + 1], 0);
								sstack.push(top);
								board[sstack.top().x - 1][sstack.top().y] = '*';
								wordIndex++;

								if ( wordIndex == word.size()-1 ) {
								//if (wordIndex == word.size()) {
								return true;
								}
								}*/
								else {
									sstack.top().next = 4;
									continue;
								}
							}

							if (sstack.top().next == 4) {
								wordIndex--;
								board[sstack.top().x][sstack.top().y] = sstack.top().value;
								sstack.pop();
								if (!sstack.empty()) {    //û��������ѭ��
									sstack.top().next++;
								}
							}

						}

						//return false; ����Ϊʲô���÷�������

					}

				}
			}

			return false;

		};



 };


int t79main() {
	Solution79 s = Solution79();
	vector<char> t1{ 'A','B','C','E' };
	vector<char> t2{ 'S','F','C','S' };
	vector<char> t3{ 'A','D','E','E' };
	vector<vector<char>> ts;
	ts.push_back(t1);
	ts.push_back(t2);
	ts.push_back(t3);
	cout<<s.exist2(ts, "SEE");


	cin.get();
	return 0;

}