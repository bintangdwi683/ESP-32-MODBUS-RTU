#ifndef PROJECT_H
#define PROJECT_H

#include <WebServer.h>
#include <EEPROM.h>

#define EEPROM_SIZE 1024

// Struktur data Project yang disimpan di EEPROM
struct ProjectConfig {
  char nama[32];
  char compile[32];
  char ukuran[32];
};

extern WebServer server;

// Fungsi helper untuk baca/tulis EEPROM khusus Project (diselaraskan ke alamat 150)
void saveProjectConfigToEEPROM(const ProjectConfig &cfg) {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.put(150, cfg);
  EEPROM.commit();
  EEPROM.end();
}

void readProjectConfigFromEEPROM(ProjectConfig &cfg) {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(150, cfg);
  EEPROM.end();
}

const char PROJECT_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Project Detail Form Module</title>
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
            color: #136fac;
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
            background: linear-gradient(135deg, #3498db, #136fac);
            color: white;
            padding: 8px 16px;
            border-radius: 8px;
            text-decoration: none;
            font-size: 14px;
            font-weight: 600;
            display: flex;
            align-items: center;
            gap: 6px;
            box-shadow: 0 4px 10px rgba(19, 111, 172, 0.3);
            transition: transform 0.2s ease, background 0.2s ease;
        }
        .btn-back-top:hover {
            transform: translateY(-2px);
            background: linear-gradient(135deg, #2980b9, #0f588c);
        }
        .main-container {
            flex: 1;
            display: flex;
            justify-content: center;
            align-items: center;
            padding: 30px 20px;
        }
        .form-card {
            background: white;
            width: 100%;
            max-width: 600px;
            padding: 40px;
            border-radius: 16px;
            box-shadow: 0 10px 25px rgba(0, 0, 0, 0.08);
        }
        .form-title {
            font-size: 24px;
            font-weight: bold;
            color: #2c3e50;
            margin-bottom: 25px;
            text-align: center;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
        }
        .form-title i {
            color: #136fac;
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
            font-size: 16px;
            box-sizing: border-box;
            transition: border-color 0.2s;
            background-color: #f9f9f9;
        }
        .form-group input:focus {
            outline: none;
            border-color: #136fac;
            box-shadow: 0 0 5px rgba(19, 111, 172, 0.3);
        }
        .form-actions {
            margin-top: 30px;
            text-align: center;
        }
        .btn-download {
            background: linear-gradient(135deg, #2ecc71, #27ae60);
            color: white;
            border: none;
            width: 100%;
            padding: 14px;
            font-size: 18px;
            font-weight: bold;
            border-radius: 8px;
            cursor: pointer;
            box-shadow: 0 6px 15px rgba(39, 174, 96, 0.3);
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
            transition: transform 0.2s ease, box-shadow 0.2s ease;
        }
        .btn-download:hover {
            transform: translateY(-2px);
            box-shadow: 0 8px 20px rgba(39, 174, 96, 0.4);
        }
    </style>
</head>
<body>

    <header>
        <div class="brand">
            <i class="fa-solid fa-microchip"></i>
            <span>Module Neotech - Project Detail</span>
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
        <div class="form-card">
            <div class="form-title">
                <i class="fa-solid fa-folder-open"></i> Project Detail
            </div>
            
            <form>
                <div class="form-group">
                    <label for="nama-project">Name Project :</label>
                    <input type="text" id="nama-project" readonly>
                </div>

                <div class="form-group">
                    <label for="waktu-compile">Time Compile :</label>
                    <input type="text" id="waktu-compile" readonly>
                </div>

                <div class="form-group">
                    <label for="ukuran-project">Size Project :</label>
                    <input type="text" id="ukuran-project" readonly>
                </div>

                <div class="form-actions">
                    <button type="button" class="btn-download" onclick="alert('Read From Module')">
                        <i class="fa-solid fa-circle-check"></i> Sinkron To Module
                    </button>
                </div>
            </form>
        </div>
    </div>

    <script>
        window.onload = function() {
            fetch('/get-project-info')
            .then(response => response.json())
            .then(data => {
                document.getElementById('nama-project').value = data.nama;
                document.getElementById('waktu-compile').value = data.compile;
                document.getElementById('ukuran-project').value = data.ukuran;
            })
            .catch(err => console.error('Gagal memuat info project:', err));
        };
    </script>
</body>
</html>
)rawliteral";

void initProject() {
  EEPROM.begin(EEPROM_SIZE);
  ProjectConfig cfg;
  EEPROM.get(150, cfg);

  // Jika EEPROM di alamat tersebut masih kosong, isi dengan data default sistem
  if (cfg.nama[0] == (char)0xFF || cfg.nama[0] == '\0') {
    strlcpy(cfg.nama, "Smart Gateway Node v1", sizeof(cfg.nama));
    strlcpy(cfg.compile, __DATE__ " " __TIME__, sizeof(cfg.compile));
    
    // Menghitung ukuran sketch secara dinamis
    String realSize = String(ESP.getSketchSize() / 1024.0, 1) + " KB (" + String((ESP.getSketchSize() * 100) / ESP.getFreeSketchSpace()) + "% Flash Used)";
    strlcpy(cfg.ukuran, realSize.c_str(), sizeof(cfg.ukuran));

    EEPROM.put(150, cfg);
    EEPROM.commit();
  }
  EEPROM.end();

  server.on("/project", HTTP_GET, []() {
    server.send_P(200, "text/html", PROJECT_HTML);
  });

  server.on("/get-project-info", HTTP_GET, []() {
    ProjectConfig cfg;
    readProjectConfigFromEEPROM(cfg);

    // Format JSON murni dari pembacaan EEPROM & Sistem ESP32
    String json = "{";
    json += "\"nama\":\"" + String(cfg.nama) + "\",";
    json += "\"compile\":\"" + String(cfg.compile) + "\",";
    json += "\"ukuran\":\"" + String(cfg.ukuran) + "\"";
    json += "}";
    
    server.send(200, "application/json", json);
  });
}

void handleProject() {
  server.send_P(200, "text/html", PROJECT_HTML);
}

#endif
