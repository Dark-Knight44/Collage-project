#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int date;
    int month;
    int year;
}date;

typedef struct{
    char name[20];
    int student_id;
    int room;
    bool is_paid;
    char phone_number[12];
    char course[10];
    date doj;
}student;


typedef struct{
    char time[6];
    char name[20];
    int room;
}lunch;


typedef struct {
    int rno;
    student students[3];
    int count;
    bool lock ;
}room;


int main(){

    student s1;
    printf("\nEnter Name Of Student - ");
    fgets(s1.name,20,stdin);
    s1.name[strcspn(s1.name,"\n")]='\0';

    printf("\nEnter Phone Number - ");
    fgets(s1.phone_number,12,stdin);
    s1.phone_number[strcspn(s1.phone_number,"\n")]='\0';

    printf("\nEnter Course Name - ");
    fgets(s1.course,10,stdin);
    s1.course[strcspn(s1.course,"\n")]='\0';

    printf("Enter date of joining(dd mm yyyy) - ");
    scanf("%d %d %d",&s1.doj.date,&s1.doj.month,&s1.doj.year);

    s1.is_paid=1;
    s1.room=1;
    s1.student_id=1;


    room r;
    r.count=0;
    r.lock=0;
    r.rno=1;
    r.students[0]=s1;


    FILE *file_of_students;

    file_of_students=fopen("students.dat","ab+");

    fwrite(&s1,sizeof(student),1,file_of_students);
    
    fclose(file_of_students);

    FILE *file_of_room;
    file_of_room=fopen("rooms.dat","rb+");
    fwrite(&r,sizeof(room),1,file_of_room);
    fclose(file_of_room);

    printf("succsess");
    
    return 0;
}