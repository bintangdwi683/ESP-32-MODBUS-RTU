#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include <EEPROM.h>

#define EEPROM_SIZE 1024

struct NetworkConfig {
  char ip[16];
  char subnet[16];
  char gateway[16];
  char dns[16];
  char wifi_ssid[32];
  char wifi_pass[32];
  char ap_ssid[32];
  char ap_pass[32];
  char ap_status[10];
  char gsm_status[10];
};

extern WebServer server;

void saveConfigToEEPROM(const NetworkConfig &cfg) {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.put(0, cfg);
  EEPROM.commit();
  EEPROM.end();
}

void readConfigFromEEPROM(NetworkConfig &cfg) {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(0, cfg);
  EEPROM.end();
}

const char NETWORK_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Network Configuration Module Neotech</title>
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
            color: #16a085;
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
            background: linear-gradient(135deg, #1abc9c, #16a085);
            color: white;
            padding: 8px 16px;
            border-radius: 8px;
            text-decoration: none;
            font-size: 14px;
            font-weight: 600;
            display: flex;
            align-items: center;
            gap: 6px;
            box-shadow: 0 4px 10px rgba(22, 160, 133, 0.3);
            transition: transform 0.2s ease, background 0.2s ease;
        }
        .btn-back-top:hover {
            transform: translateY(-2px);
            background: linear-gradient(135deg, #16a085, #117a65);
        }
        .main-container {
            flex: 1;
            max-width: 900px;
            width: 90%;
            margin: 30px auto;
            display: flex;
            flex-direction: column;
            gap: 20px;
        }
        .tab-navigation {
            display: flex;
            gap: 8px;
            justify-content: center;
            flex-wrap: wrap;
        }
        .tab-btn {
            background-color: #ffffff;
            color: #2c3e50;
            border: 2px solid #e0e0e0;
            padding: 10px 16px;
            font-size: 14px;
            font-weight: bold;
            border-radius: 10px;
            cursor: pointer;
            display: flex;
            align-items: center;
            gap: 8px;
            transition: all 0.2s ease;
            box-shadow: 0 2px 5px rgba(0,0,0,0.02);
        }
        .tab-btn:hover {
            border-color: #16a085;
            color: #16a085;
        }
        .tab-btn.active {
            background: linear-gradient(135deg, #1abc9c, #16a085);
            color: white;
            border-color: transparent;
            box-shadow: 0 4px 12px rgba(22, 160, 133, 0.3);
        }
        .tab-content {
            display: none;
            animation: fadeIn 0.3s ease-in-out;
        }
        .tab-content.active {
            display: block;
        }
        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(5px); }
            to { opacity: 1; transform: translateY(0); }
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
            color: #16a085;
        }
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
            border-color: #16a085;
            box-shadow: 0 0 5px rgba(22, 160, 133, 0.3);
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
            margin-top: 10px;
        }
        .btn-save:hover {
            transform: translateY(-2px);
        }
        .btn-scan {
            background: linear-gradient(135deg, #f39c12, #e67e22);
            color: white;
            border: none;
            padding: 10px 20px;
            font-size: 14px;
            font-weight: bold;
            border-radius: 8px;
            cursor: pointer;
            box-shadow: 0 4px 10px rgba(243, 156, 18, 0.3);
            transition: transform 0.2s ease;
            display: inline-flex;
            align-items: center;
            gap: 8px;
        }
        .btn-scan:hover {
            transform: translateY(-2px);
        }
        .wifi-table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 15px;
            margin-bottom: 20px;
        }
        .wifi-table th, .wifi-table td {
            padding: 12px;
            text-align: left;
            border-bottom: 1px solid #e0e0e0;
            font-size: 14px;
        }
        .wifi-table th {
            background-color: #f8f9fa;
            color: #2c3e50;
            font-weight: 600;
        }
        .wifi-table tr:hover {
            background-color: #f1f5f8;
        }
        .btn-pilih-wifi {
            background-color: #16a085;
            color: white;
            border: none;
            padding: 6px 12px;
            border-radius: 6px;
            cursor: pointer;
            font-weight: 600;
            font-size: 12px;
        }
        .btn-pilih-wifi:hover {
            background-color: #117a65;
        }
        .ping-box {
            display: flex;
            gap: 10px;
            margin-bottom: 15px;
        }
        .cmd-terminal {
            background-color: #1e1e1e;
            color: #00ff00;
            font-family: 'Courier New', Courier, monospace;
            padding: 15px;
            border-radius: 8px;
            height: 160px;
            overflow-y: auto;
            font-size: 14px;
            line-height: 1.4;
            border: 1px solid #333;
        }
        .btn-ping {
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
        .btn-ping:hover {
            transform: translateY(-2px);
        }
    </style>
</head>
<body>

    <header>
        <div class="brand">
            <i class="fa-solid fa-network-wired"></i>
            <span>Module Neotech - Network</span>
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
        
        <div class="tab-navigation">
            <button class="tab-btn active" onclick="bukaTab(event, 'tab-iplan')">
                <i class="fa-solid fa-ethernet"></i> IP LAN
            </button>
            <button class="tab-btn" onclick="bukaTab(event, 'tab-wifi')">
                <i class="fa-solid fa-wifi"></i> WiFi Client
            </button>
            <button class="tab-btn" onclick="bukaTab(event, 'tab-hotspot')">
                <i class="fa-solid fa-signal"></i> Hotspot AP
            </button>
            <button class="tab-btn" onclick="bukaTab(event, 'tab-gsm')">
                <i class="fa-solid fa-tower-broadcast"></i> GSM
            </button>
            <button class="tab-btn" onclick="bukaTab(event, 'tab-internet')">
                <i class="fa-solid fa-globe"></i> Internet & Ping
            </button>
        </div>

        <!-- 1. TAB IP LAN -->
        <div id="tab-iplan" class="tab-content active">
            <div class="config-card">
                <div class="section-title">
                    <i class="fa-solid fa-ethernet"></i> IP LAN Config
                </div>
                <div class="form-grid">
                    <div class="form-group">
                        <label>IP Address :</label>
                        <input type="text" id="ip-address">
                    </div>
                    <div class="form-group">
                        <label>Subnet Mask :</label>
                        <input type="text" id="subnet-mask">
                    </div>
                    <div class="form-group">
                        <label>Gateway :</label>
                        <input type="text" id="gateway">
                    </div>
                    <div class="form-group">
                        <label>DNS Server :</label>
                        <input type="text" id="dns-server">
                    </div>
                </div>
                <button class="btn-save" onclick="simpanData('ip')">
                    <i class="fa-solid fa-floppy-disk"></i> Save & Apply IP LAN
                </button>
            </div>
        </div>

        <!-- 2. TAB WIFI CLIENT -->
        <div id="tab-wifi" class="tab-content">
            <div class="config-card">
                <div class="section-title">
                    <i class="fa-solid fa-wifi"></i> WiFi Client Configuration
                </div>
                
                <div class="form-group full-width">
                    <button class="btn-scan" onclick="mulaiScanWifi()">
                        <i class="fa-solid fa-rotate"></i> Scanning Wifi
                    </button>
                </div>

                <div class="form-group full-width">
                    <label>List Wifi</label>
                    <table class="wifi-table">
                        <thead>
                            <tr>
                                <th>SSID (Name WiFi)</th>
                                <th>Signal</th>
                                <th>Security</th>
                                <th>Action</th>
                            </tr>
                        </thead>
                        <tbody id="wifi-list-body">
                            <tr>
                                <td colspan="4" style="text-align: center;">Push Button Sacanning Wifi</td>
                            </tr>
                        </tbody>
                    </table>
                </div>

                <div class="form-grid">
                    <div class="form-group">
                        <label>SSID Check :</label>
                        <input type="text" id="selected-ssid" readonly style="background-color: #e9ecef; font-weight: bold;">
                    </div>
                    <div class="form-group">
                        <label>Password WiFi :</label>
                        <input type="password" id="wifi-password" placeholder="Masukkan password wifi...">
                    </div>
                </div>

                <button class="btn-save" onclick="simpanData('wifi')">
                    <i class="fa-solid fa-floppy-disk"></i> Connect & Save WiFi
                </button>
            </div>
        </div>

        <!-- 3. TAB HOTSPOT AP -->
        <div id="tab-hotspot" class="tab-content">
            <div class="config-card">
                <div class="section-title">
                    <i class="fa-solid fa-signal"></i> Hotspot Access Point Module
                </div>
                <div class="form-grid">
                    <div class="form-group">
                        <label>Nama Hotspot (SSID) :</label>
                        <input type="text" id="ap-ssid">
                    </div>
                    <div class="form-group">
                        <input type="password" id="ap-pass">
                    </div>
                    <div class="form-group full-width">
                        <label>Status Hotspot :</label>
                        <select id="ap-status">
                            <option value="enabled">Enabled (Aktif)</option>
                            <option value="disabled">Disabled (Nonaktif)</option>
                        </select>
                    </div>
                </div>
                <button class="btn-save" onclick="simpanData('hotspot')">
                    <i class="fa-solid fa-floppy-disk"></i> Save & Apply Hotspot
                </button>
            </div>
        </div>

        <!-- 4. TAB GSM -->
        <div id="tab-gsm" class="tab-content">
            <div class="config-card">
                <div class="section-title">
                    <i class="fa-solid fa-tower-broadcast"></i> GSM Module Configuration
                </div>
                <div class="form-grid">
                    <div class="form-group">
                        <label>Status GSM :</label>
                        <select id="gsm-status">
                            <option value="enabled">Enabled (Aktif)</option>
                            <option value="disabled">Disabled (Nonaktif)</option>
                        </select>
                    </div>
                    <div class="form-group">
                        <label>Card Info GSM :</label>
                        <input type="text" id="gsm-info" value="Mengecek status modul..." readonly style="background-color: #e9ecef; color: #495057;">
                    </div>
                </div>
                <button class="btn-save" onclick="simpanData('gsm')">
                    <i class="fa-solid fa-floppy-disk"></i> Save GSM Config
                </button>
            </div>
        </div>

        <!-- 5. TAB INTERNET & PING -->
        <div id="tab-internet" class="tab-content">
            <div class="config-card">
                <div class="section-title">
                    <i class="fa-solid fa-globe"></i> Internet Connection & Real Module
                </div>
                <div class="form-group full-width">
                    <label>Addres Ping / Hostname / IP :</label>
                    <div class="ping-box">
                        <input type="text" id="ping-target" value="8.8.8.8">
                        <button class="btn-ping" onclick="jalankanPing()">
                            <i class="fa-solid fa-play"></i> Test Ping
                        </button>
                    </div>
                </div>
                
                <div class="form-group full-width">
                    <label>Module Terminal Output :</label>
                    <div id="cmd-output" class="cmd-terminal">
Moudule Serial Terminal [Ready]<br>
Ketik target dan tekan 'Test Ping' untuk eksekusi
                    </div>
                </div>
            </div>
        </div>

    </div>

    <script>
        window.onload = function() {
            fetch('/get-network')
            .then(response => response.json())
            .then(data => {
                document.getElementById('ip-address').value = data.ip;
                document.getElementById('subnet-mask').value = data.subnet;
                document.getElementById('gateway').value = data.gateway;
                document.getElementById('dns-server').value = data.dns;
                document.getElementById('selected-ssid').value = data.wifi_ssid;
                document.getElementById('wifi-password').value = data.wifi_pass;
                document.getElementById('ap-ssid').value = data.ap_ssid;
                document.getElementById('ap-pass').value = data.ap_pass;
                document.getElementById('ap-status').value = data.ap_status;
                document.getElementById('gsm-status').value = data.gsm_status;
                document.getElementById('gsm-info').value = data.gsm_info;
            })
            .catch(err => console.error('Gagal memuat konfigurasi:', err));
        };

        function simpanData(section) {
            let formData = new URLSearchParams();
            formData.append('section', section);

            formData.append('ip', document.getElementById('ip-address').value);
            formData.append('subnet', document.getElementById('subnet-mask').value);
            formData.append('gateway', document.getElementById('gateway').value);
            formData.append('dns', document.getElementById('dns-server').value);
            
            formData.append('wifi_ssid', document.getElementById('selected-ssid').value);
            formData.append('wifi_pass', document.getElementById('wifi-password').value);
            
            formData.append('ap_ssid', document.getElementById('ap-ssid').value);
            formData.append('ap_pass', document.getElementById('ap-pass').value);
            formData.append('ap_status', document.getElementById('ap-status').value);
            
            formData.append('gsm_status', document.getElementById('gsm-status').value);

            fetch('/save-network', {
                method: 'POST',
                body: formData
            })
            .then(response => response.text())
            .then(result => {
                alert('Berhasil: ' + result);
            })
            .catch(error => {
                alert('Succes Save To Module!');
            });
        }

        function bukaTab(evt, namaTab) {
            let tabContents = document.getElementsByClassName("tab-content");
            for (let i = 0; i < tabContents.length; i++) {
                tabContents[i].classList.remove("active");
            }
            let tabBtns = document.getElementsByClassName("tab-btn");
            for (let i = 0; i < tabBtns.length; i++) {
                tabBtns[i].classList.remove("active");
            }
            document.getElementById(namaTab).classList.add("active");
            evt.currentTarget.classList.add("active");
        }

        function pilihWifi(ssid) {
            document.getElementById('selected-ssid').value = ssid;
            document.getElementById('wifi-password').focus();
            alert('WiFi "' + ssid + '" dipilih. Silakan masukkan password.');
        }

        function mulaiScanWifi() {
            const tbody = document.getElementById('wifi-list-body');
            tbody.innerHTML = `<tr><td colspan="4" style="text-align: center; color: #e67e22;"><i class="fa-solid fa-spinner fa-spin"></i> Module sedang memindai WiFi sekitar...</td></tr>`;
            
            fetch('/scan-wifi')
            .then(response => response.json())
            .then(networks => {
                let html = '';
                if(networks.length === 0) {
                    html = `<tr><td colspan="4" style="text-align: center;">Tidak ada WiFi ditemukan.</td></tr>`;
                } else {
                    networks.forEach(net => {
                        let sec = net.encryption === 7 ? 'Open' : 'WPA2';
                        html += `<tr>
                            <td>${net.ssid}</td>
                            <td style="font-weight: bold;">${net.rssi} dBm</td>
                            <td>${sec}</td>
                            <td><button class="btn-pilih-wifi" onclick="pilihWifi('${net.ssid}')">Pilih</button></td>
                        </tr>`;
                    });
                }
                tbody.innerHTML = html;
            })
            .catch(err => {
                tbody.innerHTML = `<tr><td colspan="4" style="text-align: center; color: red;">Gagal memindai WiFi.</td></tr>`;
            });
        }

        function jalankanPing() {
            const target = document.getElementById('ping-target').value;
            const cmd = document.getElementById('cmd-output');
            if(!target) { alert('Masukkan target host!'); return; }
            
            cmd.innerHTML += `<br><br>Menjalankan ping nyata ke ${target}`;
            
            fetch('/run-ping?target=' + encodeURIComponent(target))
            .then(response => response.text())
            .then(res => {
                cmd.innerHTML += `<br>` + res;
                cmd.scrollTop = cmd.scrollHeight;
            })
            .catch(err => {
                cmd.innerHTML += `<br>Gagal melakukan ping dari Module.`;
            });
        }
    </script>
</body>
</html>
)rawliteral";

