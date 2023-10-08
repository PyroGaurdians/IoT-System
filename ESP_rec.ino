#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5);  //D2, D1
/*WIFI CONNECTION */
const char *ssid = "iTi@Student"; // replace with your wifi ssid and wpa2 key
const char *pass = "STU@iTi$is";
/*THINGSPEAK SERVER FOR TEST*/
String apiKey = "6UF9MTQ937M3RFLZ"; // Enter your Write API key from ThingSpeak
const char* server = "api.thingspeak.com";
WiFiClient client;

int sensor_data;
void setup()
{
  /* INIT SERIAL AND SOFT SERIAL CONNECTION */
Serial.begin(115200);
mySerial.begin(115200);
delay(10);
  /*CONNECTION TO WIFI*/
Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
}
void loop()
{
//int sensor_data = analogRead(A0);
if (isnan(sensor_data))
  {
  Serial.println("Failed to read from MQ-2 sensor!");
  return;
  }
if(mySerial.available())
  {
    sensor_data= mySerial.parseInt();
    Serial.write((char)sensor_data);
    mySerial.print("K"); // SENDING BACK ACK
  }
 
 /*CONNECTING TO THINGS*/
if (client.connect(server, 80)) // "184.106.153.149" or api.thingspeak.com
{
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(sensor_data);
    postStr += "r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.print("Gas Level: ");
    Serial.println(sensor_data);
    Serial.println("Data Send to Thingspeak");
}
delay(500);
client.stop();
Serial.println("Waiting...");
// thingspeak needs minimum 15 sec delay between updates.
delay(15000);
sensor_data=0;
}