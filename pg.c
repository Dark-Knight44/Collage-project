#include<stdio.h>



typedef struct{
    int date;
    int month;
    int year;
}date;

typedef struct{
    char name[20];
    int student_id;
    int room;
    char phone_nuber[11];
    char course[10];
    date doj;
}student;


typedef struct{
    char time[6];
    char name[20];
    int room;
}lunch;

void manage_students(){
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t STUDENT MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1. Add Students\n");
    printf("2. Remove Students\n");
    printf("3. View All Students\n");
    printf("4. Search Students\n");
    printf("5. Back To Main Menu\n");

    int choice;
    printf("Enter Choice - ");
    scanf("%d",&choice);
}


int main() {
    while(1){
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\t PG MANAGEMENT SYSTEM\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. Manage Students\n");
        printf("2. Manage Rooms\n");
        printf("3. Manage Lunch Boxs\n");
        printf("4. Rent And Payment \n");
        printf("5. Report\n");
        printf("6. Exit\n");

        int choice;
        printf("Enter Choice - ");
        scanf("%d",&choice);

        if(choice==1){
            manage_students();
        }
    }
    return 0;
}