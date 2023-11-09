#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

void get_input(int& month, int& day, int& year);


void get_input(int& month, int& year);


void get_input(int& year);


bool isValid(int month, int day, int year);


bool isValid(int month, int year);


bool isValid(int year);


void print_calendar(int month, int day, int year);


void print_calendar(int month, int year);


void print_calendar(int year);


string monthName(int month);


int daysInMonth(int month, int year);


void menu();


bool isLeapYear(int year);


int getCenturyValue(int year);

int getYearValue(int year);

int getMonthValue(int month, int year);

int dayOfWeek(int month, int day, int year);

string dayOfWeek(int day);

bool print_calendar(int year, string fileName);

void print_calendar(int month, int year, ofstream& output);

int main()
{
	char choice;
	int day, month, year;
	string filename;
	do
	{
		system("CLS");
		menu();
		cout << "\n\tPlease enter your choice: ";

		cin >> choice;

		switch (choice)
		{
		case '1': 
			get_input(month, day, year);
			print_calendar(month, day, year);
			break;

		case '2': 
			get_input(month, year);
			print_calendar(month, year);
			break;

		case '3':
			get_input(year);
			print_calendar(year);
			break;

		case '4':
			get_input(year);
			cout << "Please input a file name in format firstnameLastname: ";
			cin >> filename;
			filename += ".txt";
			print_calendar(year, filename);

			break;

		case '5': 
			cout << "\n\tThank you for using FHSU's calendar program!\n\n";
			break;

		default: 
			cout << "Error, no such choice. Please choose from Menu.\n";
			break;
		}

		cout << "\n\n\t";
		system("pause");

	} while (choice != '5');

	return 0;
}


void menu()
{
	cout << "\n\t***************************************************";
	cout << "\n\t*                   Menu                          *";
	cout << "\n\t* 1. Query a date                                 *";
	cout << "\n\t* 2. Print calendar of a given month              *";
	cout << "\n\t* 3. Print calendar of a given year               *";
	cout << "\n\t* 4. Print calendar to file						*";
	cout << "\n\t* 5. Quit                                         *";
	cout << "\n\t***************************************************";
}

void get_input(int& month, int& day, int& year)
{
	cout << "\n\tEnter the date in form of mm dd yyyy: ";
	cin >> month >> day >> year;

	while (!isValid(month, day, year)) 
	{
		cout << "\n\tThe date you entered is NOT valid. Please reenter a valid date: ";
		cin >> month >> day >> year;
	}
}

void get_input(int& month, int& year)
{
	cout << "\n\tEnter the month and year in form of mm yyyy: ";
	cin >> month >> year;

	while (!isValid(month, year)) 
	{
		cout << "\n\tThe month you entered is NOT valid. Please reenter a valid month: ";
		cin >> month >> year;
	}
}

void get_input(int& year)
{
	cout << "\n\tEnter the year as yyyy: ";
	cin >> year;

	while (!isValid(year)) 
	{
		cout << "\n\tThe year you entered is NOT valid. Please reenter a valid year: ";
		cin >> year;
	}
}

bool isValid(int month, int day, int year)
{


	bool result = true; 

	switch (month) 	
	{

	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		result = day >= 1 && day <= 31;
		break;

	case 4: case 6: case 9: case 11:
		result = day >= 1 && day <= 30;
		break;

	case 2:
		if (isLeapYear(year))
			result = day >= 1 && day <= 29;
		else
			result = day >= 1 && day <= 28;
		break;

	}
	return result && isValid(month, year); 
}

bool isValid(int month, int year)
{
	return month >= 1 && month <= 12 && year > 1582; 
}

bool isValid(int year)
{
	return year > 1582; 
}

bool isLeapYear(int year)
{
	return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)); 
}

int getCenturyValue(int year)
{
	return 2 * (3 - (year / 100) % 4); 
}

int getYearValue(int year)
{
	return year % 100 + year % 100 / 4;
}

int getMonthValue(int month, int year) 
{
	int result;

	switch (month)
	{

	case 1:
		if (isLeapYear(year))
			result = 6;
		else result = 0;
		break;

	case 2:
		if (isLeapYear(year))
			result = 2;
		else
			result = 3;
		break;

	case 3: case 11:
		result = 3;
		break;

	case 4: case 7:
		result = 6;
		break;

	case 5:
		result = 1;
		break;

	case 6:
		result = 4;
		break;

	case 8:
		result = 2;
		break;

	case 9:case 12:
		result = 5;
		break;

	default: 
		result = 0;
		break;
	}
	return result;
}

