#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Om_manekar";        // your hotspot name
const char* password = "00000000"; // your hotspot password

ESP8266WebServer server(80);

// GPS data variables
String lat = "0.0000";
String lon = "0.0000";

void handleRoot()
{
String page = "<html><head>";
page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
page += "<meta http-equiv='refresh' content='2'>";
page += "</head><body style='text-align:center;font-family:Arial;'>";

page += "<h2>Vehicle Tracking System</h2>";

page += "<p><b>Latitude:</b> " + lat + "</p>";
page += "<p><b>Longitude:</b> " + lon + "</p>";

page += "<a href='https://maps.google.com/?q=" + lat + "," + lon + "' target='_blank'>";
page += "<button style='padding:12px;font-size:18px;'>Open in Google Maps</button></a>";

page += "</body></html>";

server.send(200, "text/html", page);
}

void setup()
{
Serial.begin(9600);   // MUST match STM32 UART

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED)
{
delay(500);
}

server.on("/", handleRoot);
server.begin();
}

void loop()
{
server.handleClient();

// Receive GPS data from STM32
if (Serial.available())
{
String data = Serial.readStringUntil('\n');

int commaIndex = data.indexOf(',');

if (commaIndex > 0)
{
  lat = data.substring(0, commaIndex);
  lon = data.substring(commaIndex + 1);
}

}
}
