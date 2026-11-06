#ifndef SETTING_H
#define SETTING_H

#include <WebServer.h>
#include <EEPROM.h>

#define EEPROM_SIZE 1024

// Struktur data Setting / System Config yang disimpan di EEPROM
struct SystemConfig {
  char model[32];
  char firmware[16];
  char location[32];
};

extern WebServer server;

// Fungsi helper EEPROM untuk Setting (menggunakan offset alamat 600)
void saveSystemConfigToEEPROM(const SystemConfig &cfg) {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.put(600, cfg);
  EEPROM.commit();
  EEPROM.end();
}

void readSystemConfigFromEEPROM(SystemConfig &cfg) {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(600, cfg);
  EEPROM.end();
}

const char SETTING_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>System Setting Module Neotech</title>
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
            color: #2ecc71;
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
            background: linear-gradient(135deg, #2ecc71, #27ae60);
            color: white;
            padding: 8px 16px;
            border-radius: 8px;
            text-decoration: none;
            font-size: 14px;
            font-weight: 600;
            display: flex;
            align-items: center;
            gap: 6px;
            box-shadow: 0 4px 10px rgba(46, 204, 113, 0.3);
            transition: transform 0.2s ease, background 0.2s ease;
        }
        .btn-back-top:hover {
            transform: translateY(-2px);
            background: linear-gradient(135deg, #27ae60, #1e8449);
        }
        .main-container {
            flex: 1;
            max-width: 900px;
            width: 90%;
            margin: 30px auto;
            display: flex;
            flex-direction: column;
            gap: 25px;
        }
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
            color: #2ecc71;
        }
        .form-group {
            margin-bottom: 20px;
        }
        .form-group label {
            display: block;
            font-weight: 600;
            margin-bottom: 8px;
            color: #34495e;
        }
        .form-group input {
            width: 100%;
            padding: 12px 15px;
            border: 1px solid #ccc;
            border-radius: 8px;
            font-size: 15px;
            box-sizing: border-box;
            background-color: #f9f9f9;
        }
        .form-group input:focus {
            outline: none;
            border-color: #2ecc71;
            box-shadow: 0 0 5px rgba(46, 204, 113, 0.3);
        }
        .info-table {
            width: 100%;
            border-collapse: collapse;
            margin-bottom: 20px;
        }
        .info-table tr {
            border-bottom: 1px solid #f0f0f0;
        }
        .info-table th, .info-table td {
            padding: 12px 15px;
            text-align: left;
            font-size: 15px;
        }
        .info-table th {
            color: #7f8c8d;
            width: 35%;
            font-weight: 600;
        }
        .info-table td {
            color: #2c3e50;
            font-weight: 500;
        }
        .btn-save {
            background: linear-gradient(135deg, #2ecc71, #27ae60);
            color: white;
            border: none;
            width: 100%;
            padding: 14px;
            font-size: 16px;
            font-weight: bold;
            border-radius: 8px;
            cursor: pointer;
            box-shadow: 0 4px 10px rgba(46, 204, 113, 0.3);
            transition: transform 0.2s ease;
        }
        .btn-save:hover {
            transform: translateY(-2px);
        }
    </style>
</head>
<body>

    <header>
        <div class="brand">
            <i class="fa-solid fa-gear"></i>
            <span>Module Neotech - Setting</span>
        </div>
        <div class="header-right">
            <div class="status-koneksi">
                <span class="dot-hijau"></span> Connected
            </div>
            <a href="/" class="btn-back-top">
                <i class="fa-solid fa-arrow-left"></i> Back
            </a>
        </div>
    </header>

    <div class="main-container">
        
        <!-- 1. FORM PENGATURAN EEPROM -->
        <div class="config-card">
            <div class="section-title">
                <i class="fa-solid fa-sliders"></i> Config Module Neotech
            </div>
            <form id="setting-form" onsubmit="saveSetting(event)">
                <div class="form-group">
                    <label for="model">Model Perangkat:</label>
                    <input type="text" id="model" name="model" required>
                </div>
                <div class="form-group">
                    <label for="firmware">Versi Firmware:</label>
                    <input type="text" id="firmware" name="firmware" required>
                </div>
                <div class="form-group">
                    <label for="location">Lokasi Instalasi:</label>
                    <input type="text" id="location" name="location" required>
                </div>
                <button type="submit" class="btn-save">
                    <i class="fa-solid fa-floppy-disk"></i> Save To Module
                </button>
            </form>
        </div>

        <!-- 2. STATUS HARDWARE & RAM REAL ESP32 -->
        <div class="config-card">
            <div class="section-title">
                <i class="fa-solid fa-microchip"></i> Status Hardware & Memori Real
            </div>
            <table class="info-table">
                <tr>
                    <th>Uptime Sistem</th>
                    <td id="val-uptime">-</td>
                </tr>
                <tr>
                    <th>Penggunaan RAM (Heap)</th>
                    <td id="val-ram">-</td>
                </tr>
                <tr>
                    <th>Total Memori Flash</th>
                    <td id="val-flash">-</td>
                </tr>
            </table>
        </div>

    </div>

    <script>
        function loadSetting() {
            fetch('/get-setting-info')
            .then(response => response.json())
            .then(data => {
                // Jangan timpa input jika elemen tersebut sedang diketik (aktif) oleh user
                if (document.activeElement !== document.getElementById('model')) {
                    document.getElementById('model').value = data.model;
                }
                if (document.activeElement !== document.getElementById('firmware')) {
                    document.getElementById('firmware').value = data.firmware;
                }
                if (document.activeElement !== document.getElementById('location')) {
                    document.getElementById('location').value = data.location;
                }

                // Update data hardware secara berkala tanpa mengganggu input form
                document.getElementById('val-uptime').innerText = data.uptime;
                document.getElementById('val-ram').innerText = data.ram;
                document.getElementById('val-flash').innerText = data.flash;
            })
            .catch(err => console.error('Gagal memuat setting:', err));
        }

        function saveSetting(event) {
            event.preventDefault();
            const model = document.getElementById('model').value;
            const firmware = document.getElementById('firmware').value;
            const location = document.getElementById('location').value;

            fetch(`/save-setting?model=${encodeURIComponent(model)}&firmware=${encodeURIComponent(firmware)}&location=${encodeURIComponent(location)}`)
            .then(response => response.text())
            .then(result => {
                alert('Succes Save To Module');
                loadSetting();
            })
            .catch(err => alert('Gagal menyimpan konfigurasi!'));
        }

        window.onload = loadSetting;
        setInterval(loadSetting, 5000);
    </script>
</body>
</html>
)rawliteral";

