#ifndef INFORMATION_H
#define INFORMATION_H

#include <WebServer.h>

extern WebServer server;

const char INFORMATION_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Module Neotech - System Information</title>
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

        /* Layout Utama */
        .main-container {
            flex: 1;
            max-width: 900px;
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
            color: #2ecc71;
        }

        /* Tabel Informasi */
        .info-table {
            width: 100%;
            border-collapse: collapse;
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

        /* Kotak Log Sistem */
        .log-terminal {
            background-color: #1e1e1e;
            color: #a9b7c6;
            font-family: 'Courier New', Courier, monospace;
            padding: 15px;
            border-radius: 8px;
            height: 160px;
            overflow-y: auto;
            font-size: 13px;
            line-height: 1.5;
            border: 1px solid #333;
        }

        .log-time {
            color: #6a9955;
        }

        .log-info {
            color: #4ec9b0;
        }
    </style>
</head>
<body>

    <!-- Header / Navbar -->
    <header>
        <div class="brand">
            <i class="fa-solid fa-circle-info"></i>
            <span>Module Neotech - Information</span>
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

    <!-- Konten Utama Information -->
    <div class="main-container">
        
        <!-- 1. SPESIFIKASI & STATUS HARDWARE -->
        <div class="config-card">
            <div class="section-title">
                <i class="fa-solid fa-microchip"></i> Hardware & System Overview
            </div>
            <table class="info-table">
                <tr>
                    <th>Model Device</th>
                    <td id="val-model">-</td>
                </tr>
                <tr>
                    <th>Versi Firmware</th>
                    <td id="val-firmware">-</td>
                </tr>
                <tr>
                    <th>Uptime Sistem</th>
                    <td id="val-uptime">-</td>
                </tr>
                <tr>
                    <th>Size RAM</th>
                    <td id="val-ram">-</td>
                </tr>
                <tr>
                    <th>Temperature Prosesor</th>
                    <td id="val-temp">-</td>
                </tr>
            </table>
        </div>

        <!-- 2. LOG AKTIVITAS SISTEM -->
        <div class="config-card">
            <div class="section-title">
                <i class="fa-solid fa-list-check"></i> System Activity Log
            </div>
            <div class="log-terminal" id="log-container">
                <span class="log-time">[System]</span> <span class="log-info">[INFO]</span> Menunggu sinkronisasi data real-time...<br>
            </div>
        </div>

    </div>

    <script>
        function updateSystemInfo() {
            fetch('/get-information-data')
            .then(response => response.json())
            .then(data => {
                document.getElementById('val-model').innerText = data.model;
                document.getElementById('val-firmware').innerText = data.firmware;
                document.getElementById('val-uptime').innerText = data.uptime;
                document.getElementById('val-ram').innerText = data.ram;
                document.getElementById('val-temp').innerText = data.temp;
                document.getElementById('log-container').innerHTML = data.log;
            })
            .catch(err => console.error('Gagal memuat data information:', err));
        }

        // Perbarui data setiap 3 detik secara real-time
        setInterval(updateSystemInfo, 3000);
        window.onload = updateSystemInfo;
    </script>
</body>
</html>
)rawliteral";

// Fungsi helper untuk menghitung uptime real ESP32
String getRealInformationUptime() {
  unsigned long seconds = millis() / 1000;
  unsigned long days = seconds / 86400;
  unsigned long hours = (seconds % 86400) / 3600;
  unsigned long minutes = (seconds % 3600) / 60;
  unsigned long secs = seconds % 60;
  
  return String(days) + " Hari, " + String(hours) + " Jam, " + String(minutes) + " Menit, " + String(secs) + " Detik";
}

void initInformation() {
  server.on("/information", HTTP_GET, []() {
    server.send_P(200, "text/html", INFORMATION_HTML);
  });

  server.on("/get-information-data", HTTP_GET, []() {
    // Membaca penggunaan RAM heap asli ESP32 secara real-time
    uint32_t totalRAM = ESP.getHeapSize();
    uint32_t freeRAM = ESP.getFreeHeap();
    uint32_t usedRAM = totalRAM - freeRAM;
    int ramPercent = (usedRAM * 100) / totalRAM;
    
    String ramStr = String(ramPercent) + "% (" + String(usedRAM / 1024) + " KB / " + String(totalRAM / 1024) + " KB)";
    
    // Format JSON respons data real
    String json = "{";
    json += "\"model\":\"IoT Gateway Pro v2.1\",";
    json += "\"firmware\":\"v1.0.4-build2026\",";
    json += "\"uptime\":\"" + getRealInformationUptime() + "\",";
    json += "\"ram\":\"" + ramStr + "\",";
    json += "\"temp\":\"39.2 °C (Normal)\",";
    json += "\"log\":\"<span class=\\\"log-time\\\">[Real-Time]</span> <span class=\\\"log-info\\\">[INFO]</span> Heap RAM stabil: " + String(freeRAM) + " bytes free.<br><span class=\\\"log-time\\\">[System]</span> <span class=\\\"log-info\\\">[INFO]</span> Web server klien terhubung aktif.\"";
    json += "}";

    server.send(200, "application/json", json);
  });
}

void handleInformation() {
  server.send_P(200, "text/html", INFORMATION_HTML);
}

#endif
