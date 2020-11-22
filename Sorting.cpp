#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include <iostream>
#include <string>
#include <algorithm>

#define R 1001

using namespace std;

char WordDataSet[R][R]; // 받은 데이터를 담고있는 2차원 배열입니다.
char SaveData[R][R]; // 특수문자를 제외한 문자열을 넣어주는 배열.

int BinarySearch(const char* b, int left, int right) {  // 순환 이원탐색 함수
	if (left <= right){
		int middle = (left + right) / 2;
		if (strcmp(b, SaveData[middle]) < 0)
			return BinarySearch(b, left, (middle - 1));
		else if (strcmp(b, SaveData[middle]) > 0)
			return BinarySearch(b, (middle + 1), right);
		else return middle + 1;
	}
	return -1; // 없을경우 -1 반환 (-1 출력)
}

int main() {

	FILE* f = fopen("input.txt", "r"); // 파일을 읽기 형식으로 받아줍니다. 

	if (f == NULL) printf("None file\n"); // 파일이 존재하지 않을 경우 예외처리입니다.

	int i = 0; //  받은 데이터들의 인덱스를 표시하는 변수입니다.
	
	char c2 = 39; // ' 문자도 제외해 주기 위해서 아스키 코드를 사용
	
	while (!feof(f)) {  // 텍스트파일에서 문자열을 받고 특수문자 없애기
		fscanf(f, "%s", WordDataSet[i]); 

		string abc;

		for (int j = 0; j < strlen(WordDataSet[i]); j++) { // 특수문자가 있다면 제외해주고, push_back을 통해 더해줌
			if (WordDataSet[i][j] != '?' && WordDataSet[i][j] != c2 && WordDataSet[i][j] != '.'
				&& WordDataSet[i][j] != '@' && WordDataSet[i][j] != '"' && WordDataSet[i][j] != '!'){
				abc.push_back(WordDataSet[i][j]);
			}
		}
		strcpy(WordDataSet[i],abc.c_str()); //abc에 있는 문자열을 WordDataSet에 복사
		i++; // 단어의 개수를 표시하는 수.
	}
	cout << "[단어정렬]" << endl;
	for (int m = 0; m < i; m++) {  // 선택정렬

		for (int j = m + 1; j < i; j++) {
			if (strcmp(WordDataSet[m], WordDataSet[j]) > 0) {
				swap(WordDataSet[m], WordDataSet[j]);
			}
		}
		cout << m+1 << ". " << WordDataSet[m] << endl; // 선택정렬 출력
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
	} // 중복된 글자 제외

	cout << "[중복제거]" << endl;
	for (int v = 0; v < k+1; v++) { // 중복 글자 제외 출력
		cout << v + 1 << ". " << SaveData[v] << endl;
	}

	

	while (int l = 1) { // 계속 입력 받기 위한 while문
		string vv;
		string out = ".";
		cout << "입력 : ";
		cin >> vv;
		const char* vvv = vv.c_str();
		char c = '.';

		if (vv == out) // 입력받은 것과 . 이 동일하다면 break로 while문 탈출
			break;

		int x = 0, n = i - 1;
		int mi = BinarySearch(vvv, x, n);
		cout << mi << endl;
	}
	return 0;
}