#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

static int ShowMainMenu();
static void ShowCustomersMenu();
static void ShowOrdersMenu();
static void ShowProductMenu();
static int ShowProductSubMenu();
static int ShowCustomersSubMenu();
static int ShowOrdersSubMenu();
int connect_handle(SQLHENV env,SQLHDBC dbc,SQLHSTMT stmt);
int disconnect_handle(SQLHENV env, SQLHDBC dbc, SQLHSTMT stmt);
/* Products*/
int StockMenu();
/* Orders*/
int OpenMenu(); 
int RangeMenu(); 
int DetailMenu(); 

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

    do{
        number=ShowProductSubMenu();
        switch (number) {

            case 1: {
                StockMenu();
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
int StockMenu(){
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char x[BufferLength] = "\0";
    char y[BufferLength] = "\0";

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("productcode = ");
    (void) fflush(stdout);
    while (fgets(x, (int) sizeof(x), stdin) != NULL) {
        char query[BufferLength + 60];
        x[strlen(x)-1]='\0';
        /* snprintf is not defined if ansi flag is enabled */
        (void) snprintf(query, (size_t)(BufferLength + 60), "SELECT quantityinstock FROM products WHERE productcode = '%s';", x);

        (void) SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) y, BufferLength , NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("quantityinstock = %s\n", y);
        }

        ret2 = SQLCloseCursor(stmt);
        if (!SQL_SUCCEEDED(ret2)) {
            odbc_extract_error("", stmt, SQL_HANDLE_STMT);
           return ret;
        }

        printf("productcode = ");
        ret = fflush(stdout);
    }
    printf("\n");
    
    /* free up statement handle */
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
static void ShowOrdersMenu() {
    int number= 0;
    do {
        number=ShowOrdersSubMenu();
        switch (number) {

            case 1: {
                OpenMenu(); 
            }
                break;

            case 2: {
                RangeMenu();
            }
                break;

            case 3: {
                DetailMenu();
            }
                break;
            case 4: {
                printf("Has salido");
            }
                break;

        }
    } while (number != 4);
}

int OpenMenu ()
{
    SQLHENV env=NULL;
    SQLHDBC dbc=NULL;
    SQLHSTMT stmt=NULL;
    #define Buffer 512
    char ordernumber[Buffer]="\0";
    SQLRETURN ret2;
    int ret;

    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret= SQLPrepare(stmt, (SQLCHAR*) "SELECT orders.ordernumber FROM orders WHERE orders.shippeddate IS NULL order by(orders.ordernumber)", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    (void) SQLExecute(stmt);
    (void) SQLBindCol(stmt, 1, SQL_C_CHAR,(SQLCHAR *)ordernumber,Buffer/*longitud de dato y*/, NULL);
    printf ("Pedidos que todavia no se han enviado:\n"); 
    while (SQL_SUCCEEDED(ret=SQLFetch (stmt))){
        printf("- %s\n", ordernumber);
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

int RangeMenu()
{
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char fecha[BufferLength] = "\0"; 
    char fecha_minima[BufferLength] = "\0";
    char fecha_maxima[BufferLength] = "\0";
    char ordernumber[BufferLength] = "\0"; 
    char orderdate[BufferLength] = "\0"; 
    char shippeddate[BufferLength] = "\0";
    int i, j; 

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Introduzca la fecha minima y maxima(YYYY-MM-DD-YYYY-MM-DD) = ");
    (void) fflush(stdout);

    while (fgets(fecha, (int) sizeof(fecha), stdin) != NULL)
    {
        char query[BufferLength + 624];
        fecha[strlen(fecha)-1]='\0'; 
        
        /* Separo las 2 fechas en 2 variables */
        for (i=0; i<=9; i++) {
            fecha_minima[i]=fecha[i]; 
        }
        for (i=0, j=11; i<=9; i++, j++) {
            fecha_maxima[i]=fecha[j]; 
        }
        /* snprintf is not defined if ansi flag is enabled */
        (void) snprintf(query, (size_t)(BufferLength + 624), "SELECT ordernumber, orderdate, shippeddate FROM orders WHERE orderdate>='%s' and orderdate<='%s' order by(orderdate);", fecha_minima, fecha_maxima);

        (void) SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) ordernumber, BufferLength , NULL);
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) orderdate, BufferLength , NULL);
        (void) SQLBindCol(stmt, 3, SQL_C_CHAR, (SQLCHAR*) shippeddate, BufferLength , NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("%s | %s | %s\n", ordernumber, orderdate, shippeddate);
        }

        ret2 = SQLCloseCursor(stmt);
        if (!SQL_SUCCEEDED(ret2)) {
            odbc_extract_error("", stmt, SQL_HANDLE_STMT);
            return ret;
        }
        printf("Introduzca la fecha minima y maxima(YYYY-MM-DD-YYYY-MM-DD) = ");
        ret = fflush(stdout);
    }
    printf("\n");
    
    /* free up statement handle */
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

/* Solicito al usuario un ordernumber, le devuelvo: 
 - La primera linea mostrara el orderdate (fecha en la que se realizo el pedido) y el status (asi como si ya se ha enviado)
 - La segunda linea mostrara el coste total del pedido (sum(products.buyprice))
 - 1 linea por producto en la que aparecera: el productcode, quantityordered, priceeach
 - La salida de las lineas donde se listen los productos se ordenara por orderlinenumber 
 
    SELECT 
        orders.orderdate, orders.status, orderdetails.productcode,  orderdetails.quantityordered, orderdetails.priceeach, sum(payments.amount) as total, orderdetails.orderlinenumber
    FROM 
        orderdetails natural join orders natural join customers natural join payments
    WHERE 
        orders.ordernumber='10100'
    group by orders.orderdate, orders.status, orderdetails.productcode, orderdetails.quantityordered, orderdetails.priceeach, orderdetails.orderlinenumber
    order by(orderdetails.orderlinenumber)
    
Va todo perfecto, pero no me suma bien
    */
int DetailMenu()
{
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char ordernumber[BufferLength] = "\0"; 
    char orderdate[BufferLength] = "\0";
    char status[BufferLength] = "\0";
    char total[BufferLength] = "\0"; 
    char productcode[BufferLength] = "\0"; 
    char quantityordered[BufferLength] = "\0";
    char priceeach[BufferLength] = "\0";
    char orderlinenumber[BufferLength] = "\0";

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Ordernumber = ");
    (void) fflush(stdout);

    while (fgets(ordernumber, (int) sizeof(ordernumber), stdin) != NULL)
    {
        char query[BufferLength + 624];
        ordernumber[strlen(ordernumber)-1]='\0'; 
        
        /* snprintf is not defined if ansi flag is enabled */
        (void) snprintf(query, (size_t)(BufferLength + 624), "SELECT orders.orderdate, orders.status, orderdetails.productcode,  orderdetails.quantityordered, orderdetails.priceeach, sum(payments.amount) as total, orderdetails.orderlinenumber FROM orderdetails natural join orders natural join customers natural join payments WHERE orders.ordernumber='%s' group by orders.orderdate, orders.status, orderdetails.productcode, orderdetails.quantityordered, orderdetails.priceeach, orderdetails.orderlinenumber order by(orderdetails.orderlinenumber)", ordernumber);

        (void) SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) orderdate, BufferLength , NULL);
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) status, BufferLength , NULL);
        (void) SQLBindCol(stmt, 3, SQL_C_CHAR, (SQLCHAR*) productcode, BufferLength , NULL);
        (void) SQLBindCol(stmt, 4, SQL_C_CHAR, (SQLCHAR*) quantityordered, BufferLength , NULL);
        (void) SQLBindCol(stmt, 5, SQL_C_CHAR, (SQLCHAR*) priceeach, BufferLength , NULL);
        (void) SQLBindCol(stmt, 6, SQL_C_CHAR, (SQLCHAR*) total, BufferLength , NULL);
        (void) SQLBindCol(stmt, 7, SQL_C_CHAR, (SQLCHAR*) orderlinenumber, BufferLength , NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("Orderdate = %s | Status = %s\n", orderdate, status);
            printf("Total del pedido = %s\n", total); 
            printf("Productcode = %s | Quantityordered = %s | Priceeach = %s\n", productcode, quantityordered, priceeach); 
            printf ("\n"); 
        }

        ret2 = SQLCloseCursor(stmt);
        if (!SQL_SUCCEEDED(ret2)) {
            odbc_extract_error("", stmt, SQL_HANDLE_STMT);
            return ret;
        }
        printf("Ordernumber = ");
        ret = fflush(stdout);
    }
    printf("\n");
    
    /* free up statement handle */
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

