#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items
{
    char item[50];
    float price;
    int qty;
};


struct orders
{
    char customer[100];
    char date[20];
    int num_of_items;
    struct items itm[50];
};


void display_menu() 
{
    printf("\n\t------ MENU LIST ------\n\n");

    printf("1. Pizza - $110.00\n");
    printf("2. Burger - $40.00\n");
    printf("3. Pasta - $140.00\n");
    printf("4. Sandwich - $60.00\n");
    printf("5. Coffee - $25.00\n");
    printf("6. French Fries - $50.00\n");
    printf("7. Garlic Bread - $15.00\n");
    printf("8. Pan Cake - $100.50\n");
    printf("9. Ice-cream - $80.00\n");
    printf("10. Cold-Drinks - $20.00\n");

    printf("--------------------------------\n");
}


//to generate bill (header, body, footer)
void bill_header(char date[], char name[])
{
    printf("\n\n\t");

    printf("Hotel Krishna\n\t");

    printf("------------\n");

    printf("Date : %s\n", date);
    printf("Invoice To : %s\n", name);
    
    printf("------------\n");

    printf("Item\t  Qty\t   Price\t   Total\n");

    printf("------------\n");
}


void bill_body(char item[], int qty, float price)
{
    printf("%-20s %5d %10.2f %10.2f\n", item, qty, price, qty * price);
}


void bill_footer(float total)
{
    float dis = total * 0.10;
    float net_total = total - dis;
    float tax = net_total * 0.09;
    float grand_total = net_total + (2 * tax);

    printf("------------\n");

    printf("Sub Total : \t %.2f\n", total);
    printf("Discount @10 : \t %.2f\n", dis);
    printf("Net Total : \t %.2f\n", net_total);
    printf("CGST @9 : \t %.2f\n", tax);
    printf("SGST @9 : \t %.2f\n", tax);

    printf("------------\n");

    printf("Grand Total : \t %.2f", grand_total);

    printf("------------\n");
}


int main() {
    int num;
    struct orders ord;
    float total = 0;
    char save_bill;
    FILE *fp;
    char name[100];

    // Dashboard menu
    printf("\n\t------ HOTEL KRISHNA ------\n\n");
    printf("1. Generate Invoice\n");
    printf("2. Show all Invoices\n");
    printf("3. Search Invoice\n");
    printf("4. Exit\n\n");
    printf("Please select your preference : ");
    scanf("%d", &num);
    getchar();

    switch (num) {
        case 1:
            printf("\nEnter the Name of the Customer : ");
            fgets(ord.customer, 100, stdin);
            ord.customer[strcspn(ord.customer, "\n")] = 0;

            printf("\nEnter Date (DD/MM/YYYY) : ");
            scanf("%s", ord.date);

            display_menu();

            printf("\nEnter the Number of Items : ");
            scanf("%d", &ord.num_of_items);

            for (int i = 0; i < ord.num_of_items; i++) {
                printf("\nEnter Item %d Name : ", i + 1);
                scanf("%s", ord.itm[i].item);
                printf("\nEnter Quantity: ");
                scanf("%d", &ord.itm[i].qty);
                printf("\nEnter Price : ");
                scanf("%f", &ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }

            bill_header(ord.date, ord.customer);
            for (int i = 0; i < ord.num_of_items; i++) {
                bill_body(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            bill_footer(total);

            printf("Do you want to Save the Bill (y/n) : ");
            scanf(" %c", &save_bill);

            if (save_bill == 'y' || save_bill == 'Y') {
                fp = fopen("Hotel_KRISHNA_Bill.txt", "a+");
                if (fp == NULL) {
                    printf("Error Saving Bill...\n");
                    return 1;
                }
                fwrite(&ord, sizeof(struct orders), 1, fp);
                fclose(fp);
                printf("Bill Saved Successfully!\n");
            }
            break;

        case 2:
            fp = fopen("Hotel_KRISHNA_Bill.txt", "r");
            if (fp == NULL) {
                printf("No invoices found!\n");
                break;
            }
            while (fread(&ord, sizeof(struct orders), 1, fp)) {
                total = 0;
                bill_header(ord.date, ord.customer);
                for (int i = 0; i < ord.num_of_items; i++) {
                    bill_body(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                    total += ord.itm[i].qty * ord.itm[i].price;
                }
                bill_footer(total);
                printf("\n-----------------------------------\n");
            }
            fclose(fp);
            break;

        case 3:
            printf("Enter the name of the customer : ");
            getchar();
            fgets(name, 100, stdin);
            name[strcspn(name, "\n")] = 0;
            fp = fopen("Hotel_KRISHNA_Bill.txt", "r");
            if (fp == NULL) {
                printf("No invoices found!\n");
                break;
            }
            while (fread(&ord, sizeof(struct orders), 1, fp)) {
                total = 0;
                if (strcmp(ord.customer, name) == 0) {
                    bill_header(ord.date, ord.customer);
                    for (int i = 0; i < ord.num_of_items; i++) {
                        bill_body(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                        total += ord.itm[i].qty * ord.itm[i].price;
                    }
                    bill_footer(total);
                    printf("\n-----------------------------------\n");
                }
            }
            fclose(fp);
            break;

        case 4:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid option! Please choose a valid number.\n");
    }

    return 0;
}



//price should be generated automatically after entering item
//only items from the menu list are to be entered not other than it