#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "utils.h"

#define TEST_ARRAY_SIZE 11
#define SORTED_TEST_ARRAY_SIZE 9

int no_deleted_registers = NO_DELETED_REGISTERS;

extern Node a[TEST_ARRAY_SIZE];
extern char sort_a[SORTED_TEST_ARRAY_SIZE][PK_SIZE+1];
extern Book b[TEST_ARRAY_SIZE];

void replaceExtensionByIdx(const char *fileName, char * indexName) {
    size_t i;
    
    assert(fileName!=NULL); 
    assert(indexName!=NULL); 

    for (i=0; i<strlen(fileName) && fileName[i]!='.'; i++) {
        indexName[i] = fileName[i]; 
    } 
    strcat(indexName, ".idx");
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
    

    fclose(f);
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
    fseek (indexFileHandler, pos, SEEK_SET);
    /* Para la funcion fread (devuelve el numero de registros leidos) -> size_t fread(void *puntero, size_t tamaño, size_t nregistros, FILE *fichero)*/
    fread (&node, sizeof(Node), 1, indexFileHandler); 

    

    /* Imprimo el nodo -> side(l) book_id(MAR0) id((5)): offset(4)*/
    for (i=0; i<_level; i++)
        printf("\t");
        
    printf("%c %.4s (%d): %d\n", side, node.book_id, node_id, node.offset);

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

    f = fopen(indexName, "r"); 

    /* Veo donde esta la raiz: sera la que este en la posicion que indica el primer numero */
    fread(&raiz, sizeof(int), 1, f); 
    /* Si no hubiese raiz, return */
    if (raiz == -1) 
        return; 
    
    printnode(0, level, f, raiz, ' ');

    fclose(f);
    return;
}

bool findKey(const char * book_id, const char *indexName,
             int * nodeIDOrDataOffset)
 {
    FILE *f=NULL; 
    Node node; 
    int root=-1, cmp; 
    size_t pos; 
    bool condition=true; 
    
    if (book_id == NULL || indexName == NULL || nodeIDOrDataOffset == NULL)
        return false; 

    f = fopen (indexName, "rb+"); 
    if (f == NULL)
        return false; 
    /* Leo y guardo la posicion del nodo raiz en root */
    fread(&root, sizeof(int), 1, f); 
    *nodeIDOrDataOffset = root; 

    while (condition == true) /* M*/
    {    
        /* Busco el nodo que ocupa la posicion pos y lo guardo en node */
        pos = INDEX_HEADER_SIZE + sizeof (Node) * (*nodeIDOrDataOffset); 
        fseek (f, pos, SEEK_SET); 
        fread (&node, sizeof(Node), 1, f); 

        /* si los bytes son iguales, he encontrado la llave */
        cmp = memcmp(book_id, node.book_id ,PK_SIZE); 
        if (cmp == 0)
        {
            *nodeIDOrDataOffset = node.offset; 
            fclose (f); 
            return true; 
        }
        else if (cmp > 0) /* Quiere decir que el nodo que buscamos esta por la parte derecha, ya que es mayor que el actual */
        {
            if (node.right == -1) /* Si no existe el nodo derecho al actual, no hemos encontrado la llave */
            {
                fclose (f); 
                return false; 
            }
            else 
                *nodeIDOrDataOffset = node.right; 
        }
        else /* cmp <0 -> quiere decir que el nodo que buscamos esta a la izquierda, ya que es menor que el nodo actual */
        {
            if (node.left == -1) /* Si no existe el nodo izquierdo al actual, no hemos encontrado la llave */
            {
                fclose (f); 
                return false; 
            }
            else 
                *nodeIDOrDataOffset = node.left; 
        }
        condition = true; 
    }

     return true;
 }

bool addIndexEntry(char * book_id,  int bookOffset, char const * indexName) {
    
    FILE *f;


    f=fopen(indexName,"r");
    if(!f){
        return false;
    }


    



    
    
    return true;
}

bool addTableEntry(Book * book, const char * dataName,
                   const char * indexName) {
    
    FILE *f;
    int raiz,len,nodeIDOrDataOffset;
    size_t pos;

    if(findKey(book->book_id,indexName,&nodeIDOrDataOffset)==true){
        return false;
    }

    f=fopen(indexName,"rb+");
    if(!f){
        return false;
    }


    fseek (f, 0, SEEK_SET);
    fread(&raiz,sizeof(int),1,f);
    if (raiz== -1){
        fseek (f, 0, SEEK_END);
        fwrite(book->book_id,PK_SIZE,1,f);
        fwrite(&(book->title_len),sizeof(int),1,f);
        fwrite(book->title,book->title_len,1,f);
        pos=INDEX_HEADER_SIZE+(book->book_id)*PK_SIZE;
        fwrite(&pos,sizeof(size_t),1,f);

        return true;
    }

    fclose(f);
    f=fopen(dataName,"rb+");
    if(!f){
        return false;
    }

    raiz=raiz*PK_SIZE+INDEX_HEADER_SIZE;

    fseek(f,raiz+4,SEEK_SET);
    fread(&len,sizeof(int),1,f);
    if((book->title_len)>len){
        fclose(f);
        return false;
    }
    fclose(f);
    f=fopen(dataName,"wb+");
    if(!f){
        return false;
    }

    fseek(f,raiz,SEEK_SET);
    fwrite(book->book_id,PK_SIZE,1,f);
    fwrite(&(book->title_len),sizeof(int),1,f);
    fwrite(book->title,book->title_len,1,f);
    fseek(f,0,SEEK_SET);
    fwrite(&no_deleted_registers, sizeof(int), 1, f);


    
    return true;
}