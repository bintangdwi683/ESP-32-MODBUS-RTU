#include <WiFi.h>
#include <WebServer.h>

#include "Dashboard.h"
#include "Network.h"
#include "Setting.h"
#include "Information.h"
#include "Cloud.h"
#include "Project.h" 

WebServer server(80);

// Konfigurasi LED Blink
const int LED_PIN = 35;
unsigned long previousMillis = 0;
const long interval = 500; 
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("[Booting.....");

  // Inisialisasi Pin LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  initNetwork(); 
  initSetting();
  initInformation();
  initDashboard();
  initCloud();
  initProject(); 

  server.on("/", []() {
    server.send_P(200, "text/html", DASHBOARD_HTML);
  });
  
  server.on("/network", handleNetwork);
  server.on("/setting", handleSetting);
  server.on("/information", handleInformation);
  server.on("/cloud", handleCloud);
  server.on("/project", handleProject); 

  server.begin();
  Serial.println("MODULE NEOTECH RUNNING....");
}

void loop() {
  server.handleClient();
  runDashboard();

  // Cek apakah WiFi terhubung
  if (WiFi.status() == WL_CONNECTED) {
    unsigned long currentMillis = millis();
    
    // Logika millis untuk kedip setiap 500 ms[cite: 1]
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
      // Membalik status LED
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      
      digitalWrite(LED_PIN, ledState);
    }
  } else {
    // Jika WiFi terputus, matikan LED (opsional)
    digitalWrite(LED_PIN, LOW);
    ledState = LOW;
  }
}
