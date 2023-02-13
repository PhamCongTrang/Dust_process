#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdlib.h>
#include <time.h>
#include <string.h>
int int_to_hex(int x, char * c)
{
    itoa(x, c, 16);
    
    return 0;
}
int int_to_hex_1(int x, char * c)
{
    char d[5];
    itoa(x, d, 16);
    if(strlen(d) == 1) 
    {
        d[1] = d[0];
        d[0] = '0';
        d[2] = '\0';
    }
    c[0] = d[0]; c[1] = d[1]; c[2] = d[2];
    for(int i=0; i<=1; i++)
        if(c[i] > 96) c[i] -=32;
    return 0;
}
int int_to_hex_2(int x, char * c)
{
    char d[6];
    itoa(x, d, 16);
    if(strlen(d) == 1) 
    {
        d[3] = d[0];
        d[2] = '0';
        d[1] = '0';
        d[0] = '0';
        d[4] = '\0';
    }
    if(strlen(d) == 2) 
    {
        d[3] = d[1];
        d[2] = d[0];
        d[1] = '0';
        d[0] = '0';
        d[4] = '\0';
    }
    if(strlen(d) == 3) 
    {
        d[3] = d[2];
        d[2] = d[1];
        d[1] = d[0];
        d[0] = '0';
        d[4] = '\0';
    }
    c[0] = d[0]; c[1] = d[1]; c[2] = ' '; c[3] = d[2]; c[4] = d[3]; c[5] = '\0';
    for(int i=0; i<=4; i++)
        if(c[i] > 96) c[i] -=32;
    return 0;
}
int float_to_hex(float x, char *c)
{
    unsigned int temp;
    temp = *(unsigned int*) &x;
    char d[20];
    itoa(temp, d, 16);
    c[0] = d[0];
    c[1] = d[1];
    c[2] = ' ';
    c[3] = d[2];
    c[4] = d[3];
    c[5] = ' ';
    c[6] = d[4];
    c[7] = d[5];
    c[8] = ' ';
    c[9] = d[6];
    c[10] = d[7];
    c[11] = '\0';
    for(int i=0; i<=11; i++)
        if(c[i] > 96) c[i] -=32;
    return 0;
}
int time_tm_to_hex(char* t_m, char *c)
{
    struct tm local;

    local.tm_year = (t_m[0]-48)*1000 + (t_m[1]-48)*100 + (t_m[2]-48)*10 + (t_m[3]-48)*1 - 1900;
    local.tm_mon = (t_m[5]-48)*10 + (t_m[6]-48)*1 - 1;
    local.tm_mday = (t_m[8]-48)*10 + (t_m[9]-48)*1;
    local.tm_hour = (t_m[11]-48)*10 + (t_m[12]-48)*1 ;
    local.tm_min = (t_m[14]-48)*10 + (t_m[15]-48)*1;
    local.tm_sec = (t_m[17]-48)*10 + (t_m[18]-48)*1;
    
    time_t tim = mktime(&local) + 7*3600;
    char d[20];
    itoa(tim, d, 16);
    c[0] = d[0];
    c[1] = d[1];
    c[2] = ' ';
    c[3] = d[2];
    c[4] = d[3];
    c[5] = ' ';
    c[6] = d[4];
    c[7] = d[5];
    c[8] = ' ';
    c[9] = d[6];
    c[10] = d[7];
    c[11] = '\0';
    for(int i=0; i<=11; i++)
        if(c[i] > 96) c[i] -=32;
    return 0;
}
int hex_to_int(char a, char b)
{
    int x,y;
    if(a >= '0' && a <= '9') x = a - '0';
    if(a >= 'A' && a <= 'F') x = a - 'A' + 10;
    if(a >= 'a' && a <= 'f') x = a - 'a' + 10;

    if(b >= '0' && b <= '9') y = b - '0';
    if(b >= 'A' && b <= 'F') y = b - 'A' + 10;
    if(b >= 'a' && b <= 'f') y = b - 'a' + 10;
    return (x*16 + y);
}
int hex_to_int(char a, char b, char c, char d)
{
    int x,y,z,t;
    if(a >= '0' && a <= '9') x = a - '0';
    if(a >= 'A' && a <= 'F') x = a - 'A' + 10;
    if(a >= 'a' && a <= 'f') x = a - 'a' + 10;

    if(b >= '0' && b <= '9') y = b - '0';
    if(b >= 'A' && b <= 'F') y = b - 'A' + 10;
    if(b >= 'a' && b <= 'f') y = b - 'a' + 10;

    if(c >= '0' && c <= '9') z = c - '0';
    if(c >= 'A' && c <= 'F') z = c - 'A' + 10;
    if(c >= 'a' && c <= 'f') z = c - 'a' + 10;  

    if(d >= '0' && d <= '9') t = d - '0';
    if(d >= 'A' && d <= 'F') t = d - 'A' + 10;
    if(d >= 'a' && d <= 'f') t = d - 'a' + 10; 

    return (x*16*16*16 + y*16*16 + z*16 + t);
}
int hex_to_int(char a, char b, char c, char d,
                char e, char f, char g, char h)
{
    int x,y,z,t,u,v,r,s;
    if(a >= '0' && a <= '9') x = a - '0';
    if(a >= 'A' && a <= 'F') x = a - 'A' + 10;
    if(a >= 'a' && a <= 'f') x = a - 'a' + 10;

    if(b >= '0' && b <= '9') y = b - '0';
    if(b >= 'A' && b <= 'F') y = b - 'A' + 10;
    if(b >= 'a' && b <= 'f') y = b - 'a' + 10;

    if(c >= '0' && c <= '9') z = c - '0';
    if(c >= 'A' && c <= 'F') z = c - 'A' + 10;
    if(c >= 'a' && c <= 'f') z = c - 'a' + 10;  

    if(d >= '0' && d <= '9') t = d - '0';
    if(d >= 'A' && d <= 'F') t = d - 'A' + 10;
    if(d >= 'a' && d <= 'f') t = d - 'a' + 10; 

    if(e >= '0' && e <= '9') u = e - '0';
    if(e >= 'A' && e <= 'F') u = e - 'A' + 10;
    if(e >= 'a' && e <= 'f') u = e - 'a' + 10; 

    if(f >= '0' && f <= '9') v = f - '0';
    if(f >= 'A' && f <= 'F') v = f - 'A' + 10;
    if(f >= 'a' && f <= 'f') v = f - 'a' + 10; 

    if(g >= '0' && g <= '9') r = g - '0';
    if(g >= 'A' && g <= 'F') r = g - 'A' + 10;
    if(g >= 'a' && g <= 'f') r = g - 'a' + 10; 

    if(h >= '0' && h <= '9') s = h - '0';
    if(h >= 'A' && h <= 'F') s = h - 'A' + 10;
    if(h >= 'a' && h <= 'f') s = h - 'a' + 10; 

    return (x*16*16*16*16*16*16*16 + y*16*16*16*16*16*16 + z*16*16*16*16*16 + t*16*16*16*16 + u*16*16*16 + v*16*16 + r*16 + s);
}
int checksum(char * id, char *time, char *pm, char *aqi, char *ck)
{
    
        int id_i, time_i, pm_i, aqi_i;
        id_i = hex_to_int(id[0],id[1]);
        time_i = hex_to_int(time[0],time[1]) + hex_to_int(time[3],time[4]) + hex_to_int(time[6],time[7]) + hex_to_int(time[9],time[10]);
        pm_i = hex_to_int(pm[0],pm[1]) + hex_to_int(pm[3],pm[4]) + hex_to_int(pm[6],pm[7]) + hex_to_int(pm[9],pm[10]);
        aqi_i = hex_to_int(aqi[0],aqi[1]) + hex_to_int(aqi[3],aqi[4]);

        int sum_i = id_i + time_i + pm_i + aqi_i + 15;
        char c[30];
        int_to_hex(sum_i,c);
        int sum_2 = hex_to_int(c[strlen(c)-2],c[strlen(c)-1]);
        sum_2 = ~sum_2 + 1;
        int_to_hex(sum_2,c);
        
        ck[0] = c[6];
        ck[1] = c[7];
        ck[2] = '\0';
        for(int i=0; i<=1; i++)
            if(ck[i] > 96) ck[i] -=32;
    return 0;
}
time_t timestamp_to_tim(char* t_m)
{
    struct tm local;

    local.tm_year = (t_m[0]-48)*1000 + (t_m[1]-48)*100 + (t_m[2]-48)*10 + (t_m[3]-48)*1 - 1900;
    local.tm_mon = (t_m[5]-48)*10 + (t_m[6]-48)*1 - 1;
    local.tm_mday = (t_m[8]-48)*10 + (t_m[9]-48)*1;
    local.tm_hour = (t_m[11]-48)*10 + (t_m[12]-48)*1 ;
    local.tm_min = (t_m[14]-48)*10 + (t_m[15]-48)*1;
    local.tm_sec = (t_m[17]-48)*10 + (t_m[18]-48)*1;
    
    time_t tim = mktime(&local);
    return tim;
}
int hex4_to_tm(char* t1, char * t2, char * t3, char* t4, char * timestamp)
{
    time_t tim = hex_to_int(t1[0],t1[1],t2[0],t2[1],t3[0],t3[1],t4[0],t4[1]);
    struct tm* loc;
    loc = local(&tim);
    strftime(timestamp,29,"%Y:%m:%d %H:%M:%S",loc);
    return 0;
}
#endif