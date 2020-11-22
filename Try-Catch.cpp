#include <iostream>
#include <string.h>
#include <time.h>

using namespace std;

class Date{
public:
	void input_Date();
	void output_Date();
	void idnum_modify();

private:
	char major[20];
	char idnum[20];
	char name[20];
	int idnum_c;
};

class Birthdate{
public:
	void input_Birthdate();
	void output_Birthdate();
private :
	char birthday[256];
	int year;
	int month;
	int day;

	time_t curr_time;
	struct tm curr_tm;
};

int main(){
	Date today;
	Birthdate now;


	cout << "환영합니다! 학과명, 학번, 이름, 생년월일(yyyy/mm/dd)을 입력하세요." << endl;
	
	today.input_Date();
	now.input_Birthdate();
	today.idnum_modify();
	today.output_Date();
	now.output_Birthdate();

	return 0;
};

void Date::input_Date(){
	cin.getline(major, 20, ',');
	cin.getline(idnum, 20, ',');
	cin.getline(name, 20, ',');
}

void Date::idnum_modify() {
	int i = 1;

	while (i) {
		try {
			idnum_c = atoi(idnum);
			if (idnum_c > 2021000000 || idnum_c < 1900000000) {
				throw idnum_c;
			}
			i = 0;
		}
		catch (int err) {
			cout << "잘못된 학번을 입력하셨습니다. 학번을 재입력 바랍니다.  \n";
			cin.getline(idnum, 20);
			cout << idnum;
		}
	}
}

void Birthdate::input_Birthdate() {
	int n = 1;

	while (n) {
		try{
			cin >> birthday;

			char* cp;
			char* context = NULL;
			cp = strtok_s(birthday, "/", &context);
			year = atoi(cp);
			cp = strtok_s(NULL, "/", &context);
			month = atoi(cp);
			cp = strtok_s(NULL, "/", &context);
			day = atoi(cp);
			
			curr_time = time(NULL);
			localtime_s(&curr_tm, &curr_time);

			if ((year < 1900) || (year > (curr_tm.tm_year + 1900))) {
				cout << "잘못된 년을 입력하셨습니다.\n";
				throw year;
			}

			if ((month < 1) || (month > 12)) {
				cout << "잘못된 월을 입력하셨습니다.\n";
				throw month;
			};

			if ((day < 1) || (day > 31)){
				cout << "잘못된 일을 입력하셨습니다.\n";
				throw day;
			}
			n = 0;
		}

		catch (int err2){
			cout << "생년월일(yyyy/mm/dd)을 재입력 바랍니다.\n ";
		}
	}

}

void Date::output_Date(){
	cout << major << " " << idnum << name << "님 ";
}

void Birthdate::output_Birthdate(){
	cout << year << "년 "<< month << "월 " << day << "일생" << endl;

	curr_time = time(NULL);
	localtime_s(&curr_tm, &curr_time);

	cout << (curr_tm.tm_year + 1900) << "년 " << (curr_tm.tm_mon + 1) << "월 "
		<< (curr_tm.tm_mday) << "일 ";
	cout << "현재 " << ((curr_tm.tm_year + 1900) - year + 1) << "세 입니다.";
}