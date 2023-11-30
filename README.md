# ESP32S3 Weather station

## Weather forecast 
This Application fetches a temperature   
forecast from given url and presents the result on TXT 240x240 panel   

Forecast format:
```
{
  "name": "weather",
  "forecast": [
    {
      "hours": 1,
      "temp": -3,
      "wind": 5,
      "windDir": 47,
      "symbol": 7
    },
    ... 
```
Where hour is 01:00:00 given on your local time.

![alt text](https://github.com/vesakoo/FmiWeatherStationESP32S3/blob/main/images/display_weath.jpg?raw=true)
![alt text](https://github.com/vesakoo/FmiWeatherStationESP32S3/blob/main/images/display_wind.jpg?raw=true)




### Web backend
Example backend solution:  https://github.com/vesakoo/fmiForecastEspoo  
Creates a weather.json file that one can place into webserver to share.   
Example renders weather forecast on Finland / Espoo - area fetching the data  
from  Finish institute of meteorology Open data interface:   
https://www.ilmatieteenlaitos.fi/avoin-data   


### Hardware
* Elecard ESP32-S3 Core Board ESP32 DevKit module with IPS Display Wi-Fi&BLE MCU Module

https://www.elecrow.com/esp32-s3-core-board-esp32-devkit-module-with-ips-display-wi-fi-ble-mcu-module.html


### Requirements
* install libs
https://github.com/Bodmer/TFT_eSPI   
Arduino JSON  
https://arduinojson.org/?utm_source=meta&utm_medium=library.properties
PNGdec   
https://github.com/bitbank2/PNGdec


* add SSID.h to with connection parameters for your WIFI router

SSID.h
```
#define SECRET_SSID "your-secret"
#define SECRET_PASS "your-pass"
#define ACTION_TTL (unsigned long) 15000
#define AUTH      WIFLY_AUTH_WPA2_PSK
```

###Tools  

Tools folder contains a Python script to create symbols.h -file containing png-images in hex array format.
* Run script in same folder where your images are locted to create this file.
* Images on folder need to use numeric naming: 1.png,2.png,...   
* By default script handles images from 0-200.png
Example:
```
cp ./symbol_images/*.png ./tools/original
cd ./tools/original
python3 ../pngsymbolsToC.py
cp symbols.h ../../
```

TODO: index allocation table shuld be pre-filled with -1 instead of 0.   
