#include <WiFi.h>

#include "wifi_credentials.h"

constexpr char WIFI_SSID[] = "UNIVALI IoT";

constexpr unsigned long WIFI_CONNECT_TIMEOUT_MS = 20000;

// Retorna nullptr quando o MAC nao esta cadastrado na tabela.
const char *findPasswordForMac(const String &macAddress) {
  for (size_t credentialIndex = 0; credentialIndex < WIFI_CREDENTIAL_COUNT;
       ++credentialIndex) {
    if (macAddress == WIFI_CREDENTIALS[credentialIndex].macAddress) {
      return WIFI_CREDENTIALS[credentialIndex].password;
    }
  }

  return nullptr;
}

bool connectToWiFi() {
  const String macAddress = WiFi.macAddress();
  const char *wifiPassword = findPasswordForMac(macAddress);
  if (wifiPassword == nullptr) {
    Serial.printf("MAC %s nao cadastrado. Adicione-o em wifi_credentials.h.\n",
                  macAddress.c_str());
    return false;
  }

  Serial.printf("Conectando a %s", WIFI_SSID);
  WiFi.begin(WIFI_SSID, wifiPassword);

  const unsigned long startedAt = millis();
  while (WiFi.status() != WL_CONNECTED &&
         millis() - startedAt < WIFI_CONNECT_TIMEOUT_MS) {
    delay(500);
    Serial.print('.');
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.printf("\nFalha ao conectar ao Wi-Fi. Status: %d\n", WiFi.status());
    return false;
  }

  Serial.printf("\nConectado. IP: %s\n", WiFi.localIP().toString().c_str());
  return true;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  Serial.printf("MAC da placa: %s\n", WiFi.macAddress().c_str());
  connectToWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  delay(5000);
}