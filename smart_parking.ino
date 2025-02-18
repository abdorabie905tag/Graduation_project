#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <uart.h>

// Update these with values suitable for your network.

const char* ssid = "OPPO A1k";
const char* password = "123456789Y";
const char* mqtt_server = "mqtt-dashboard.com"; //ping test.mosquitto.org 91.121.93.94

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
   if (((char)payload[0] == '1')) {
    //action of my
    Serial.write('z');

  } 
  else if (((char)payload[0] == '2')) {
          Serial.write('b');
  }
  else {
     
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("Abdo", "mqtt is connected");
      // ... and resubscribe
       client.subscribe("ahmed");

      client.subscribe("Abo");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
       // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  //uart.setup(0,9600,8, uart.PARITY_NONE,uart.STOPBITS_1,0);
 


}

void loop() {
  if(!client.connected()) reconnect();
  client.loop();
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  // wait for one minute before checking the condition again
  if (currentMillis - previousMillis >= 1000) {
    if (Serial.available()) {
      


      //String message = Serial.readStringUntil('\n');
      char message = Serial.read();
      //message.trim(); // remove leading and trailing whitespace
      //Serial.println(message);
      if (message == '1' || message == '2' || message == '3' || message == '4' || message == '0') {
        // do something for all reed switches
        Serial.println(message);
      snprintf (msg, 75, "%ld",message);
      client.publish("Abdo", msg);
      }  if (message == 'c') {
        // do something for reed c
        Serial.println("yes2");
      snprintf (msg, 75, "%ld",8);
      client.publish("Abdo", msg);
      }  if (message == 'o') {
        // do something for reed o
        Serial.println("yes1");
      snprintf (msg, 75, "%ld",7);
      client.publish("Abdo", msg);
      } else {
        Serial.println("Received unknown command");
      }
     }
    previousMillis = currentMillis;
  }
}

