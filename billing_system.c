#include <stdio.h>
#include <string.h>


#define MAX_ITEMS 5
#define DISCOUNT 0.10
#define TAX 0.09


char items[MAX_ITEMS][20] = {"Pizza", "Burger", "Pasta", "Fries", "Coffee"};
float prices[MAX_ITEMS] = {110.0, 40.0, 140.0, 50.0, 25.0};


//to generate invoice
void generate_invoice() 
{
    char customer[50], date[15];
    int item_count, item_no, quantity;
    float total = 0;
    int ordered_items[10], ordered_qty[10];
    int order_index = 0;

    printf("Enter Customer Name : ");
    scanf(" %[^\n]", customer);

    printf("Enter Date (DD/MM/YYYY) : ");
    scanf(" %[^\n]", date);

    printf("\n------ MENU ------\n");

    for(int i = 0; i < MAX_ITEMS; i++) 
    {
        printf("%d. %s - $%.2f\n", i + 1, items[i], prices[i]);
    }

    printf("\nNumber of Items : ");
    scanf("%d", &item_count);

    for(int i = 0; i < item_count; i++) 
    {
        printf("Enter Item Number (1-5) : ");
        scanf("%d", &item_no);

        if(item_no < 1 || item_no > MAX_ITEMS) 
        {
            printf("Invalid Item Number! Try Again!\n");

            i--;

            continue;
        }

        printf("Enter Quantity : ");
        scanf("%d", &quantity);

        ordered_items[order_index] = item_no - 1;
        ordered_qty[order_index] = quantity;
        total = total + (prices[item_no - 1] * quantity);

        order_index++;
    }

    float discount = total * DISCOUNT;
    float net_total = total - discount;
    float tax = net_total * TAX;
    float grand_total = net_total + (2 * tax);

    //to print the bill
    printf("\n\n        --------------------------\n");
    printf("              HOTEL KRISHNA\n");
    printf("        --------------------------\n");
    printf("Customer Name : %s\n", customer);
    printf("Date          : %s\n", date);
    printf("-------------------------------\n");
    printf("Item            Qty     Price\n");
    printf("-------------------------------\n");

    for(int i = 0; i < order_index; i++) 
    {
        int id = ordered_items[i];
        quantity = ordered_qty[i];
        float item_total = prices[id] * quantity;
        printf("%-15s   %2d     %7.2f\n", items[id], quantity, item_total);
    }

    printf("-------------------------------\n");
    printf("Sub Total          : $%7.2f\n", total);
    printf("Discount @10%%      : $%7.2f\n", discount);
    printf("CGST @9%%           : $%7.2f\n", tax);
    printf("SGST @9%%           : $%7.2f\n", tax);
    printf("-------------------------------\n");
    printf("Grand Total        : $%7.2f\n", grand_total);
    printf("-------------------------------\n");
    printf("    Thank You! Visit Again!\n\n");

    //to save invoice
    FILE *fp = fopen("invoices.txt", "a");

    if(fp != NULL) 
    {
        fprintf(fp, "%s|%s|", customer, date);

        for(int i = 0; i < order_index; i++) 
        {
            fprintf(fp, "%s-%d ", items[ordered_items[i]], ordered_qty[i]);
        }

        fprintf(fp, "|%.2f\n", total);

        fclose(fp);
    }
}


//to show all invoices
void show_all_invoices() 
{
    FILE *fp = fopen("invoices.txt", "r");

    char line[200];

    if(fp == NULL) 
    {
        printf("No Invoices Found!\n");

        return;
    }

    printf("\n------ All Invoices ------\n");

    while(fgets(line, sizeof(line), fp)) 
    {
        printf("%s", line);
    }

    fclose(fp);
}


//to search invoice
void search_invoice() 
{
    char search_name[50], name[50], date[15], items_data[100];
    float total;
    int found = 0;

    printf("Enter Customer Name To Search : ");
    scanf(" %[^\n]", search_name);

    FILE *fp = fopen("invoices.txt", "r");

    if(fp == NULL) 
    {
        printf("No Invoices Found!\n");

        return;
    }

    while(fscanf(fp, " %49[^|]|%14[^|]|%99[^|]|%f\n", name, date, items_data, &total) != EOF) 
    {
        if(strcmp(name, search_name) == 0) 
        {
            printf("\n--------------------------\n");
            printf("Customer : %s\n", name);
            printf("Date     : %s\n", date);
            printf("Items    : %s\n", items_data);
            printf("Total    : $%.2f\n", total);
            printf("--------------------------\n");

            found = 1;
        }
    }

    if(!found) 
    {
        printf("No Invoice Found For %s!\n", search_name);
    }

    fclose(fp);
}


int main() 
{
    int choice;
    do 
    {
        printf("\n------ HOTEL KRISHNA ------\n\n");
        printf("1. Generate Invoice\n");
        printf("2. Show all Invoices\n");
        printf("3. Search Invoice\n");
        printf("4. Exit\n\n");

        printf("Enter Your Choice : ");
        scanf("%d", &choice);

        switch(choice) 
        {
            case 1 : 
                generate_invoice(); 
                break;

            case 2 : 
                show_all_invoices(); 
                break;

            case 3 : 
                search_invoice(); 
                break;

            case 4 : 
                printf("THANK YOU!\n"); 
                break;

            default : 
                printf("Invalid choice! Try again!\n");
        }

    } while(choice != 4);

    return 0;
}