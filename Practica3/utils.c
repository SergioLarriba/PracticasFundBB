#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "utils.h"

int no_deleted_registers = NO_DELETED_REGISTERS;

void replaceExtensionByIdx(const char *fileName, char * indexName) {
    size_t i;
    
    assert(fileName!=NULL); 
    assert(indexName!=NULL); 

    for (i=0; i<strlen(fileName) && fileName[i]!='.'; i++) {
        indexName[i] = fileName[i]; 
    } 
    indexName[i+1]='i'; 
    indexName[i+2]='d'; 
    indexName[i+3]='x'; 

    return;
}


bool createTable(const char * tableName) {
    FILE *f=NULL; 
    char *indexName=NULL; 

    /* Abro el fichero */
    f = fopen(tableName, "rb+"); 
    /* Si el fichero no existe, lo creo */
    if (f == NULL) 
    {
        f = fopen(tableName, "wb+"); 
        if (f == NULL) 
            return EXIT_FAILURE; 
        
        /* Escribo -1, que indica que no hay ningun fichero borrado */
        fwrite(&no_deleted_registers, sizeof(int), 1, f); 
    }
    /* Reservo memoria para el nombre del indice */
    indexName = (char*) malloc (strlen(tableName) * sizeof(indexName[0])); 
    if (indexName == NULL) 
        return EXIT_FAILURE;       
    
    /* Cambio el nombre a .idx */
    replaceExtensionByIdx (tableName, indexName); 
    if (createIndex (indexName) == EXIT_FAILURE)
        return EXIT_FAILURE;
    
    free(indexName); 

    return EXIT_SUCCESS; 
}

bool createIndex(const char *indexName) {
    FILE *f=NULL; 

    /* Abro el fichero de indices */
    f = fopen(indexName, "rb+"); 
    /* Si el fichero no existe */
    if (f == NULL)
    {
        f = fopen(indexName, "wb+"); 
        if (f == NULL)
            return EXIT_FAILURE; 

        /* Asigno -1 a los 2 primeros punteros iniciales */
        fwrite(&no_deleted_registers, sizeof(int), 1, f); 
        fwrite(&no_deleted_registers, sizeof(int), 1, f); 
    }

    fclose (f); 

    return EXIT_SUCCESS;
}

void printnode(size_t _level, size_t level, FILE * indexFileHandler, int node_id, char side) 
{
    Node node; 
    size_t pos, i; 

    /* Control de errores */
    if (_level>level || node_id == -1 || indexFileHandler == NULL) 
        return; 

    /* Para la funcion fseek -> fseek(fichero, desplazamiento, origen)
        SEEK_SET: el desplazamiento se cuenta desde el principio del fichero 
        SEEK_CUR: el desplazamiento se cuenta desde la posicion actual del cursor
        SEEK_END: el desplazamiento se cuenta desde el final del fichero 
    */
    /* Calculo la posicion que ocupa el nodo en el fichero */
    pos = INDEX_HEADER_SIZE + sizeof(node) * node_id;
    if (fseek (indexFileHandler, pos, SEEK_CUR) != 0) 
        return; 
    /* Para la funcion fread (devuelve el numero de registros leidos) -> size_t fread(void *puntero, size_t tamaño, size_t nregistros, FILE *fichero)*/
    fread (&node, sizeof(Node), 1, indexFileHandler); 

    /* Imprimo el nodo -> side(l) book_id(MAR0) id((5)): offset(4)*/
    for (i=0; i<_level; i++)
    {
        printf ("   "); 
        printf ("%c %s (%d): %d", side, node.book_id, node_id, node.offset); 
    }

    /* Imprimo sus hijos de manera recursiva, de tal forma que, en la funcion printTree solo sea necesario llamar a la funcion printNode */
    _level++; 
    printnode(_level, level, indexFileHandler, node.left, 'l');
    printnode(_level, level, indexFileHandler, node.right, 'r');

    return;
}

void printTree(size_t level, const char * indexName)
{
    FILE *f=NULL; 
    int raiz; 

    f = fopen(indexName, "rb+"); 

    /* Veo donde esta la raiz: sera la que este en la posicion que indica el primer numero */
    fread(&raiz, sizeof(int), 1, f); 
    /* Si no hubiese raiz, return */
    if (raiz == -1) 
        return; 
    
    printnode(0, level, f, raiz, ' '); 
    return;
}

bool findKey(const char * book_id, const char *indexName,
             int * nodeIDOrDataOffset)
 {
     return true;
 }

bool addIndexEntry(char * book_id,  int bookOffset, char const * indexName) {
    return true;
}

bool addTableEntry(Book * book, const char * dataName,
                   const char * indexName) {
    return true;
}