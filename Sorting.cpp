#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include <iostream>
#include <string>
#include <algorithm>

#define R 1001

using namespace std;

char WordDataSet[R][R]; // ���� �����͸� ����ִ� 2���� �迭�Դϴ�.
char SaveData[R][R]; // Ư�����ڸ� ������ ���ڿ��� �־��ִ� �迭.

int BinarySearch(const char* b, int left, int right) {  // ��ȯ �̿�Ž�� �Լ�
	if (left <= right){
		int middle = (left + right) / 2;
		if (strcmp(b, SaveData[middle]) < 0)
			return BinarySearch(b, left, (middle - 1));
		else if (strcmp(b, SaveData[middle]) > 0)
			return BinarySearch(b, (middle + 1), right);
		else return middle + 1;
	}
	return -1; // ������� -1 ��ȯ (-1 ���)
}

int main() {

	FILE* f = fopen("input.txt", "r"); // ������ �б� �������� �޾��ݴϴ�. 

	if (f == NULL) printf("None file\n"); // ������ �������� ���� ��� ����ó���Դϴ�.

	int i = 0; //  ���� �����͵��� �ε����� ǥ���ϴ� �����Դϴ�.
	
	char c2 = 39; // ' ���ڵ� ������ �ֱ� ���ؼ� �ƽ�Ű �ڵ带 ���
	
	while (!feof(f)) {  // �ؽ�Ʈ���Ͽ��� ���ڿ��� �ް� Ư������ ���ֱ�
		fscanf(f, "%s", WordDataSet[i]); 

		string abc;

		for (int j = 0; j < strlen(WordDataSet[i]); j++) { // Ư�����ڰ� �ִٸ� �������ְ�, push_back�� ���� ������
			if (WordDataSet[i][j] != '?' && WordDataSet[i][j] != c2 && WordDataSet[i][j] != '.'
				&& WordDataSet[i][j] != '@' && WordDataSet[i][j] != '"' && WordDataSet[i][j] != '!'){
				abc.push_back(WordDataSet[i][j]);
			}
		}
		strcpy(WordDataSet[i],abc.c_str()); //abc�� �ִ� ���ڿ��� WordDataSet�� ����
		i++; // �ܾ��� ������ ǥ���ϴ� ��.
	}
	cout << "[�ܾ�����]" << endl;
	for (int m = 0; m < i; m++) {  // ��������

		for (int j = m + 1; j < i; j++) {
			if (strcmp(WordDataSet[m], WordDataSet[j]) > 0) {
				swap(WordDataSet[m], WordDataSet[j]);
			}
		}
		cout << m+1 << ". " << WordDataSet[m] << endl; // �������� ���
	}

	int k = 0;
	char* a = WordDataSet[0]; 
	strcpy(SaveData[0], a); 
	for (int j = 1; j < i; j++) { 
		if (strcmp(a, WordDataSet[j]) != 0) {
			k++;
			strcpy(SaveData[k], WordDataSet[j]);
			strcpy(a, WordDataSet[j]);
		}
	} // �ߺ��� ���� ����

	cout << "[�ߺ�����]" << endl;
	for (int v = 0; v < k+1; v++) { // �ߺ� ���� ���� ���
		cout << v + 1 << ". " << SaveData[v] << endl;
	}

	

	while (int l = 1) { // ��� �Է� �ޱ� ���� while��
		string vv;
		string out = ".";
		cout << "�Է� : ";
		cin >> vv;
		const char* vvv = vv.c_str();
		char c = '.';

		if (vv == out) // �Է¹��� �Ͱ� . �� �����ϴٸ� break�� while�� Ż��
			break;

		int x = 0, n = i - 1;
		int mi = BinarySearch(vvv, x, n);
		cout << mi << endl;
	}
	return 0;
}