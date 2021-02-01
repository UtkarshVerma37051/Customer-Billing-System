#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
//int check_input(char []);
//float check_price();

int check_input(char s[20])
{
    int i=0;
    int dec_point = 0;
    for(i=0;i<strlen(s);i++)
    {
        if(s[i]=='.')
            dec_point++;
        else
        {
            if(!isdigit(s[i]) || dec_point == 2)
                return 0;
        }
    }
    return 1;
}


float check_price(char s[20])
{
    float num=0.0;
        int validity = check_input(s);
        if(!validity)
            num=0;
        else
        {
            num = atof(s);
            num=(float)((int)(100*num))/100;

        }
        return num;
}



int check_number(char a[20])
{
    int i=0;
    for(i=0;i<strlen(a);i++)
    {
        if(!isdigit(a[i]))
            return 0;
    }
    int n=(int)(atof(a));
    return n;
}
