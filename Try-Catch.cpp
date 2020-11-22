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


	cout << "ȯ���մϴ�! �а���, �й�, �̸�, �������(yyyy/mm/dd)�� �Է��ϼ���." << endl;
	
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
			cout << "�߸��� �й��� �Է��ϼ̽��ϴ�. �й��� ���Է� �ٶ��ϴ�.  \n";
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
				cout << "�߸��� ���� �Է��ϼ̽��ϴ�.\n";
				throw year;
			}

			if ((month < 1) || (month > 12)) {
				cout << "�߸��� ���� �Է��ϼ̽��ϴ�.\n";
				throw month;
			};

			if ((day < 1) || (day > 31)){
				cout << "�߸��� ���� �Է��ϼ̽��ϴ�.\n";
				throw day;
			}
			n = 0;
		}

		catch (int err2){
			cout << "�������(yyyy/mm/dd)�� ���Է� �ٶ��ϴ�.\n ";
		}
	}

}

void Date::output_Date(){
	cout << major << " " << idnum << name << "�� ";
}

void Birthdate::output_Birthdate(){
	cout << year << "�� "<< month << "�� " << day << "�ϻ�" << endl;

	curr_time = time(NULL);
	localtime_s(&curr_tm, &curr_time);

	cout << (curr_tm.tm_year + 1900) << "�� " << (curr_tm.tm_mon + 1) << "�� "
		<< (curr_tm.tm_mday) << "�� ";
	cout << "���� " << ((curr_tm.tm_year + 1900) - year + 1) << "�� �Դϴ�.";
}