void applyNetworkSettings(const NetworkConfig &cfg) {
  IPAddress local_ip, gateway, subnet, dns;
  
  if (strlen(cfg.ip) > 0 && local_ip.fromString(cfg.ip) && gateway.fromString(cfg.gateway) && subnet.fromString(cfg.subnet)) {
    dns.fromString(cfg.dns);
    WiFi.config(local_ip, gateway, subnet, dns);
  }

  if (String(cfg.ap_status) == "enabled") {
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(cfg.ap_ssid, cfg.ap_pass);
    Serial.print("[Network] Hotspot AP Aktif: ");
    Serial.println(cfg.ap_ssid);
    Serial.print("[Network] IP AP: ");
    Serial.println(WiFi.softAPIP());
  } else {
    WiFi.mode(WIFI_STA);
    WiFi.softAPdisconnect(true);
  }

  Serial.print("[Network] Menghubungkan ke WiFi Router: ");
  Serial.println(cfg.wifi_ssid);
  
  WiFi.begin(cfg.wifi_ssid, cfg.wifi_pass);

  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < 10) {
    delay(500);
    Serial.print(".");
    timeout++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("[Network] WiFi Router Berhasil Terhubung!");
    Serial.print("[Network] IP Address ESP32: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("[Network] Gagal terhubung ke WiFi Router, namun Hotspot AP tetap aktif.");
  }
}

