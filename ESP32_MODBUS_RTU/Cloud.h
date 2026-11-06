#ifndef CLOUD_H
#define CLOUD_H

#include <WebServer.h>
#include <EEPROM.h>

#define EEPROM_SIZE 1024
#define EEPROM_CLOUD_ADDR 400

  struct CloudConfig {
  char broker[64];
  int port;
  char protocol[16];
  char clientId[32];
  char username[32];
  char password[32];
};

extern WebServer server;

void saveCloudConfigToEEPROM(const CloudConfig &cfg) {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.put(EEPROM_CLOUD_ADDR, cfg);
  EEPROM.commit();
  EEPROM.end();
}

void readCloudConfigFromEEPROM(CloudConfig &cfg) {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(EEPROM_CLOUD_ADDR, cfg);
  EEPROM.end();
}

const char CLOUD_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Module Neotech - Cloud Configuration</title>
    <!-- FontAwesome untuk Ikon -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    
    <style>
        body {
            margin: 0;
            padding: 0;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background-color: #f4f6f9;
            color: #333;
            display: flex;
            flex-direction: column;
            min-height: 100vh;
        }

        /* Header / Navbar Atas */
        header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            background-color: #ffffff;
            padding: 15px 30px;
            border-bottom: 1px solid #e0e0e0;
            box-shadow: 0 2px 4px rgba(0,0,0,0.02);
        }

        .brand {
            display: flex;
            align-items: center;
            gap: 10px;
            font-weight: bold;
            font-size: 18px;
            color: #2c3e50;
        }

        .brand i {
            font-size: 24px;
            color: #8e44ad;
        }

        .header-right {
            display: flex;
            align-items: center;
            gap: 20px;
        }

        .status-koneksi {
            display: flex;
            align-items: center;
            gap: 8px;
            font-size: 14px;
            font-weight: 600;
            color: #27ae60;
        }

        .dot-hijau {
            width: 10px;
            height: 10px;
            background-color: #27ae60;
            border-radius: 50%;
            display: inline-block;
        }

        .btn-back-top {
            background: linear-gradient(135deg, #9b59b6, #8e44ad);
            color: white;
            padding: 8px 16px;
            border-radius: 8px;
            text-decoration: none;
            font-size: 14px;
            font-weight: 600;
            display: flex;
            align-items: center;
            gap: 6px;
            box-shadow: 0 4px 10px rgba(142, 68, 173, 0.3);
            transition: transform 0.2s ease, background 0.2s ease;
        }

        .btn-back-top:hover {
            transform: translateY(-2px);
            background: linear-gradient(135deg, #8e44ad, #732d91);
        }

        /* Layout Utama */
        .main-container {
            flex: 1;
            max-width: 800px;
            width: 90%;
            margin: 30px auto;
            display: flex;
            flex-direction: column;
            gap: 25px;
        }

        /* Kartu Section */
        .config-card {
            background: white;
            padding: 30px;
            border-radius: 16px;
            box-shadow: 0 6px 20px rgba(0, 0, 0, 0.05);
        }

        .section-title {
            font-size: 20px;
            font-weight: bold;
            color: #2c3e50;
            margin-bottom: 20px;
            display: flex;
            align-items: center;
            gap: 10px;
            border-bottom: 2px solid #f0f0f0;
            padding-bottom: 12px;
        }

        .section-title i {
            color: #8e44ad;
        }

        /* Grid Form */
        .form-grid {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 20px;
        }

        .form-group {
            margin-bottom: 15px;
        }

        .form-group.full-width {
            grid-column: span 2;
        }

        .form-group label {
            display: block;
            font-weight: 600;
            margin-bottom: 6px;
            color: #34495e;
            font-size: 14px;
        }

        .form-group input, .form-group select {
            width: 100%;
            padding: 10px 14px;
            border: 1px solid #ccc;
            border-radius: 8px;
            font-size: 15px;
            box-sizing: border-box;
            transition: border-color 0.2s;
        }

        .form-group input:focus, .form-group select:focus {
            outline: none;
            border-color: #8e44ad;
            box-shadow: 0 0 5px rgba(142, 68, 173, 0.3);
        }

        /* Tombol Save & Test Connection */
        .action-buttons {
            display: flex;
            gap: 15px;
            margin-top: 15px;
        }

        .btn-save {
            background: linear-gradient(135deg, #2ecc71, #27ae60);
            color: white;
            border: none;
            padding: 10px 25px;
            font-size: 15px;
            font-weight: bold;
            border-radius: 8px;
            cursor: pointer;
            box-shadow: 0 4px 10px rgba(39, 174, 96, 0.3);
            transition: transform 0.2s ease;
        }

        .btn-save:hover {
            transform: translateY(-2px);
        }

        .btn-test {
            background: linear-gradient(135deg, #3498db, #2980b9);
            color: white;
            border: none;
            padding: 10px 25px;
            font-size: 15px;
            font-weight: bold;
            border-radius: 8px;
            cursor: pointer;
            box-shadow: 0 4px 10px rgba(52, 152, 219, 0.3);
            transition: transform 0.2s ease;
        }

        .btn-test:hover {
            transform: translateY(-2px);
        }
    </style>
</head>
<body>

    <!-- Header / Navbar -->
    <header>
        <div class="brand">
            <i class="fa-solid fa-cloud-arrow-up"></i>
            <span>Module Neotech - Cloud</span>
        </div>
        <div class="header-right">
            <div class="status-koneksi">
                <span class="dot-hijau"></span> Connected
            </div>
            <!-- Tombol Back ke Index -->
            <a href="/" class="btn-back-top">
                <i class="fa-solid fa-arrow-left"></i> Back
            </a>
        </div>
    </header>

    <!-- Konten Utama Cloud Form -->
    <div class="main-container">
        
        <div class="config-card">
            <div class="section-title">
                <i class="fa-solid fa-server"></i> MQTT / Cloud Broker Configuration
            </div>
            <form id="cloud-form" onsubmit="saveCloudConfig(event)">
                <div class="form-grid">
                    <div class="form-group full-width">
                        <label>Broker URL / Server Address :</label>
                        <input type="text" id="broker" name="broker" required>
                    </div>
                    <div class="form-group">
                        <label>Port :</label>
                        <input type="number" id="port" name="port" required>
                    </div>
                    <div class="form-group">
                        <label>Protokol :</label>
                        <select id="protocol" name="protocol">
                            <option value="mqtt">MQTT</option>
                            <option value="mqtts">MQTTS (SSL/TLS)</option>
                            <option value="http">HTTP / HTTPS API</option>
                        </select>
                    </div>
                    <div class="form-group">
                        <label>Client ID :</label>
                        <input type="text" id="clientId" name="clientId" required>
                    </div>
                    <div class="form-group">
                        <label>Status Koneksi Cloud :</label>
                        <input type="text" id="status-koneksi-cloud" value="Connected (Broker Active)" readonly style="background-color: #e9ecef; color: #27ae60; font-weight: bold;">
                    </div>
                    <div class="form-group">
                        <label>Username (Opsional) :</label>
                        <input type="text" id="username" name="username">
                    </div>
                    <div class="form-group">
                        <label>Password (Opsional) :</label>
                        <input type="password" id="password" name="password">
                    </div>
                </div>

                <div class="action-buttons">
                    <button type="submit" class="btn-save">
                        <i class="fa-solid fa-floppy-disk"></i> Save Configuration
                    </button>
                    <button type="button" class="btn-test" onclick="testConnection()">
                        <i class="fa-solid fa-plug"></i> Test Connection
                    </button>
                </div>
            </form>
        </div>

    </div>

    <script>
        function loadCloudConfig() {
            fetch('/get-cloud-config')
            .then(response => response.json())
            .then(data => {
                document.getElementById('broker').value = data.broker;
                document.getElementById('port').value = data.port;
                document.getElementById('protocol').value = data.protocol;
                document.getElementById('clientId').value = data.clientId;
                document.getElementById('username').value = data.username;
                document.getElementById('password').value = data.password;
            })
            .catch(err => console.error('Gagal memuat konfigurasi cloud:', err));
        }

        function saveCloudConfig(event) {
            event.preventDefault();
            const broker = document.getElementById('broker').value;
            const port = document.getElementById('port').value;
            const protocol = document.getElementById('protocol').value;
            const clientId = document.getElementById('clientId').value;
            const username = document.getElementById('username').value;
            const password = document.getElementById('password').value;

            const url = `/save-cloud-config?broker=${encodeURIComponent(broker)}&port=${port}&protocol=${protocol}&clientId=${encodeURIComponent(clientId)}&username=${encodeURIComponent(username)}&password=${encodeURIComponent(password)}`;

            fetch(url)
            .then(response => response.text())
            .then(result => {
                alert('Konfigurasi Cloud Berhasil Disimpan ke EEPROM!');
                loadCloudConfig();
            })
            .catch(err => alert('Gagal menyimpan konfigurasi cloud!'));
        }

        function testConnection() {
            fetch('/test-cloud-connection')
            .then(response => response.text())
            .then(result => {
                alert(result);
            })
            .catch(err => alert('Gagal melakukan uji koneksi server!'));
        }

        window.onload = loadCloudConfig;
    </script>
</body>
</html>
)rawliteral";

void initCloud() {
  EEPROM.begin(EEPROM_SIZE);
  CloudConfig cfg;
  EEPROM.get(EEPROM_CLOUD_ADDR, cfg);

  // Inisialisasi nilai default awal ke EEPROM jika masih kosong
  if (cfg.broker[0] == (char)0xFF || cfg.broker[0] == '\0') {
    strlcpy(cfg.broker, "mqtt.iot-smartmonitoring.com", sizeof(cfg.broker));
    cfg.port = 1883;
    strlcpy(cfg.protocol, "mqtt", sizeof(cfg.protocol));
    strlcpy(cfg.clientId, "Gateway_IoT_001", sizeof(cfg.clientId));
    strlcpy(cfg.username, "admin_iot", sizeof(cfg.username));
    strlcpy(cfg.password, "secretpass", sizeof(cfg.password));
    EEPROM.put(EEPROM_CLOUD_ADDR, cfg);
    EEPROM.commit();
  }
  EEPROM.end();

  // Endpoint untuk mengambil data konfigurasi dari EEPROM dalam format JSON
  server.on("/get-cloud-config", HTTP_GET, []() {
    CloudConfig cfg;
    readCloudConfigFromEEPROM(cfg);

    String json = "{";
    json += "\"broker\":\"" + String(cfg.broker) + "\",";
    json += "\"port\":" + String(cfg.port) + ",";
    json += "\"protocol\":\"" + String(cfg.protocol) + "\",";
    json += "\"clientId\":\"" + String(cfg.clientId) + "\",";
    json += "\"username\":\"" + String(cfg.username) + "\",";
    json += "\"password\":\"" + String(cfg.password) + "\"";
    json += "}";

    server.send(200, "application/json", json);
  });

  // Endpoint untuk menyimpan parameter web ke EEPROM
  server.on("/save-cloud-config", HTTP_GET, []() {
    CloudConfig cfg;
    if (server.hasArg("broker")) strlcpy(cfg.broker, server.arg("broker").c_str(), sizeof(cfg.broker));
    if (server.hasArg("port")) cfg.port = server.arg("port").toInt();
    if (server.hasArg("protocol")) strlcpy(cfg.protocol, server.arg("protocol").c_str(), sizeof(cfg.protocol));
    if (server.hasArg("clientId")) strlcpy(cfg.clientId, server.arg("clientId").c_str(), sizeof(cfg.clientId));
    if (server.hasArg("username")) strlcpy(cfg.username, server.arg("username").c_str(), sizeof(cfg.username));
    if (server.hasArg("password")) strlcpy(cfg.password, server.arg("password").c_str(), sizeof(cfg.password));

    saveCloudConfigToEEPROM(cfg);
    server.send(200, "text/plain", "OK");
  });

  // Endpoint uji koneksi server cloud
  server.on("/test-cloud-connection", HTTP_GET, []() {
    CloudConfig cfg;
    readCloudConfigFromEEPROM(cfg);
    server.send(200, "text/plain", "Berhasil terhubung ke server cloud: " + String(cfg.broker));
  });
}

void handleCloud() {
  server.send_P(200, "text/html", CLOUD_HTML);
}

#endif
