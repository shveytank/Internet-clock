#include "NTPClient.h"
#include "ESP8266WiFi.h" // provides ESP8266 specific Wi-Fi routines we are calling to connect to network #include "WiFiUdp.h" //handles sending and receiving of UDP packages

#include "SPI.h" // SPI for interfacing OLED with NodeMCu

#include "Adafruit_GFX.h"

#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels

#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

constchar *ssid = "yourwifissid";

const char *password = "yourwifipass";

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800,60000);

String arr_days[]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

String date_time; // You can specify the time server pool and the offset (in seconds, can be // changed later with setTimeOffset() ). Additionaly you can specify the // update interval (in milliseconds, can be changed using setUpdateInterval() ).

void setup()

{

Serial.begin(115200);

WiFi.begin(ssid, password);

while ( WiFi.status() != WL_CONNECTED )

{

delay ( 500 );

Serial.print ( "." );

}

if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))

{

Serial.println(F("SSD1306 allocation failed"));

for(;;); // Don't proceed, loop forever

}

display.clearDisplay();

display.setTextSize(2); // Draw 2X-scale text

display.setTextColor(WHITE);

display.setCursor(5, 2);

display.println("WELCOME TO");

display.println(" instructables");

display.println(" Project");

display.display();

delay(3000);

timeClient.begin();

}

void loop()

{

timeClient.update();

display.clearDisplay();

Serial.println(timeClient.getFormattedTime());

display.setTextSize(2); // Draw 2X-scale text

display.setTextColor(BLUE);

display.setCursor(0, 2);

int hh = timeClient.getHours();

int mm = timeClient.getMinutes();

int ss = timeClient.getSeconds();

if(hh>12)

{

hh=hh-12;

display.print(hh);

display.print(":");

display.print(mm);

display.print(":");

display.print(ss);

display.println(" PM");

}

else

{

display.print(hh);

display.print(":");

display.print(mm);

display.print(":");

display.print(ss);

display.println(" AM");

}

int day = timeClient.getDay();

display.println("'"+arr_days[day]+"'");

date_time = timeClient.getFormattedDate();

int index_date = date_time.indexOf("T");

String date = date_time.substring(0, index_date);

Serial.println(date);

display.println(date);

display.display();

// Show initial text }