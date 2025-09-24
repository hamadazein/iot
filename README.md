# 🚀 Arduino IoT Projects Collection

![Arduino](https://img.shields.io/badge/Arduino-Uno-blue?logo=arduino&logoColor=white)
![Language](https://img.shields.io/badge/Language-C++-blue?logo=cplusplus&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)
![Status](https://img.shields.io/badge/Status-Complete-success?style=flat-square)

Koleksi proyek Arduino IoT untuk pembelajaran dan pengembangan. Setiap proyek dilengkapi dengan kode, diagram wiring, dan simulasi online.

## 📁 Daftar Proyek

| No. | Nama Proyek | Tingkat Kesulitan | Komponen Utama | Link Simulasi |
|-----|-------------|-------------------|-----------------|---------------|
| 1 | [Turn On The Light](./01-turn-on-light/) | 🟢 Mudah | LED, Resistor | [Wokwi](https://wokwi.com/) |
| 2 | [Proximity Sensor](./02-proximity-sensor/) | 🟡 Sedang | HC-SR04, Arduino | [Wokwi](https://wokwi.com/projects/418680848311396353) |
| 3 | [Buzzer Sound](./03-buzzer-sound/) | 🟢 Mudah | Buzzer, Arduino | [Wokwi](https://wokwi.com/) |
| 4 | [RGB Light](./04-rgb-light/) | 🟡 Sedang | RGB LED, Resistor | [Wokwi](https://wokwi.com/) |
| 5 | [LED Button](./05-led-button/) | 🟢 Mudah | LED, Push Button | [Wokwi](https://wokwi.com/) |
| 6 | [Servo Motor](./06-servo/) | 🟡 Sedang | Servo SG90, Arduino | [Wokwi](https://wokwi.com/) |
| 7 | [Smart Parking System](./07-smart-parking/) | 🔴 Sulit | HC-SR04, Servo, LCD, LED | [Wokwi](https://wokwi.com/) |

## 🛠️ Persyaratan

### Hardware
- Arduino Uno R3
- Breadboard
- Kabel Jumper Male-Male dan Male-Female
- Resistor (220Ω, 1kΩ, 10kΩ)
- LED berbagai warna
- Push Button
- Servo Motor SG90
- Sensor Ultrasonik HC-SR04
- Buzzer
- RGB LED
- LCD 16x2 dengan I2C Module

### Software
- [Arduino IDE](https://www.arduino.cc/en/software) v2.0+
- Library yang diperlukan:
  - `Servo.h` (Built-in)
  - `Wire.h` (Built-in)
  - `LiquidCrystal_I2C.h` ([Download](https://github.com/johnrickman/LiquidCrystal_I2C))

## 🚀 Cara Memulai

1. **Clone repository**
   ```bash
   git clone https://github.com/hamadazein/arduino-iot-projects.git
   cd arduino-iot-projects
   ```

2. **Install Arduino IDE**
   - Download dari [arduino.cc](https://www.arduino.cc/en/software)
   - Install driver untuk Arduino Uno

3. **Pilih proyek yang ingin dicoba**
   - Masuk ke folder proyek
   - Buka file `.ino` di Arduino IDE
   - Upload ke Arduino Uno

4. **Simulasi Online (Opsional)**
   - Gunakan link simulasi Wokwi untuk setiap proyek
   - Tidak perlu hardware fisik

## 📚 Struktur Proyek

```
arduino-iot-projects/
├── 01-turn-on-light/
│   ├── README.md
│   ├── lights.ino
│   └── wiring-diagram.png
├── 02-proximity-sensor/
│   ├── README.md
│   ├── sensor.ino
│   └── sensor.png
├── ... (proyek lainnya)
└── README.md (file ini)
```

## 🎯 Tujuan Pembelajaran

- **Dasar Arduino**: Pin I/O, digitalWrite(), digitalRead()
- **Sensor**: Membaca data dari sensor ultrasonik
- **Aktuator**: Mengontrol servo, LED, buzzer
- **Komunikasi**: Serial Monitor, I2C
- **Logika**: Conditional statements, loops
- **Proyek Lanjutan**: Integrasi multiple komponen

## 🤝 Kontribusi

1. Fork repository ini
2. Buat branch baru (`git checkout -b feature/proyek-baru`)
3. Commit perubahan (`git commit -am 'Tambah proyek baru'`)
4. Push ke branch (`git push origin feature/proyek-baru`)
5. Buat Pull Request

## 📝 Lisensi

Proyek ini menggunakan lisensi MIT - lihat file [LICENSE](LICENSE) untuk detail.

## 👨‍💻 Penulis

**Hamada Zein**
- GitHub: [@hamadazein](https://github.com/hamadazein)
- Website: [hamadazein.github.io/arduino-iot-projects](https://hamadazein.github.io/arduino-iot-projects)

## 🙏 Acknowledgments

- [Arduino Community](https://www.arduino.cc/en/Main/Community)
- [Wokwi Simulator](https://wokwi.com/)
- [Fritzing](https://fritzing.org/) untuk diagram wiring

---

⭐ **Jangan lupa beri star jika proyek ini membantu!** ⭐