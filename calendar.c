/*Matt Layman - CS211 - mtl104@scaletmail.rutgers.edu*/
#include <stdio.h>

int length(int, int);     /*funtion protypes*/
int day_of_week(int, int, int);
void print_calendar(int, int);

int main(void)
{
	/*declare variables*/
	int month, days, year, dayofweek;

	do{
		printf("Enter month(1=Jan, ..., 12=Dec):");
		scanf("%d", &month);
		if (month<=0)
			printf("Error:month must be in range 1..12\n");

		else if(month > 12)
			printf("Error:month must be in range 1..12\n");
	} while ( month <= 0 || month > 12);

	do{
		printf("Enter year(>0):");
		scanf("%d", &year);
		if (year<=0)
			printf("Error:year must be > 0\n");
	} while ( year <= 0 );

	days = length(month, year);
	dayofweek = day_of_week(1, month, year);
	print_calendar(dayofweek, days);
	printf("\n");
	return 0;
}

int length(int month, int year)
{
	int numberofdays;
	if (month == 4 || month == 6 || month == 9 || month == 11)
	    numberofdays = 30;

	else if (month == 2)
	    if((year % 4 == 0 && year%100 != 0)  || (year%400 == 0))
	    {
	    	numberofdays = 29;
	    }
	    else
	    {
	    	numberofdays = 28;
	    }
	else
	  numberofdays = 31;

	return numberofdays;
}

int day_of_week(int day, int month, int year)
{
	int h,q,m,k,j;

	if (month == 1)
	{
	month = 13;
	year --;
	}
	if (month == 2)
	{
	month = 14;
	year--;
	}

	q = day;
	m = month;
	k = year % 100;
	j = year / 100;
	h = q + 13*(m+1)/5 + k + k/4 + j/4 + 5*j;
	h = h % 7;

	return h;
}

void print_calendar(int start_day, int month_length)
{
	int dayofweek, i;
	dayofweek = start_day-1;

	printf("\nSun Mon Tue Wed Thu Fri Sat\n");
	
	for(i = 0; i < dayofweek; i++)  
	    printf("    ");

	for(i = 1; i <= month_length; i++)
	{

	printf("%3d ", i);

	dayofweek = (dayofweek + 1) % 7;

	if(dayofweek == 0)
	    printf("\n");
	}
}
