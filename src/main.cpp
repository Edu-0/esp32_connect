#include <WiFi.h>

#include "wifi_credentials.h"

constexpr char WIFI_SSID[] = "UNIVALI IoT";

constexpr unsigned long WIFI_CONNECT_TIMEOUT_MS = 20000;

const char *findPasswordForMac(const String &macAddress) {
  for (size_t credentialIndex = 0; credentialIndex < WIFI_CREDENTIAL_COUNT;
       ++credentialIndex) {
    if (macAddress == WIFI_CREDENTIALS[credentialIndex].macAddress) {
      return WIFI_CREDENTIALS[credentialIndex].password;
    }
  }

  return nullptr;
}

void showAvailableNetworks() {
  Serial.println("Procurando redes Wi-Fi...");
  const int networkCount = WiFi.scanNetworks();

  if (networkCount == 0) {
    Serial.println("Nenhuma rede encontrada.");
    return;
  }

  for (int networkIndex = 0; networkIndex < networkCount; ++networkIndex) {
    Serial.printf("%d: %s (%d dBm, %s)\n", networkIndex + 1,
                  WiFi.SSID(networkIndex).c_str(), WiFi.RSSI(networkIndex),
                  WiFi.encryptionType(networkIndex) == WIFI_AUTH_OPEN ? "aberta"
                                                                         : "protegida");
  }
}

bool connectToWiFi() {
  const char *wifiPassword = findPasswordForMac(WiFi.macAddress());
  if (wifiPassword == nullptr) {
    Serial.println("MAC nao cadastrado; conexao cancelada.");
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
  showAvailableNetworks();
  connectToWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  delay(5000);
}