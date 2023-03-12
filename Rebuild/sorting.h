#include "typedefine.h"
#include <string.h>
/*
* field = 1 : Sap xep theo sensor_id
* field = 2 : Sap xep theo time
* field = 3 : Sap xep theo value
* trend = 1 : Tang dan
* trend = -1:  Giam dan
*/
int compare(struct dust_t a, struct dust_t b, int field)
{
    if(field == 1)
    {
        if(a.sensor_id > b.sensor_id) return 1;
        if(a.sensor_id < b.sensor_id) return -1;
        if(a.sensor_id == b.sensor_id) return 0;
    }
    if(field == 2)
    {
        if(a.time > b.time) return 1;
        if(a.time < b.time) return -1;
        if(a.time == b.time) return 0;
    }
    if(field == 3)
    {
        if(a.value > b.value) return 1;
        if(a.value < b.value) return -1;
        if(a.value == b.value) return 0;
    }
    if(field == 0) return 0;
    return 100; // tat warning
}
void swap(struct dust_t* a, struct dust_t* b)
{
    struct dust_t temp = *a;
    *a = *b;
    *b = temp;
}
int multi_compare(struct dust_t a, struct dust_t b, int* sort)
{
    int x = compare(a,b,sort[1]);
    int y = compare(a,b,sort[2]);
    int z = compare(a,b,sort[3]);
    if(x > 0) return 1;
    if(x == 0 && y > 0 ) return 1;
    if(x == 0 && (y == 0 && z > 0)) return 1;
    if(x < 0) return -1;
    if(x == 0 && y < 0 ) return -1;
    if(x == 0 && (y == 0 && z < 0)) return -1;  
    return 0;
}
double selection_sort(struct dust_t* dust, int size, int * sort)
{
    clock_t start, end;
    double run_time;
    start = clock();
    if(sort[4] == 1)
        for(int i = 0; i < size - 1; i++)
            for(int j = i + 1; j < size; j++)
                if(multi_compare(dust[i],dust[j],sort) > 0) swap(dust + i,dust + j);
    if(sort[4] == -1)
        for(int i = 0; i < size - 1; i++)
            for(int j = i + 1; j < size; j++)
                if(multi_compare(dust[i],dust[j],sort) < 0) swap(dust + i,dust + j);
    end = clock();
    run_time = (double) (end - start)/CLOCKS_PER_SEC;
    return run_time*1000;
}
void quicksort_non_time(struct dust_t* dust, int left, int right, int* sort) 
{
    if(sort[4] == 1)
    {
        if (left >= right) return;
    
        struct dust_t pivot = dust[left];
        int i = left + 1;
        int j = right;
        
        while (i <= j) 
        {
            if (multi_compare(dust[i],pivot,sort) < 0) 
            {
                i++;
            } else if (multi_compare(dust[j],pivot,sort) >= 0) 
            {
                j--;
            } else 
            {
                swap(dust + i,dust + j);
                i++;
                j--;
            }
        }
        swap(dust + left,dust + j);
        quicksort_non_time(dust, left, j - 1, sort);
        quicksort_non_time(dust, j + 1, right, sort);
    }
    if(sort[4] == -1)
    {
        if (left >= right) return;
    
        struct dust_t pivot = dust[left];
        int i = left + 1;
        int j = right;
        
        while (i <= j) 
        {
            if (multi_compare(dust[i],pivot,sort) > 0) 
            {
                i++;
            } else if (multi_compare(dust[j],pivot,sort) <= 0) 
            {
                j--;
            } else 
            {
                swap(dust + i,dust + j);
                i++;
                j--;
            }
        }
        swap(dust + left,dust + j);
        quicksort_non_time(dust, left, j - 1, sort);
        quicksort_non_time(dust, j + 1, right, sort);
    }
}
double quicksort(struct dust_t* dust, int size, int* sort)
{
    clock_t start, end;
    double run_time;
    start = clock();
    quicksort_non_time(dust, 0, size - 1, sort);
    end = clock();
    run_time = (double) (end - start)/CLOCKS_PER_SEC;
    return run_time*1000;
}
void heapify(struct dust_t* dust, int size, int i, int* sort) 
{
    if(sort[4] == 1)
    {
        int largest = i; 
        int left = 2 * i + 1; 
        int right = 2 * i + 2; 

        if (left < size && (multi_compare(dust[left], dust[largest], sort) > 0)) 
            largest = left;

        if (right < size && (multi_compare(dust[right], dust[largest], sort) > 0)) 
            largest = right;

        if (largest != i) 
        {
            swap(dust + i, dust + largest);
            heapify(dust, size, largest, sort);
        }
    }
    if(sort[4] == -1)
    {
        int largest = i; 
        int left = 2 * i + 1; 
        int right = 2 * i + 2; 

        if (left < size && (multi_compare(dust[left], dust[largest], sort) < 0)) 
            largest = left;

        if (right < size && (multi_compare(dust[right], dust[largest], sort) < 0)) 
            largest = right;

        if (largest != i) 
        {
            swap(dust + i, dust + largest);
            heapify(dust, size, largest, sort);
        }
    }
    
}

double heapsort(struct dust_t* dust, int size, int* sort) 
{
    clock_t start, end;
    double run_time;
    start = clock();
    for (int i = size / 2 - 1; i >= 0; i--) 
        heapify(dust, size, i, sort);

    for (int i = size - 1; i > 0; i--) 
    {
        swap(dust, dust + i);
        heapify(dust, i, 0, sort);
    }
    end = clock();
    run_time = (double) (end - start)/CLOCKS_PER_SEC;
    return run_time*1000;
}