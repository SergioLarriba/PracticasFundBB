#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int no_deleted_registers = NO_DELETED_REGISTERS;

void replaceExtensionByIdx(const char *fileName, char * indexName) 
{
    int i, tam;

    if (fileName == NULL || indexName == NULL) 
        return; 
    
    tam = strlen(fileName); 

    for (i=0; i<tam && fileName[i]!='.'; i++) {
        indexName[i] = fileName[i]; 
    } 
    strcat (indexName, ".idx"); 

    return;
}


bool createTable(const char * tableName) 
{
    FILE *f=NULL; 
    char *indexName=NULL; 

    /* Abro el fichero */
    f = fopen(tableName, "rb+"); 
    /* Si el fichero no existe, lo creo */
    if (f == NULL) 
    {
        f = fopen(tableName, "wb+"); 
        if (f == NULL) 
            return false; 
        
        /* Escribo -1, que indica que no hay ningun fichero borrado */
        fwrite(&no_deleted_registers, sizeof(int), 1, f); 
    }
    /* Reservo memoria para el nombre del indice */
    indexName = (char*) malloc (strlen(tableName) * sizeof(indexName[0])); 
    if (indexName == NULL) 
        return false;       
    
    /* Cambio el nombre a .idx */
    replaceExtensionByIdx (tableName, indexName); 
    if (createIndex (indexName) == false)
        return false;
    
    free(indexName); 
    fclose (f); 

    return true;
}

bool createIndex(const char *indexName) 
{
    FILE *f=NULL; 

    /* Abro el fichero de indices */
    f = fopen(indexName, "rb+"); 
    /* Si el fichero no existe */
    if (f == NULL)
    {
        f = fopen(indexName, "wb+"); 
        if (f == NULL)
            return false; 

        /* Asigno -1 a los 2 primeros punteros iniciales */
        fwrite(&no_deleted_registers, sizeof(int), 1, f); 
        fwrite(&no_deleted_registers, sizeof(int), 1, f); 
    }

    fclose (f); 
    return true;
}

void printnode(size_t _level, size_t level, FILE * indexFileHandler, int node_id, char side)
{
    Node node;
    size_t pos, i;

    if (node_id == -1 || indexFileHandler == NULL || _level>level)
        return; 

    pos = INDEX_HEADER_SIZE + sizeof (node) * node_id;

    fseek(indexFileHandler, pos, SEEK_SET);
    fread(&node, sizeof(Node), 1, indexFileHandler);
   
    for (i=0; i< _level; i++)
        printf("\t");
    
    printf("%c %.4s (%d): %d\n", side, node.book_id, node_id, node.offset);

    _level++;
    printnode(_level, level, indexFileHandler, node.left, 'l');
    printnode(_level, level, indexFileHandler, node.right, 'r');

    return; 
}

void printTree(size_t level, const char * indexName)
{
    int root;
    FILE *f = NULL;

    if (indexName == NULL)
        return; 

    f = fopen(indexName, "r");
    
    fread(&root, sizeof(int), 1, f);
    if (root == -1)
        return;
    
    printnode(0, level, f, root, ' ');

    fclose (f); 

    return; 
}


bool findKey(const char * book_id, const char *indexName, int * nodeIDOrDataOffset)
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
    return true;
}

bool addTableEntry(Book * book, const char * dataName,
                   const char * indexName) {
    return true;
}