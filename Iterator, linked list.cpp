#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Node {
	int c = -1, e = -1;
	Node* next;
};

class Polynomial_Iterator { // 반복자 구현
private:
	Node* cur;
public:
	Polynomial_Iterator(Node* ptr) {
		cur = ptr;
	}

	Polynomial_Iterator& operator++() {
		cur = cur->next;
		return *this;
	}

	Node& operator*() {
		return *cur;
	}

	Node* operator->() {
		return cur;
	}

	bool operator==(Polynomial_Iterator rhs) {
		return cur == rhs.cur;
	}

	bool operator!=(Polynomial_Iterator rhs) {
		return cur != rhs.cur;
	}
};

class Polynomial {
private:
	Node* head;


public:
	friend istream& operator>>(istream&, Polynomial&);
	friend ostream& operator<<(ostream&, Polynomial&);

	Polynomial() {
		head = new Node();
		head->next = head;
	}

	~Polynomial() {
		for (Node* node = head; node != head; node = node->next) {
			delete node;
		}
	}

	Polynomial sMultPoly(int c, int e) {
		if (begin() == end()) return Polynomial();

		Polynomial rst;
		for (auto it = begin(); it != end(); ++it) {
			rst.insert(it->c * c, it->e + e);
		}
		return rst;
	}

	int evalPoly(int c) {
		if (begin() == end()) return 0;

		int rst = 0;
		for (auto it = begin(); it != end(); ++it) {
			int sub = it->c;
			for (int i = 0; i < it->e; i++) sub *= c;
			rst += sub;
		}
		return rst;
	}

	void insert(int c, int e) {
		Node* prev;
		for (prev = head; prev->next != head; prev = prev->next) {
			if (prev->next->e < e) break;
		}

		Node* next = prev->next;
		prev->next = new Node();
		prev->next->c = c;
		prev->next->e = e;
		prev->next->next = next;
	}

	Polynomial operator+(Polynomial rhs) {
		Polynomial result;
		auto lit = begin();
		auto rit = rhs.begin();
		while (1) {
			if (lit != end() && rit != rhs.end()) {
				if (lit->e == rit->e) {
					result.insert(lit->c + rit->c, lit->e);
					++lit;
					++rit;
				}
				else if (lit->e > rit->e) {
					result.insert(lit->c, lit->e);
					++lit;
				}
				else {
					result.insert(rit->c, rit->e);
					++rit;
				}
			}
			else if (lit != end()) {
				result.insert(lit->c, lit->e);
				++lit;
			}
			else if (rit != rhs.end()) {
				result.insert(rit->c, rit->e);
				++rit;
			}
			else break;
		}
		return result;
	}

	Polynomial operator*(Polynomial rhs) {
		Polynomial result;
		for (auto it = rhs.begin(); it != rhs.end(); ++it) {
			result = result + sMultPoly(it->c, it->e);
		}
		return result;
	}

	Polynomial_Iterator begin() {
		return ++Polynomial_Iterator(head);
	}

	Polynomial_Iterator end() {
		return Polynomial_Iterator(head);
	}


};

istream& operator>>(istream& in, Polynomial& poly) {
	string input;
	in >> input;
	for (int i = 0; i < input.size(); i += 5) {
		poly.insert(input[i + 1] - '0', input[i + 3] - '0');
	}
	return in;
}

ostream& operator<<(ostream& out, Polynomial& poly) {
	for (auto it = poly.begin(); it != poly.end(); ++it) {
		if (it != poly.begin()) out << '+';

		if (it->e > 1) {
			if (it->c > 1) out << it->c;
			out << "x^" << it->e;
		}
		else if (it->e == 1) {
			if (it->c > 1) out << it->c;
			out << "x";
		}
		else {
			out << it->c;
		}
	}
	return out;
}

int main() {
	while (1) {
		Polynomial a, b, c, t, d;
		int x;

		string str;
		getline(cin, str);
		if (str == ".") break;
		stringstream ss;
		ss.str(str);

		ss >> a >> b >> c >> x;

		t = a * b;
		d = t + c;

		cout << "A(x)= " << a << "\n";
		cout << "B(x)= " << b << "\n";
		cout << "C(x)= " << c << "\n";
		cout << "T(x)= " << t << "\n";
		cout << "D(x)= " << d << "\n";
		cout << "X=" << x << "-->" << d.evalPoly(x) << "\n";
	}

	return 0;
}