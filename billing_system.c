#include<stdio.h>

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