﻿# Final_project_KTLT
The task of the problem is to process dust data.
## Consensus problem:
1. Read the csv file containing dust data including: sensor number, measurement time, dust concentration
2. Convert dust concentration to air quality AQI
3. Remove invalid data
4. Encode data to hex for UART communication
## Inverse problem:
1. Read hex file containing encrypted data
2. Convert from hex data to readable form: sensor number, measurement time, dust concentration, AQI index
3. Sort data by one or more parameters: sensor number, measurement time, dust concentration, AQI index
