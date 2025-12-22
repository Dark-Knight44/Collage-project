#include<stdio.h>
#include<stdbool.h>
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


typedef struct {
    int rno;
    student students[3];
    int count;
    bool lock ;
}room;

void main(){
    FILE *fp = fopen("rooms.dat", "wb");
    if (fp == NULL) {
        printf("Cannot create rooms file\n");
        return;
    }

    room r;

    for (int i = 1; i <= 30; i++) {
        r.rno = i;
        r.count = 0;       // ✅ INITIALIZED
        r.lock = false;    // ✅ INITIALIZED

        // optional: clear student slots
        memset(r.students, 0, sizeof(r.students));

        fwrite(&r, sizeof(room), 1, fp);
    }

    fclose(fp);}