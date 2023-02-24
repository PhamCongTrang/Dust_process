#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct dust_t
{
    int sensor_id;
    char timestamp[20];
    float value;
    int aqi;
    char pollution[50];

    char start_byte[4];
    char packet_length[4];
    char sensor_id_hex[4];
    char timestamp_hex[20];
    char value_hex[20];
    char aqi_hex[10];
    char checksum[4];
    char stop_byte[4];
};
/*
* Use to read each line of f_name_csv to struct dust_t
* Field will be changed: {sensor_id, timestamp, value, aqi, pollution}
*/
int import_csv_to_dust_t(char* f_name_csv, struct dust_t * dust)
{
    FILE* f;
    f = fopen(f_name_csv, "r");
    //printf("fopen: %d\n",f);
    struct dust_t temp;
    char line[50];
    fgets(line, 50,f); // Bo qua dong dau
    int i = 0;
    while (fgets(line,sizeof(line),f))
    {
        char * pch;

        pch = strtok(line,",");
        temp.sensor_id = atoi(pch);
        
        pch = strtok(NULL,",");
        if(pch!= NULL) strcpy(temp.timestamp, pch);

        pch = strtok(NULL,",");
        temp.value = atof(pch);

        pch = strtok(NULL,",");
        temp.aqi = atoi(pch);

        pch = strtok(NULL,"\n");
        if(pch!= NULL) strcpy(temp.pollution, pch);

        dust[i] = temp;
        pch = strtok(NULL,"\n");
        i++;
    }
    fclose(f);
    return i;
}
/*
* Use to read each line of f_name_hex to struct dust_t
* Field will be changed: {start_byte, packet_length, sensor_id_hex, timestamp_hex, value_hex, aqi_hex, checksum, stop_byte}
*/
void import_hex_to_dust_t(char* f_name_hex, struct dust_t * dust)
{

}
int sum_byte(char *c)
{
    int n = strlen(c);
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        int dec;
        if(c[i] == ' ') continue;
        if(c[i] >= '0' && c[i] <= '9') dec = c[i] - '0';
        if(c[i] >= 'A' && c[i] <= 'F') dec = c[i] - 'A' + 10;
        if(c[i] >= 'a' && c[i] <= 'f') dec = c[i] - 'a' + 10;
        /*
        * 2 dong duoi co chuc nang tai ra chuoi y = {16 1 0} lien tuc
        * Ung voi x = { 0 1 2} lien tuc la so du cua i cho 3
        */
        int x = i % 3;
        int y = 7*x*x - 22*x + 16;
        sum += y*dec;
    }
    return sum;
}
/*
* Use to convert csv info to hex. Print to f_name_hex
* dust_t before: {sensor_id, timestamp, value, aqi, pollution}
* dust_t after: add {start_byte, packet_length, sensor_id_hex, timestamp_hex, value_hex, aqi_hex, checksum, stop_byte}
*/
void convert_csv_to_hex(struct dust_t * dust, int size, char* f_name_hex)
{
    FILE* fhex;
    fhex = fopen(f_name_hex,"w");
    for(int i = 0; i < size; i++)
    {
        //-- start_byte_hex
        strcpy(dust[i].start_byte, "00");
        //--packet_length_hex
        strcpy(dust[i].packet_length, "0F");
        //--sensor_id_hex
        itoa(dust[i].sensor_id,dust[i].sensor_id_hex,16);
        //--timestamp_hex
        struct tm local;
        local.tm_year = ((dust[i].timestamp)[0]-48)*1000 + ((dust[i].timestamp)[1]-48)*100 + ((dust[i].timestamp)[2]-48)*10 + ((dust[i].timestamp)[3]-48)*1 - 1900;
        local.tm_mon = ((dust[i].timestamp)[5]-48)*10 + ((dust[i].timestamp)[6]-48)*1 - 1;
        local.tm_mday = ((dust[i].timestamp)[8]-48)*10 + ((dust[i].timestamp)[9]-48)*1;
        local.tm_hour = ((dust[i].timestamp)[11]-48)*10 + ((dust[i].timestamp)[12]-48)*1 ;
        local.tm_min = ((dust[i].timestamp)[14]-48)*10 + ((dust[i].timestamp)[15]-48)*1;
        local.tm_sec = ((dust[i].timestamp)[17]-48)*10 + ((dust[i].timestamp)[18]-48)*1;
        time_t tim = mktime(&local) + 7*3600;
        itoa(tim,dust[i].timestamp_hex,16);
        //--value_hex
        unsigned int temp;
        temp = *(unsigned int*) &dust[i].value;
        itoa(temp, dust[i].value_hex, 16);
        //--aqi_hex
        itoa(dust[i].aqi,dust[i].aqi_hex,16);
        //--checksum
        sum = sum_byte(dust[i].packet_length) + sum_byte(dust[i].sensor_id_hex) + sum_byte(dust[i].timestamp_hex) 
                    + (dust[i].aqi_hex) + sum_byte(dust[i].value_hex);
        int sum_last_2 = sum % 256;
        sum_last_2 = ~ sum_last_2 + 1;
        

        //--stop_byte
        strcpy(dust[i].stop_byte,"FF");

    }
    fclose(fhex);   
}
void format_hex(char* c)
{
    int n = strlen(c);
    char cold[20];
    strcpy(cold,c);
    int j = 0;
    if(n % 2 == 1) 
    {
        c[0] = '0';
        j++;
    }
    for(int i = 0; i < n; i++)
    {
        if(cold[i] >= 'a') cold[i] -=32;
        if(j % 3 == 2)
        {
            c[j] = ' ';
            j++;
        } 
        c[j] = cold[i];
        j++;

    }
}
void format_dust_hex(struct dust_t* dust, int size)
{
    for(int i = 0; i < size; i++ )
    {
        format_hex(dust[i].sensor_id_hex);
        format_hex(dust[i].timestamp_hex);
        format_hex(dust[i].value_hex);
        format_hex(dust[i].aqi_hex);
        format_hex(dust[i].checksum);
    }
}
/*
* Use to convert hex info to csv. Print to f_name_csv
* dust_t before: {start_byte, packet_length, sensor_id_hex, timestamp_hex, value_hex, aqi_hex, checksum, stop_byte}
* dust_t after: add {sensor_id, timestamp, value, aqi, pollution}
*/
int hex_to_dec(char *c)
{
    int n = strlen(c);
    int sum = 0;
    for(int i = 0; i < n; i++ )
    {
        if(c[i] == ' ') continue;
        int dec;
        if(c[i] >= '0' && c[i] <= '9') dec = c[i] - '0';
        if(c[i] >= 'A' && c[i] <= 'F') dec = c[i] - 'A' + 10;
        if(c[i] >= 'a' && c[i] <= 'f') dec = c[i] - 'a' + 10;
        sum += dec*round(pow(16,(n+1)*2/3 - i - 1)); 
    }
    return sum;
}
void convert_hex_to_csv(struct dust_t * dust, char* f_name_csv)
{

}
#endif
