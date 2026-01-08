#include<stdio.h>
#include<stdbool.h>
#include<string.h>
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
    char phone_number[12];
    char course[10];
    bool active;
    date doj;
}student;


typedef struct{
    int hour;
    int min;
    student stu;
    date date;
    int roti;
    int id;
}lunch;


typedef struct {
    int rno;
    student students[10];
    int count;
    bool lock ;
}room;


void remove_student();
void view_students();
int search_student(int id,student *stu);
void manage_students();
void view_all_rooms();
void manage_room();
void manage_lunch();
void rent();
void report();
void shift_student();
void lock_room();
void view_past_students();
void view_active_students();
void submit_lunch_req();

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

void add_student(){

    while (getchar() != '\n');

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
    s1.active =1;
    //for id

    FILE *File_of_students;
    File_of_students=fopen("students.dat","rb");
    student s_last;

    fseek(File_of_students,0,SEEK_END);
    if(ftell(File_of_students)==0){
        s1.student_id=1;
    }else{
        fseek(File_of_students,-sizeof(student),SEEK_END);
        fread(&s_last,sizeof(student),1,File_of_students);
        s1.student_id=s_last.student_id+1;
    }
    fclose(File_of_students);

    //for rno.
    room r;
    FILE *file_of_room;
    file_of_room=fopen("rooms.dat","rb+");
    while(fread(&r,sizeof(room),1,file_of_room)==1){
        if(r.count<3){
            r.students[r.count]=s1;
            s1.room=r.rno;
            r.count+=1;
            fseek(file_of_room,-sizeof(room),SEEK_CUR);
            fwrite(&r,sizeof(room),1,file_of_room);
            fclose(file_of_room);
            break;
        }
    }
    
    FILE *file_of_students;

    file_of_students=fopen("students.dat","ab+");

    fwrite(&s1,sizeof(student),1,file_of_students);

    printf("succsess\n\n");
    
    fclose(file_of_students);
    manage_students();
}

void remove_student(){
    
    int stu_id;
    printf("Enter Student Id -");
    scanf("%d",&stu_id);

    FILE *file;
    file=fopen("students.dat","rb+");

    student stu;
    while (getchar() != '\n');

    while(fread(&stu,sizeof(student),1,file)==1){
        if(stu_id==stu.student_id){
            stu.active=0;

            fseek(file,-sizeof(student),SEEK_CUR);
            fwrite(&stu,sizeof(student),1,file);
            printf("\nUpdated The Records in Student File\n");

            fclose(file);

            FILE *file_of_room;
            file_of_room=fopen("rooms.dat","rb+");
            room r;
            
            while(fread(&r,sizeof(room),1,file_of_room)==1){
                if(stu.room==r.rno){
                    for(int i=0;i<r.count;i++){
                        if(r.students[i].student_id==stu.student_id){
                            r.students[i]=stu;
                            r.count--;
                            fseek(file_of_room,-sizeof(room),SEEK_CUR);
                            fwrite(&r,sizeof(room),1,file_of_room);
                            printf("Updated The Records IN Room File\n");
                            fclose(file_of_room);
                            return;
                        }
                    }
                }
            }
        }
    }
    printf("Student ID Not Found");
    fclose(file);
}

void view_past_students(){
    FILE *file_of_students;
    file_of_students=fopen("students.dat","rb");
    student s1;
    system("clear");
    

    while(fread(&s1,sizeof(student),1,file_of_students)==1){
        printf("%d",s1.active);
        if(!(s1.active)){
            printf("Student ID :%d\nStudent Name -%s\nPhone Number - %s\nRoom Number - %d\nPaid -%s\nCourse - %s\n\n",s1.student_id,s1.name,s1.phone_number,s1.room,(s1.is_paid?"yes":"no"),s1.course);
        }
    }
    fclose(file_of_students);
    manage_students();
}

