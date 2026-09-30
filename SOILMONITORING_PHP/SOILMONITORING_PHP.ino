#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ESPTest";
const char* password = "12345678";

const char* serverURL = "http://192.168.181.142/SOILMONITOR/SOIL_PHP/soil.php2";

#define SOIL_PIN 4

void setup()
{
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("ESP8266 IP: ");
  Serial.println(WiFi.localIP());
}

void loop()
{

  int SoilValue = analogRead (SOIL_PIN);

  Serial.print("SOIL Value: ");
  Serial.println(SoilValue);

  if (WiFi.status() == WL_CONNECTED) 
  {
    
    WiFiClient Client;
    HTTPClient http;

    String url = String(serverURL) + "?soil=" + String(SoilValue);
    
    Serial.println(url);
    http.begin( Client, url);

    int httpCode = http.GET();
    
    if(httpCode > 0)
    {
     
     Serial.print("HTTP Response Code: ");
     Serial.println(httpCode);

     String response = http.getString();


     Serial.print("Server Response: ");
     Serial.println(response);

    }

    http.end();
  }

  delay(5000);
}


