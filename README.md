# Controlling ESP32 with Mobile Phone using Dabble App
Activity: Controlling ESP32 with mobile phone using Dabble App 

Board: ESP32 Dev Module

# WHAT THIS DOES

The ESP32 connects to a smartphone over Bluetooth (BLE) using the Dabble app's Terminal module. Messages sent from the phone are printed on the Serial Monitor, and the ESP32 sends a reply back to the app.

# WHY THE CODE IS DIFFERENT FROM THE ORIGINAL LAB INSTRUCTIONS

- The lab instructions say to install the "Dabble" library by STEMpedia, but that library does not actually work on the ESP32 — it fails to compile with the error avr/interrupt.h: No such file or directory. This happens because "Dabble" includes a file meant only for Arduino Uno/Nano boards, and the Arduino IDE tries to compile that file even when the target board is an ESP32, where it simply doesn't exist. To fix this, I switched to DabbleESP32, which is the ESP32-specific version of the same library from the same publisher.

- That still wasn't enough, though. The newest version of DabbleESP32 (1.6.1) also failed to compile, this time with errors like 'ledcAttachChannel' was not declared and a String to std::string conversion error. This is because version 1.6.1 was built for a newer ESP32 board package than the one installed on my machine (2.0.17). So I downgraded DabbleESP32 to version 1.5.1 in the Library Manager, which matches the installed board package and compiles cleanly.

- Lastly, the original code itself mixes two things that don't work together: it uses BluetoothSerial (Classic Bluetooth) alongside Dabble (which actually runs over BLE, not Classic Bluetooth). Things like ESP_BT.setPin(), Dabble.begin(ESP_BT), and ESP_BT.hasClient() are all Classic Bluetooth methods that don't exist or don't apply in DabbleESP32's BLE-based API, and Terminal.readString() isn't a real method either. So I removed all the BluetoothSerial/ESP_BT code and rewrote the setup and loop functions using the correct DabbleESP32 API, reading the incoming message one character at a time instead.

# FINAL SETUP

Arduino IDE 2.3.10, ESP32 board package 2.0.17, DabbleESP32 library version 1.5.1, board set to "ESP32 Dev Module", Serial Monitor at 115200 baud.

# HOW TO RUN

Install DabbleESP32 version 1.5.1 through the Arduino IDE Library Manager, select "ESP32 Dev Module" as the board along with the correct COM port, then upload the sketch. Open the Serial Monitor at 115200 baud — you should see "Bluetooth is ready. Connect using Dabble app." On your phone, open the Dabble app, connect to "ESP32_Dabble", and open the Terminal module. Any message you send will appear on the Serial Monitor, and the ESP32 will reply back to the app.
