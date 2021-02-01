#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<stdlib.h>
#include"check_price.c"
//#include"reset_password.c"
//#include"login.c"
//void resetpassword();
struct inventory_node
{
	int productno;
	char productname[10];
	int quantity;
	float price;
	struct inventory_node *next;
};                                                                                  // Structure of Inventory



struct inventory_node* get_inventory();                                             // Reading Inventory
void display_inventory(struct inventory_node *start);                               // Displaying Inventory
void create_inventory();
void add_inventory(FILE *fptr,struct inventory_node **start);
struct inventory_node* search_inventory(struct inventory_node *start, int pno);     //Searching in inventory.
void modify_inventory(struct inventory_node **start);
void writeinventorytofile(struct inventory_node **start);                           //Write to file
int count_inventory=0;

void admin()
{
    char ch;
    struct inventory_node *start;
    while(1)
    {
        printf("\n\t****************************");
        printf("\n");
        printf("\t");
        printf("Please Select an Option: ");
        printf("\n");
        printf("\t");
        printf("****************************");
        printf("\n");
        printf("\t01.Add to inventory :");
        printf("\n\t");
        printf("02.Delete from inventory :");
        printf("\n\t");
        printf("03.Display :");
        printf("\n\t");
        printf("04.Reset password :");
        printf("\n\t");
        printf("05.Log Out :");
        printf("\n");
        printf("\n");
        printf("\t");
        printf("Please Enter an Option : ");
        valid : fflush(stdin);
        scanf("%c",&ch);
        if(ch=='5')
        {
            printf("\tLogging Out...");
            break;
        }
        switch(ch)
        {
            case '1' :    create_inventory();
            break  ;
            case '2' :    start = get_inventory();
                        modify_inventory(&start);
            break  ;
            case '3' :    start = get_inventory();
                        system("cls");
                        display_inventory(start);
            break  ;
            case '4' :    system("cls");
                        resetpassword();
            break  ;
            default :
                        printf("\tInvalid Option!\n\n\tPlease enter a valid option :");
                        goto valid;
        }
    }
}

void create_inventory()
{
    struct inventory_node *start;
    int i=0,quant=0;
	FILE *inv;
//	inv=fopen("Inventory.txt","r");
//	if(inv==NULL)
//	{
//	    fclose(inv);
//	    inv=fopen("Inventory.txt","w");
//	    start=get_inventory();
//	    add_inventory(inv,&start);
//	    fclose(inv);
//	}
//	else
//    {
//        fclose(inv);
	    start=get_inventory();
        inv=fopen("Inventory.txt","w");
	    add_inventory(inv,&start);
	    fclose(inv);
//    }
}


void display_inventory(struct inventory_node *start)
{
    struct inventory_node *ptr = start;
    if(ptr==NULL)                                                       //If no data is there in the milk
    {
        printf("\tInventory is empty.\n\n");
        return;
    }
    printf("\n\t%-20s %-20s %-20s %s","Product Code","Product Name","Quantity","Price\n");
    while(ptr != NULL)
    {
        printf("\t%-20d %-20s %-20d %.2f\n",ptr->productno,ptr->productname,ptr->quantity,ptr->price);
        ptr = ptr->next;
    }
    printf("\n");
}