String getSettingUptime() {
  unsigned long seconds = millis() / 1000;
  unsigned long days = seconds / 86400;
  unsigned long hours = (seconds % 86400) / 3600;
  unsigned long minutes = (seconds % 3600) / 60;
  return String(days) + " Hari, " + String(hours) + " Jam, " + String(minutes) + " Menit";
}

void initSetting() {
  EEPROM.begin(EEPROM_SIZE);
  SystemConfig cfg;
  EEPROM.get(600, cfg);

  // Jika EEPROM masih kosong (belum pernah disimpan), isi data awal
  if (cfg.model[0] == (char)0xFF || cfg.model[0] == '\0') {
    strlcpy(cfg.model, "IoT Gateway Pro v2.1", sizeof(cfg.model));
    strlcpy(cfg.firmware, "v1.0.4-build2026", sizeof(cfg.firmware));
    strlcpy(cfg.location, "Ruang Kontrol Utama", sizeof(cfg.location));
    EEPROM.put(600, cfg);
    EEPROM.commit();
  }
  EEPROM.end();

  server.on("/setting", HTTP_GET, []() {
    server.send_P(200, "text/html", SETTING_HTML);
  });

  server.on("/get-setting-info", HTTP_GET, []() {
    SystemConfig cfg;
    readSystemConfigFromEEPROM(cfg);

    // Data real hardware ESP32
    uint32_t totalRAM = ESP.getHeapSize();
    uint32_t freeRAM = ESP.getFreeHeap();
    uint32_t usedRAM = totalRAM - freeRAM;
    int ramPercent = (usedRAM * 100) / totalRAM;
    String ramStr = String(ramPercent) + "% (" + String(usedRAM / 1024) + " KB / " + String(totalRAM / 1024) + " KB)";
    
    String flashStr = String(ESP.getFlashChipSize() / (1024 * 1024)) + " MB";

    // Format JSON dari EEPROM & Real Hardware
    String json = "{";
    json += "\"model\":\"" + String(cfg.model) + "\",";
    json += "\"firmware\":\"" + String(cfg.firmware) + "\",";
    json += "\"location\":\"" + String(cfg.location) + "\",";
    json += "\"uptime\":\"" + getSettingUptime() + "\",";
    json += "\"ram\":\"" + ramStr + "\",";
    json += "\"flash\":\"" + flashStr + "\"";
    json += "}";

    server.send(200, "application/json", json);
  });

  server.on("/save-setting", HTTP_GET, []() {
    SystemConfig cfg;
    if (server.hasArg("model")) strlcpy(cfg.model, server.arg("model").c_str(), sizeof(cfg.model));
    if (server.hasArg("firmware")) strlcpy(cfg.firmware, server.arg("firmware").c_str(), sizeof(cfg.firmware));
    if (server.hasArg("location")) strlcpy(cfg.location, server.arg("location").c_str(), sizeof(cfg.location));

    saveSystemConfigToEEPROM(cfg);
    server.send(200, "text/plain", "OK");
  });
}

void handleSetting() {
  server.send_P(200, "text/html", SETTING_HTML);
}

#endif
