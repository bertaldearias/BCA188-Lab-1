#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <DabbleESP32.h>

void setup() {
  Serial.begin(115200);
  Dabble.begin("ESP32_Dabble");
  Serial.println("Bluetooth is ready. Connect using Dabble app.");
}

void loop() {
  Dabble.processInput();

  if (Terminal.available()) {
    String message = "";
    while (Terminal.available()) {
      message += (char)Terminal.read();
    }
    Serial.print("Received from phone: ");
    Serial.println(message);

    Terminal.print("ESP32: Message received - ");
    Terminal.println(message);
  }
}