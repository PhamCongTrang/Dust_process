#include <stdio.h>
#include "converter.h"
#include <string.h>
struct dust_t_op 
{
    //dust_t mở rộng
    int sensor_id;
    char timestamp[20];
    float value;
    int aqi;
};
int csv_to_hex(char* f_name_aqi, char* f_name_hex )
{
    FILE *faqi, *fhex;
    faqi = fopen(f_name_aqi,"r");
    fhex = fopen(f_name_hex, "w");

    char line[50];
    fgets(line,50,faqi); // Bo qua dong dau

    while (fgets(line,sizeof(line),faqi))
    {
        char * pch;
        struct dust_t_op temp_dust;
        pch = strtok(line,",");
        temp_dust.sensor_id = atoi(pch);
        
        pch = strtok(NULL,",");
        if(pch!=NULL)
            strcpy(temp_dust.timestamp, pch);

        pch = strtok(NULL,",");
        temp_dust.value = atof(pch);

        pch = strtok(NULL,",");
        temp_dust.aqi = atoi(pch);

        pch = strtok(NULL,"\n");

        char id[3], time[13],pm[13],aqi[7], ck[3];
        int_to_hex_1(temp_dust.sensor_id,id);
        time_tm_to_hex(temp_dust.timestamp,time);
        float_to_hex(temp_dust.value,pm);
        int_to_hex_2(temp_dust.aqi,aqi);

        checksum(id, time, pm, aqi, ck);

        fprintf(fhex,"00 0F %s %s %s %s %s FF\n",id, time, pm, aqi, ck);
    }
    fclose(faqi);
    fclose(fhex);
    return 0;
}
int hex_to_csv(char* f_name_hex, char * f_name_aqi)
{
    FILE *faqi, *fhex;
    fhex = fopen(f_name_hex, "r");
    faqi = fopen(f_name_aqi, "w");
    char line[50];

    while (fgets(line,sizeof(line),fhex))
    {
        char * pch;
        struct dust_t_op temp_dust;
        pch = strtok(line," "); /*Loai bo Start byte*/
        
        pch = strtok(NULL," "); /*Loai bo Packet length*/
        
        pch = strtok(NULL," "); /*pch: dia chi xau chua sensor_id*/
        char id[3]; strcpy(id,pch);
        temp_dust.sensor_id = hex_to_int(id[0],id[1]);

        char t1[3], t2[3], t3[3], t4[3]; // Lan luot chua 4 nhom cua timestamp
        pch = strtok(NULL," ");
        if(pch!=NULL) strcpy(t1, pch);
        pch = strtok(NULL," ");
        if(pch!=NULL) strcpy(t2, pch);
        pch = strtok(NULL," ");
        if(pch!=NULL) strcpy(t3, pch);   
        pch = strtok(NULL," ");
        if(pch!=NULL) strcpy(t4, pch);    
        time_t tim = hex_to_int(t1[0],t1[1],t2[0],t2[1],t3[0],t3[1],t4[0],t4[1]);
        struct tm* loc;
        loc = local(&tim);
        strftime(temp_dust.timestamp,29,"%Y:%m:%d %H:%M:%S",loc);

        char v1[3], v2[3], v3[3], v4[3]; // Lan luot chua 4 nhom cua value PM2.5
        pch = strtok(NULL," ");
        if(pch!=NULL) strcpy(v1, pch);
        pch = strtok(NULL," ");
        if(pch!=NULL) strcpy(v2, pch);
        pch = strtok(NULL," ");
        if(pch!=NULL) strcpy(v3, pch);   
        pch = strtok(NULL," ");
        if(pch!=NULL) strcpy(v4, pch);          

        char a1[3], a2[3]; // Lan luot chua 2 bit cua AQI
        pch = strtok(NULL," ");
        if(pch!=NULL) strcpy(a1, pch);    
        pch = strtok(NULL," ");
        if(pch!=NULL) strcpy(a2, pch);     
        temp_dust.aqi = hex_to_int(a1[0],a1[1],a2[0],a2[1]);

        fprintf(faqi, "%d, %s, %.1f, %d", temp_dust.sensor_id, temp_dust.timestamp,temp_dust.value,temp_dust.aqi);

    }
    fclose(faqi);
    fclose(fhex);
    return 0;
}