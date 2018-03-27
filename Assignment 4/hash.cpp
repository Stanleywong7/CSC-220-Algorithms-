// By: Stanley Wong
// CSC 22000
/* Assignment 4:    The aim of this homework is to implement a hash table with overflow lists, using a
 *                  universal family of hash functions, the bit-xor function described in the class.
 *                  The keys are supposed to be 32-bit unsigned integers, the values are integers. */

#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct node
{
    int key;
    int data;
    struct node* next;
}node;

typedef struct hashtable_t
{
    int table_size;
    unsigned int rand_nums[32];
    node** table;

}hashtable_t;

/* Creates the parameters for a hash function (random choice) and allocates the hash table.
 * The size of the created hash table is the power of two that is next larger than the given size. */
hashtable_t * create_hash(int size){
    int table_size = 2;
    while(table_size<= size)
        table_size*=2;
    hashtable_t * ht = (hashtable_t*)malloc(sizeof(hashtable_t));
    for(int i = 0;i<32;i++)
        ht->rand_nums[i] = (unsigned int)rand();
    ht->table = (node**)malloc(table_size*sizeof(node*));
    for(int i = 0;i<table_size;i++)
        ht->table[i] = NULL;
    ht->table_size = table_size;

    return ht;
}

/* Enters the (key, value) pair in the hash table. */
void insert_hash(hashtable_t * hp, unsigned int key, int value){
    unsigned int key_org = key;
    key = key%hp->table_size;
    if(hp->table[key] == NULL)
    {
        node * n = (node*)malloc(sizeof(node));
        n->key = key_org;
        n->data = value;
        n->next = NULL;
        hp->table[key] = n;

    }
    else
    {
        node * t = hp->table[key];
        while(t->next != NULL)
            t = t->next;

        node * n = (node*)malloc(sizeof(node));
        n->key = key_org;
        n->data = value;
        n->next = NULL;
        t->next = n;
    }
}

/* Deletes the (key, value) pair in the hash table. */
void delete_hash(hashtable_t * hp, unsigned int key){
    node * t = hp->table[key%hp->table_size];
    node*prev = t;

    if(t->key == key)
    {
        //free(t);
        hp->table[key%hp->table_size] = t->next;
    }

    while(t != NULL)
    {
        if(t->key == key)
        {
            prev->next = t->next;
            //free(t);
            return;
        }
        prev = t;
        t = t->next;
    }
}

/* Returns the value associated with key, if it exists, or 0 else. */
int find_hash(hashtable_t * hp, unsigned int key){

    node * t = hp->table[key%hp->table_size];
    while(t != NULL)
    {
        if(t->key == key)
        {
            return t->data;
        }
        t = t->next;
    }
    return 0;
}

int main(void)
{  int i;
    hashtable_t *table1, *table2, *table3;
    table1 = create_hash(1000);
    table2 = create_hash(10000);
    table3 = create_hash(100000);
    for( i=0; i< 2000; i++)
        insert_hash( table1, 2*i, 3*i+1);
    for( i=0; i< 4000; i++)
    { int f;
        f = find_hash(table1, i);
        if( i%2== 0)
        {  if( f != 3*(i/2)+1 )
            {  printf("Test1 Error: key %d, value found %d, should be %d.\n",
                      i,f, 3*(i/2)+1 );
            }
        }
        else
        {  if( f!= 0 )
            {  printf("Test1 Error: key %d, value found %d, should be 0 (not found)\n",
                      i,f);
            }
        }
    }
    printf("End Test1\n");
    for( i=0; i< 20000; i++)
    {  insert_hash( table2, 3*i, 2*i+1);
        insert_hash( table3, 5*i, 2*i+1);
    }
    for( i=1000; i< 20000; i++)
        delete_hash( table2, 3*i);
    for( i=0; i< 3000; i++)
    { int f;
        f = find_hash(table2, i);
        if( (i%3== 0) && ( f != 2*(i/3)+1 ) )
            printf("Test2 Error: key %d, value found %d, should be %d.\n",
                   i,f, 2*(i/3)+1 );
        if( (i%3!=0) && ( f!= 0 ) )
            printf("Test2 Error: key %d, value found %d, should be 0 (not found)\n",
                   i,f);
    }
    for( i=3000; i< 60000; i++)
    {  if( find_hash(table2, i) != 0 )
            printf("Test2 Error: key %d found, should be not found\n",i);
    }
    printf("End Test2\n");
    for( i=0; i< 100000; i++)
    { int f;
        f = find_hash(table3, i);
        if( (i%5== 0) && ( f != 2*(i/5)+1 ) )
            printf("Test3 Error: key %d, value found %d, should be %d.\n",
                   i,f, 2*(i/5)+1 );
        if( (i%5!=0) && ( f!= 0 ) )
            printf("Test3 Error: key %d, value found %d, should be 0 (not found)\n",
                   i,f);
    }
    printf("End Test3\n");
}