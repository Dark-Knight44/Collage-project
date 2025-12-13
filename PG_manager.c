#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>

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
    char phone_number[11];
    char course[10];
    date doj;
}student;


typedef struct{
    char time[6];
    char name[20];
    int room;
}lunch;


typedef struct{
    int rno;
    student std1;
    student std2;
    student std3;
    bool lock ;
}room;



void add_student(){

    FILE *file;

    fopen("students.csv","a+");

    student s1;
    printf("\nEnter Name Of Student - ");
    fgets(s1.name,20,stdin);

    printf("\nEnter Phone Number - ");
    fgets(s1.phone_number,20,stdin);

    printf("\nEnter Course Name - ");
    fgets(s1.course,20,stdin);

    fprintf(file,"%d,%s,%s,%s,%d,%s",randint())

}


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

    if(choice==1){
    }
}


void manage_room(){
    while(1){
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\t ROOM MANAGEMENT\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. View Room Status\n");
        printf("2. View Vacant Beds\n");
        printf("3. Shift Student\n");
        printf("4. Lock Room \n");
        printf("5. Back to Menu\n");

        int choice;
        printf("Enter Choice - ");
        scanf("%d",&choice);
    }
}


void manage_lunch(){
    while(1){
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\t LUNCH MANAGEMENT\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. Sumbit Lunch Box Request\n");
        printf("2. Modify The Request\n");
        printf("3. Delete The Request\n");
        printf("4. Veiw Today's Delivery Schedule\n");
        printf("5. Veiw Student Lunch History\n");
        printf("6. Back to Main Menu\n");

        int choice;
        printf("Enter Choice - ");
        scanf("%d",&choice);
    }
} 


void rent(){
    while(1){
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\t RENT AND PAYEMENT\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. Set Monthly Payment (8k default)\n");
        printf("2. Record Payment\n");
        printf("3. View Payment Status\n");
        printf("4. View Pending Students \n");
        printf("5. Back To Main Menu\n");

        int choice;
        printf("Enter Choice - ");
        scanf("%d",&choice);
    }
}

void report(){
        while(1){
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("\t REPORTS\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("1. Rent Collection Efficiency Report\n");
            printf("2. Room Utilization Report\n");
            printf("3. Lunch Demand Summary Report\n");
            printf("4. Back To Main Menu\n");

            int choice;
            printf("Enter Choice - ");
            scanf("%d",&choice);

    }
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
        }else if(choice==2){
            manage_room();
        }else if(choice==3){
            manage_lunch();
        }else if(choice==4){
            rent();
        }else if(choice==5){
            report();
        }
    }
    return 0;
}