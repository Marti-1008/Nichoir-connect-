#include <WiFi.h>

const char* ssid = "esp32_test";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);

  // Mettre explicitement le mode AP
  WiFi.mode(WIFI_MODE_AP);

  // Créer le point d'accès avec SSID et mot de passe
  bool ok = WiFi.softAP(ssid, password);

  if(ok) {
    Serial.println("AP lancé avec succès !");
  } else {
    Serial.println("Erreur lors du lancement de l'AP !");
  }

  Serial.print("IP AP : ");
  Serial.println(WiFi.softAPIP());
}

void loop() {}
