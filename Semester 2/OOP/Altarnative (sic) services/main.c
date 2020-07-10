#include <stdio.h>

const int numberDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//array that stores the number of days for each month

int main()
{
	char date[256];
	int isRunning = 1, day, month, index;
	while (isRunning)
	{
		scanf("%s", date);
		if (strcmp(date, "exit") == 0) //checks if the user entered exit
			return 0;

		day = date[0] - '0';
		day *= 10;
		day += date[1] - '0'; // computes the day of the date

		month = date[3] - '0';
		month *= 10;
		month += date[4] - '0'; // computes the month of the date

		int numberOfDays = day;

		for (index = 0; index < month-1; index += 1)
			numberOfDays += numberDaysInMonth[index];

		printf("%d ", numberOfDays);

	}
	return 0;
}