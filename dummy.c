#include<stdio.h>

int main() {
    FILE *fp = fopen("students.csv", "r");
    int a;
    fscanf(fp,"%d",&a);
    printf("%d",a);
    return 0;
}