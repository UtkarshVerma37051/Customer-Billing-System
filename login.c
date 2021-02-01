#include <stdio.h>
#include <conio.h>
#include <string.h>
#include<stdlib.h>
#include <windows.h>
#define SIZE 32
short int checkValid(char*);
void checkStrength(char*);
void resetpassword();


short int alphabetCount=0, digitCount=0;
short int length=0;
short int symbolCount=0;                  //to count symbols like ;'./ etc
int count_reset=3;
void admin();
void LOGIN()
{

    char pwd[SIZE],pd[SIZE],ch;
    char option;
    int count=3;
    //Read inbuild passward
    FILE *fp;
    fp=fopen("abc.txt","r");
    fscanf(fp,"%s",pwd);
    //printf("\n\n%s\n\n",pwd);
    //Login details
    ENTER_PASSWARD:
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n \t\t\t\t\tPLEASE ENTER THE LOGIN PASSWORD: ");
    int p=0;
    do
    {
        pd[p]=getch();
        if(pd[p]!='\r')
        {
            if(pd[p]=='\b')
            {
                p=p-2;
                printf("\b");
                printf(" ");
                printf("\b");
            }
            else
            printf("*");
        }

        p++;
    }while(pd[p-1]!='\r');
    pd[p-1]='\0';

    // Compare Enter passward with inbuild passward
    if(strcmp(pwd,pd)==0)
    {
        printf("\n\n \t\t\t\t\tWELCOME........LOGIN IN SUCESSFULLY ");
        printf("\n\n \t\t\t\t\tPLEASE WAIT . . . ");

        Sleep(1000);
//        system("cls");
//        printf("\nDo you want to reset your password: ");
//        fflush(stdin);
//        scanf("%c",&option);
//        fflush(stdin);
//        if (option == 'y' || option == 'Y')
//        {
//           system("cls");
//           resetpassword();
//        }
//        else
//        {
            //printf("\n\n  EXIT");
            system("cls");
            admin();

            Sleep(1000);
            //exit(0);
//        }

    }
    else
    {
//        count=count-1;
//        if (count!=0)
//        {
//            printf("\n\n \t\t\t\t\tINCORRECT LOGIN Attempt left : %d",count);
//            printf("\n\n \t\t\t\t\tPLEASE WAIT . . . ");
//            Sleep(3000);
//            system("cls");
//            goto ENTER_PASSWARD;
//
//        }
//        else
//           printf("\n\n \t\t\t\t\tINCORRECT LOGIN");
        printf("\n\n \t\t\t\t\tIncorrect Login!");
        printf("\n\n \t\t\t\t\tPLEASE WAIT . . . ");
        Sleep(1000);
        system("cls");
        goto ENTER_PASSWARD;
    }
    fclose(fp);

}

void resetpassword()
{
    char pw[SIZE],c,rpw[SIZE];
    short int count,error,i=0;
    int option;

//    Enter new passward
    Enter:
    //printf("\n****************************** ");
    printf("\nENETR NEW PASSWORD: ");
    int p=0;
    do{
        pw[p]=getch();
        if(pw[p]!='\r')
        {
            printf("*");
        }
        p++;
    }while(pw[p-1]!='\r');
    pw[p-1]='\0';
    length=strlen(pw);
    FILE *fp;
    if( error=checkValid(pw) )
        {
        printf("\n\nIts a valid password");
        checkStrength(pw);

//        RECONFIRM PASSWORD
        printf("\nRECONFIRM PASSWORD: ");
        while( (c=getch()) !='\r')
            {
                rpw[i]=c;
                putchar('*');
                i++;
            }
        rpw[i]='\0';
        length=strlen(rpw);
        }

//        Compair both the Entered and RECONFIRM Passward
        if(strcmp(pw,rpw)==0)
        {
            fp=fopen("abc.txt","w");
            fprintf(fp, "%s", rpw);
            fclose(fp);
            printf("\n\n*******************************");
            printf("\nPASSWORD RESET SUCESSFULLY");
            printf("\n*******************************");
            Sleep(1000);
            system("cls");
        }
        else
        {

//            count_reset=count_reset-1;
//            if (count_reset!=0)
//            {
//                printf("\n\n INCORRECT LOGIN Attempt left : %d",count_reset);
//                Sleep(3000);
                system("cls");
                printf("\nERROR: Password does not match");
                resetpassword();
//            }
//            else
//               printf("\n\n \t\t\t\t\tMore then 3 attemps Cannot Rest passward");
        }
//     else
//        goto Enter;
}

