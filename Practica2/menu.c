#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "orders.h"

#include "connection.h"

#define Buferlen 512
#define Buferlen2 30

static int ShowMainMenu();
static int ShowCustomersMenu();
static void ShowOrdersMenu();
static int ShowProductMenu();
static int ShowProductSubMenu();
static int ShowCustomersSubMenu();
static int ShowOrdersSubMenu();
int StockMenu();
int FindMenu();
int FindMenu2();
int ListProductsMenu();
int BalanceMenu(); 


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

/*******************************************************************************PRODUCTS***********************************************************************/

int ShowProductMenu() {
    int number= 0;
    int flag;
    
    do{
        flag=0; 
        number=ShowProductSubMenu();
        switch (number) {

            case 1: {
                StockMenu();
                flag=1; 
            }
                break; 

            case 2: {
                FindMenu();
                flag=1; 
            }
                break;

            case 3: {
                printf("Has salido");
                flag=1; 
            }
                break;

        }
    } while (number!= 3 && flag==1);
    return 0;
}

int ShowProductSubMenu() {
    int number = 0;
    char buf[16];

    do{
        printf(" (1) Stock\n"
               " (2) Find\n"
               " (3) Back\n\n"
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

int StockMenu(){
    SQLHENV env=NULL;
    SQLHDBC dbc=NULL;
    SQLHSTMT stmt=NULL;
    
    char x[Buferlen]="\0";
    char quantityinstock[Buferlen]="\0";
    
    int ret;

    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }
    
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret= SQLPrepare(stmt, (SQLCHAR*) "SELECT quantityinstock FROM products WHERE productcode = ?", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
   
    printf("Enter productcode > ");
    (void) fflush(stdout);
    if(fgets(x, Buferlen, stdin)){
        x[strcspn(x, "\n")]= '\0';
    }
    
    (void) SQLBindParameter(stmt,1,SQL_PARAM_INPUT, SQL_C_CHAR,
                                    SQL_CHAR,0,0,x,0,NULL);
    (void) SQLExecute(stmt);
    (void) SQLBindCol(stmt, 1, SQL_C_CHAR,(SQLCHAR *)quantityinstock,Buferlen, NULL);
    
    while (SQL_SUCCEEDED(ret=SQLFetch (stmt))){
        printf("%s\n", quantityinstock);
    }

    (void) SQLCloseCursor(stmt);
    (void) fflush(stdout);
    
    printf("\n");

    ret=disconnect_handle(env, dbc, stmt);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
    return EXIT_SUCCESS;
}

int FindMenu(){
    SQLHENV env=NULL;
    SQLHDBC dbc=NULL;
    SQLHSTMT stmt=NULL;
    #define Buferlen 512
    char x[Buferlen]="\0";
    char productcode[Buferlen]="\0";
    char cadena[Buferlen]="%";
    /*SQLRETURN ret2;*/
    int ret;

    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }
    /**/
    /* Allocate a statement handle */
    
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret= SQLPrepare(stmt, (SQLCHAR*) "SELECT productcode FROM products WHERE productname like ? ORDER BY productcode", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
    
    printf("Enter productname > ");
    (void) fflush(stdout);
    if(fgets(x, Buferlen, stdin)){
        x[strcspn(x, "\n")]= '\0';
    }
        
    strcat(cadena,x);
    strcat(cadena,"%");

    printf("\n");
    (void) SQLBindParameter(stmt,1,SQL_PARAM_INPUT, SQL_C_CHAR,
                                    SQL_CHAR,0,0,cadena,0,NULL);
    (void) SQLExecute(stmt);
    (void) SQLBindCol(stmt, 1, SQL_C_CHAR,(SQLCHAR *)productcode,Buferlen/*longitud de dato y*/, NULL);
    
    while (SQL_SUCCEEDED(ret=SQLFetch (stmt))){
        
        printf("%s %s\n", productcode, x);
        printf("\n");
    }

    (void) SQLCloseCursor(stmt);
    (void) fflush(stdout);
    
    ret=disconnect_handle(env, dbc, stmt);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
    return EXIT_SUCCESS;
}

/*******************************************************************************ORDERS***********************************************************************/

void ShowOrdersMenu() {
    int number=0, flag;
    do {
        flag=0; 
        number=ShowOrdersSubMenu();
        switch (number) {

            case 1: {
                OpenMenu();
                flag=1; 
            }
                break;

            case 2: {
                RangeMenu();
                flag=1; 
            }
                break;

            case 3: {
                DetailMenu();
                flag=1; 
            }
                break;
            case 4: {
                printf("Has salido");
            }
                break;
        }
    } while (number!=4 && flag==1);
}

int ShowOrdersSubMenu() {
    int number = 0;
    char buf[16];

    do {

        printf(" (1) Open\n"
               " (2) Range\n"
               " (3) Detail\n"
               " (4) Back\n\n"
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
    
    while (SQL_SUCCEEDED(ret=SQLFetch (stmt))){
        printf("%s\n", ordernumber);
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

    ret= SQLPrepare(stmt, (SQLCHAR*) "SELECT ordernumber, orderdate, shippeddate FROM orders WHERE orderdate>= ? and orderdate<= ? order by(ordernumber);", SQL_NTS);

    printf("Enter dates (YYYY-MM-DD - YYYY-MM-DD) > ");
    (void) fflush(stdout);
    if(fgets(fecha, Buferlen, stdin)){
        fecha[strcspn(fecha, "\n")]= '\0';
    } 
       
    /* Separo las 2 fechas en 2 variables */
    for (i=0; i<=9; i++) {
        fecha_minima[i]=fecha[i]; 
    }
    for (i=0, j=13; i<=9; i++, j++) {
        fecha_maxima[i]=fecha[j]; 
    }

    (void) SQLBindParameter(stmt,1,SQL_PARAM_INPUT, SQL_C_CHAR,
                                    SQL_CHAR,0,0,fecha_minima,0,NULL);
    (void) SQLBindParameter(stmt,2,SQL_PARAM_INPUT, SQL_C_CHAR,
                                    SQL_CHAR,0,0,fecha_maxima,0,NULL);

    (void) SQLExecute(stmt);

    (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) ordernumber, BufferLength , NULL);
    (void) SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) orderdate, BufferLength , NULL);
    (void) SQLBindCol(stmt, 3, SQL_C_CHAR, (SQLCHAR*) shippeddate, BufferLength , NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("%s %s %s\n", ordernumber, orderdate, shippeddate);
    }

    ret2 = SQLCloseCursor(stmt);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }
    
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

int DetailMenu()
{
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL, stmt2 = NULL;
    int ret, i=0; 
    SQLRETURN ret2; 
    #define BufferLength 512
    char ordernumber[BufferLength] = "\0"; 
    char orderdate[BufferLength] = "\0";
    char status[BufferLength] = "\0";
    char total[BufferLength] = "\0"; 
    char productcode[BufferLength] = "\0"; 
    char quantityordered[BufferLength] = "\0";
    char priceeach[BufferLength] = "\0";
    
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt2);
    ret = SQLPrepare(stmt2, (SQLCHAR*) "SELECT sum(total.suma) FROM (SELECT orders.orderdate, orders.status, orderdetails.productcode,  orderdetails.quantityordered, orderdetails.priceeach, (orderdetails.priceeach * orderdetails.quantityordered) as suma, orderdetails.orderlinenumber FROM orders natural join orderdetails natural join products WHERE orders.ordernumber= ? group by orders.orderdate, orders.status, orderdetails.productcode, orderdetails.quantityordered, orderdetails.priceeach, orderdetails.orderlinenumber order by(orderdetails.orderlinenumber)) as total", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt2, SQL_HANDLE_ENV);
        return ret;
    }

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR*) "SELECT orders.orderdate, orders.status, orderdetails.productcode,  orderdetails.quantityordered, orderdetails.priceeach, (orderdetails.priceeach * orderdetails.quantityordered) as suma, orderdetails.orderlinenumber FROM orders natural join orderdetails natural join products WHERE orders.ordernumber= ? group by orders.orderdate, orders.status, orderdetails.productcode, orderdetails.quantityordered, orderdetails.priceeach, orderdetails.orderlinenumber order by(orderdetails.orderlinenumber)", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
    printf ("Enter ordernumber > "); 
    (void)fflush(stdout); 
    if(fgets(ordernumber, Buferlen, stdin)){
        ordernumber[strcspn(ordernumber, "\n")]= '\0';

        (void) SQLBindParameter(stmt,1,SQL_PARAM_INPUT, SQL_C_CHAR,
                                    SQL_CHAR,0,0,ordernumber,0,NULL);

        (void) SQLExecute(stmt); 

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) orderdate, BufferLength , NULL);
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) status, BufferLength , NULL);
        (void) SQLBindCol(stmt, 3, SQL_C_CHAR, (SQLCHAR*) productcode, BufferLength , NULL);
        (void) SQLBindCol(stmt, 4, SQL_C_CHAR, (SQLCHAR*) quantityordered, BufferLength , NULL);
        (void) SQLBindCol(stmt, 5, SQL_C_CHAR, (SQLCHAR*) priceeach, BufferLength , NULL);
        
        (void) SQLBindParameter(stmt2,1,SQL_PARAM_INPUT, SQL_C_CHAR,
                                SQL_CHAR,0,0,ordernumber,0,NULL);
        
        (void) SQLExecute(stmt2); 

        (void) SQLBindCol(stmt2, 1, SQL_C_CHAR, (SQLCHAR*) total, BufferLength , NULL);

        (void) SQLFetch(stmt2); 

        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            if (i == 0) {
                printf ("----------------------\n"); 
                printf ("%s %s\n", orderdate, status);
                printf ("--------------------\n");  
                printf ("Totalcost: %s \n", total); 
                printf ("--------------------\n");  
                i++; 
            }
            printf ("%s %s %s\n", productcode, quantityordered, priceeach); 
        }

        (void) SQLCloseCursor(stmt); 

        (void) fflush(stdout); 
    }
    printf ("\n"); 

    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*******************************************************************************CUSTOMERS***********************************************************************/
