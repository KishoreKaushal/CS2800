//

//  main.c

//  heap_new

//

//  Created by Ishan Gadgil on 30/01/18.

//  Copyright © 2018 Ishan Gadgil. All rights reserved.

//


#include <stdio.h>

#include <stdlib.h>



void displayList(void);

void newHeap(int **, int **,int *,int );

void insertElement(int **,int);

void minHeapify(int **,int,int);


void displayList(void)

{

    printf("SELECT from the below options:\n\n");

    printf("1.Build a heap from a row array\n");

    printf("2.Insert a new element\n");

    printf("3.Delete the minimum element\n");

    printf("4.Heapsort\n");

    printf("5.Display the heap\n");

    printf("6.End\n----------------------------------\n");

    return;

}


void minHeapify(int ** heap,int index, int heapsize)

{

    int smaller_index,temp;

    smaller_index = index;



    if((index*2)+1 <= heapsize - 1)

    {

        if((*heap)[index]>(*heap)[(index*2)+1])

        smaller_index = (index*2)+1;

    }



    else if((index*2)+2 <= heapsize - 1)

    {

        if((*heap)[index]>(*heap)[(index*2)+2])

        smaller_index = (index*2)+2;

    }



    if(smaller_index == index)

    return;



    else

    {

        temp = (*heap)[index];

        (*heap)[index] = (*heap)[smaller_index];

        (*heap)[smaller_index] = temp;

        minHeapify(heap, smaller_index, heapsize);

        return;

    }

}



void newHeap(int ** heap, int ** array,int * heapsize,int n)

{

    int i,temp;



    for(i = 0; i<n; i++)

    {

        (*heap)[(*heapsize)] = (*array)[i];

        temp = ((*heapsize)-1)/2;

        (*heapsize)++;

        while(temp > 0)

        {

            minHeapify(heap,(temp-1)/2,(*heapsize));

            temp =(temp-1)/2;

        }

    }



    return;

}


int main()

{

    int i,j,n,heapsize = 0,temp;

    int * array;

    int * heap;



    displayList();

    scanf("%d", &j);



    heap = (int *) calloc (1000, sizeof(int));

    while(j != 6)

    {

        if(j == 1)

        {

            printf("Enter the value of n:\n");

            scanf("%d", &n);



            array = (int *) calloc (n, sizeof(int));



            for(i = 0; i<n; i++)

            {

                printf("Enter #%d:\n",i+1);

                scanf("%d", &array[i]);

            }





            newHeap(&heap,&array,&heapsize,n);

            free(array);



        }



        else if(j == 2)

        {

            printf("Heap size: %d\n", heapsize);

            printf("Enter the number to be inserted:\n");

            scanf("%d",&i);





            heap[heapsize] = i;

            temp = heapsize;

            heapsize++;

            while(temp != 0)

            {

                minHeapify(&heap,(temp-1)/2,heapsize);

                temp =(temp-1)/2;

            }

        }







        displayList();

        scanf("%d", &j);



    }



    

    printf("%d\n",heapsize);

    printf("Heap:\n");

    for(i = 0; i<heapsize; i++)

    printf("%d\n", heap[i]);




    return(0);

}
