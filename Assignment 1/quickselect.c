/* By: Stanley Wong */
/* CSC 220 - Algorithms */
/* Assignment 1 */

#include <stdio.h>
#include <stdlib.h>


int quickselect(int *A, int k, int n)
{
    int a, b, r, pivot, temp, smaller = 0, larger = n - 1;

    while (smaller < larger)
    {
        a = smaller, b = larger;
        //Randomization near the center (Makes sure pivot is not highly skewed)
        r = (a + b) / 2;
        r = r + rand() % (n-k);
        pivot = A[r%n];

        // Parition
        while (a < b)
        {
            if (A[a] < pivot) {
                a++;
            }
            else
            {
                temp = A[b];
                A[b] = A[a];
                A[a] = temp;
                b--;
            }
        }
        if (A[a] > pivot)
            a--;

        // Selection
        if (k <= a)
        {
            larger = a;
        }
        else
        {
            smaller = a + 1;
        }

    }
    return A[k]-1;
}


int main(void)
{
    long i;
    int *space; int tmp;
    space =  (int *) malloc( 1000000*sizeof(int));
    for( i=0; i< 500000; i++ )
    {  *(space + i) = ((139*i)%500000);
        *(space + i + 500000) = 1000000 + ((141*i)%500000);
    }
    if( (tmp = quickselect(  space, 500001, 1000000)) != 1000000 )
    {  printf(" Failed test 1. Returned %d instead of 1000000\n", tmp);
        fflush(stdout); exit(-1);
    }
    else printf("passed test1\n");
    for( i=0; i< 500000; i++ )
    {  *(space + i) = ((139*i)%500000);
        *(space + i + 500000) = 1000000 + ((141*i)%500000);
    }
    if( (tmp = quickselect(  space, 1, 1000000)) != 0 )
    {  printf(" Failed test 2. Returned %d instead of 0\n", tmp);
        fflush(stdout); exit(-1);
    }
    else printf("passed test2\n");
    for( i=0; i< 500000; i++ )
    {  *(space + i) = ((139*i)%500000);
        *(space + i + 500000) = 1000000 + ((141*i)%500000);
    }
    if( (tmp = quickselect(  space, 124, 1000000)) != 123 )
    {  printf(" Failed test 3. Returned %d instead of 123\n", tmp);
        fflush(stdout); exit(-1);
    }
    else printf("passed test3\n");

    printf("Quickselect successful\n");
    exit(0);
}