void view_active_students(){
    FILE *file_of_students;
    file_of_students=fopen("students.dat","rb");
    student s1;
    system("clear");

    while(fread(&s1,sizeof(student),1,file_of_students)==1){
        printf("%d",s1.active);
        if(s1.active){
            printf("Student ID :%d\nStudent Name -%s\nPhone Number - %s\nRoom Number - %d\nPaid -%s\nCourse - %s\n\n",s1.student_id,s1.name,s1.phone_number,s1.room,(s1.is_paid?"yes":"no"),s1.course);
        }
    }
    fclose(file_of_students);
    manage_students();
}

void view_students(){
    system("clear");
    printf("1.View All Active Students\n");
    printf("2.View All Past Students\n");
    int choice;
    printf("Enter Your Choice - ");
    scanf("%d",&choice);
    if(choice==1){
        view_active_students();
    }else if(choice==2){
        view_past_students();
    }else{
        printf("Enter Correct Choice\n");
        manage_students();
    }
}

int search_student(int id , student *stu){

    FILE *file;
    file=fopen("students.dat","rb+");
    student s;
    system("clear");
    while(fread(&s,sizeof(student),1,file)==1){
        if(s.student_id==id){
            *stu=s;
            fclose(file);
            return 1;
        }
    }
    printf("No Student Found");
    fclose(file);
    return 0;
}


void manage_students(){
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t STUDENT MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1. Add Students\n");
    printf("2. Remove Student\n");
    printf("3. View All Students\n");
    printf("4. Search Students\n");
    printf("5. Back To Main Menu\n");

    int choice;
    while(1){
        printf("Enter Choice - ");
        scanf("%d",&choice);

        if(choice==1){
            add_student();
        }else if(choice==2){
            remove_student();
        }else if(choice==3){
            view_students();
        }else if(choice==4){
            int sid;
            student s;
            printf("Enter Student ID - ");
            scanf("%d",&sid);
            if(search_student(sid,&s)){
                printf("NAME - %s\nPhone no. - %s\nCourse - %s\nRoom no.%d\nPaid - %s\nDate of Join - %d-%d-%d\n\n",s.name,s.phone_number,s.course,s.room,s.is_paid?"yes":"no",s.doj.date,s.doj.month,s.doj.year);
            }
        }else if(choice==5){
            main();
        }else{
            printf("Please Enter Valid Option");
        }
    }
}
void view_all_rooms(){
    FILE *file;
    file=fopen("rooms.dat","rb+");
    room r;
    system("clear");
    while(fread(&r,sizeof(room),1,file)==1){
        printf("====================Room No. - %d====================",r.rno);
        printf("\nlock - %s\n",r.lock?"yes\n":"no\n");
        printf("count = %d\n",r.count);
        for(int i=0;i<r.count;i++){
            if(r.students[i].active){
                printf("%d. Student Name -%s\n\n",r.students[i].student_id,r.students[i].name);
            }else{
                printf("%d. Student Name -%s (PAST STUDENTS)\n\n",r.students[i].student_id,r.students[i].name);
                r.count++;
            }
        }
    }
    char temp;
    scanf("%c",&temp);
    fclose(file);
}

