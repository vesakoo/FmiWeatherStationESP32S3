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
* add SSID.h to with connection parameters for your WIFI router

SSID.h
```
#define SECRET_SSID "your-secret"
#define SECRET_PASS "your-pass"
#define ACTION_TTL (unsigned long) 15000
#define AUTH      WIFLY_AUTH_WPA2_PSK
```