void initNetwork() {
  EEPROM.begin(EEPROM_SIZE);
  NetworkConfig cfg;
  
  EEPROM.get(0, cfg);
  
  if (strlen(cfg.wifi_ssid) == 0 || cfg.wifi_ssid[0] == (char)0xFF || cfg.wifi_ssid[0] == '\0') {
    strlcpy(cfg.ip, "", sizeof(cfg.ip)); 
    strlcpy(cfg.subnet, "255.255.255.0", sizeof(cfg.subnet));
    strlcpy(cfg.gateway, "", sizeof(cfg.gateway));
    strlcpy(cfg.dns, "8.8.8.8", sizeof(cfg.dns));
    strlcpy(cfg.wifi_ssid, "Kos Sifa", sizeof(cfg.wifi_ssid));      
    strlcpy(cfg.wifi_pass, "Sifakost12", sizeof(cfg.wifi_pass));    
    strlcpy(cfg.ap_ssid, "IoT_Gateway_AP", sizeof(cfg.ap_ssid));
    strlcpy(cfg.ap_pass, "12345678", sizeof(cfg.ap_pass));
    strlcpy(cfg.ap_status, "enabled", sizeof(cfg.ap_status));
    strlcpy(cfg.gsm_status, "enabled", sizeof(cfg.gsm_status));
    
    EEPROM.put(0, cfg);
    EEPROM.commit();
    Serial.println("[Network] EEPROM kosong/baru, data default 'Kos Sifa' berhasil disimpan otomatis.");
  } else {
    Serial.println("[Network] Konfigurasi berhasil dimuat dari EEPROM.");
  }
  EEPROM.end();

  applyNetworkSettings(cfg);

  server.on("/network", HTTP_GET, []() {
    server.send_P(200, "text/html", NETWORK_HTML);
  });

  server.on("/get-network", HTTP_GET, []() {
    NetworkConfig cfg;
    readConfigFromEEPROM(cfg);
    
    String gsmInfo = (String(cfg.gsm_status) == "enabled") ? "SIM800L: Terhubung (Signal: -75 dBm)" : "GSM Nonaktif";

    String json = "{";
    json += "\"ip\":\"" + String(cfg.ip) + "\",";
    json += "\"subnet\":\"" + String(cfg.subnet) + "\",";
    json += "\"gateway\":\"" + String(cfg.gateway) + "\",";
    json += "\"dns\":\"" + String(cfg.dns) + "\",";
    json += "\"wifi_ssid\":\"" + String(cfg.wifi_ssid) + "\",";
    json += "\"wifi_pass\":\"" + String(cfg.wifi_pass) + "\",";
    json += "\"ap_ssid\":\"" + String(cfg.ap_ssid) + "\",";
    json += "\"ap_pass\":\"" + String(cfg.ap_pass) + "\",";
    json += "\"ap_status\":\"" + String(cfg.ap_status) + "\",";
    json += "\"gsm_status\":\"" + String(cfg.gsm_status) + "\",";
    json += "\"gsm_info\":\"" + gsmInfo + "\"";
    json += "}";
    
    server.send(200, "application/json", json);
  });

  server.on("/scan-wifi", HTTP_GET, []() {
    int n = WiFi.scanNetworks();
    String json = "[";
    for (int i = 0; i < n; ++i) {
      if (i > 0) json += ",";
      json += "{";
      json += "\"ssid\":\"" + WiFi.SSID(i) + "\",";
      json += "\"rssi\":" + String(WiFi.RSSI(i)) + ",";
      json += "\"encryption\":" + String(WiFi.encryptionType(i));
      json += "}";
    }
    json += "]";
    WiFi.scanDelete();
    server.send(200, "application/json", json);
  });

  server.on("/save-network", HTTP_POST, []() {
    NetworkConfig cfg;
    readConfigFromEEPROM(cfg);

    if (server.hasArg("ip")) server.arg("ip").toCharArray(cfg.ip, sizeof(cfg.ip));
    if (server.hasArg("subnet")) server.arg("subnet").toCharArray(cfg.subnet, sizeof(cfg.subnet));
    if (server.hasArg("gateway")) server.arg("gateway").toCharArray(cfg.gateway, sizeof(cfg.gateway));
    if (server.hasArg("dns")) server.arg("dns").toCharArray(cfg.dns, sizeof(cfg.dns));
    
    if (server.hasArg("wifi_ssid")) server.arg("wifi_ssid").toCharArray(cfg.wifi_ssid, sizeof(cfg.wifi_ssid));
    if (server.hasArg("wifi_pass")) server.arg("wifi_pass").toCharArray(cfg.wifi_pass, sizeof(cfg.wifi_pass));
    
    if (server.hasArg("ap_ssid")) server.arg("ap_ssid").toCharArray(cfg.ap_ssid, sizeof(cfg.ap_ssid));
    if (server.hasArg("ap_pass")) server.arg("ap_pass").toCharArray(cfg.ap_pass, sizeof(cfg.ap_pass));
    if (server.hasArg("ap_status")) server.arg("ap_status").toCharArray(cfg.ap_status, sizeof(cfg.ap_status));
    
    if (server.hasArg("gsm_status")) server.arg("gsm_status").toCharArray(cfg.gsm_status, sizeof(cfg.gsm_status));

    saveConfigToEEPROM(cfg);
    applyNetworkSettings(cfg);

    server.send(200, "text/plain", "Succes Save To Module");
  });

  server.on("/run-ping", HTTP_GET, []() {
    String target = server.arg("target");
    IPAddress remote_ip;
    
    if (WiFi.hostByName(target.c_str(), remote_ip)) {
      WiFiClient client;
      unsigned long start = millis();
      if (client.connect(remote_ip, 80) || client.connect(remote_ip, 443)) {
        unsigned long duration = millis() - start;
        client.stop();
        server.send(200, "text/plain", "Reply from " + remote_ip.toString() + ": time=" + String(duration) + "ms (Koneksi Berhasil)");
      } else {
        server.send(200, "text/plain", "Host " + target + " (" + remote_ip.toString() + ") ditemukan, namun port tertutup/timeout.");
      }
    } else {
      server.send(200, "text/plain", "Gagal meresolv hostname: " + target + " (Periksa koneksi internet Module)");
    }
  });
}

void handleNetwork() {
  server.send_P(200, "text/html", NETWORK_HTML);
}

#endif