short int checkValid(char *x)
{
    alphabetCount=0;
    digitCount=0;

if(length<6)
{
printf("\n Password should be atleast 6 characters wide");
return 0;
 }

  while((*x)!='\0')
    {
     if( isalpha(*x))
      alphabetCount++;       //alphabet, digits and symbol
     else if( isdigit(*x) )  //count are made to check the
      digitCount++;          //password strength
     else if( isascii(*x) )
      symbolCount++;
     x++;
    }

 if(alphabetCount==length) //this condition is true when u enter
 {                         //only alphabets, which is invalid
  printf("\n ERROR: Password should contain both alphabets and digits");
  return 0;
 }
 else if(digitCount==length) //this condion is true when u enter
 {                           //only digits, which is invalid
  printf("\n ERROR: Password should contain both alphabets and digits");
  return 0;
 }
 else
 return 1;
}

void checkStrength(char *p)
{
  short int strengthVar=0;

  if( length>8 )
  strengthVar++;
  if( symbolCount >= 1 )
  strengthVar++;
  if( digitCount >= alphabetCount )
  strengthVar++;
  if( length>12 )
  strengthVar++;

  printf("\nPASSWORD STRENGTH : ");
  switch(strengthVar)
  {
  case 0 :printf("low\n");
   break;
  case 1 :printf("medium\n");
   break;
  case 2 :printf("fair\n");
   break;
  case 3 :printf("high\n");
   break;
  case 4 :printf("very high\n");
   break;
  }

}























