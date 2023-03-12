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
    FILE* flog;
    flog = fopen("dust_convert_run.log","w");
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
    
    if( Mode == 1 )
    {
        size = import_csv_to_dust_t(source_file, dust);
        convert_csv_to_hex(dust,size);
    }
    if( Mode == 0)
    {
        size = import_hex_to_dust_t(source_file, dust);
        convert_hex_to_csv(dust,size);
    }
    fprintf(flog,"Total number of rows:%d",size);
    fprintf(flog,"\nSuccesfully converted rows: %d",size);
    fprintf(flog,"\nError rows: 0");

    if(sort[0] == 1)
    {
        fprintf(flog,"\nSorting algorithm heap [ms]:%f",heapsort(dust, size, sort));
        if( Mode == 1 )
        {
            size = import_csv_to_dust_t(source_file, dust);
            convert_csv_to_hex(dust,size);
        }
        if( Mode == 0)
        {
            size = import_hex_to_dust_t(source_file, dust);
            convert_hex_to_csv(dust,size);
        }
        fprintf(flog,"\nSorting algorithm select [ms]:%f",selection_sort(dust, size, sort));
        if( Mode == 1 )
        {
            size = import_csv_to_dust_t(source_file, dust);
            convert_csv_to_hex(dust,size);
        }
        if( Mode == 0)
        {
            size = import_hex_to_dust_t(source_file, dust);
            convert_hex_to_csv(dust,size);
        }
        fprintf(flog,"\nSorting algorithm quick [ms]:%f",quicksort(dust, size, sort));
    }  

    if( Mode == 1) print_hex(dust, size, target_file);
    if( Mode == 0) print_csv(dust, size, target_file);
    fclose(flog);
    return 0;
}