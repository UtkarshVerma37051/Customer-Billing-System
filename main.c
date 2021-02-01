#include <stdio.h>
#include <stdlib.h>
#include "login.c"
#include "Employee.c"

//#include "Inventory.c"
//#include"Customer_Data.c"
//#include "reset_password.c"
int main()
{
    char op;
    while(1)
    {
        system("cls");
        printf("************************************************************************************************************************");
        printf("\n");
        printf("*****************************************    WELCOME TO DENIMXPRESS    *************************************************");
        printf("\n");
        printf("\t                               YOU ARE LUCKY TO BE SHOPPING HERE");
        printf("\n\n");
        printf("\t\t\tPlease note that all the Product's Price are Discounted and are Genuine");
        printf("\n");
        printf("\n\t");
        printf("****************************");
        printf("\n");
        printf("\t");
        printf("Please Select an Option: ");
        printf("\n");
        printf("\t");
        printf("****************************");
        printf("\n");
        printf("\t");
        printf("01. ADMINISTRATOR :");
        printf("\n\t");
        printf("02. CUSTOMER :");
        printf("\n\t");
        printf("03. EXIT :");
        printf("\n");
        printf("\n\t");
        option_loop : printf("Please Enter an Option : ");
        fflush(stdin);
        scanf("%c",&op);
        fflush(stdin);
        if(op=='3')
            break;
        if((op!='1')&&(op!='2'))
        {
            printf("\tInvalid option!\n\n\t");
            goto option_loop;
        }
        switch(op)
        {
            case '1' :  system("cls");
                        LOGIN();
            break;
            case '2' :  system("cls");
                        emp();
            break;
            default : printf("Invalid Choice.");
        }
    }
	return 0;
}

