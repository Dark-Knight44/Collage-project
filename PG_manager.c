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
    char phone_number[11];
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
    bool lock ;
}room;



void add_student(){

    while (getchar() != '\n');

    student s1;
    printf("\nEnter Name Of Student - ");
    fgets(s1.name,20,stdin);
    s1.name[strcspn(s1.name,"\n")]='\0';

    printf("\nEnter Phone Number - ");
    fgets(s1.phone_number,11,stdin);
    s1.phone_number[strcspn(s1.phone_number,"\n")]='\0';

    printf("\nEnter Course Name - ");
    fgets(s1.course,10,stdin);
    s1.course[strcspn(s1.course,"\n")]='\0';

    printf("Enter date of joining(dd-mm-yyyy) - ");
    scanf("%d %d %d",&s1.doj.date,&s1.doj.month,&s1.doj.year);

    //for id

    FILE *file;

    file=fopen("students.dat","rb");

    fseek(file,-sizeof(student),SEEK_END);

    student s_last;

    fread(&s_last,sizeof(student),1,file);

    s1.student_id=s_last.student_id+1;

    //for rno.
    
    room r;

    FILE *file_of_room;

    file_of_room=fopen("rooms.dat","a+");

    fseek(file_of_room, - sizeof(room),SEEK_END);

    fread(&r,sizeof(room),1,file_of_room);

    int students_init=sizeof(r.students)/sizeof(r.students[0]);
    
    if(students_init<=3){
        r.students[students_init+1]=s1;
    }else{
        r.rno=r.rno+1;
        r.students[0]=s1;
        r.lock=0;

        fseek(file, - sizeof(room),SEEK_END);
    }

    //writing in file

    fwrite(&r,sizeof(room),1,file_of_room);

    fclose(file_of_room);
    
    FILE *file1;

    file1=fopen("students.dat","ab+");

    fwrite(&s1,sizeof(student),1,file);

    printf("succsess");
    
    fclose(file1);

}



void view_all_students(){
    FILE *file;
    file=fopen("students.dat","rb");
    student s1;
    int temp;
    while(fread(&s1,sizeof(student),1,file)==1){
        system("clear");
        printf("Student ID :%s\n,Student Name -%s\n Phone Number -%s\n Room Number - %d\n Paid -%s\nCourse - %s",s1.student_id,s1.name,s1.phone_number,s1.room,(s1.is_paid?"yes":"no"),s1.course);
        scanf("%d",&temp);
    }
    fclose(file);
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
        add_student();
    }else if(choice==3){
        view_all_students();
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