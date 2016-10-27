#include <stdio.h>
#include <string.h>

typedef char str[50];

typedef struct {
	str title;
	str given_name;
	str middle_name;
	str family_name;
}name;

typedef struct {
	int dd;
	int mm;
	int yyyy;
}date;

typedef struct {
	date m_date;
	name spouse;
}marriage;

typedef struct {
	date death_date;
	int is_dead;
}death;

typedef struct {
	int yyyy;
	int income;
	int tax_liability;
	date tax_paid;
}work;

typedef struct {
	
	name full_name;
	date birth;
	marriage marriages[10];
	date divorce[10];
	death death_day;

	work work_year[100];

}person;




float calc_age(date d1, date d2){
	return ((d2.dd-d1.dd)*1.0/365 + 
		(d2.mm-d1.mm)*1.0/12 + (d2.yyyy-d1.yyyy));
}

float ave_age_death(person *contry, int population){
	
	int i, count=0;
	float ave_age=0.0;

	for(i=0;i<population;i++){
		if(contry[i].death_day.is_dead==1){
			ave_age += calc_age(contry[i].birth, 
				contry[i].death_day.death_date);
			count++;
		}
		
	}
	return ave_age/count;
}

int total_tax(person *contry, int population, int year){
	int i, j, total=0;

	for(i=0;i<population;i++){
		for(j=0;j<100;j++){
			if(contry[i].work_year[j].yyyy==year){
				total += contry[i].work_year[j].tax_liability;
			}
		}
		
	}
	return total;
		
}

int main(int argc, char *argv[]){

	person australian[3];
	
	australian[1].work_year[2].yyyy=1952;
	australian[1].work_year[2].tax_liability=100;
	australian[1].birth.mm=1;
	australian[1].birth.dd=30;

	australian[1].death_day.death_date.yyyy=2012;
	australian[1].death_day.death_date.mm=5;
	australian[1].death_day.death_date.dd=30;
	australian[1].death_day.is_dead=1;

	australian[0].work_year[1].yyyy=1991;
	australian[0].work_year[1].tax_liability=200;
	australian[0].birth.mm=11;
	australian[0].birth.dd=30;

	australian[0].death_day.death_date.yyyy=1992;
	australian[0].death_day.death_date.mm=11;
	australian[0].death_day.death_date.dd=30;
	australian[0].death_day.is_dead=1;
	
	printf(">>%d\n", total_tax(australian, 3, 1991));
	return 0;
}






