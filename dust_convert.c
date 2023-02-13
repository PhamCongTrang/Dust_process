#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "converter.h"
#include "converterfinal.h"
int main()
{
    char f_name_aqi[] = "dust_aqi.csv";
    char f_name_hex[] = "dust.hex";
    csv_to_hex(f_name_aqi,f_name_hex);
    return 0;
}