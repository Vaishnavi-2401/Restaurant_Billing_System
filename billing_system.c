#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define TAX_RATE 0.09
#define DISCOUNT_RATE 0.10


typedef struct 
{
        char customer[50];
        char date[50];
        int item_count;
        float total;
}invoice;


typedef struct
{
        char name[50];
        float price;
}menu_item;


//menu list
menu_item menu[] = 
{
        {"Pizza", 110.00}, {"Burger", 40.00}, {"Pasta", 140.00}, {"Sandwich", 60.00},
        {"Coffee", 25.00}, {"French Fries", 50.00}, {"Garlic Bread", 15.00}, 
        {"Pan Cake", 100.50}, {"Ice-cream", 80.00}, {"Cold-Drinks", 20.00}
};
    

int menu_size = sizeof(menu) / sizeof(menu[0]);


//to display menu list
void display_menu()
{
        printf("------ MENU LIST ------\n\n");

        for(int i = 0; i < menu_size; i++)
        {
                printf("%d. %s - $%.2f\n", i + 1, menu[i].name, menu[i].price);
        }

        printf("-------------------------\n");
}


//bill header
void bill_header(char date[], char name[])
{
        printf("Hotel Krishna\n");

        printf("-------------\n");

        printf("Date : %s\n", date);
        printf("Invoice To : %s\n", name);

        printf("-------------\n");

        printf("Item\tQty\tPrice\tTotal\n");

        printf("-------------\n");
}


//bill body
void bill_body(char item[], int qty, float price)
{
        printf("%-15s %5d %8.2f %8.2f\n", item, qty, price, qty * price);
}


//bill footer
void bill_footer(float total)
{
        float discount = total * DISCOUNT_RATE;
        float net_total = total - discount;
        float tax = net_total * TAX_RATE;
        float grand_total = net_total + (2 * tax);

        printf("-------------\n");

        printf("Sub Total : %.2f\n", total);
        printf("Discount @10%% : %.2f\n", discount);
        printf("Net Total : %.2f\n", net_total);
        printf("CGST @9%% : %.2f\n", tax);
        printf("SGST @9%% : %.2f\n", tax);

        printf("-------------\n");

        printf("Grand Total : %.2f\n", grand_total);

        printf("-------------\n");
}


//main
int main()
{
    int choice;

    do
    {
        printf("------ HOTEL KRISHNA ------\n\n");
        printf("1. Generate Invoice\n");
        printf("2. Show all Invoices\n");
        printf("3. Search Invoice\n");
        printf("4. Exit\n");

        printf("Enter your Choice : \n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                    generate_invoice();
                    break;

            case 2:
                    show_all_invoices();
                    break;

            case 3:
                    search_invoice();
                    break;

            case 4:
                    printf("Exiting...\n");
                    break;

            default:
                    printf("Invalid Choice. Try Again!\n");
        }

    } while (choice != 4);

    return 0;

}