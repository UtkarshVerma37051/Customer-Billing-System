#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<stdlib.h>
#include"Customer_Data.c"
#include"Inventory.c"
//#include"login.c"

struct inventory_node *m_inv;
struct customer_cart
{
    int productno;
	char *productname;
	int quantity;
	float price;
	float pricetopay;
	struct customer_cart *next;
};
struct customer_cart *cstmr_cart;
struct node *cstmr_list;

void cart();
void add_to_my_cart(struct inventory_node *tmp,int quant,struct customer_cart **cst_cart,int original_quant);
void display_customer_cart(struct customer_cart *start);
int  search_mycart(struct customer_cart **start,int prdctno,int pquant,int original_quant);
void generate_bill(struct customer_cart *start);
void delete_customer_cart(struct customer_cart **start);
void dlt_prdct_cstmr_cart(struct customer_cart **start);
void updt_inventory(struct inventory_node **minv,struct customer_cart *cst_crt);
void add_bill_records(struct customer_cart *start);



void cart()
{
    int pno,quant;
    struct inventory_node *prdct;
    while(1)
    {
        ch_1 :printf("\n\tEnter the Product No. :");
        char c[20];
        scanf("%s",c);
        fflush(stdin);
        int v=check_number(c);                                                  //Checking validity of product number.
        if(v==0)
        {
            printf("\tINVALID INPUT\n");
            goto ch_1;
        }
        else
            pno = v;

        prdct= search_inventory(m_inv,pno);
        if(prdct==NULL)
        {
            printf("\tProduct Not Found.\n");
            goto l;
        }
        else
        {
            ch_2 : printf("\tEnter the Quantity : ");
            fflush(stdin);
            scanf("%s",c);
            fflush(stdin);
            v=check_number(c);                                                  //Checking validity of product number.
            if(v==0)
            {
                printf("\n\tINVALID INPUT\n");
                goto ch_2;
            }
            else
                quant = v;

            if((prdct->quantity) >= quant)
            {
                add_to_my_cart(prdct,quant,&cstmr_cart,prdct->quantity);
                system("cls");
                display_customer_cart(cstmr_cart);

            }
            else
            {
                printf("\tOut of stock!\n");
            }
        }
        l : printf("\n\tPress 1 to continue adding :");
        printf("\n\tPress 2 to exit :\n\t");
        char ch;
        fflush(stdin);
        scanf("%c",&ch);
        if(ch=='2')
            break;
        else if(ch=='1')
            continue;
        else
        {
            printf("\tInvalid Choice.\n");
            goto l;
        }
    }

}

void add_to_my_cart(struct inventory_node *tmp,int quant,struct customer_cart **cst_cart,int original_quant)
{
    struct customer_cart *ptr;
    struct customer_cart *new_node = malloc(sizeof(struct customer_cart));
    int found=0;
    if(*cst_cart!=NULL)
    {
        found = search_mycart(cst_cart,tmp->productno,quant,original_quant);
        if(found)
            return;

    }
    new_node->next=NULL;
    new_node->productno=tmp->productno;
    new_node->productname=tmp->productname;
    new_node->price=tmp->price;
    new_node->quantity=quant;
    new_node->pricetopay=(tmp->price)*quant;
    if(*cst_cart==NULL)
    {
        *cst_cart=new_node;
    }
    else
    {
        ptr=*cst_cart;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        ptr->next=new_node;
    }
}


void display_customer_cart(struct customer_cart *start)
{
    float total_price=0;
    if(start==NULL)
    {
        system("cls");
        printf("\tCart is empty.\n");
        return ;
    }
    struct customer_cart *ptr;
    ptr=start;
    printf("\n\t%-16s %-16s %-20s %-16s %-16s","Product Number","Product Name","Product Quantity","Product Price","Total Price");
    while(ptr!=NULL)
    {
        printf("\n\t%-16d %-16s %-20d %-16.2f %-16.2f",ptr->productno,ptr->productname,ptr->quantity,ptr->price,ptr->pricetopay);
        total_price+=(ptr->pricetopay);
        ptr=ptr->next;
    }
    printf("\n\tAmount Payable : Rs.%.2f\n",total_price);
}




int search_mycart(struct customer_cart **start,int prdctno,int pquant,int original_quant)
{
    struct customer_cart *ptr;
    ptr=*start;
    while(ptr!=NULL)
    {
        if(ptr->productno == prdctno)
        {
            if((ptr->quantity + pquant)>original_quant)
            {
                printf("\n\tOut of Stock.\n");
                //printf("\n\tRemaining Quantity : %d.\n",(original_quant-ptr->quantity));
                return 1;
            }
//            printf("\n\tProduct found.\n");
            ptr->quantity = ptr->quantity + pquant;
            ptr->pricetopay = ptr->price * ptr->quantity;
            return 1;
        }
        ptr=ptr->next;
    }
    return 0;
}







