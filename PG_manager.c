#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
typedef struct
{
    int date;
    int month;
    int year;
} date;

typedef struct
{
    char name[20];
    int student_id;
    int room;
    bool is_paid;
    char phone_number[12];
    char course[10];
    bool active;
    date doj;
} student;

typedef struct
{
    int hour;
    int min;
    student stu;
    date date;
    int roti;
    int id;
    bool completed;
} lunch;

typedef struct
{
    int rno;
    student students[10];
    int count;
    bool lock;
} room;

void remove_student();
void view_students();
int search_student(int id, student *stu);
void manage_students();
void view_all_rooms();
void manage_room();
void manage_lunch();
void rent_payment();
void shift_student();
void lock_room();
void view_past_students();
void view_active_students();
void submit_lunch_req();
void veiw_completed_delivery();
void veiw_incomplete_delivery();
void modify_lunch();
void mark_done();
void student_lunch_history();
void set_rent();
int rent();
void record_payment();
void pending_students();
void start_new_month();

void initialize_room_file()
{
    FILE *file;
    file = fopen("rooms.dat", "rb+");

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        room r;
        for (int i = 1; i <= 30; i++)
        {
            r.rno = i;
            r.count = 0;
            r.lock = false;

            fwrite(&r, sizeof(room), 1, file);
        }
        fclose(file);
    }
}

int main()
{
    initialize_room_file();
    system("clear");
    while (1)
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\t PG MANAGEMENT SYSTEM\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. Manage Students\n");
        printf("2. Manage Rooms\n");
        printf("3. Manage Lunch Boxs\n");
        printf("4. Rent And Payment \n");
        printf("5. Exit\n");

        int choice;
        printf("Enter Choice - ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            system("clear");
            manage_students();
        }
        else if (choice == 2)
        {
            system("clear");
            manage_room();
        }
        else if (choice == 3)
        {
            system("clear");
            manage_lunch();
        }
        else if (choice == 4)
        {
            system("clear");
            rent_payment();
        }
        else if (choice == 5)
        {
            abort();
        }
        else
        {
            system("clear");
            printf("Enter Correct Option");
        }
    }
}

void add_student()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t STUDENT MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    while (getchar() != '\n')
        ;

    student s1;
    printf("\nEnter Name Of Student - ");
    fgets(s1.name, 20, stdin);
    s1.name[strcspn(s1.name, "\n")] = '\0';

    printf("\nEnter Phone Number - ");
    fgets(s1.phone_number, 12, stdin);
    s1.phone_number[strcspn(s1.phone_number, "\n")] = '\0';

    printf("\nEnter Course Name - ");
    fgets(s1.course, 10, stdin);
    s1.course[strcspn(s1.course, "\n")] = '\0';

    printf("\nEnter date of joining(dd mm yyyy) - ");
    scanf("%d %d %d", &s1.doj.date, &s1.doj.month, &s1.doj.year);
    s1.is_paid = 1;
    s1.active = 1;
    // for id

    FILE *File_of_students;
    File_of_students = fopen("students.dat", "rb");
    student s_last;

    fseek(File_of_students, 0, SEEK_END);
    if (ftell(File_of_students) == 0)
    {
        s1.student_id = 1;
    }
    else
    {
        fseek(File_of_students, -sizeof(student), SEEK_END);
        fread(&s_last, sizeof(student), 1, File_of_students);
        s1.student_id = s_last.student_id + 1;
    }
    fclose(File_of_students);

    // for rno.
    room r;
    FILE *file_of_room;
    file_of_room = fopen("rooms.dat", "rb+");
    while (fread(&r, sizeof(room), 1, file_of_room) == 1)
    {
        if (r.count < 3)
        {
            r.students[r.count] = s1;
            s1.room = r.rno;
            r.count += 1;
            fseek(file_of_room, -sizeof(room), SEEK_CUR);
            fwrite(&r, sizeof(room), 1, file_of_room);
            fclose(file_of_room);
            break;
        }
    }

    FILE *file_of_students;

    file_of_students = fopen("students.dat", "ab+");

    fwrite(&s1, sizeof(student), 1, file_of_students);

    system("clear");

    printf("Success\n\n");
    printf("Assigned Room-%d\n Assigned Student ID-%d", s1.room, s1.student_id);

    fclose(file_of_students);
    manage_students();
}