void shift_student(){
    int sid;
    printf("Enter Student ID - ");
    scanf("%d",&sid);
    student s;
    FILE *file_of_students;
    file_of_students=fopen("students.dat","rb+");
    while(fread(&s,sizeof(student),1,file_of_students)==1){
        if(sid==s.student_id){
            room r;
            int prev_room=s.room;
            FILE *file_of_rooms;
            file_of_rooms=fopen("rooms.dat","rb+");

            int num;
            printf("Enter Room Number To be Shiffted - ");
            scanf("%d",&num);
            bool temp=false;
            while(fread(&r,sizeof(room),1,file_of_rooms)==1){
                if((r.rno==num && !r.lock) && (r.count<3 && !temp)){
                    s.room=r.rno;
                    fseek(file_of_students,-sizeof(student),SEEK_CUR);
                    fwrite(&s,sizeof(student),1,file_of_students);
                    fclose(file_of_students);

                    r.students[r.count]=s;
                    r.count+=1;
                    fseek(file_of_rooms,-sizeof(room),SEEK_CUR);
                    fwrite(&r,sizeof(room),1,file_of_rooms);
                    fseek(file_of_rooms,0,SEEK_SET);
                    temp=true;
                    printf("addition done\n");
                }
                //removing from room
                if(temp){;
                    if(prev_room==r.rno){
                        for(int i=0;i<r.count;i++){
                            if(r.students[i].student_id==sid){
                                r.students[i].active=0;
                                r.count-=1;
                                temp++;
                                fseek(file_of_rooms,-sizeof(room),SEEK_CUR);
                                fwrite(&r,sizeof(room),1,file_of_rooms);
                                fclose(file_of_rooms);
                                printf("deletion done");
                                return;
                            }
                        }
                    }
                }
            }
            printf("Cannot shift student to that room");
        }

    }
    printf("No Student found");
}

void lock_room(){
    int room_to_lock;
    printf("Enter Room Number To Lock - ");
    scanf("%d",&room_to_lock);

    FILE *file_of_rooms;
    file_of_rooms=fopen("rooms.dat","rb+");
    room r;

    while(fread(&r,sizeof(room),1,file_of_rooms)==1){
        if(r.rno==room_to_lock){
            if(r.count<1){
                r.lock=!r.lock;
                fseek(file_of_rooms,-sizeof(room),SEEK_CUR);
                fwrite(&r,sizeof(room),1,file_of_rooms);
                fclose(file_of_rooms);
                printf("Sucessfull");
                return;
            }else{
                printf("Cant lock the room as it contain students");
                fclose(file_of_rooms);
                return;
            }
        }
    }
    printf("Cant find Room");
    fclose(file_of_rooms);
}

void manage_room(){
    while(1){
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\t ROOM MANAGEMENT\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. View All Room \n");
        printf("2. Shift Student\n");
        printf("3. Lock Room\\Unlock Room \n");
        printf("4. Back to Menu\n");

        int choice;
        printf("Enter Choice - ");
        scanf("%d",&choice);
        if(choice==1){
            view_all_rooms();
        }else if(choice==2){
            shift_student();
        }else if(choice==3){
            lock_room();
        }else if(choice==4){
            main();
        }else{
            printf("Enter a Valid Option");
        }
    }
}

void submit_lunch_req(){
    system("clear");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t LUNCH MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    FILE *file;
    file=fopen("lunch.dat","rb+");

    lunch l;

    int id;
    printf("Enter Student Id - ");
    scanf("%d",&id);

    student stu;
    if(search_student(id,&stu)){
        printf("Enter Date dd mm yyyy - ");
        scanf("%d %d %d",&l.date.date,&l.date.month,&l.date.year);
        
        l.stu=stu;

        printf("Enter Time (hh mm) - ");
        scanf("%d %d",&l.hour,&l.min);

        printf("Enter Number Chapatis - ");
        scanf("%d",&l.roti);

        fseek(file,0,SEEK_END);
        if(ftell(file)==0){
            l.id=1;
        }else{
            fseek(file,-sizeof(lunch),SEEK_END);
            lunch last;
            fread(&last,sizeof(lunch),1,file);
            l.id=last.id+1;
        }
        fwrite(&l,sizeof(lunch),1,file);
        fclose(file);
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
        printf("4. Delete The Request\n");
        printf("5. Veiw Undone Deliveries\n");
        printf("6. Veiw Student Lunch History\n");
        printf("7. Back to Main Menu\n");

        int choice;
        printf("Enter Choice - ");
        scanf("%d",&choice);
        if(choice==1){
            submit_lunch_req();
        }
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