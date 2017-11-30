#include <iostream>
#include <string>
#include <math.h>

int firstPartOfYear(long year);
int secondPartOfYear(long year, long month);
int shiftedMonth(long month);
int calculate(long month, long day, long year);


int main() {

	long month, day, year;
	int dayOfWeek;
	std::string daysOfWeek[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	std::cout << "Enter value for month: ";
	std::cin >> month;
	std::cout << "Enter value for day: ";
	std::cin >> day;
	std::cout << "Enter value for year: ";
	std::cin >> year;

	dayOfWeek = calculate(month, day, year);

	if (dayOfWeek < 0) {
		dayOfWeek += 7;
	}
	std::cout << "\n\nYour birthday fell on a " << daysOfWeek[dayOfWeek] << std::endl;


	return 0;
}

int firstPartOfYear(long year) {
	return (int)((year - (year % 100)) / 100);
}

int secondPartOfYear(long year, long month) {
	if (month < 3)
		return (int)((year % 100) - 1);
	else
		return (int)(year % 100);
}

int shiftedMonth(long month) {
	if (month > 2)
		return (int)(month - 2);
	else if (month == 1)
		return 11;
	else if (month == 2) {
		return 12;
	}
}

int calculate(long month, long day, long year) {
	int sum = (day + (int)floor((2.6*shiftedMonth(month)) - 0.2) + secondPartOfYear(year, month) + (int)floor(secondPartOfYear(year, month) / 4) + (int)floor(firstPartOfYear(year) / 4) - (2 * firstPartOfYear(year))) % 7;
	return sum;
}