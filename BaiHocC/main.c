#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	read_binary_file_category();
	read_binary_file_product();
	read_binary_file_account();
    int choice;
    while(1){
        system("color 7");
        printf("\n\t-=-=-=-Store Management Using C-=-=-=-\n");
        printf("\n\t%25s\n","CHOOSE YOUR ROLE");
        printf("\t%30s\n","*========================*");
        printf("\t%31s\n","[1] Admin (Need Account).");
        printf("\t%19s\n","[2] Employee.");
        printf("\t%27s\n","[0] Exit the Program.");
        printf("\t%30s\n","*========================*");
        printf("\t%19s","Your Choice: ");
        scanf("%d",&choice);
        while(getchar() != '\n');
        switch(choice){
            case 1://Admin usernaem: abc, password: 123
            	adminLogin();
                managerMenuC();
           		break;
            case 2://Employee
            	employeeMenu();
                break;
            case 0://Thoat
                exit(1);
        }
        refresh();
    }
    return 0;
}
