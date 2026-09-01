#pragma once

#include <Arduino.h>

struct WiFiCredential {
  const char *macAddress;
  const char *password;
};

constexpr WiFiCredential WIFI_CREDENTIALS[] = {
    {"20:43:A8:E6:01:C8", "aas7jxan"},
    {"08:3A:F2:7C:D4:64", "4sppki9v"},
    {"20:43:A8:E5:6D:20", "wbn8py4f"},
    {"20:43:A8:E6:19:60", "8927ef2t"},
    {"C8:C9:A3:C5:EE:34", "s5uhkqfx"},
    {"D0:EF:76:48:2A:5C", "dyecjwdb"},
    {"70:B8:F6:71:DD:F4", "zyn3w9sy"},
    {"C8:C9:A3:C7:85:54", "njiarrp7"},
    {"20:43:A8:E6:D5:EC", "5cfmtiz4"},
    {"20:43:A8:E6:1F:9C", "zeyadwuh"},
    {"20:43:A8:E5:A4:D0", "jfj2y462"},
    {"14:33:5C:03:E4:40", "xzc6a627"},
    {"94:B5:55:27:25:A8", "jfg7ndq5"},
    {"20:43:A8:E6:43:B0", "y6exyb42"},
    {"20:43:A8:E6:16:98", "bqrx96pk"},
    {"14:33:5C:65:4B:E0", "qhczt444"},
    {"20:43:A8:E5:7F:E8", "uqg65upe"},
    {"40:22:D8:03:E7:F0", "k49jqdx8"},
    {"D0:EF:76:48:4E:40", "xf4bmf9i"},
    {"24:6F:28:0B:8A:EC", "n6iv56z2"},
    {"D0:EF:76:48:69:F4", "fy5r87uv"},
};

constexpr size_t WIFI_CREDENTIAL_COUNT =
    sizeof(WIFI_CREDENTIALS) / sizeof(WIFI_CREDENTIALS[0]);