int dayOfWeek(int month, int day, int year) 
{
	if (!isValid(month, day, year)) return -1;
	return (getCenturyValue(year) + getMonthValue(month, year) + getYearValue(year) + day) % 7;
}

void print_calendar(int month, int day, int year)
{

	if (!isValid(month, day, year)) { 
		cout << "\n\tThe date is NOT valid!";
		return;
	}
	cout << "\n\t" << monthName(month) << " " << day << " , " << year << " is " << dayOfWeek(dayOfWeek(month, day, year));
}

void print_calendar(int month, int year)
{
	if (!isValid(month, year)) { 
		cout << "\n\tThe month is NOT valid!";
		return;
	}

	cout << "\n\t " << monthName(month) << ", " << year << endl;

	cout << "\n\t SUN MON TUE WED THU FRI SAT\n\t";
	int spaceCount = dayOfWeek(month, 1, year);

	for (int i = 0; i < spaceCount; i++)
		cout << setw(4) << "";

	int days = daysInMonth(month, year);

	for (int j = 1; j <= days; j++)
	{
		cout << setw(4) << j;
		if ((spaceCount + j) % 7 == 0) 
			cout << "\n\t";
	}
}

void print_calendar(int year)
{
	if (!isValid(year)) { 
		cout << "\n\tThe year is NOT valid!";
		return;
	}

	for (int i = 1; i <= 12; i++) 
	{
		print_calendar(i, year); 
		cout << endl;
	}
}

string monthName(int month)
{
	string result;
	switch (month)
	{

	case 1:
		result = "January";
		break;

	case 2:
		result = "February";
		break;

	case 3:
		result = "March";
		break;

	case 4:
		result = "April";
		break;

	case 5:
		result = "May";
		break;

	case 6:
		result = "June";
		break;

	case 7:
		result = "July";
		break;

	case 8:
		result = "August";
		break;

	case 9:
		result = "September";
		break;

	case 10:
		result = "October";
		break;

	case 11:
		result = "November";
		break;

	case 12:
		result = "December";
		break;

	default:
		result = "Not valid month";
		break;
	}

	return result;
}

string dayOfWeek(int day)
{
	string result;
	switch (day)
	{

	case 0:
		result = "Sunday";
		break;

	case 1:
		result = "Monday";
		break;

	case 2:
		result = "Tuesday";
		break;

	case 3:
		result = "Wednesday";
		break;

	case 4:
		result = "Thursday";
		break;

	case 5:
		result = "Friday";
		break;

	case 6:
		result = "Saturday";
		break;

	default:
		result = "Invalid date";
		break;
	}

	return result;
}

int daysInMonth(int month, int year)
{

	int result;
	switch (month)
	{

	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		result = 31;
		break;

	case 4: case 6: case 9: case 11:
		result = 30;
		break;

	case 2:
		if (isLeapYear(year))
			result = 29;
		else result = 28;
		break;

	default:
		result = -1;
		break;
	}

	return result;
}

bool print_calendar(int year, string fileName)
{
	{
		if (!isValid(year)) {
			cout << "\n\tThe year is NOT valid!";
			return false;
		}
		ofstream output;

		output.open(fileName);
		if (output.is_open()) {
			for (int i = 1; i <= 12; i++)
			{
				print_calendar(i, year, output);
				cout << endl;
			}
			output.close();
			cout << "File successfully written, check source files for your calendar";
			return true;
		}
		else {
			cout << "File failed to open";
			return false;
		}

	}
}

void print_calendar(int month, int year, ofstream& output)
{
	if (!isValid(month, year)) { 
		cout << "\n\tThe month is NOT valid!";
		return;
	}
	output << "\n\t " << monthName(month) << ", " << year << endl;

	output << "\n\t SUN MON TUE WED THU FRI SAT\n\t";
	int spaceCount = dayOfWeek(month, 1, year);

	for (int i = 0; i < spaceCount; i++)
		output << setw(4) << "";

	int days = daysInMonth(month, year);

	for (int j = 1; j <= days; j++)
	{
		output << setw(4) << j;
		if ((spaceCount + j) % 7 == 0) 
			output << "\n\t";
	}
	output << "\n\n";
}


