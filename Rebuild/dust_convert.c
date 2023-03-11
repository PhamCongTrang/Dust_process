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
    * Convert Hex to CSV: Mode = 0
    */
    int Mode = 10;
    int x = argc; //printf("%d",x);
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
    
    if( Mode == 1 )
    {
        size = import_csv_to_dust_t(source_file, dust);
        convert_csv_to_hex(dust,size);
        printf("\nSize:%d",size);
        print_hex(dust,size, target_file);
    }
    if( Mode == 0)
    {
        size = import_hex_to_dust_t(source_file, dust);
                for(int i = 0; i < size; i++)
            printf("%s %s %s %s %s %s %s %s\n", 
                dust[i].start_byte,dust[i].packet_length, dust[i].sensor_id_hex,
                dust[i].timestamp_hex,dust[i].value_hex,dust[i].aqi_hex,dust[i].checksum,dust[i].stop_byte);
        convert_hex_to_csv(dust,size);
        printf("\nSize:%d",size);
        print_csv(dust,size, target_file);

    }
    return 0;
}