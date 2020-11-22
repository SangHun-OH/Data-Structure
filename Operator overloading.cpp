#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

using namespace std;

class Save // 입력받은 수를 저장하는 클래스
{
public:
	float coef;
	int exp;
	int c_term;
};

class Node // 노드를 추가할때 사용하는 클래스
{

public:
	Save* data;
	Node* next;

	Node()
	{
		next = NULL;
		data = new Save;
	}
};

class Polynomial // 다항식 클래스 선언
{
private:
	Node* begin;
	Node* end;
	Node* poly;

public:
	Polynomial()
	{
		begin = NULL; // 시작부분
		end = NULL; // 끝부분
		poly = NULL; // 다항식 포인터
	}

	void newnode(float, int);
	void input_Poly();
	void show();
	void PlusPoly(Polynomial, Polynomial);
	void MultPoly(Polynomial, Polynomial);
	void evalPoly(float);
};

void Polynomial::newnode(float coef, int exp) // 노드 추가 함수
{
	if (begin == NULL)
	{
		begin = new Node;
		end = begin;
		begin->data->coef = coef;
		begin->data->exp = exp;
	}
	else
	{
		poly = new Node;
		end->next = poly;
		end = poly;

		poly->data->coef = coef;
		poly->data->exp = exp;
	}
}

void Polynomial::input_Poly() // 1. 다항식 입력
{
	int exp, before_exp = 1000; // 입력된 지수를 저장하기 위한 변수
	float coef = 0;

	while (1) { 
		while (1) {  // 계수 및 지수 입력
			cout << "계수 지수 : ";
			cin >> coef >> exp;
			if (cin.fail()) {
				cout << " 재확인" << endl << endl;
				cin.clear();
				cin.ignore(256, '\n');
				continue;
			}
			if (cin.fail() /*|| before_exp <= exp*/ || exp < 0)
			{
				cout << "재확인" << endl << endl;
				cin.clear();
				cin.ignore(256, '\n');
				continue;
			}
			else break;
		}
		if (coef != 0) newnode(coef, exp); // 노드 추가 함수 호출
		if (exp == 0) break; // 지수가 0 이면 더이상 추가하지 않음.
		// 꼭 지수가 0이여야 종료되기에 문제가 있습니다.
	}
}

void Polynomial::show() // 2. 다항식 출력
{
	poly = begin;
	int count = 0;
	while (1)
	{
		if (poly->data->exp == 0)  // 1x^1 을 x로 출력하기 위한 처리
			cout << poly->data->coef;
		else if (poly->data->coef == 1)
			cout << "";
		else
			cout << poly->data->coef;

		if (poly->data->exp == 1)
			cout << "x";
		else if (poly->data->exp == 0)
			cout << " ";
		else
			cout << "x" << "^" << poly->data->exp;

		count++;

		if (poly->next == NULL) // 노드가 끝이라면 종료
			break;
		cout << " + ";
		poly = poly->next; 
	}
	begin->data->c_term = count;
}

void Polynomial::PlusPoly(Polynomial f, Polynomial s) // 3. 다항식의 덧셈

{
	f.poly = f.begin;
	s.poly = s.begin;
	float sum = 0;
	int f_terms = f.begin->data->c_term; // 1번 다항식의 항 수
	int s_terms = s.begin->data->c_term; // 2번 다항식의 항 수

	while (f_terms != 0 && s_terms != 0) { // 모든 항을 확인하도록 하는 코드
		if (f.poly->data->exp == s.poly->data->exp) { // 다항식이 동일하다면 덧셈
			sum = f.poly->data->coef + s.poly->data->coef;
			if (sum != 0)
				this->newnode(sum, f.poly->data->exp);
			if (--f_terms > 0) { // 1번 다음 항으로 이동
				f.poly = f.poly->next;
			}
			if (--s_terms > 0) { // 2번 다음 항으로 이동
				s.poly = s.poly->next;;
			}
		}
		else if (f.poly->data->exp > s.poly->data->exp) { // 1번의 지수 값이 더 클 경우
			this->newnode(f.poly->data->coef, f.poly->data->exp);
			if (--f_terms > 0) {
				f.poly = f.poly->next;
			}
		}
		else if (f.poly->data->exp < s.poly->data->exp) { // 2번의 지수 값이 더 클 경우
			this->newnode(s.poly->data->coef, s.poly->data->exp);
			if (--s_terms > 0)
			{
				s.poly = s.poly->next;
			}
		}
	}

	if (f_terms == 0)  // 1번에 남은 항이 없을 경우
	{
		while (s_terms)
		{
			this->newnode(s.poly->data->coef, s.poly->data->exp);
			if (--s_terms > 0) {
				s.poly = s.poly->next;
			}
		}
	}
	else if (s_terms == 0) {
		while (f_terms) {
			this->newnode(f.poly->data->coef, f.poly->data->exp);
			if (--f_terms > 0) {
				f.poly = f.poly->next;
			}
		}
	}
}