struct inventory_node* get_inventory()
{
    FILE *fp=fopen("Inventory.txt","r");
    if(fp==NULL)
    {
        return NULL;
    }
    fscanf(fp,"%d\n",&count_inventory);
    //printf("\tTotal Product : %d",count_inventory);
    struct inventory_node *list=NULL;
    struct inventory_node *ptr;
    int i=count_inventory;
    //printf("Total Product : %d.\n",i);
    while(i!=0)                                                                     //Reading data from file and storing in linked list.
    {
        i--;
        struct inventory_node *new_node = malloc(sizeof(struct inventory_node));
        new_node->next = NULL;
        fscanf(fp,"%d\t",&new_node->productno);
        fscanf(fp,"%[^\t]%*c",new_node->productname);
        fscanf(fp,"%d\t",&new_node->quantity);
        fscanf(fp,"%f\n",&new_node->price);
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
    fclose(fp);
    return list;                                                                //Returning the address of starting list.
}



void add_inventory(FILE *fptr,struct inventory_node **start)
{
    struct inventory_node *ptr;
    struct inventory_node *found;
    int choice=1;
    while(choice!=2)                                                            //Checking for invalid choice.
    {
        char inp[20];
        printf("\n");
        struct inventory_node *new_node=malloc(sizeof(struct inventory_node));  // Creating node to insert in list.
        new_node->next=NULL;
        fflush(stdin);
        chk_1 : printf("\t");
        printf("Enter Product No. :");
        char c[20];
        scanf("%s",c);
        fflush(stdin);
        int v=check_number(c);                                                  //Checking validity of product number.
        if(v==0)
        {
            printf("\n\tINVALID INPUT\n");
            goto chk_1;
        }
        else
            new_node->productno = v;
        fflush(stdin);
        found = search_inventory(*start,new_node->productno);                   // seaching if product is already present or not.
        if(found!=NULL)
            goto g;
        printf("\t");
        printf("Enter Product Name:");
        scanf("%[^\n]%*c",new_node->productname);
        g : printf("\t");
        printf("Enter Quantity:");
        //scanf("%d",&new_node->quantity);
        scanf("%s",c);
        fflush(stdin);
        v=check_number(c);
        if(v==0)
        {
            printf("\n\tINVALID INPUT\n");
            goto g;
        }
        else
            new_node->quantity = v;
        if(found!=NULL)
        {
            found->quantity += new_node->quantity;
            goto f;
        }
        chk_pr :printf("\tEnter Price:");
        char p[20];
        scanf("%s",p);
        float n= check_price(p);                                //Validating the price entered.
        if(n == 0)
        {
            printf("\n\tINVALID INPUT\n");
            goto chk_pr;
        }
        else
            new_node->price = n;
        fflush(stdin);
        if(*start == NULL)
        {
            *start = new_node;
        }
        else
        {
            ptr = *start;
            while(ptr->next!= NULL)
            {
                //printf("coming");
                ptr = ptr->next;
            }

            ptr->next = new_node;
        }
        count_inventory++;                                              //Incrementinh the number of products.
        f : printf("\n");
        printf("\tEnter 1 to continue :\n\tEnter 2 to exit :\n\t");
        fflush(stdin);

        scanf("%d",&choice);
        if(choice==2)
        {
            system("cls");
            break;
        }
        else if(choice!=1)
        {
            printf("\tInvalid Choice.\n");
            goto f;
        }

    }
    struct inventory_node *temp;
    temp=*start;
    fprintf(fptr,"%d\n",count_inventory);
    while(temp!=NULL)                                           //Finally writing the list to file.
    {
        fprintf(fptr,"%d\t",temp->productno);
        fprintf(fptr,"%s\t",temp->productname);
        fprintf(fptr,"%d\t",temp->quantity);
        fprintf(fptr,"%f\n",temp->price);
        temp=temp->next;
    }
}



struct inventory_node* search_inventory(struct inventory_node *start, int pno)
{
    struct inventory_node *ptr;
    ptr=start;
    while(ptr!=NULL)
    {
        if(ptr->productno==pno)
        {
            return ptr;
        }
        ptr=ptr->next;
    }
    return NULL;
}

struct inventory_node* update_inventory(struct inventory_node **start)          // If whole product is deleted then the list should be updated.
{
    FILE *fptr= fopen("Inventory.txt","w");
    struct inventory_node *temp;
    struct inventory_node *fre;
    temp=*start;
    fprintf(fptr,"%d\n",count_inventory);
    while(temp!=NULL)                                           //writing to file.
    {
        if(temp->quantity!=0)
        {
            //printf("Adding %d\t%s\t%d\t%d\n",temp->productno,temp->productname,temp->quantity,temp->price);
            fprintf(fptr,"%d\t",temp->productno);
            fprintf(fptr,"%s\t",temp->productname);
            fprintf(fptr,"%d\t",temp->quantity);
            fprintf(fptr,"%f\n",temp->price);
        }
        else
            fre=temp;
        temp=temp->next;
    }
    free(fre);
    fclose(fptr);
    if(count_inventory==0)                                          //returning null if inventory is empty.
        return NULL;
    return *start;
}

void modify_inventory(struct inventory_node **start)                            //to ddelete from inventory
{
    int todelete,quantity;
    s : if(*start==NULL)
        printf("\tInventory is empty\n\n");
    else
    {
        not_found : printf("\n\tEnter product No. : ");
        //scanf("%d",&todelete);
        char c[20];
        scanf("%s",c);
        fflush(stdin);
        int v=check_number(c);
        if(v==0)
        {
            printf("\n\tINVALID INPUT\n");
            goto not_found;
        }
        else
            todelete = v;








        struct inventory_node *ptr;
        ptr=*start;
        while(ptr!=NULL)
        {
            //printf("\n\tComparing %d with %d.\n",ptr->productno,todelete);
            if(ptr->productno == todelete && (ptr->quantity)!=0)
            {
                q : printf("\tEnter the quantity to delete : ");
                //scanf("%d",&quantity);
                scanf("%s",c);
                fflush(stdin);
                v=check_number(c);
                if(v==0)
                {
                    printf("\n\tINVALID INPUT\n");
                    goto q;
                }
                else
                    quantity = v;

                if(quantity<=(ptr->quantity))                                               //Validating the quantity entered.
                {
                    (ptr->quantity)=(ptr->quantity) - quantity;                             //Decrementing the quantity by the entered amount.
                    if((ptr->quantity)==0)                                                  //If whole quantity of product is deleted, then deleting it from list.
                    {
                        count_inventory--;
                    }
                    *start = update_inventory(start);                                       //updating list after deletion.
                    if(*start == NULL)
                    {
                        //printf("going to s\n");
                        goto s;
                    }
                    else
                    {
                        //printf("going to d\n");
                        goto d;
                    }

                }
                else
                {
                    printf("\tEntered quantity is greater than quantity present.\n\n");
                    goto q ;
                }
            }
            ptr=ptr->next;
            if(ptr==NULL)
            {
                printf("\tProduct not found.\n\n");
                goto d;
            }
        }
        d : ;
        char choice;
        while(1)
        {
            printf("\n\tEnter 1 to continue :\n\tEnter 2 to exit :\n\t");
            fflush(stdin);
            scanf("%c",&choice);
            if(choice=='2')
            {
                system("cls");
                break;
            }
            else if(choice!= '1')
            {
                printf("\tInvalid choice!\n");
                 continue;
            }
            else
                goto not_found;
        }
    }
}