void remove_student()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t STUDENT MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    int stu_id;
    printf("Enter Student Id -");
    scanf("%d", &stu_id);

    FILE *file;
    file = fopen("students.dat", "rb+");

    student stu;
    while (getchar() != '\n')
        ;

    while (fread(&stu, sizeof(student), 1, file) == 1)
    {
        if (stu_id == stu.student_id)
        {
            stu.active = 0;

            fseek(file, -sizeof(student), SEEK_CUR);
            fwrite(&stu, sizeof(student), 1, file);
            printf("\nUpdated The Records in Student File\n");
            fclose(file);

            FILE *file_of_room;
            file_of_room = fopen("rooms.dat", "rb+");
            room r;

            while (fread(&r, sizeof(room), 1, file_of_room) == 1)
            {
                if (stu.room == r.rno)
                {
                    for (int i = 0; i < r.count; i++)
                    {
                        if (r.students[i].student_id == stu.student_id)
                        {
                            r.count--;
                            r.students[i].active = 0;
                            fseek(file_of_room, -sizeof(room), SEEK_CUR);
                            fwrite(&r, sizeof(room), 1, file_of_room);
                            printf("Updated The Records IN Room File\n");
                            fclose(file_of_room);
                            manage_students();
                        }
                    }
                }
            }
        }
    }
    system("clear");
    printf("Student ID Not Found");
    fclose(file);
    manage_students();
}

void view_past_students()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t STUDENT MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    FILE *file_of_students;
    file_of_students = fopen("students.dat", "rb");
    student s1;

    while (fread(&s1, sizeof(student), 1, file_of_students) == 1)
    {
        if (!(s1.active))
        {
            printf("Student ID :%d\nStudent Name -%s\nPhone Number - %s\nRoom Number - %d\nPaid -%s\nCourse - %s\n\n", s1.student_id, s1.name, s1.phone_number, s1.room, (s1.is_paid ? "yes" : "no"), s1.course);
        }
    }
    getchar();
    getchar();
    system("clear");
    fclose(file_of_students);
    manage_students();
}

void view_active_students()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t STUDENT MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    FILE *file_of_students;
    file_of_students = fopen("students.dat", "rb");
    student s1;
    system("clear");

    while (fread(&s1, sizeof(student), 1, file_of_students) == 1)
    {
        if (s1.active)
        {
            printf("Student ID :%d\nStudent Name -%s\nPhone Number - %s\nRoom Number - %d\nPaid -%s\nCourse - %s\n\n", s1.student_id, s1.name, s1.phone_number, s1.room, (s1.is_paid ? "yes" : "no"), s1.course);
        }
    }
    getchar();
    getchar();
    system("clear");
    fclose(file_of_students);
    manage_students();
}

void view_students()
{
    system("clear");

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t STUDENT MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("1.View All Active Students\n");
    printf("2.View All Past Students\n");
    int choice;
    printf("Enter Your Choice - ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        view_active_students();
    }
    else if (choice == 2)
    {
        view_past_students();
    }
    else
    {
        printf("Enter Correct Choice\n");
        manage_students();
    }
}

int search_student(int id, student *stu)
{

    FILE *file;
    file = fopen("students.dat", "rb+");
    student s;
    system("clear");
    while (fread(&s, sizeof(student), 1, file) == 1)
    {
        if (s.student_id == id)
        {
            *stu = s;
            fclose(file);
            return 1;
        }
    }
    getchar();
    getchar();
    system("clear");
    printf("No Student Found");
    fclose(file);
    return 0;
}

void manage_students()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t STUDENT MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1. Add Students\n");
    printf("2. Remove Student\n");
    printf("3. View All Students\n");
    printf("4. Search Students\n");
    printf("5. Back To Main Menu\n");

    int choice;
    while (1)
    {
        printf("Enter Choice - ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            system("clear");
            add_student();
        }
        else if (choice == 2)
        {
            system("clear");
            remove_student();
        }
        else if (choice == 3)
        {
            system("clear");
            view_students();
        }
        else if (choice == 4)
        {
            system("clear");
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("\t STUDENT MANAGEMENT\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            int sid;
            student s;
            printf("Enter Student ID - ");
            scanf("%d", &sid);
            if (search_student(sid, &s))
            {
                printf("NAME - %s\nPhone no. - %s\nCourse - %s\nRoom no.%d\nPaid - %s\nDate of Join - %d-%d-%d\n\n", s.name, s.phone_number, s.course, s.room, s.is_paid ? "yes" : "no", s.doj.date, s.doj.month, s.doj.year);
            }
            manage_students();
        }
        else if (choice == 5)
        {
            system("clear");
            main();
        }
        else
        {
            system("clear");
            printf("Please Enter Valid Option");
        }
    }
}
void view_all_rooms()
{
    FILE *file;
    file = fopen("rooms.dat", "rb+");
    room r;
    system("clear");
    while (fread(&r, sizeof(room), 1, file) == 1)
    {
        printf("====================Room No. - %d====================", r.rno);
        printf("\nlock - %s\n", r.lock ? "yes\n" : "no\n");
        printf("count = %d\n", r.count);
        for (int i = 0; i < r.count; i++)
        {
            if (r.students[i].active)
            {
                printf("%d. Student Name -%s\n\n", r.students[i].student_id, r.students[i].name);
            }
            else
            {
                printf("%d. Student Name -%s (PAST STUDENTS)\n\n", r.students[i].student_id, r.students[i].name);
                r.count++;
            }
        }
    }
    getchar();
    getchar();
    system("clear");
}

