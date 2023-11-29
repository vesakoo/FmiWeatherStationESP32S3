/**
 * FMiWeatherStationESP32S2.ino
 * based on examples:
 * BasicHTTPClient.ino from ESP32S2 Dev Module examples and 
 * Flash_PNG from TFT_eSPI.h examples
 * 
 *
 *  Created on: 2023-11-30
 *
 */

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#include <User_Setup.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include <math.h>
#include <ArduinoJson.h>

#include <PNGdec.h>

#include "symbols.h" // Image is stored here in an 8 bit array
#include "SSID.h"

PNG png;
#define MAX_IMAGE_WIDTH 42 // Adjust for your images
int16_t xpos = 0; //for symbol image
int16_t ypos = 0; //for symbol image



#define USE_SERIAL Serial
#define TFT_GREY 0x5AEB
#define DARKER_GREY 0x18E3

WiFiMulti wifiMulti;

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
bool swap =true;
//TFT_eSprite face = TFT_eSprite(&tft);
//StaticJsonDocument<7000> doc;

/*
const char* ca = \ 
"-----BEGIN CERTIFICATE-----\n" \  
"MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/\n" \  
"MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \  
"DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow\n" \  
"SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT\n" \  
"GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC\n" \  
"AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF\n" \  
"q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8\n" \  
"SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0\n" \  
"Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA\n" \  
"a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj\n" \  
"/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T\n" \  
"AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG\n" \  
"CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv\n" \  
"bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k\n" \  
"c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw\n" \  
"VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC\n" \  
"ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz\n" \  
"MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu\n" \  
"Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF\n" \  
"AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo\n" \  
"uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/\n" \  
"wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu\n" \  
"X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG\n" \  
"PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6\n" \  
"KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==\n" \  
"-----END CERTIFICATE-----\n";
*/

void setup() {

    USE_SERIAL.begin(115200);

    tft.init();
    tft.setSwapBytes(true);  
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(3);
    //ledcSetup(0,20000,10);
    //ledcAttachPin(BUZ_PIN,0);
    //pinMode(Sound_PIN,INPUT);
    
    tft.setSwapBytes(true); 

    //USE_SERIAL.println();
    //USE_SERIAL.println();
    //USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP(SECRET_SSID, SECRET_PASS);
    tft.setCursor(0, 0, 4);
    //tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
     tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    tft.setTextFont(5);
    tft.println("Hello World!");
  // The background colour will be read during the character rendering
  

}

void loop() {
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {
        HTTPClient http;
        //USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http.begin("http://robo.sukelluspaikka.fi/images/weather.json"); //HTTP
        //USE_SERIAL.print("[HTTP] GET...\n");
        //tft.println("[HTTP] GET...");
        // Allocate the JSON document
  // Use https://arduinojson.org/v6/assistant to compute the capacity.
  //const size_t capacity = JSON_OBJECT_SIZE(3600) + JSON_ARRAY_SIZE(2) + 60;
  
  

        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            //USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
            //tft.printf("[HTTP] GET... code: %d\n",httpCode);
             //tft.printf(const char *format, ...)
            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                DynamicJsonDocument doc(3072);

                DeserializationError error = deserializeJson(doc, payload);
                tft.fillScreen(TFT_BLACK);
                tft.setCursor(0, 0, 4);
                if (error) {
                  tft.print("deserializeJson() failed: ");
                  tft.println(error.c_str());
                  return;
                }
                int i =0;
                
                
                for (JsonObject forecast_item : doc["forecast"].as<JsonArray>()) {
                  //if(++i<10){    
                  int hrs = forecast_item["hours"]; 
                  if(hrs==8 ||hrs==12 ||hrs==16||hrs==20||hrs==1){
                    int temp = forecast_item["temp"]; 
                    int wps = forecast_item["wind"]; 
                    int wDir = forecast_item["windDir"];
                    int symbol = forecast_item["symbol"];
                    tft.setTextFont(6);
                    tft.printf("%02d %3d ",hrs,temp );
                    tft.setTextFont(4);
                    tft.printf("%2d",wps);
                    tft.setTextFont(2);
                    tft.print(" m/s");
                    tft.setTextFont(6);
                    int x=tft.getCursorX();
                    int y = tft.getCursorY();
                    if(swap ){
                        //int x=tft.getCursorX();
                        //int y = tft.getCursorY();
                        //tft.drawLine(x, y, x+20, y+20, TFT_CYAN);
                        //tft.drawCircleHelper()
                        tft.drawSmoothCircle(x+24, y+24, 22, TFT_SILVER, DARKER_GREY);
                        // Draw cecond hand
                        float xp = 0.0, yp = 0.0;
                        float xa = 0.0, ya = 0.0;
                        //float xz = 0.0, yz = 0.0;
                        getCoord(x+24, y+24, &xa, &ya, 6, 1.0f*wDir);
                        tft.drawWedgeLine(x+24, y+24, xa, ya, 0.5, 4.5, TFT_RED);
                        //getCoord(x+24, y+24, &xz, &yz, 20, 1.0f*wDir);
                        getCoord(x+24, y+24, &xp, &yp, 19, 1.0f*wDir);
                        tft.drawWedgeLine(xa, ya, xp, yp,2.5, 2.5, TFT_RED);

                    }else{
                      xpos =x;
                      ypos =y;
                      drawSymbol(symbol);
                    }                    
                    tft.print('\n');
                  }
                }
                 swap = !swap;
                
            }
        } else {
            tft.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());

        }

        http.end();
        delay(5000);
    }

    delay(5000);
}

void drawSymbol(int symbol) {
  int symbol_index = getSymbol[symbol];
  int16_t rc = png.openFLASH((uint8_t *)fmisymbols[symbol_index], fmisizes[symbol_index], pngDraw);
  if (rc == PNG_SUCCESS) {
    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
    // png.close(); // not needed for memory->memory decode
  }
}


// =========================================================================
// Get coordinates of end of a line, pivot at x,y, length r, angle a
// =========================================================================
// Coordinates are returned to caller via the xp and yp pointers
#define DEG2RAD 0.0174532925
void getCoord(int16_t x, int16_t y, float *xp, float *yp, int16_t r, float a)
{
  float sx1 = cos( (a - 90) * DEG2RAD);
  float sy1 = sin( (a - 90) * DEG2RAD);
  *xp =  sx1 * r + x;
  *yp =  sy1 * r + y;
}

//=========================================v==========================================
//                                      pngDraw
//====================================================================================
// This next function will be called during decoding of the png file to
// render each image line to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
// Callback function to draw pixels to the display
void pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WIDTH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}
