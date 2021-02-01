#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    struct details
    {
        char address[100];
        char mob[11];
        char name[30];
    }customer;
    struct node *next;
};
int customer_count=0;

char *adr;
char *mno;
char *nm;


void enter_details(struct node **start);
void write_file(struct node *start);
struct node* get_List();
int search_customer(struct node *start,char s[]);


void enter_details(struct node **start)
{
    struct node *ptr;
    struct node *new_node = malloc(sizeof(struct node));
    new_node->next = NULL;
    while(1)
    {
        printf("\n\tEnter the mobile number :");
        char c;
        int i=0;
        while((c=getchar())!='\n')
        {
            if((i==10) || (c < '0'|| c > '9'))                                   //Checking validity of the entered number.
            {
                i=0;
                break;
            }
            else
            {
                new_node->customer.mob[i]=c;
                i++;
            }
        }
        fflush(stdin);
        if(i==0 || i!=10)
        {
            printf("\tInvalid Number!\n");
            continue;
        }
        new_node->customer.mob[10]='\0';
        break;
    }
    fflush(stdin);
    if(search_customer(*start,new_node->customer.mob))
    {
        printf("\tEnter the name : ");
        gets(new_node->customer.name);
        printf("\tEnter address : ");
        gets(new_node->customer.address);
        if(*start == NULL)                                      // List is empty
        {
            *start = new_node;
        }
        else
        {
            ptr = *start;
            while(ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            ptr->next = new_node;
        }
        customer_count++;
        adr=new_node->customer.address;
        nm=new_node->customer.name;
    }

    mno=new_node->customer.mob;

}

void write_file(struct node *start)
{
    if(start==NULL)
        printf("List is empty.");
    else
    {
        FILE *fptr=fopen("CustomerData.txt","w");
        if(fptr==NULL)                                                      // If file is not created(Memory Full)
        {
            printf("File can not be created.\n");
            fclose(fptr);
            return;
        }
        fprintf(fptr,"%d\n",customer_count);
        struct node *ptr=start;
        while(ptr!=NULL)
        {
            fprintf(fptr,"%s\t",ptr->customer.mob);
            fprintf(fptr,"%s\t",ptr->customer.name);
            fprintf(fptr,"%s\n",ptr->customer.address);
            ptr=ptr->next;
        }
        fclose(fptr);
    }

}

struct node* get_List()
{
    //printf("coming");
    FILE *fptr=fopen("CustomerData.txt","r");
    if(fptr==NULL)
    {
        printf("File does not exist.\n");
        return NULL;
    }
    fscanf(fptr,"%d\n",&customer_count);
    struct node *list=NULL;
    struct node *ptr;

    int i=customer_count;
    //printf("Total Customer : %d.\n",i);
    while(i!=0)
    {
        i--;
        struct node *new_node = malloc(sizeof(struct node));
        new_node->next = NULL;
        fscanf(fptr,"%[^\t]%*c",new_node->customer.mob);
        fscanf(fptr,"%[^\t]%*c",new_node->customer.name);
        fscanf(fptr,"%[^\n]%*c",new_node->customer.address);
        if(list == NULL)
        {
            list = new_node;
        }
        else
        {
            ptr = list;
            while(ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            ptr->next = new_node;
        }
    }
    return list;
}



int search_customer(struct node *start,char s[11])
{
   // printf("Searching for customer :\n");
    struct node *temp=start;
    while(temp!=NULL)
    {
        //printf("comparing %s with %s\n",temp->customer.mob,s);
        if(!(strcmp(temp->customer.mob,s)))
        {
            adr=temp->customer.address;
            nm=temp->customer.name;
            //printf("\tCustomer found\n");
            return 0;
        }

        temp=temp->next;
    }
    //printf("\tCustomer not found\n");
    return 1;
}


void display(struct node *start)
{
    struct node *ptr = start;
    if(ptr==NULL)                                                       //If no data is there in the milk
    {
        printf("No details.\n");
        return ;
    }
    printf("\n%-20s %-20s %s","Name","Mobile Number ","Address :\n");
    while(ptr != NULL)
    {
        printf("%-20s %-20s %s\n",(ptr->customer).name,(ptr->customer).mob, (ptr->customer).address);  //Printing in formatted manner.
        ptr = ptr->next;
    }
    printf("\n");
}



struct node* getdata()
{
    char ch;
    struct node *start=NULL;
    FILE *fptr=fopen("CustomerData.txt","r");
    if(fptr!=NULL)
    {
        start = get_List();
        //printf("List extracted.\n");
    }
    fclose(fptr);

    while(1)
    {
        printf("\tPress 1 to enter customer details :");
        printf("\n\tPress 2 to exit :\n\t");
        fflush(stdin);
        scanf("%c",&ch);
        fflush(stdin);
        if(ch=='2')
            break;
        switch(ch)
        {
            case '1' : enter_details(&start);
                     write_file(start);
                     goto br;
            break;

            default :printf("\tInvalid Choice.\n\n");
            break;
        }
    }
    br : return start;
}