void shift_student()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t ROOM MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    int sid;
    printf("Enter Student ID - ");
    scanf("%d", &sid);
    student s;
    FILE *file_of_students;
    file_of_students = fopen("students.dat", "rb+");
    while (fread(&s, sizeof(student), 1, file_of_students) == 1)
    {
        if (sid == s.student_id)
        {
            room r;
            int prev_room = s.room;
            FILE *file_of_rooms;
            file_of_rooms = fopen("rooms.dat", "rb+");

            int num;
            printf("Enter Room Number To be Shiffted - ");
            scanf("%d", &num);
            bool temp = false;
            while (fread(&r, sizeof(room), 1, file_of_rooms) == 1)
            {
                if ((r.rno == num && !r.lock) && (r.count < 3 && !temp))
                {
                    s.room = r.rno;
                    fseek(file_of_students, -sizeof(student), SEEK_CUR);
                    fwrite(&s, sizeof(student), 1, file_of_students);
                    fclose(file_of_students);

                    r.students[r.count] = s;
                    r.count += 1;
                    fseek(file_of_rooms, -sizeof(room), SEEK_CUR);
                    fwrite(&r, sizeof(room), 1, file_of_rooms);
                    fseek(file_of_rooms, 0, SEEK_SET);
                    temp = true;
                    printf("addition done\n");
                }
                // removing from room
                if (temp)
                {
                    ;
                    if (prev_room == r.rno)
                    {
                        for (int i = 0; i < r.count; i++)
                        {
                            if (r.students[i].student_id == sid)
                            {
                                r.students[i].active = 0;
                                r.count -= 1;
                                temp++;
                                fseek(file_of_rooms, -sizeof(room), SEEK_CUR);
                                fwrite(&r, sizeof(room), 1, file_of_rooms);
                                fclose(file_of_rooms);
                                printf("deletion done");
                                system("clear");
                                return;
                            }
                        }
                    }
                }
            }
            system("clear");
            printf("Cannot shift student to that room\n");
        }
    }
    system("clear");
    printf("No Student found\n");
}

void lock_room()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t ROOM MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    int room_to_lock;
    printf("Enter Room Number To Lock - ");
    scanf("%d", &room_to_lock);

    FILE *file_of_rooms;
    file_of_rooms = fopen("rooms.dat", "rb+");
    room r;

    while (fread(&r, sizeof(room), 1, file_of_rooms) == 1)
    {
        if (r.rno == room_to_lock)
        {
            if (r.count < 1)
            {
                r.lock = !r.lock;
                fseek(file_of_rooms, -sizeof(room), SEEK_CUR);
                fwrite(&r, sizeof(room), 1, file_of_rooms);
                fclose(file_of_rooms);
                printf("Sucessfull");
                return;
            }
            else
            {
                printf("Cant lock the room as it contain students");
                fclose(file_of_rooms);
                return;
            }
        }
    }
    printf("Cant find Room");
    fclose(file_of_rooms);
}

void manage_room()
{
    while (1)
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\t ROOM MANAGEMENT\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. View All Room \n");
        printf("2. Shift Student\n");
        printf("3. Lock Room\\Unlock Room \n");
        printf("4. Back to Menu\n");

        int choice;
        printf("Enter Choice - ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            system("clear");
            view_all_rooms();
        }
        else if (choice == 2)
        {
            system("clear");
            shift_student();
        }
        else if (choice == 3)
        {
            system("clear");
            lock_room();
        }
        else if (choice == 4)
        {
            system("clear");
            main();
        }
        else
        {
            printf("Enter a Valid Option\n");
        }
    }
}

