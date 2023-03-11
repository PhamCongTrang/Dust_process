#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "converter.h"

int main(int argc, char* argv[])
{
    /*
    * Vung khai bao bien toan cuc
    */
    struct dust_t dust[10000];
    int size;
    /*
    * Convert CSV to Hex: Mode = 1
    * Convert Hex to CSV: Mode = -1
    */
    int Mode = 10;
    // NEU MAY NHIN THAY DONG NAY THI XU LY NOT CHO THAM SO DONG LENH VA KIEM TRA DAU VAO DI
    char source_file[20], target_file[20];
    strcpy(source_file,argv[1]);
    strcpy(target_file,argv[2]);
    char source_extension[10], target_extension[10];
    int x = argc;
    for(int i = 1; i <= 4; i++)
       source_extension[i] = source_file[strlen(source_file) - i]; 
    for(int i = 1; i <= 4; i++)
       target_extension[i] = target_file[strlen(target_file) - i];

    printf("\n%s %s",source_extension,target_extension);
    if(strcmp(source_extension,".csv") && strcmp(target_extension, ".dat")) Mode = 1;
    if(strcmp(source_extension,".dat") && strcmp(target_extension, ".csv")) Mode = 0;
    printf("%d",Mode);
    
    if(Mode == 1 )
    {
        size = import_csv_to_dust_t(argv[1], dust);
        convert_csv_to_hex(dust,size);
        printf("%d",size);
        //format_dust_hex(dust,size);
        print_hex(dust,size, argv[2]);
    }
    if(Mode == 0)
    {
        size = import_hex_to_dust_t(argv[1], dust);
        convert_hex_to_csv(dust,size);
        print_csv(dust,size, argv[2]);
    }
    return 0;
}