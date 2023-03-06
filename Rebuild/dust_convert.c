#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "converter.h"

int main()
{
    /*
    * Vung khai bao bien toan cuc
    */
    struct dust_t dust[10000];
    int size;
    char f_name_csv[30] = "dust_aqi.csv";
    char f_name_hex[30] = "hex_dust.dat";
    /*
    * Convert CSV to Hex: Mode = 1
    * Convert Hex to CSV: Mode = -1
    */
    int Mode = 1;
    if(Mode == 1 )
    {
        size = import_csv_to_dust_t(f_name_csv, dust);
        convert_csv_to_hex(dust,size);
        printf("%d",size);
        format_dust_hex(dust,size);
        print_hex(dust,size,f_name_hex);
    }
    else
    {
        size = import_hex_to_dust_t(f_name_hex, dust);
        convert_hex_to_csv(dust,size, f_name_csv);
    }
    return 0;
}