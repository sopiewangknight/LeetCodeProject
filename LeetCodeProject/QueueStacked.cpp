#include<stack>
#include<iostream>
#include<queue>
using namespace std;

class CStack {
public:
	void push(int value);
	int pop();
private:
	queue<int> data;
	queue<int> exchange;
};
void CStack::push(int value) {
	data.push(value);
}

int CStack::pop() {
	if (data.empty())return -1;
	int tmp;
	while (!data.empty()) {
		tmp = data.front();
		exchange.push(tmp);
		data.pop();
	}
	tmp = exchange.front();
	exchange.pop();
	int ex;
	while (!exchange.empty()) {
		ex = exchange.front();
		data.push(ex);
		exchange.pop();
	}
	return tmp;
}


class CQueue {
public:
	void appendTail(int value);
	int deleteHead();
private:
	stack<int> input;
	stack<int> output;
};

void CQueue::appendTail(int value) {
	input.push(value);
}

int CQueue::deleteHead() {
	if (output.empty()) {
		int tmp;
		if (input.empty()) {
			return -1;
		}
		else {
			while (!input.empty()) {
				tmp = input.top();
				input.pop();
				output.push(tmp);
			}
			int res = output.top();
			output.pop();
			return res;
		}
	}
	else {
		int res = output.top();
		output.pop();
		return res;
	}
}

int stack_main() {
	CStack s = CStack();
	s.push(1);
	s.push(2);
	cout << s.pop() << " ";
	s.push(3);
	s.push(4);
	cout << s.pop() << " ";
	cout << s.pop() << " ";
	cout << s.pop() << " ";


	cin.get();
	return 0;

}