#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TAX_RATE 0.09
#define DISCOUNT_RATE 0.10


typedef struct 
{
    char customer[50];
    char date[15];
    int item_count;
    float total;
}Invoice;


typedef struct 
{
    char name[20];
    float price;
}Menu_Item;


//Menu List
Menu_Item menu[] = 
{
    {"Pizza", 110.00}, {"Burger", 40.00}, {"Pasta", 140.00}, {"Sandwich", 60.00},
    {"Coffee", 25.00}, {"French Fries", 50.00}, {"Garlic Bread", 15.00}, 
    {"Pan Cake", 100.50}, {"Ice-cream", 80.00}, {"Cold-Drinks", 20.00}
};

int menu_size = sizeof(menu) / sizeof(menu[0]);


//to display menu
void display_menu() 
{
    printf("\n\t------ MENU LIST ------\n\n");

    for(int i = 0; i < menu_size; i++) 
    {
        printf("%d. %s - $%.2f\n", i + 1, menu[i].name, menu[i].price);
    }

    printf("--------------------------------\n");
}


//bill header
void bill_header(char date[], char name[]) 
{
    printf("\n\n\tHotel Krishna\n\t");

    printf("------------\n");

    printf("Date : %s\n", date);
    printf("Invoice To : %s\n", name);

    printf("------------\n");

    printf("Item\t\tQty\tPrice\tTotal\n");

    printf("------------\n");
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

    printf("------------\n");

    printf("Sub Total : \t%.2f\n", total);
    printf("Discount @10%% : \t%.2f\n", discount);
    printf("Net Total : \t%.2f\n", net_total);
    printf("CGST @9%% : \t%.2f\n", tax);
    printf("SGST @9%% : \t%.2f\n", tax);

    printf("------------\n");

    printf("Grand Total : \t%.2f\n", grand_total);

    printf("------------\n");
}


//generate invoice
void generate_invoice() 
{
    Invoice invoice;

    printf("Enter customer name : ");
    scanf(" %49[^\n]", invoice.customer);

    printf("Enter date (DD/MM/YYYY) : ");
    scanf(" %14[^\n]", invoice.date);

    display_menu();
    
    printf("Enter number of items : ");
    scanf("%d", &invoice.item_count);

    char items[invoice.item_count][20];
    int quantities[invoice.item_count];
    float total_price[invoice.item_count];
    invoice.total = 0;

    for(int i = 0; i < invoice.item_count; i++) 
    {
        int item_number, quantity;
        
        printf("Enter item number : ");
        scanf("%d", &item_number);

        printf("Enter quantity : ");
        scanf("%d", &quantity);

        if(item_number < 1 || item_number > menu_size) 
        {
            printf("Invalid item number. Try again!\n");

            i--;
            continue;
        }

        strcpy(items[i], menu[item_number - 1].name);
        quantities[i] = quantity;
        total_price[i] = menu[item_number - 1].price * quantity;
        invoice.total += total_price[i];
    }

    bill_header(invoice.date, invoice.customer);

    for(int i = 0; i < invoice.item_count; i++) 
    {
        bill_body(items[i], quantities[i], total_price[i] / quantities[i]);
    }

    bill_footer(invoice.total);

    FILE *fp = fopen("invoices.txt", "a");

    if(fp != NULL) 
    {
        fprintf(fp, "%s|%s|", invoice.customer, invoice.date);

        for(int i = 0; i < invoice.item_count; i++) 
        {
            fprintf(fp, "%s-%d ", items[i], quantities[i]);
        }
        fprintf(fp, "|%.2f\n", invoice.total);
        fclose(fp);
    }
}


//show all invoices
void show_all_invoices() 
{
    FILE *fp = fopen("invoices.txt", "r");

    if(fp == NULL) 
    {
        printf("No invoices found.\n");

        return;
    }
    
    char customer[50], date[15], items[150];
    float total;
    
    printf("\n\t------ All Invoices ------\n");

    while (fscanf(fp, " %49[^|]|%14[^|]|%149[^|]|%f\n", customer, date, items, &total) != EOF) 
    {
        printf("\n--------------------------\n");

        printf("Customer : %s\n", customer);
        printf("Date     : %s\n", date);
        printf("Items    : %s\n", items);
        printf("Total Bill : $%.2f\n", total);

        printf("--------------------------\n");
    }

    fclose(fp);
}


void search_invoice() 
{
    char customer[50];

    printf("Enter customer name to search : ");
    scanf(" %49[^\n]", customer);

    FILE *fp = fopen("invoices.txt", "r");

    if(fp == NULL) 
    {
        printf("No invoices found.\n");
        return;
    }

    Invoice invoice;
    char line[200];
    int found = 0;

    while(fgets(line, sizeof(line), fp)) 
    {
        char items[100];

        sscanf(line, "%49[^|]|%14[^|]|%99[^|]|%f", invoice.customer, invoice.date, items, &invoice.total);

        if(strcmp(invoice.customer, customer) == 0) 
        {
            found = 1;

            bill_header(invoice.date, invoice.customer);

            char *token = strtok(items, " ");

            while(token != NULL) 
            {
                char item_name[20];
                int qty;

                sscanf(token, "%[^-]-%d", item_name, &qty);

                float price = 0;

                for(int i = 0; i < menu_size; i++) 
                {
                    if(strcmp(menu[i].name, item_name) == 0) 
                    {
                        price = menu[i].price;
                        break;
                    }
                }

                bill_body(item_name, qty, price);

                token = strtok(NULL, " ");
            }

            bill_footer(invoice.total);
        }
    }
    
    fclose(fp);
    if(!found) 
    {
        printf("No invoices found for %s.\n", customer);
    }
}


int main() 
{
    int choice;
    do 
    {
        printf("\n\t------ HOTEL KRISHNA ------\n\n");

        printf("1. Generate Invoice\n");
        printf("2. Show all Invoices\n");
        printf("3. Search Invoice\n");
        printf("4. Exit\n\n");

        printf("Enter your choice: ");
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
                printf("Invalid choice. Try again!\n");
        }
    } while(choice != 4);
    
    return 0;
}