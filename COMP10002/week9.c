#include <stdio.h>
#include <string.h>

float calc_age(date d1, date d2);
float ave_age_death(person *contry, int population);
int total_tax(person *contry, int population, int year);

/*- People have titles, a given name, a middle name, 
  and a family name, all of up to 50 characters each*/

/*- People also have dates of birth (dd/mm/yyyy), 
  dates of marriage and divorce (as many as 10 of each), 
  and dates of death (with a flag to indicate whether or
  not they are dead yet). */

/*- Each date of marriage is accompanied by
  the name of a person.*/

/*- Assuming that people work for less than 100 years each,
  people also have, for each year they worked, a year
  (yyyy), a net income and a tax liability (both rounded 
  to whole dollars), and a date when that tax liability was paid

;*/

typedef char str[50];
typedef struct{
	str title;
	str first;
	str middle;
	str last;
}name;

typedef struct
{
	int yyyy;
	int mm;
	int dd;
}date;

typedef struct
{
	date m_date;
	name spouse;
}marriage;

typedef struct
{
	int yyyy;
	int income;
	int tax;
	date tax_paid;
}work;

typedef struct
{
	date d_date;
	int is_dead;
}death;

typedef struct{
	name full_name;
	date birthday;
	date divorce[10];
	marriage marriages[10];
	death death_day;
	work work_year[100];
}person;


int main(int argc, char *argv[]){

	person australian[30000000];
	float ave_death = ave_age_death(australian, 30000000);
	
	int t_tax = total_tax(australian, 30000000, 2015);
	return 0;
}

/*Exercise 2
Write a function that calculates, for a specified country
indicated by a pointer argument (argument 1) with a
number of persons in it (argument 2), the average age of
death. Do not include people that are not yet dead.*/

float ave_age_death(person *national, int population){
	
	int i, count=0;
	float age_sum=0.0;

	//sum the age of dead people
	for (i=0; i < population; i++){
		if(national[i].death_day.is_dead){
			age_sum += calc_age(national[i].birthday, 
								national[i].death_day.d_date);
			count++
		}
	}
	
	return (age_sum/count);
}

float calc_age(date d1, date d2){
	return ((d2.yyyy - d1.yyyy) + 
		(d2.mm - d1.mm)*1.0/12 +
		(d2.dd - d1.dd)*1.0/365);
}

/*Exercise 3
Write a function that calculates, for the country indicated by
a pointer argument (argument 1) with a number of persons
in it (argument 2) the total taxation revenue in a specified
year (argument 3).*/

int total_tax(person *national, int population, int year){
	int i, j, total=0;

	//for each person, 
	//find the tax_liability of work_year[j] == year 

	for (i=0; i < population; i++){
		for (j=0; j < 100; j++){
			if(national[i].work_year[j].yyyy == year){
				total += national[i].work_year[j].tax;
				//break;
			}
		}
	}
	
	return total;
		
}




