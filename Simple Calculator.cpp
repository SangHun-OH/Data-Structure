#include <iostream>
#include <string>

using namespace std;

template <typename T>
class MyStack {
private:
	T* data;
	int pos;
	int capacity;

	void extends() {
		T* temp = new T[capacity *= 2];
		for (int i = 0; i < pos; i++)
			temp[i] = data[i];
		delete[] data;
		data = temp;
	}

public:
	MyStack() : capacity(10), pos(0) {
		data = new T[capacity];
	}

	~MyStack() {
		delete[] data;
	}

	void push(T t) {
		if (pos == capacity) extends();
		data[pos++] = t;
	}

	T pop() { return data[--pos]; }

	T peek() { return data[pos - 1]; }

	bool isEmpty() { return !pos; }
};

char operPriority(char ch) {
	if (ch == '(') return 0;
	else if (ch == '+' || ch == '-') return 1;
	else if (ch == '*' || ch == '/') return 3;
	return 5;
}

string toPostFix(const string& infix) {
	string ret = "";
	MyStack<char> s;

	for (int i = 0; infix[i]; i++) {
		char ch = infix[i];
		if ('0' <= ch && ch <= '9') {
			ret.push_back(infix[i]);
			ret.push_back(' ');
		}
		else {
			if (ch == '(') s.push(ch);
			else if (ch == ')') {
				char top;
				while ((top = s.pop()) != '(') {
					ret.push_back(top);
					ret.push_back(' ');
				}
			}
			else {
				while (!s.isEmpty() && operPriority(s.peek()) > operPriority(ch)) {
					ret.push_back(s.pop());
					ret.push_back(' ');
				}
				s.push(ch);
			}
		}
	}

	while (!s.isEmpty()) {
		ret.push_back(s.pop());
		ret.push_back(' ');
	}
	return ret;
}

int calcPostFix(const string& postfix) {
	MyStack<int> s;
	for (int i = 0; postfix[i]; i++) {
		char ch = postfix[i];
		if (ch == ' ') continue;

		if ('0' <= ch && ch <= '9') s.push(ch - '0');
		else {
			int opnd2 = s.pop();
			int opnd1 = s.pop();

			if (ch == '+') s.push(opnd1 + opnd2);
			else if (ch == '-') s.push(opnd1 - opnd2);
			else if (ch == '*') s.push(opnd1 * opnd2);
			else if (ch == '/') s.push(opnd1 / opnd2);
		}
	}

	return s.pop();
}

int main()
{
	while (true) {
		string line; cin >> line;
		if (line.find('.') != -1) break;
		string post = toPostFix(line);
		cout << post << endl;
		cout << calcPostFix(post) << endl;
	}

	return 0;
}