//
//
//#include <stdio.h>
//#include <conio.h>
//#include <string.h>
//#include<stdlib.h>
//#include <windows.h>
//#define SIZE 32
//short int checkValid(char*);
//void checkStrength(char*);
//void resetpassword();
//
//
//short int alphabetCount=0, digitCount=0;
//short int length=0;
//short int symbolCount=0;                  //to count symbols like ;'./ etc
//int count_reset=3;
//void admin();
//void LOGIN()
//{
//
//    char pwd[SIZE],pd[SIZE],ch;
//    char option;
//    int count=3;
//    //Read inbuild passward
//    FILE *fp;
//    fp=fopen("abc.txt","r");
//    fscanf(fp,"%s",pwd);
//    //printf("\n\n%s\n\n",pwd);
//    //Login details
//    ENTER_PASSWARD:
//    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n \t\t\t\t\tPLEASE ENTER THE LOGIN PASSWORD: ");
//    int p=0;
//    do
//    {
//        pd[p]=getch();
//        if(pd[p]!='\r')
//            printf("*");
//        p++;
//    }while(pd[p-1]!='\r');
//    pd[p-1]='\0';
//
//    // Compare Enter passward with inbuild passward
//    if(strcmp(pwd,pd)==0)
//    {
//        printf("\n\n \t\t\t\t\tWELCOME........LOGIN IN SUCESSFULLY ");
//        printf("\n\n \t\t\t\t\tPLEASE WAIT . . . ");
//
//        Sleep(1000);
////        system("cls");
////        printf("\nDo you want to reset your password: ");
////        fflush(stdin);
////        scanf("%c",&option);
////        fflush(stdin);
////        if (option == 'y' || option == 'Y')
////        {
////           system("cls");
////           resetpassword();
////        }
////        else
////        {
//            //printf("\n\n  EXIT");
//            system("cls");
//            admin();
//
//            Sleep(1000);
//            //exit(0);
////        }
//
//    }
//    else
//    {
//        count=count-1;
//        if (count!=0)
//        {
//            printf("\n\n \t\t\t\t\tINCORRECT LOGIN Attempt left : %d",count);
//            printf("\n\n \t\t\t\t\tPLEASE WAIT . . . ");
//            Sleep(3000);
//            system("cls");
//            goto ENTER_PASSWARD;
//
//        }
//        else
//           printf("\n\n \t\t\t\t\tINCORRECT LOGIN");
//    }
//    fclose(fp);
//
//}
//
//void resetpassword()
//{
//    char pw[SIZE],c,rpw[SIZE];
//    short int count,error,i=0;
//    int option;
//
////    Enter new passward
//    Enter:
//    //printf("\n****************************** ");
//    printf("\nENETR NEW PASSWORD: ");
//    int p=0;
//    do{
//        pw[p]=getch();
//        if(pw[p]!='\r')
//        {
//            printf("*");
//        }
//        p++;
//    }while(pw[p-1]!='\r');
//    pw[p-1]='\0';
//
//    length=strlen(pw);
//    FILE *fp;
//    if( error=checkValid(pw) )
//        {
//        printf("\n\nIts a valid password");
//        checkStrength(pw);
//
////        RECONFIRM PASSWORD
//        printf("\nRECONFIRM PASSWORD: ");
//        while( (c=getch()) !='\r')
//            {
//                rpw[i]=c;
//                putchar('*');
//                i++;
//            }
//        rpw[i]='\0';
//        length=strlen(rpw);
//
////        Compair both the Entered and RECONFIRM Passward
//        if(strcmp(pw,rpw)==0)
//        {
//            fp=fopen("abc.txt","w");
//            fprintf(fp, "%s", rpw);
//            fclose(fp);
//            printf("\n\n*******************************");
//            printf("\nPASSWORD RESET SUCESSFULLY");
//            printf("\n*******************************");
//            Sleep(3000);
//            system("cls");
//        }
//        else
//        {
//            printf("\nERROR: Password does not match");
//            count_reset=count_reset-1;
//            if (count_reset!=0)
//            {
//                printf("\n\n INCORRECT LOGIN Attempt left : %d",count_reset);
//                Sleep(3000);
//                system("cls");
//                resetpassword();
//            }
//            else
//               printf("\n\n \t\t\t\t\tMore then 3 attemps Cannot Rest passward");
//        }
//     }
//     else
//        goto Enter;
//}
//
//short int checkValid(char *x)
//{
//    alphabetCount=0;
//    digitCount=0;
//
//if(length<6)
//{
//printf("\n Password should be atleast 6 characters wide");
//return 0;
// }
//
//  while((*x)!='\0')
//    {
//     if( isalpha(*x))
//      alphabetCount++;       //alphabet, digits and symbol
//     else if( isdigit(*x) )  //count are made to check the
//      digitCount++;          //password strength
//     else if( isascii(*x) )
//      symbolCount++;
//
//     x++;
//    }
//
// if(alphabetCount==length) //this condition is true when u enter
// {                         //only alphabets, which is invalid
//  printf("\n ERROR: Password should contain both alphabets and digits");
//  return 0;
// }
// else if(digitCount==length) //this condion is true when u enter
// {                           //only digits, which is invalid
//  printf("\n ERROR: Password should contain both alphabets and digits");
//  return 0;
// }
// else
// return 1;
//}
//
//void checkStrength(char *p)
//{
//  short int strengthVar=0;
//
//  if( length>8 )
//  strengthVar++;
//  if( symbolCount >= 1 )
//  strengthVar++;
//  if( digitCount >= alphabetCount )
//  strengthVar++;
//  if( length>12 )
//  strengthVar++;
//
//  printf("\nPASSWORD STRENGTH : ");
//  switch(strengthVar)
//  {
//  case 0 :printf("low\n");
//   break;
//  case 1 :printf("medium\n");
//   break;
//  case 2 :printf("fair\n");
//   break;
//  case 3 :printf("high\n");
//   break;
//  case 4 :printf("very high\n");
//   break;
//  }
//
//}
//
