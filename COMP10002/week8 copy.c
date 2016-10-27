#include <stdio.h>
#include <string.h>

typedef struct name
{
	char first_name[50];
	char last_name[50];

}full_name;

typedef struct person{

	int ID;
	full_name name;
	char email[50];
	float grade;

}student;

void print_student(struct person stu);
void read_student(student *stu);

int
main(int argc, char *argv[]){

	//struct person alicia;
	student alicia;

	//alicia.ID = 12345;

	//strcpy(alicia.name.first_name, "ziying yang");
	//alicia.name = "ziying yang";


	//printf("Enter email\n");
	//scanf("%s", alicia.email);

	//printf("Enter grade\n");
	//scanf("%f", &alicia.grade);
	read_student(&alicia);
	print_student(alicia);


	return 0;
}

void print_student(struct person stu){
	printf("student ID: %d\n", stu.ID);
	printf("student name: %s\n", stu.name.first_name);
	printf("student email: %s\n", stu.email);
	printf("student grade: %.1f\n", stu.grade);

}

void read_student(student *stu){
	stu->ID=1234;
	strcpy(stu->name.first_name, "ziying yang");
	printf("Enter email\n");
	scanf("%s", stu->email);

	printf("Enter grade\n");
	scanf("%f", &stu->grade);
}