void submit_lunch_req()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t LUNCH MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    FILE *file;
    file = fopen("lunch.dat", "rb+");

    lunch l;

    int id;
    printf("Enter Student Id - ");
    scanf("%d", &id);

    student stu;
    if (search_student(id, &stu))
    {
        if (!stu.active)
        {
            printf("Student Removed");
            return;
        }
        printf("Enter Date dd mm yyyy - ");
        scanf("%d %d %d", &l.date.date, &l.date.month, &l.date.year);

        l.stu = stu;

        printf("Enter Time (hh mm) - ");
        scanf("%d %d", &l.hour, &l.min);

        printf("Enter Number Chapatis - ");
        scanf("%d", &l.roti);

        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0)
        {
            l.id = 1;
        }
        else
        {
            fseek(file, -sizeof(lunch), SEEK_END);
            lunch last;
            fread(&last, sizeof(lunch), 1, file);
            l.id = last.id + 1;
        }
        l.completed = 0;
        fwrite(&l, sizeof(lunch), 1, file);
        fclose(file);
        system("clear");
        printf("Success");
        printf("Assigned Lunch ID - %d", l.id);
    }
}

void veiw_completed_delivery()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t LUNCH MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FILE *file;
    lunch l;
    system("clear");
    file = fopen("lunch.dat", "rb");
    while (fread(&l, sizeof(lunch), 1, file))
    {
        if (l.completed)
        {
            printf("%d. Name -%s\n", l.stu.student_id, l.stu.name);
            printf("date - %d %d %d \ntime - %d:%d\n", l.date.date, l.date.month, l.date.year, l.hour, l.min);
            printf("chapatii -%d\n", l.roti);
        }
    }
    getchar();
    getchar();
    system("clear");
    fclose(file);
}

void veiw_incomplete_delivery()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t LUNCH MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FILE *file;
    file = fopen("lunch.dat", "rb");
    lunch l;
    while (fread(&l, sizeof(lunch), 1, file) == 1)
    {
        if (!l.completed)
        {
            printf("\n\n===========ID - %d===========\n\n", l.id);
            printf("%d. Name -%s\n", l.stu.student_id, l.stu.name);
            printf("date - %d %d %d \ntime - %d:%d\n", l.date.date, l.date.month, l.date.year, l.hour, l.min);
            printf("chapatii -%d\n", l.roti);
        }
    }
    getchar();
    getchar();
    system("clear");
    fclose(file);
}

void view_deliveries()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t LUNCH MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1. View Completed Deliveries\n");
    printf("2. View Incompleted Deliveries\n");

    int choice;
    printf("Enter Choice - ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        veiw_completed_delivery();
    }
    else if (choice == 2)
    {
        veiw_incomplete_delivery();
    }
    else
    {
        system("clear");
        printf("Enter Correct Option\n");
        view_deliveries();
    }
}

void modify_lunch()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t LUNCH MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FILE *file;
    file = fopen("lunch.dat", "rb+");

    lunch l;
    int id;
    printf("Enter Lunch id");
    scanf("%d", &id);

    while (fread(&l, sizeof(lunch), 1, file) == 1)
    {
        if (l.id == id && !l.completed)
        {
            printf("Enter Date dd mm yyyy - ");
            scanf("%d %d %d", &l.date.date, &l.date.month, &l.date.year);

            printf("Enter Time (hh mm) - ");
            scanf("%d %d", &l.hour, &l.min);

            printf("Enter Number Chapatis - ");
            scanf("%d", &l.roti);

            fseek(file, -sizeof(lunch), SEEK_CUR);
            fwrite(&l, sizeof(lunch), 1, file);
            system("clear");
            printf("success");
            fclose(file);
            return;
        }
    }
    fclose(file);
    system("clear");
    printf("Couldn't Edit The Details (Completed or no ID found)");
}

void mark_done()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t LUNCH MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FILE *file;
    file = fopen("lunch.dat", "rb+");
    int id;
    printf("Enter Lunch ID -");
    scanf("%d", &id);
    lunch l;
    while (fread(&l, sizeof(lunch), 1, file) == 1)
    {
        if (l.id == id && !l.completed)
        {
            l.completed = 1;
            fseek(file, -sizeof(lunch), SEEK_CUR);
            fwrite(&l, sizeof(lunch), 1, file);
            system("clear");
            printf("Success\n");
            fclose(file);
            return;
        }
    }
    system("clear");
    printf("Couldn't Mark it Done (Already Completed or No ID Found)");
    fclose(file);
}