void Polynomial::MultPoly(Polynomial f, Polynomial s) // 5. 다항식의 곱셈
{
	f.poly = f.begin;
	s.poly = s.begin;

	bool flag = true;
	float coef_mult = 0;
	int exp_sum = 0;
	int s_count = 0;
	int f_term = f.begin->data->c_term; //1번 다항식 항수
	int s_term = s.begin->data->c_term; //2번 다항식 항수

	while (f_term != 0) {      // 1번식 항이 남은지 확인 
		while (s_term != 0) {  // 2번식 항이 남은지 확인
			coef_mult = f.poly->data->coef * s.poly->data->coef; // 계수곱
			exp_sum = f.poly->data->exp + s.poly->data->exp; // 지수합
			this->poly = this->begin; 

			if (s_count > 0) { // 항끼리 연살결과가 있는지 확인
				while (1) {
					if (exp_sum == this->poly->data->exp) { 
						this->poly->data->coef += coef_mult;
						flag = false;
					}
					if (this->poly->next == NULL)
						break;
					this->poly = this->poly->next;
				}
			}
			if (flag) { // 결과와 방금 연산된 지수의 합과 같은 것이 없으면 동작
				this->newnode(coef_mult, exp_sum);
				s_count++;
			}
			flag = true;
			if (--s_term > 0) {
				s.poly = s.poly->next;
			}
		}
		s.poly = s.begin;
		s_term = s.begin->data->c_term;
		if (--f_term > 0) {
			f.poly = f.poly->next;
		}
	}
}

void Polynomial::evalPoly(float x) // 6. 다항식의 값 계산

{
	poly = begin;
	float eval_val = 1;
	float total_val = 0;
	while (1) {
		for (int i = 0; i < poly->data->exp; i++) {
			if (poly->data->exp > 0) eval_val *= x;
			else if (poly->data->exp < 0) eval_val /= x;
		}

		eval_val *= poly->data->coef;
		if (poly->next == NULL) {
			total_val += eval_val;
			break;
		}
		else poly = poly->next;
		total_val += eval_val;
		eval_val = 1;
	}
	cout << " x = " << x << " --> " << total_val << endl;
}

int main()
{
	Polynomial poly_1;
	Polynomial poly_2;
	Polynomial poly_3;
	Polynomial sum;
	Polynomial mult;

	float x = 0;
	cout << "A(x)" << endl;
	poly_1.input_Poly();
	cout << endl << "A(x) = ";
	poly_1.show();

	cout << endl << endl << "B(x)" << endl;
	poly_2.input_Poly();
	cout << endl << "B(x) = ";
	poly_2.show();

	mult.MultPoly(poly_1, poly_2);
	
	cout << endl << endl << "C(x)" << endl;
	poly_3.input_Poly();

	cout << endl << "C(x) = ";
	poly_3.show();
	
	cout << endl << endl << "T(x) = ";
	mult.show();
	
	sum.PlusPoly(mult, poly_3);
	cout << endl << endl << "D(x) = ";
	sum.show();

	while (1){
		cout << endl << endl;
		cout << "x = ";
		cin >> x;

		if (cin.fail()){
			cout << "재입력" << endl << endl;
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}
		else break;
	}
	sum.evalPoly(x);
}