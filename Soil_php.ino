#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ESPTest";
const char* password = "12345678";

const char* serverURL = "http://192.168.181.142/Soil_php/Soil_php.php";

#define SOIL_PIN A0

void setup()
{
  Serial.begin(9600);
  delay(2000);

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

  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());

  Serial.print("PC Server IP: ");
  Serial.println("192.168.181.142");
}

void loop()
{
  int soilValue = analogRead(SOIL_PIN);

  Serial.println();
  Serial.println("STEP 1");
  Serial.print("SOIL Value: ");
  Serial.println(soilValue);

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("STEP 2 - WiFi Connected");

    WiFiClient client;
    HTTPClient http;

    String url = String(serverURL) + "?soil=" + String(soilValue);

    Serial.print("URL: ");
    Serial.println(url);

    http.setTimeout(10000);

    Serial.println("STEP 3 - Sending");

    if (http.begin(client, url))
    {
      int httpCode = http.GET();

      Serial.print("HTTP Response code: ");
      Serial.println(httpCode);

      if (httpCode > 0)
      {
        String response = http.getString();

        Serial.print("PHP Response: ");
        Serial.println(response);
      }
      else
      {
        Serial.print("HTTP Error: ");
        Serial.println(http.errorToString(httpCode));
      }

      http.end();
    }
    else
    {
      Serial.println("HTTP begin failed");
    }
  }
  else
  {
    Serial.println("STEP 2 - WiFi NOT connected");
  }

  Serial.println("--------------------");

  delay(5000);
}


