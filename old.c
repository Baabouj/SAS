#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char first_name[20];
    char last_name[20];
    char cin[10];
    float amount;
} Accounts;

void createNewAccount(Accounts *, int *, int);
void createNewAccounts(Accounts *, int *, int);
void amountsOperations(Accounts *, int, int);
void displayOperations(Accounts *, int);
void addLoyaltyBonus(Accounts *, int);

int main()
{
    int size = 0, repeat = 1, number;

    Accounts *accounts = (Accounts *)malloc(size * sizeof(Accounts));

    do
    {
        int option;

        puts("\n\t\tMenu\n");
        puts("\t- 1 - Create New Account");
        puts("\t- 2 - Create New Accounts");
        puts("\t- 3 - Operations");
        puts("\t- 4 - Display");
        puts("\t- 5 - Loyality");
        puts("\t- 6 - Exit");

        puts("\nChoose Your Option:");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            system("cls");
            puts("Creating New Account");
            accounts = realloc(accounts, (size + 1) * sizeof(Accounts));
            createNewAccounts(accounts, &size, 1);
            printf("\n");
            break;

        case 2:
            system("cls");
            puts("Creating New Accounts");
            puts("How many accounts you want to add? ");
            scanf("%d", &number);
            accounts = realloc(accounts, (size + number) * sizeof(Accounts));
            createNewAccounts(accounts, &size, number);
            printf("\n");
            break;

        case 3:
            system("cls");
            puts("\n\t\tOperations\n");
            puts("\t- 1 - Withdraw");
            puts("\t- 2 - Depose");
            puts("\t- 3 - Back");
            scanf("%d", &number);
            if (number == 3)
            {
                system("cls");
                break;
            }
            amountsOperations(accounts, size, number);
            printf("\n");
            break;

        case 4:
            displayOperations(accounts, size);
            printf("\n");
            break;

        case 5:
            addLoyaltyBonus(accounts, size);
            printf("\n");
            break;

        case 6:
            repeat = 0;
            free(accounts);
            printf("\n");
            break;

        default:
            puts("Command Not Found!");
            printf("\n");
            break;
        }
    } while (repeat);
    return 0;
}

void createNewAccounts(Accounts *accounts, int *size, int number)
{
    for (int i = *size; i < *size + number; i++)
    {
        char cin[10];
        printf("First Name : ");
        scanf("%s", (accounts + i)->first_name);
        printf("Last Name : ");
        scanf("%s", (accounts + i)->last_name);
        printf("CIN : ");
        scanf("%s", cin);
        while (find(accounts, i, cin))
        {
            puts("Oops! This CIN is already in use!\nTry Again!");
            printf("CIN : ");
            scanf("%s", cin);
        }
        strcpy((accounts + i)->cin, cin);
        printf("Amount : ");
        scanf("%f", &(accounts + i)->amount);
        puts("------------------------");
    }

    *size += number;
    puts("Accounts Created Successfully!\n");
}

void amountsOperations(Accounts *accounts, int size, int operation)
{
    char query[10];
    int index;
    float amount;
    if (operation == 1)
    {
        puts("Withdraw");
        puts("Enter CIN");
        scanf("%s", query);
        index = search(accounts, size, query);
        if (index < 0)
            printf("No Account With ID %s\n", query);
        else
        {
            puts("How much money you want to withdraw?");
            scanf("%f", &amount);
            (accounts + index)->amount -= amount;
            display(accounts + index, 1);
            puts("Withdraw Operation is Done Succesfully!!");
        }
    }
    else if (operation == 2)
    {
        puts("Depose");
        puts("Enter CIN");
        scanf("%s", query);
        index = search(accounts, size, query);
        if (index < 0)
            printf("No Account With ID %s\n", query);
        else
        {
            puts("How much money you want to depose?");
            scanf("%f", &amount);
            (accounts + index)->amount += amount;
            display(accounts + index, 1);
            puts("Depose Operation is Done Succesfully!!");
        }
    }
    else
        puts("Operation Not Found");
}
void displayOperations(Accounts *accounts, int size)
{
    int option;
    char query[10];
    float amount;

    if (size == 0)
        puts("No Accounts Yet!!");
    else
    {
        system("cls");
        puts("\n\t\tAccounts\n");
        puts("\t- 1 - Display in Ascendant Order");
        puts("\t- 2 - Display in Descendant Order");
        puts("\t- 3 - Display in Ascendant Order Based on Amount");
        puts("\t- 4 - Display in Descendant Order Based on Amount");
        puts("\t- 5 - Search");
        puts("\t- 6 - Back");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            sort(accounts, size, 1);
            display(accounts, size);
            break;

        case 2:
            sort(accounts, size, 2);
            display(accounts, size);
            break;

        case 3:
            puts("Enter Amount");
            scanf("%f", &amount);
            sort(accounts, size, 1);
            for (int i = 0; i < size; i++)
                if ((accounts + i)->amount > amount)
                    display(accounts + i, 1);

            break;

        case 4:
            puts("Enter Amount");
            scanf("%f", &amount);
            sort(accounts, size, 2);
            for (int i = 0; i < size; i++)
                if ((accounts + i)->amount > amount)
                    display(accounts + i, 1);
            break;

        case 5:
            puts("Enter CIN");
            scanf("%s", query);
            option = search(accounts, size, query);
            if (option < 0)
                printf("No Account With ID %s\n", query);
            break;

        default:
            break;
        }
    }
}

void addLoyaltyBonus(Accounts *accounts, int size)
{
    sort(accounts, size, 1);
    if (size < 3)
    {
        puts("Oops! Operation can't be done!\nThere is less than 3 accounts!");
    }
    else
    {
        puts("\nLoyalty Bonus will be Added To the Following Accounts:");
        display(accounts, 3);
        for (int i = 0; i < 3; i++)
            (accounts + i)->amount *= 1.013;
        puts("\nLoyalty Bonus Added Successfully!");
        display(accounts, 3);
    }
}

//Function to display accounts
void display(Accounts *accounts, int size)
{
    for (int i = 0; i < size; i++)
        printf("Full Name : %s %s , CIN: %s , Amount: %.2f\n", (accounts + i)->first_name, (accounts + i)->last_name, (accounts + i)->cin, (accounts + i)->amount);
}

//Function to sort the accounts. if order = 1, the function will sort them in asc order. if not, it will sort them in desc order.
void sort(Accounts *accounts, int size, int order)
{
    int i, j;
    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
            if (order == 1 ? (accounts + j)->amount < (accounts + j + 1)->amount : (accounts + j)->amount > (accounts + j + 1)->amount)
            {
                Accounts temp = *(accounts + j);
                *(accounts + j) = *(accounts + j + 1);
                *(accounts + j + 1) = temp;
            }
}

//Function to search for an account by its CIN, if it exists the function will display the account and return its index,if not it will return -1.
int search(Accounts *accounts, int size, char query[])
{
    for (int i = 0; i < size; i++)
        if (strcmp((accounts + i)->cin, query) == 0)
        {
            display((accounts + i), 1);
            return i;
        }
    return -1;
}

//Function to find an account by its CIN, if it exist, the function will return 1, if it's not it will return 0.
int find(Accounts *accounts, int size, char query[])
{
    for (int i = 0; i < size; i++)
        if (strcmp((accounts + i)->cin, query) == 0)
            return 1;
    return 0;
}