#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


static int ShowMainMenu();
static void ShowCustomersMenu();
static void ShowOrdersMenu();
static int ShowProductMenu();
static int ShowProductSubMenu();
static int ShowCustomersSubMenu();
static int ShowOrdersSubMenu();
int connect_handle(SQLHENV env,SQLHDBC dbc,SQLHSTMT stmt);
int disconnect_handle(SQLHENV env, SQLHDBC dbc, SQLHSTMT stmt);
int StockMenu();

int main(void){
    int choice=0;

    do{
        choice=ShowMainMenu();
        switch(choice){
            case 1: {
                if(ShowProductMenu()==0){
                    return 0;
                }
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
int ShowProductMenu() {
    int number= 0;
    int ret;
    
    do{
        number=ShowProductSubMenu();
        switch (number) {

            case 1: {
                ret=StockMenu();
                if(!ret){
                    return 0;
                }
                return 0;
            }
                

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
    return 0;
}
int StockMenu(){
    SQLHENV env=NULL;
    SQLHDBC dbc=NULL;
    SQLHSTMT stmt=NULL;
    #define Buffer 512
    char x[Buffer]="\0";
    char quantityinstock[Buffer]="\0";
    SQLRETURN ret2;
    int ret;

    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret= SQLPrepare(stmt, (SQLCHAR*) "SELECT quantityinstock FROM products WHERE productcode = ?", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
        
    
    
   
    printf("productcode = ");
    (void) fflush(stdout);
    scanf("%s", x);
    
    (void) SQLBindParameter(stmt,1,SQL_PARAM_INPUT, SQL_C_CHAR,
                                    SQL_CHAR,0,0,x,0,NULL);
    (void) SQLExecute(stmt);
    (void) SQLBindCol(stmt, 1, SQL_C_CHAR,(SQLCHAR *)quantityinstock,Buffer/*longitud de dato y*/, NULL);
    
    while (SQL_SUCCEEDED(ret=SQLFetch (stmt))){
        printf("Unidades en stock: %s\n", quantityinstock);
    }

    (void) SQLCloseCursor(stmt);

        /*volver a pedir*/
    (void) fflush(stdout);
    
    printf("\n");

    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}
int ShowProductSubMenu() {
    int number = 0;
    char buf[16];

    
    do{
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
/*int connect_handle(SQLHENV env,SQLHDBC dbc,SQLHSTMT stmt){

    int ret;

     
    ret= odbc_connect(&env,&dbc);
    if (!SQL_SUCCEEDED(ret)){
        printf("Error en la conexion");
        return EXIT_FAILURE;
    }

    
    ret=SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (!SQL_SUCCEEDED(ret)){
        odbc_extract_error("",stmt,SQL_HANDLE_ENV);
        return ret;
    }
    return EXIT_SUCCESS;
}
int disconnect_handle(SQLHENV env, SQLHDBC dbc, SQLHSTMT stmt){

    int ret2,ret;

    
    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret2;
    }

    
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}*/

