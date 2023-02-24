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
    char f_name_hex[30] = "dust.hex";
    /*
    * Convert CSV to Hex: Mode = 1
    * Convert Hex to CSV: Mode = -1
    */
    int Mode = 1;
    if(Mode == 1 )
    {
        size = import_csv_to_dust_t(f_name_csv, dust);
        convert_csv_to_hex(dust,size, f_name_hex);
        printf("%d",size);
    }
    else
    {
        import_hex_to_dust_t(f_name_hex, dust);
        convert_hex_to_csv(dust, f_name_csv);
    }
    format_dust_hex(dust,size);
    for(int i = 0; i < size; i++)
        //printf("\n%d,%s,%.1f,%d,%s",dust[i].sensor_id,dust[i].timestamp,dust[i].value,dust[i].aqi,dust[i].pollution);
        printf("\n%s,%s,%s,%s,%s,%s,%s", 
        dust[i].start_byte,dust[i].packet_length, dust[i].sensor_id_hex,dust[i].timestamp_hex,dust[i].value_hex,dust[i].aqi_hex,dust[i].stop_byte);
    printf("\n%d",sum_byte(dust[size -1].timestamp_hex));
    return 0;
}