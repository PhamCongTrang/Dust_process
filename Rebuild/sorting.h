#include "typedefine.h"
#include <string.h>
/*
* field = 1 : Sap xep theo sensor_id
* field = 2 : Sap xep theo time
* field = 3 : Sap xep theo value
* trend = 1 : Tang dan
* trend = -1:  Giam dan
*/
void sorting(struct dust_t * dust, int size, int field, int trend)
{
    if(trend == 1)
    {
        if(field == 1) // Sort by sensor_id
            for(int i = 0; i < size - 1; i++)
                for(int j = i + 1; j < size; j++)
                    if(dust[i].sensor_id > dust[j].sensor_id)
                    {
                        struct dust_t temp = dust[i];
                        dust[i] = dust[j];
                        dust[j] = temp;
                    }
        if(field == 2) // Sort by time
            for(int i = 0; i < size - 1; i++)
                for(int j = i + 1; j < size; j++)
                    if(dust[i].time > dust[j].time)
                    {
                        struct dust_t temp = dust[i];
                        dust[i] = dust[j];
                        dust[j] = temp;
                    }
        if(field == 3) // Sort by value
            for(int i = 0; i < size - 1; i++)
                for(int j = i + 1; j < size; j++)
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
            for(int i = 0; i < size - 1; i++)
                for(int j = i + 1; j < size; j++)
                    if(dust[i].sensor_id < dust[j].sensor_id)
                    {
                        struct dust_t temp = dust[i];
                        dust[i] = dust[j];
                        dust[j] = temp;
                    }
        if(field == 2) // Sort by time
            for(int i = 0; i < size - 1; i++)
                for(int j = i + 1; j < size; j++)
                    if(dust[i].time < dust[j].time)
                    {
                        struct dust_t temp = dust[i];
                        dust[i] = dust[j];
                        dust[j] = temp;
                    }
        if(field == 3) // Sort by value
            for(int i = 0; i < size - 1; i++)
                for(int j = i + 1; j < size; j++)
                    if(dust[i].value < dust[j].value)
                    {
                        struct dust_t temp = dust[i];
                        dust[i] = dust[j];
                        dust[j] = temp;
                    }  
    }
    

}