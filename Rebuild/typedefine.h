#ifndef TYPEDEFINE
#define TYPEDEFINE
struct dust_t
{
    int sensor_id;
    char timestamp[20];
    float value;
    int aqi;
    char pollution[80];

    char start_byte[8];
    char packet_length[6];
    char sensor_id_hex[6];
    char timestamp_hex[20];
    char value_hex[20];
    char aqi_hex[10];
    char checksum[10];
    char stop_byte[8];
    
    int time;
};

#endif