void generate_bill(struct customer_cart *start)
{
    if(start==NULL)
    {
        printf("\tCart is empty.\n");
        return;
    }
    float total_price=0;
    printf("\t*************************************************INVOICE******************************************************");
	printf("");
//	printf("product number\t| product name\t| price\t| quantity\t| amount\t|\n");
//	printf("*************************************************************\n");
    printf("\n\tCustomer Name     : %s",nm);
    printf("\n\tCustomer Mob. No. : %s",mno);
    printf("\n\tCustomer Address  : %s\n",adr);
    struct customer_cart *ptr;
    ptr=start;
    printf("\n\t%-16s %-16s %-20s %-16s %-16s","Product Number","Product Name","Product Quantity","Product Price","Total Price");
    while(ptr!=NULL)
    {
        printf("\n\t%-16d %-16s %-20d %-16.2f %-16.2f",ptr->productno,ptr->productname,ptr->quantity,ptr->price,ptr->pricetopay);
        total_price=total_price + ptr->pricetopay;
        ptr=ptr->next;
    }
    printf("\n\tAmount Payable : Rs.%.2f\n",total_price);
    printf("\n\t**************************************************************************************************************\n");
}




void delete_customer_cart(struct customer_cart **start)
{
    int pno,quant;
    char choice;
    loop :
    if(*start == NULL)
    {
        system("cls");
        printf("\tCart is empty.\n");
        return;
    }
    ch_3 : printf("\n\tEnter Product Number : ");
    fflush(stdin);
    //scanf("%d",&pno);
    char c[20];
    scanf("%s",c);
    fflush(stdin);
    int v=check_number(c);                                                  //Checking validity of product number.
    if(v==0)
    {
        printf("\n\tINVALID INPUT");
        goto ch_3;
    }
    else
        pno = v;

    struct customer_cart *ptr;
    struct customer_cart *prv;
    ptr=*start;
    while(ptr!=NULL)
    {
        prv=ptr;
        if(ptr->productno == pno)
        {
            ch_4 : printf("\tEnter the quantity   : ");
            //scanf("%d",&quant);
            fflush(stdin);
            scanf("%s",c);
            fflush(stdin);
            v=check_number(c);                                                  //Checking validity of product number.
            if(v==0)
            {
                printf("\n\tINVALID INPUT\n");
                goto ch_4;
            }
            else
                quant = v;


            if(quant<=ptr->quantity)
            {
                ptr->quantity=ptr->quantity - quant ;
                ptr->pricetopay = ptr->price * ptr->quantity;
                if(ptr->quantity == 0)
                {
                    dlt_prdct_cstmr_cart(start);
                }
                system("cls");
                display_customer_cart(cstmr_cart);
                if(cstmr_cart == NULL)
                    return;
                goto cnt;
            }
            else
            {
                printf("\n\tEntered quantity is greater than present quantity.\n");
                goto cnt;
            }
        }
        ptr=ptr->next;
    }
    printf("\tProduct not found.\n");
    cnt : printf("\n\tPress 1 to continue deleting : ");
    printf("\n\tPress 2 to exit :\n\t");
    fflush(stdin);
    scanf("%c",&choice);
    fflush(stdin);
    if(choice == '1')
        goto loop;
    else if(choice != '2')
    {
        printf("\tInvalid Choice!");
        goto cnt;
    }

    else
        system("cls");
}

void dlt_prdct_cstmr_cart(struct customer_cart **start)
{
    struct customer_cart *ptr;
    struct customer_cart *prev;
    ptr=*start;
    if(ptr->next==NULL)
    {
        *start=NULL;
        return;
    }
    struct customer_cart *trav;
    if(ptr->quantity == 0)
    {
        *start=ptr->next;
        return;
    }
    while(ptr!=NULL && ptr->quantity!=0)
    {
        prev=ptr;
        ptr=ptr->next;
    }
    prev->next=ptr->next;
}





void updt_inventory(struct inventory_node **minv,struct customer_cart *cst_crt)
{
    struct customer_cart *trav_cart;
    struct inventory_node *trav_inv;
    trav_cart = cst_crt ;
    trav_inv  = *minv ;
    while(trav_cart!=NULL)
    {
        while(trav_inv!=NULL)
        {
            if(trav_inv->productno == trav_cart->productno)
            {
                trav_inv->quantity -= trav_cart->quantity;
                if(trav_inv->quantity == 0)
                    count_inventory--;
                break;
            }
            trav_inv=trav_inv->next;
        }
        trav_cart = trav_cart->next;
    }

}


