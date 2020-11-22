#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

using namespace std;

class Save // �Է¹��� ���� �����ϴ� Ŭ����
{
public:
	float coef;
	int exp;
	int c_term;
};

class Node // ��带 �߰��Ҷ� ����ϴ� Ŭ����
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

class Polynomial // ���׽� Ŭ���� ����
{
private:
	Node* begin;
	Node* end;
	Node* poly;

public:
	Polynomial()
	{
		begin = NULL; // ���ۺκ�
		end = NULL; // ���κ�
		poly = NULL; // ���׽� ������
	}

	void newnode(float, int);
	void input_Poly();
	void show();
	void PlusPoly(Polynomial, Polynomial);
	void MultPoly(Polynomial, Polynomial);
	void evalPoly(float);
};

void Polynomial::newnode(float coef, int exp) // ��� �߰� �Լ�
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

void Polynomial::input_Poly() // 1. ���׽� �Է�
{
	int exp, before_exp = 1000; // �Էµ� ������ �����ϱ� ���� ����
	float coef = 0;

	while (1) { 
		while (1) {  // ��� �� ���� �Է�
			cout << "��� ���� : ";
			cin >> coef >> exp;
			if (cin.fail()) {
				cout << " ��Ȯ��" << endl << endl;
				cin.clear();
				cin.ignore(256, '\n');
				continue;
			}
			if (cin.fail() /*|| before_exp <= exp*/ || exp < 0)
			{
				cout << "��Ȯ��" << endl << endl;
				cin.clear();
				cin.ignore(256, '\n');
				continue;
			}
			else break;
		}
		if (coef != 0) newnode(coef, exp); // ��� �߰� �Լ� ȣ��
		if (exp == 0) break; // ������ 0 �̸� ���̻� �߰����� ����.
		// �� ������ 0�̿��� ����Ǳ⿡ ������ �ֽ��ϴ�.
	}
}

void Polynomial::show() // 2. ���׽� ���
{
	poly = begin;
	int count = 0;
	while (1)
	{
		if (poly->data->exp == 0)  // 1x^1 �� x�� ����ϱ� ���� ó��
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

		if (poly->next == NULL) // ��尡 ���̶�� ����
			break;
		cout << " + ";
		poly = poly->next; 
	}
	begin->data->c_term = count;
}

void Polynomial::PlusPoly(Polynomial f, Polynomial s) // 3. ���׽��� ����

{
	f.poly = f.begin;
	s.poly = s.begin;
	float sum = 0;
	int f_terms = f.begin->data->c_term; // 1�� ���׽��� �� ��
	int s_terms = s.begin->data->c_term; // 2�� ���׽��� �� ��

	while (f_terms != 0 && s_terms != 0) { // ��� ���� Ȯ���ϵ��� �ϴ� �ڵ�
		if (f.poly->data->exp == s.poly->data->exp) { // ���׽��� �����ϴٸ� ����
			sum = f.poly->data->coef + s.poly->data->coef;
			if (sum != 0)
				this->newnode(sum, f.poly->data->exp);
			if (--f_terms > 0) { // 1�� ���� ������ �̵�
				f.poly = f.poly->next;
			}
			if (--s_terms > 0) { // 2�� ���� ������ �̵�
				s.poly = s.poly->next;;
			}
		}
		else if (f.poly->data->exp > s.poly->data->exp) { // 1���� ���� ���� �� Ŭ ���
			this->newnode(f.poly->data->coef, f.poly->data->exp);
			if (--f_terms > 0) {
				f.poly = f.poly->next;
			}
		}
		else if (f.poly->data->exp < s.poly->data->exp) { // 2���� ���� ���� �� Ŭ ���
			this->newnode(s.poly->data->coef, s.poly->data->exp);
			if (--s_terms > 0)
			{
				s.poly = s.poly->next;
			}
		}
	}

	if (f_terms == 0)  // 1���� ���� ���� ���� ���
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

void Polynomial::MultPoly(Polynomial f, Polynomial s) // 5. ���׽��� ����
{
	f.poly = f.begin;
	s.poly = s.begin;

	bool flag = true;
	float coef_mult = 0;
	int exp_sum = 0;
	int s_count = 0;
	int f_term = f.begin->data->c_term; //1�� ���׽� �׼�
	int s_term = s.begin->data->c_term; //2�� ���׽� �׼�

	while (f_term != 0) {      // 1���� ���� ������ Ȯ�� 
		while (s_term != 0) {  // 2���� ���� ������ Ȯ��
			coef_mult = f.poly->data->coef * s.poly->data->coef; // �����
			exp_sum = f.poly->data->exp + s.poly->data->exp; // ������
			this->poly = this->begin; 

			if (s_count > 0) { // �׳��� �������� �ִ��� Ȯ��
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
			if (flag) { // ����� ��� ����� ������ �հ� ���� ���� ������ ����
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

void Polynomial::evalPoly(float x) // 6. ���׽��� �� ���

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
			cout << "���Է�" << endl << endl;
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}
		else break;
	}
	sum.evalPoly(x);
}