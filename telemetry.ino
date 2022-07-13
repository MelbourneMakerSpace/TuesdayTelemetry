/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <WiFi.h>
#include <WiFiMulti.h>
#include <ArduinoHttpClient.h>

WiFiMulti WiFiMulti;


char ssid[] = "Makerspace";
char pass[] = "Makerspace1";
int port = 443;

int status = WL_IDLE_STATUS;

char serverAddress[] = "https://webhook.site/b0826dd3-e372-489d-b6b8-de1785eedde3";  // server address
WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);

void setup()
{
    Serial.begin(9600);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}


void loop()
{
Serial.println("making POST request");
  String postData = "{\"millis\":" + String(millis()) + "\"}";

  client.beginRequest();
  client.post("/");
  client.sendHeader("Content-Type", "application/x-www-form-urlencoded");
  client.sendHeader("Content-Length", postData.length());
  client.sendHeader("X-Custom-Header", "custom-header-value");
  client.beginBody();
  client.print(postData);
  client.endRequest();

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println("Wait five seconds");
  delay(5000);
}