void student_lunch_history()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t LUNCH MANAGEMENT\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FILE *file;
    file = fopen("lunch.dat", "rb");
    lunch l;

    int stu_id;
    printf("Enter Student ID - ");
    scanf("%d", &stu_id);
    while (fread(&l, sizeof(lunch), 1, file) == 1)
    {
        if (stu_id == l.stu.student_id)
        {
            printf("\n\n===========ID - %d===========\n\n", l.id);
            printf("%d. Name -%s\n", l.stu.student_id, l.stu.name);
            printf("date - %d %d %d \ntime - %d:%d\n", l.date.date, l.date.month, l.date.year, l.hour, l.min);
            printf("chapatii -%d\n", l.roti);
        }
    }
    fclose(file);
    getchar();
    getchar();
    system("clear");
}

void manage_lunch()
{
    while (1)
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\t LUNCH MANAGEMENT\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. Sumbit Lunch Box Request\n");
        printf("2. Modify The Request\n");
        printf("3. Mark Delivery Done\n");
        printf("4. Veiw Deliveries\n");
        printf("5. Veiw Student Lunch History\n");
        printf("6. Back to Main Menu\n");

        int choice;
        printf("Enter Choice - ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            system("clear");
            submit_lunch_req();
        }
        else if (choice == 2)
        {
            system("clear");
            modify_lunch();
        }
        else if (choice == 3)
        {
            system("clear");
            mark_done();
        }
        else if (choice == 4)
        {
            system("clear");
            view_deliveries();
        }
        else if (choice == 5)
        {
            system("clear");
            student_lunch_history();
        }
        else if (choice == 6)
        {
            system("clear");
            main();
        }
        else
        {
            system("clear");
            printf("Enter Correct Option");
        }
    }
}

int rent()
{
    FILE *file;
    file = fopen("rent.dat", "rb");
    int rent;
    fread(&rent, sizeof(int), 1, file);
    fclose(file);
    return rent;
}

void set_rent()
{
    FILE *file;
    file = fopen("rent.dat", "wb");
    int rent;
    printf("Enter Rent To be Set - ");
    scanf("%d", &rent);
    fwrite(&rent, sizeof(int), 1, file);
    fclose(file);
    printf("Sucesss");
}

void record_payment()
{
    int id;
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t RENT AND PAYEMENT (₹%d)\n", rent());
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Enter Student ID - ");
    scanf("%d", &id);

    FILE *file;
    file = fopen("students.dat", "rb+");

    student s;
    while (fread(&s, sizeof(student), 1, file) == 1)
    {
        if (s.student_id == id && !s.is_paid)
        {
            s.is_paid = 1;
            fseek(file, -sizeof(student), SEEK_CUR);
            fwrite(&s, sizeof(student), 1, file);
            fclose(file);
            system("clear");
            printf("Success\n");
            return;
        }
    }
    system("clear");
    printf("Cant Update Record (Already Paid or No Student Found)\n");
    fclose(file);
}

void pending_students()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t RENT AND PAYEMENT (₹%d)\n", rent());
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    FILE *file;
    file = fopen("students.dat", "rb");
    student s;

    while (fread(&s, sizeof(student), 1, file) == 1)
    {
        if (!s.is_paid && s.active)
        {
            printf("Student ID :%d\nStudent Name -%s\nPhone Number - %s\nRoom Number - %d\nPaid -%s\nCourse - %s\n\n", s.student_id, s.name, s.phone_number, s.room, (s.is_paid ? "yes" : "no"), s.course);
        }
    }
    getchar();
    getchar();
    system("clear");
}
void start_new_month()
{
    FILE *file;
    file = fopen("students.dat", "rb+");

    student s;

    while (fread(&s, sizeof(student), 1, file) == 1)
    {
        s.is_paid = 0;
        fseek(file, -sizeof(student), SEEK_CUR);
        fwrite(&s, sizeof(student), 1, file);
    }
    printf("Sucess\n");
    fclose(file);
}
void rent_payment()
{
    while (1)
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\t RENT AND PAYEMENT (₹%d)\n", rent());
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. Set Monthly Rent\n");
        printf("2. Record Payment\n");
        printf("3. View Pending Students \n");
        printf("4. Start a New Month\n");
        printf("5. Back To Main Menu\n");

        int choice;
        printf("Enter Choice - ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            system("clear");
            set_rent();
        }
        else if (choice == 2)
        {
            system("clear");
            record_payment();
        }
        else if (choice == 3)
        {
            system("clear");
            pending_students();
        }
        else if (choice == 5)
        {
            system("clear");
            main();
        }
        else if (choice == 4)
        {
            system("clear");
            start_new_month();
        }
        else
        {
            system("clear");
            printf("Enter Correct Choice");
        }
    }
}