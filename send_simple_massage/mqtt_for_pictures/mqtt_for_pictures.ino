#include "M5TimerCAM.h"
#include "base64.h"
#include <PubSubClient.h>
#include <WiFi.h>


const char* ssid     = "electroProjectWifi";
const char* password = "B1MesureEnv";
IPAddress server(192,168,2,35); // IP du broker MQTT

WiFiClient espClient;           // client réseau WiFi
PubSubClient client(espClient); // client MQTT


void setup() {
  setSocketTimeout (90000) // maintiens la connexion même en mode deepsleep
  subscribe ("Raspberry/couleur")
  Serial.begin(115200);
  TimerCAM.begin();
  TimerCAM.Camera.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
    // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(server,1883);
  String esp32 = "ESP32Client-";
  esp32 += String(random(0xffff), HEX);
  client.connect(esp32.c_str());
}

void loop() {
  if (TimerCAM.Camera.get()) {
        // encode jpeg in Base64
    String b64 = base64::encode(
      TimerCAM.Camera.fb->buf,
      TimerCAM.Camera.fb->len
    );

        // print result
    Serial.println("----- BASE64 START -----");
    Serial.println(b64); // rajouter le data:image/jpeg;base64, pour que ça puisse le lire
    Serial.println("----- BASE64 END -----");
        // regarder serial write Serial.write(TimerCAM.Camera.fb->buf, TimerCAM.Camera.fb->len);
    client.publish("esp32/MineurBenNanna/image",b64);
    TimerCAM.Camera.free();
    delay(6000);
    }
    
}
