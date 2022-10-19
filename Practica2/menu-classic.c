#include <stdlib.h>
#include <stdio.h>


static int ShowMainMenu();
static void ShowCustomersMenu();
static void ShowOrdersMenu();
static void ShowProductMenu();
static int ShowProductSubMenu();
static int ShowCustomersSubMenu();
static int ShowOrdersSubMenu();




int main(void){
    int choice=0;

    do{
        choice=ShowMainMenu();
        switch(choice){
            case 1: {
                ShowProductMenu();
            }
                break;
            case 2:{
                ShowOrdersMenu();
            }
                break;
            case 3:{
                ShowCustomersMenu();
            }
                break;
            case 4:{
                printf("Has salido");
            }
                break;

        }

    }while(choice!=4);

    return 0;
}


int ShowMainMenu() {
    int number = 0;
    char buf[16];

    do {
        printf("Este programa mostrará un menú de 4 opciones\n");
        printf("Segun el numero que insertes accederas al submenú correspondiente\n\n");

        printf(" (1) Products\n"
               " (2) Orders\n"
               " (3) Customers\n"
               " (4) Exit\n\n"
               "Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            
            number =0;
        else
            
            number = atoi(buf);
        printf("\n");

        if ((number < 1) || (number > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n");
        }
    } while ((number < 1) || (number > 4));

    return number;
}
void ShowProductMenu() {
    int number= 0;
    do {
        number=ShowProductSubMenu();
        switch (number) {

            case 1: {
                /*StockMenu();*/
            }
                break;

            case 2: {
                /*FindMenu();*/
            }
                break;

            case 3: {
                printf("Has salido");
            }
                break;

        }
    } while (number!= 3);

}
int ShowProductSubMenu() {
    int number = 0;
    char buf[16];

    do {

        printf(" (1) Stock\n"
               " (2) Find\n"
               " (3) Back\n"
               "Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            
            number =0;
        else
            
            number = atoi(buf);
        printf("\n");

        if ((number < 1) || (number > 3)) {
            printf("You have entered an invalid choice. Please try again\n\n");
        }
    } while ((number < 1) || (number > 3));

    return number;
}
int ShowOrdersSubMenu() {
    int number = 0;
    char buf[16];

    do {
        
        printf(" (1) Find\n"
               " (2) List Products\n"
               " (3) Balance\n"
               " (4) Back\n"
               "Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            
            number =0;
        else
            
            number = atoi(buf);
        printf("\n");

        if ((number < 1) || (number > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n");
        }
    } while ((number < 1) || (number > 4));

    return number;
}
int ShowCustomersSubMenu() {
    int number = 0;
    char buf[16];

    do {

        printf(" (1) Open\n"
               " (2) Range\n"
               " (3) Detail\n"
               " (4) Back\n"
               "Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            
            number =0;
        else
            
            number = atoi(buf);
        printf("\n");

        if ((number < 1) || (number > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n");
        }
    } while ((number < 1) || (number > 4));

    return number;
}
void ShowCustomersMenu() {
    int number= 0;
    do {
        number=ShowCustomersSubMenu();
        switch (number) {

            case 1: {
                /*FindMenu();*/
            }
                break;

            case 2: {
                /*ListProductsMenu();*/
            }
                break;

            case 3: {
                /*BalanceMenu();*/
            }
                break;
            case 4: {
                printf("Has salido");
            }
                break;

        }
    } while (number != 4);

}
void ShowOrdersMenu() {
    int number= 0;
    do {
        number=ShowOrdersSubMenu();
        switch (number) {

            case 1: {
                /*OpenMenu();*/
            }
                break;

            case 2: {
                /*RangeMenu();*/
            }
                break;

            case 3: {
                /*DetailMenu();*/
            }
                break;
            case 4: {
                printf("Has salido");
            }
                break;

        }
    } while (number != 4);

}