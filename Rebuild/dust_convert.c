#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "converter.h"
#include "typedefine.h"
#include "sorting.h"

int main(int argc, char* argv[])
{
    /*
    * Vung khai bao bien toan cuc
    */
    struct dust_t dust[1000];
    int size;
    /*
    * sort[0] : Enable Sort
    * sort[1], sort[2], sort[3] : theo thu tu uu tien sort; nhan cac hoan vi cua 1, 2, 3 
    * sort[4] : trend sort: 1: Tang dan; 2: Giam dan
    */
    int sort[5];
    /*
    * Convert CSV to Hex: Mode = 1
    * Convert Hex to CSV: Mode = 0
    */
    int Mode = 10;
    char source_file[20], target_file[20];
    strcpy(source_file,argv[1]);
    strcpy(target_file,argv[2]);
    printf("%s %s",source_file, target_file);
    char source_extension[10], target_extension[10];
    for(int i = 1; i <= 4; i++)
        source_extension[4-i] = source_file[strlen(source_file) - i];
    source_extension[5] = '\0';
    for(int i = 1; i <= 4; i++)
       target_extension[4-i] = target_file[strlen(target_file) - i];
    if(strcmp(source_extension,".csv") && strcmp(target_extension, ".dat")) Mode = 0; // nguoc
    if(strcmp(source_extension,".dat") && strcmp(target_extension, ".csv")) Mode = 1; // nguoc
    printf("\nMode:%d",Mode);
    // sort setmode
    if(argc > 3 )
        if(strcmp(argv[3],"-s") == 0)
        {
            sort[0] = 1;
            if(argc == 5 )
            {
                sort[1] = 1; sort[2] = 2; sort[3] = 3;
            }
            if(argc == 6)
            {
                char* pch;
                int i = 1;
                pch = strtok(argv[4],",");
                if(strcmp(pch,"id") == 0) sort[i] = 1;
                if(strcmp(pch,"time") == 0) sort[i] = 2;
                if(strcmp(pch,"values") == 0) sort[i] = 3;
                pch = strtok(NULL,",");
                if(pch!= NULL)
                {
                    i++;
                    if(strcmp(pch,"id") == 0) sort[i] = 1;
                    if(strcmp(pch,"time") == 0) sort[i] = 2;
                    if(strcmp(pch,"values") == 0) sort[i] = 3;
                    pch = strtok(NULL,",");
                    if(pch!= NULL)
                    {
                        i++;
                        if(strcmp(pch,"id") == 0) sort[i] = 1;
                        if(strcmp(pch,"time") == 0) sort[i] = 2;
                        if(strcmp(pch,"values") == 0) sort[i] = 3;
                    }
                }
            }
            if(strcmp(argv[argc - 1], "-asc") == 0) sort[4] = 1;
            if(strcmp(argv[argc - 1], "-dsc") == 0) sort[4] = -1;
        }
    printf("\nSort:");
    for(int i = 0 ; i < 5; i++) printf(" %d",sort[i]);
    if( Mode == 1 )
    {
        size = import_csv_to_dust_t(source_file, dust);
        convert_csv_to_hex(dust,size);
        printf("\nSize:%d",size);
    }
    if( Mode == 0)
    {
        size = import_hex_to_dust_t(source_file, dust);
        convert_hex_to_csv(dust,size);
        printf("\nSize:%d",size);
    }
    if(sort[0] == 1)
    {
    //    for(int i = 3; i >= 1; i--)
    //     if(sort[i] != 0) sorting(dust, size, sort[i], sort[4]);
        // sorting(dust, 0, size - 1, sort[1], sort[4]);
        // struct dust_t temp = dust[0]; int start = 0, end;
        // if(sort[2] != 0)
        //     while( end < size)
        //         {
        //             if(sort[1] == 1)
        //                 if(dust[end].sensor_id == temp.sensor_id) end++;
        //                     else
        //                     {

        //                     }
        //         }
        selection_sort(dust, size, sort);

    }
    // for(int i = 0; i < size; i++)
    //     printf("\n%d,%s,%.1f,%d,%s",dust[i].sensor_id,dust[i].timestamp,dust[i].value,dust[i].aqi,dust[i].pollution);
    if( Mode == 1) print_hex(dust, size, target_file);
    if( Mode == 0) print_csv(dust, size, target_file);
    printf("\nDone");
    return 0;
}