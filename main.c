
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

        printf("\n\t\tMenu\n\n\t- 1 - Create An Account\n\t- 2 - Create New Accounts\n\t- 3 - Operations\n\t- 4 - Display\n\t- 5 - Loyality\n\t- 6 - Exit\n");
        scanOption(&option);

        switch (option)
        {
        case 1:
            system("cls");
            puts("Creating New Account");
            accounts = realloc(accounts, (size + 1) * sizeof(Accounts));
            createNewAccounts(accounts, &size, 1);
            break;

        case 2:
            system("cls");
            puts("Creating New Accounts");
            puts("How many accounts you want to add? ");
            scanf("%d", &number);
            accounts = realloc(accounts, (size + number) * sizeof(Accounts));
            createNewAccounts(accounts, &size, number);
            break;

        case 3:
            system("cls");
            printf("\n\t\tOperations\n\n\t- 1 - Withdraw\n\t- 2 - Depose\n\t- 3 - Back\n");
            scanOption(&number);
            if (number == 3)
            {
                system("cls");
                break;
            }
            amountsOperations(accounts, size, number);
            break;

        case 4:
            displayOperations(accounts, size);
            break;

        case 5:
            addLoyaltyBonus(accounts, size);
            break;

        case 6:
            repeat = 0;
            free(accounts);
            break;

        default:
            puts("Command Not Found!");
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
    float amount;
    system("cls");
    if (operation == 1)
    {
        puts("\n\t\tWithdraw\n");
        scanCard(query);
        if (find(accounts, size, query))
        {
            puts("How much money you want to withdraw?");
            scanf("%f", &amount);
            int index = findIndex(accounts, size, query);
            (accounts + index)->amount -= amount;
            display(accounts + index, 1);
            puts("Withdraw Operation is Done Succesfully!!");
        }
        else
            printf("No Account With ID %s\n", query);
    }
    else if (operation == 2)
    {
        puts("\n\t\tDepose\n");
        scanCard(query);
        if (find(accounts, size, query))
        {
            puts("How much money you want to withdraw?");
            scanf("%f", &amount);
            int index = findIndex(accounts, size, query);
            (accounts + index)->amount += amount;
            display(accounts + index, 1);
            puts("Withdraw Operation is Done Succesfully!!");
        }
        else
            printf("No Account With ID %s\n", query);
    }
}
void displayOperations(Accounts *accounts, int size)
{
    int option;
    char query[10];
    float amount;
    system("cls");
    if (size == 0)
        puts("No Accounts Yet!!");
    else
    {
        system("cls");
        printf("\n\t\tAccounts\n\n\t- 1 - Display in Ascendant Order\n\t- 2 - Display in Descendant Order\n\t- 3 - Display in Ascendant Order Based on Amount\n\t- 4 - Display in Descendant Order Based on Amount\n\t- 5 - Search\n\t- 6 - Back\n");
        scanOption(&option);
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
            scanCard(query);
            int index = findIndex(accounts, size, query);
            if (index >= 0)
                display(accounts + index, 1);
            else
                printf("No Account With ID %s\n", query);
            break;

        default:
            break;
        }
    }
}

void addLoyaltyBonus(Accounts *accounts, int size)
{
    system("cls");
    sort(accounts, size, 1);
    if (size < 3)
        puts("Oops! Operation can't be done!\nThere is less than 3 accounts!");
    else
    {
        int option;
        puts("\n\t\tBonus\n\nLoyalty Bonus will be Added To the Following Accounts:\n");
        display(accounts, 3);
        puts("\n\t- 1 - Continue\n\t- 2 - Back\n");
        scanOption(&option);
        if (option == 1)
        {
            for (int i = 0; i < 3; i++)
                (accounts + i)->amount *= 1.013;
            puts("\nLoyalty Bonus Added Successfully!");
        }
        else
            system("cls");
    }
}

void scanCard(char *query)
{
    puts("Enter CIN");
    scanf("%s", query);
}

void scanOption(int *option)
{
    printf("\n\tChoose Your Option: ");
    scanf("%d", option);
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

//Function to find an account by its CIN, if it exist, the function will return 1, if it's not it will return 0.
int find(Accounts *accounts, int size, char query[])
{
    for (int i = 0; i < size; i++)
        if (strcmp((accounts + i)->cin, query) == 0)
            return 1;
    return 0;
}

//Function to find an account by its CIN, if it exist, the function will return its index, if it's not it will return -1.
int findIndex(Accounts *accounts, int size, char query[])
{
    for (int i = 0; i < size; i++)
        if (strcmp((accounts + i)->cin, query) == 0)
            return i;
    return -1;
}