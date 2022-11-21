int FindMenu(){
    
    
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

        /*volver a pedir*/
    (void) fflush(stdout);
    
    

    ret=disconnect_handle(env, dbc, stmt);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }
    return EXIT_SUCCESS;

}