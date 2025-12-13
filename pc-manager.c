#include<stdio.h>
#include<stdbool.h>
struct pc{
    int pc_id;
    bool status;
    char games[10][100];
};

struct customer{
    int cus_id;
    char name[20];
    char pin[3];
    int phone_number;
};

void pc_management(){
    printf("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    printf("\t PC MANAGEMENT\n");
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
    printf("1. Add PC\n");
    printf("2. Remove Game \n");
    printf("3. View All Games\n");
    printf("4. Assign Game To Pc\n");
    printf("5. View Games Assigned to PCs\n");
    printf("6. Back to Main Menu\n");

    int choice;

    printf("Enter Your Choice - ");
    scanf("%d",&choice);
}

void user_management(){
    printf("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    printf("\t USER SESSION MANAGEMENT\n");
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
    printf("1. Start New Session\n");
    printf("2. End Session\n");
    printf("3. Search Session by User ID\n");
    printf("4. View Active Session\n");
    printf("5. Back to Main Menu\n");

    int choice;

    printf("Enter Your Choice - ");
    scanf("%d",&choice);
}


int main(){
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    printf("\t GAMING CAFE MANAGEMENT\n");
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
    printf("1. PC Management\n");
    printf("2. User Session Management\n");
    printf("3. Game Library\n");
    printf("4. Reports\n");
    printf("5. Save / Load Data\n");
    printf("6. Exit Program\n");    
    
    int choice;

    printf("Enter Your Choice - ");
    scanf("%d",&choice);

    if(choice==1){
        pc_management();
    }else if(choice==2){
        user_management();
    }
    return 0;
}

