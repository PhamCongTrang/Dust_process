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
void sorting(struct dust_t * dust, int start, int end, int field, int trend)
{
    if(trend == 1)
    {
        if(field == 1) // Sort by sensor_id
            for(int i = start; i < end; i++)
                for(int j = i + 1; j <= end; j++)
                    if(dust[i].sensor_id > dust[j].sensor_id)
                    {
                        struct dust_t temp = dust[i];
                        dust[i] = dust[j];
                        dust[j] = temp;
                    }
        if(field == 2) // Sort by time
            for(int i = start; i < end; i++)
                for(int j = i + 1; j <= end; j++)
                    if(dust[i].time > dust[j].time)
                    {
                        struct dust_t temp = dust[i];
                        dust[i] = dust[j];
                        dust[j] = temp;
                    }
        if(field == 3) // Sort by value
            for(int i = start; i < end; i++)
                for(int j = i + 1; j <= end; j++)
                    if(dust[i].value > dust[j].value)
                    {
                        struct dust_t temp = dust[i];
                        dust[i] = dust[j];
                        dust[j] = temp;
                    }
    }
    if(trend == -1)
    {
        if(field == 1) // Sort by sensor_id
            for(int i = start; i < end; i++)
                for(int j = i + 1; j <= end; j++)
                    if(dust[i].sensor_id < dust[j].sensor_id)
                    {
                        struct dust_t temp = dust[i];
                        dust[i] = dust[j];
                        dust[j] = temp;
                    }
        if(field == 2) // Sort by time
            for(int i = start; i < end; i++)
                for(int j = i + 1; j <= end; j++)
                    if(dust[i].time < dust[j].time)
                    {
                        struct dust_t temp = dust[i];
                        dust[i] = dust[j];
                        dust[j] = temp;
                    }
        if(field == 3) // Sort by value
            for(int i = start; i < end; i++)
                for(int j = i + 1; j <=end; j++)
                    if(dust[i].value < dust[j].value)
                    {
                        struct dust_t temp = dust[i];
                        dust[i] = dust[j];
                        dust[j] = temp;
                    }  
    }
}
void selection_sort(struct dust_t* dust, int size, int * sort)
{
    if(sort[4] == 1)
        for(int i = 0; i < size - 1; i++)
            for(int j = i + 1; j < size; j++)
                if(multi_compare(dust[i],dust[j],sort) > 0) swap(dust + i,dust + j);
    if(sort[4] == -1)
        for(int i = 0; i < size - 1; i++)
            for(int j = i + 1; j < size; j++)
                if(multi_compare(dust[i],dust[j],sort) < 0) swap(dust + i,dust + j);
}