int ShowCustomersMenu() {
    int number= 0;
    int flag;
    do {
        flag=0; 
        number=ShowCustomersSubMenu();
        switch (number) {

            case 1: {
                FindMenu2();
                flag=1; 
            }
                break;

            case 2: {
                ListProductsMenu();
                flag=1; 
            }
                break;

            case 3: {
                BalanceMenu();
                flag=1; 
            }
                break;
            case 4: {
                printf("Has salido");
            }
                break;

        }
    } while (number != 4 && flag==1);
    return 0;
}

int ShowCustomersSubMenu() {
    int number = 0;
    char buf[16];

    do {
        
        printf(" (1) Find\n"
               " (2) List Products\n"
               " (3) Balance\n"
               " (4) Back\n\n"
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

int FindMenu2(){
    SQLHENV env=NULL;
    SQLHDBC dbc=NULL;
    SQLHSTMT stmt=NULL;
    
    char x[Buferlen]="\0";
    char customername[Buferlen]="\0";
    char contactfirstname[Buferlen]="\0";
    char contactlastname[Buferlen]="\0";
    char customernumber[Buferlen]="\0";
    char cadena[Buferlen]="%%%"; 
    /*SQLRETURN ret2;*/
    int ret;

    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }
    
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret= SQLPrepare(stmt, (SQLCHAR*) "SELECT customernumber, customername, contactfirstname, contactlastname FROM customers WHERE contactfirstname like ? or contactlastname like ? ORDER BY customernumber", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
        
    printf("Enter customer name > ");
    (void) fflush(stdout);
    if(fgets(x, Buferlen, stdin)){
        x[strcspn(x, "\n")]= '\0';
    }

    strcat(cadena, x); 
    strcat(cadena, "%%"); 

    printf("\n");

    (void) SQLBindParameter(stmt,1,SQL_PARAM_INPUT, SQL_C_CHAR,
                                    SQL_CHAR,0,0,cadena,0,NULL);
    (void) SQLBindParameter(stmt,2,SQL_PARAM_INPUT, SQL_C_CHAR,
                                    SQL_CHAR,0,0,cadena,0,NULL);
    (void) SQLExecute(stmt);    
        
    (void) SQLBindCol(stmt, 1, SQL_C_CHAR,(SQLCHAR *)customername,Buferlen, NULL);
    (void) SQLBindCol(stmt, 2, SQL_C_CHAR,(SQLCHAR *)contactfirstname,Buferlen, NULL);
    (void) SQLBindCol(stmt, 3, SQL_C_CHAR,(SQLCHAR *)contactlastname,Buferlen, NULL);
    (void) SQLBindCol(stmt, 4, SQL_C_CHAR,(SQLCHAR *)customernumber,Buferlen, NULL);



    while (SQL_SUCCEEDED(ret=SQLFetch (stmt))){
        printf("%s %s %s %s", customername ,contactfirstname, contactlastname, customernumber);
        printf("\n");
    }
    
    (void) SQLCloseCursor(stmt);
            /*volver a pedir*/
    (void) fflush(stdout);
    
    printf("\n");

    ret=disconnect_handle(env, dbc, stmt);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
    return EXIT_SUCCESS;
}


int BalanceMenu(){
    SQLHENV env=NULL;
    SQLHDBC dbc=NULL;
    SQLHSTMT stmt=NULL; 
    char customernumber[Buferlen]="\0";
    char total[Buferlen]="\0";
    /*SQLRETURN ret2;*/
    int ret;

    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }
    
    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR *)"select (select sum(pa.amount) from payments pa where pa.customernumber = ?) - (select sum(od.quantityordered*od.priceeach) from orders o, orderdetails od where o.customernumber = ? and o.ordernumber = od.ordernumber);", SQL_NTS);
    if (!SQL_SUCCEEDED(ret))
    {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
    
    printf("Enter customer number > ");
    (void) fflush(stdout);
    if(fgets(customernumber, Buferlen, stdin)){
        customernumber[strcspn(customernumber, "\n")]= '\0';

        (void) SQLBindParameter(stmt,1,SQL_PARAM_INPUT, SQL_C_CHAR,
                                    SQL_CHAR,0,0,customernumber,0,NULL);
        (void) SQLBindParameter(stmt,2,SQL_PARAM_INPUT, SQL_C_CHAR,
                                    SQL_CHAR,0,0,customernumber,0,NULL);

        (void) SQLExecute(stmt);    
            
        (void) SQLBindCol(stmt, 1, SQL_C_CHAR,(SQLCHAR *)total,Buferlen/*longitud de dato y*/, NULL);

        while (SQL_SUCCEEDED(ret=SQLFetch (stmt))){
            printf("Balance = %s\n",total);
            printf("\n");
        }

        (void) SQLCloseCursor(stmt);
        (void) fflush(stdout);
    }

    ret=disconnect_handle(env, dbc, stmt);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
    return EXIT_SUCCESS;
}

int ListProductsMenu(){
    SQLHENV env=NULL;
    SQLHDBC dbc=NULL;
    SQLHSTMT stmt=NULL;
    
    char customernumber[Buferlen]="\0";
    char ordernumber[Buferlen]="\0";
    char total[Buferlen]="\0";
    /*SQLRETURN ret2;*/
    int ret;

    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }
    
    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret= SQLPrepare(stmt, (SQLCHAR*) "SELECT p.productname, sum(od.quantityordered) FROM products p join orderdetails od on od.productcode=p.productcode join orders o on od.ordernumber=o.ordernumber join customers c on c.customernumber=o.customernumber where c.customernumber=? group by p.productname, p.productcode order by p.productcode ", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter customer number > ");
    (void) fflush(stdout);
    if(fgets(customernumber, Buferlen, stdin)){
        customernumber[strcspn(customernumber, "\n")]= '\0';

        (void) SQLBindParameter(stmt,1,SQL_PARAM_INPUT, SQL_C_CHAR,
                                    SQL_CHAR,0,0,customernumber,0,NULL);
        (void) SQLExecute(stmt);
        
        (void) SQLBindCol(stmt, 1, SQL_C_CHAR,(SQLCHAR *)ordernumber,Buferlen/*longitud de dato y*/, NULL);
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR,(SQLCHAR *)total,Buferlen/*longitud de dato y*/, NULL);
            
        while (SQL_SUCCEEDED(ret=SQLFetch (stmt))){
            printf("%s %s\n", ordernumber,total);
        }

        (void) SQLCloseCursor(stmt);

                /*volver a pedir*/
        (void) fflush(stdout);
    }
    
    printf("\n");

    ret=disconnect_handle(env, dbc, stmt);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
    return EXIT_SUCCESS;
    
}

/*int disconnect_handle(SQLHENV env, SQLHDBC dbc, SQLHSTMT stmt){
    
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


