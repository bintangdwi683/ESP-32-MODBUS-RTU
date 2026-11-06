#ifndef DASHBOARD_H
#define DASHBOARD_H

const char DASHBOARD_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Configurasi Module Neotech v1.2</title>
    <!-- Menggunakan ikon dari FontAwesome untuk simbol tombol -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    
    <style>
        /* Pengaturan Dasar Halaman */
        body {
            margin: 0;
            padding: 0;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background-color: #f4f6f9;
            color: #333;
            display: flex;
            flex-direction: column;
            height: 100vh;
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
            color: #136fac;
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

        /* Kontainer Utama Menu */
        .main-container {
            flex: 1;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            gap: 30px;
            padding: 20px;
        }

        /* Baris Tombol */
        .menu-row {
            display: flex;
            justify-content: center;
            gap: 30px;
            width: 100%;
            max-width: 900px;
        }

        /* Kartu Tombol Utama */
        .menu-card {
            text-decoration: none;
            width: 260px;
            height: 160px;
            border-radius: 16px;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            color: white;
            box-shadow: 0 8px 20px rgba(0, 0, 0, 0.15);
            transition: transform 0.2s ease, box-shadow 0.2s ease;
            position: relative;
            overflow: hidden;
        }

        /* Efek saat mouse menyentuh tombol */
        .menu-card:hover {
            transform: translateY(-5px);
            box-shadow: 0 12px 25px rgba(0, 0, 0, 0.25);
        }

        /* Efek kilau transparan di atas tombol */
        .menu-card::before {
            content: '';
            position: absolute;
            top: 0;
            left: 0;
            width: 100%;
            height: 50%;
            background: linear-gradient(to bottom, rgba(255,255,255,0.25), rgba(255,255,255,0));
            border-top-left-radius: 16px;
            border-top-right-radius: 16px;
        }

        .menu-icon {
            font-size: 50px;
            margin-bottom: 12px;
            z-index: 1;
        }

        .menu-text {
            font-size: 20px;
            font-weight: bold;
            letter-spacing: 1px;
            z-index: 1;
        }

        /* Variasi Warna Tombol */
        .btn-project {
            background: linear-gradient(135deg, #3498db, #1b6ca8);
        }

        .btn-network {
            background: linear-gradient(135deg, #1abc9c, #16a085);
        }

        .btn-setting {
            background: linear-gradient(135deg, #f39c12, #d35400);
        }

        .btn-information {
            background: linear-gradient(135deg, #2ecc71, #27ae60);
        }

        .btn-cloud {
            background: linear-gradient(135deg, #9b59b6, #8e44ad);
        }

        .btn-back {
            background: linear-gradient(135deg, #e74c3c, #c0392b);
        }
    </style>
</head>
<body>

    <!-- Header / Navbar -->
    <header>
        <div class="brand">
            <i class="fa-solid fa-microchip"></i>
            <span>IOT MODULE GATEWAY NEOTECH</span>
        </div>
        <div class="status-koneksi">
            <span class="dot-hijau"></span> Connected
        </div>
    </header>

    <!-- Konten Menu Dashboard -->
    <div class="main-container">
        
        <!-- Baris Tombol 1 -->
        <div class="menu-row">
            <a href="/project" class="menu-card btn-project">
                <i class="fa-solid fa-folder-plus menu-icon"></i>
                <span class="menu-text">PROJECT</span>
            </a>
            
            <a href="/network" class="menu-card btn-network">
                <i class="fa-solid fa-network-wired menu-icon"></i>
                <span class="menu-text">NETWORK</span>
            </a>
            
            <a href="/setting" class="menu-card btn-setting">
                <i class="fa-solid fa-gears menu-icon"></i>
                <span class="menu-text">SETTING</span>
            </a>
        </div>

        <!-- Baris Tombol 2 -->
        <div class="menu-row">
            <a href="/information" class="menu-card btn-information">
                <i class="fa-solid fa-circle-info menu-icon"></i>
                <span class="menu-text">INFORMATION</span>
            </a>
            
            <a href="/cloud" class="menu-card btn-cloud">
                <i class="fa-solid fa-cloud-arrow-up menu-icon"></i>
                <span class="menu-text">CLOUD</span>
            </a>
            
            <a href="/" class="menu-card btn-back">
                <i class="fa-solid fa-arrow-rotate-left menu-icon"></i>
                <span class="menu-text">BACK</span>
            </a>
        </div>

    </div>

</body>
</html>
)rawliteral";

// Fungsi tambahan untuk mencegah error di file utama (.ino)
void initDashboard() {
  // Inisialisasi tambahan jika diperlukan
}

void runDashboard() {
  // Logika loop dashboard jika diperlukan
}

#endif