void emp()
{

    while(1)
    {
        lst : cstmr_list=getdata();                                // Checking if customer present or not.
        m_inv=get_inventory();
//        display_inventory(m_inv);
//        printf("Printing customer list :");
//        struct node *trav=cstmr_list;
//        display(trav);
//        printf("Printing Inventory :\n");
//        display_inventory(m_inv);
//        printf("\n\tPrinting present customer data :");
//        printf("\n\tName : %s\n",nm);
//        printf("\tAddress : %s\n",adr);
//        printf("\tMob. No. : %s\n",mno);
        //break;
        if(nm!=NULL)                                        //If customer not present
        {
            char ch;
            system("cls");
            loop :
            printf("\n\t");
            printf("****************************\n\t");
            printf("Please Select an Option : ");
            printf("\n");
            printf("\t");
            printf("****************************\n\t");
            printf("\n");
            printf("\t");
            printf("01.ADD TO CART :");
            printf("\n\t");
            printf("02.GENERATE BILL :");
            printf("\n\t");
//            printf("03.DISPLAY :");
//            printf("\n\t");
            printf("03.MYCART :");
            printf("\n\t");
            printf("04.DELETE ITEMS IN CART :");
            printf("\n\t");
            printf("05.EXIT :");
            printf("\n\n\t");
            printf("Please Enter an Option :\n\t");
            op : fflush(stdin);
            scanf("%c",&ch);
            fflush(stdin);
            exit :
            if(ch=='5')
            {
                adr=NULL;
                mno=NULL;
                nm=NULL;
                cstmr_cart=NULL;
                system("cls");
                goto lst;
            }

            switch(ch)
            {
                case '1' :  cart();
                            system("cls");
                            goto loop;
                break;
                case '2' :  system("cls");
                            generate_bill(cstmr_cart);
                            if(cstmr_cart!=NULL)
                            {
                                updt_inventory(&m_inv,cstmr_cart);
                                m_inv=update_inventory(&m_inv);
                                m_inv=get_inventory(m_inv);
                                add_bill_records(cstmr_cart);
                            }
                            if(cstmr_cart!=NULL)
                            {
                                printf("\n\tPress any key to exit :");
                                fflush(stdin);
                                char c=getchar();
                                fflush(stdin);
                                if(c!='m')
                                {
                                    printf("\n\tgoing to exit.");
                                    adr=NULL;
                                    mno=NULL;
                                    nm=NULL;
                                    cstmr_cart=NULL;
                                    system("cls");
                                    goto lst;
                                }
                            }
                            goto loop;
                break;
//                case '3' :  system("cls");
//                            display_inventory(m_inv);
//                            goto loop;
//                break;
                case '3' :  system("cls");
                            display_customer_cart(cstmr_cart);
                            goto loop;
                break;
                case '4' :  delete_customer_cart(&cstmr_cart);
                            //system("cls");
                            goto loop;
                            break;
                default : printf("\tInvalid Choice!\n\n\tPlease enter a valid option : ");
                          goto op;
//                break;
            }
        }
        else
            break;

    }
}


void add_bill_records(struct customer_cart *start)
{
    FILE *fptr;
    fptr = fopen("Bill_Records.txt","r");
    if(fptr == NULL)
    {
        fclose(fptr);
        fptr=fopen("Bill_Records.txt","w");
    }
    else
        fptr = fopen("Bill_Records.txt","a");
    fprintf(fptr,"%s\n\n","**************************************************************");
    fprintf(fptr,"%-15s\t%-10s\t%-15s\n","Name\t","Mob. No.","Address");
    struct customer_cart *ptr;
    ptr=start;
    fprintf(fptr,"%-15s\t%-10s\t%-15s\n",nm,mno,adr);
    fprintf(fptr,"\n%s\n","Products Bought :");
    fprintf(fptr,"%-10s%-12s%-16s%-10s\n","Prdct No.","Prdct Name","Prdct Quantity","Price");
    while(ptr!=NULL)
    {
        fprintf(fptr,"%-10d%-12s%-16d%-10.2f\n",ptr->productno,ptr->productname,ptr->quantity,ptr->pricetopay);
//        fprintf(fptr),"%-20s\t",ptr->productname);
//        fprintf(fptr),"%-20s\t",ptr->quantity);
//        fprintf(fptr),"%-20\t",ptr->price);
//        fprintf(fptr),"%-20s\t",ptr->pricetopay);
        ptr=ptr->next;
    }
    fprintf(fptr,"\n");

    fclose(fptr);
}



