#include <ESP8266WiFi.h>

WiFiClient client = WiFiClient();

const int BUTTON_PIN = 13;
bool IS_DOWN = false;
bool IS_CONNECTED = false;

void setup() {
    Serial.begin(115200);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    WiFi.begin((char*)"SSID", (char*)"PASSWORD");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print("...\n");
    }
}

void loop() {
    int BUTTON_STATE = digitalRead(BUTTON_PIN);
    if (BUTTON_STATE == HIGH && IS_DOWN == false) {
        IS_DOWN = true;
        if (!IS_CONNECTED) {
            client.connect((char*)"HOST", (uint16_t)6060);
            client.print("Connection from ESP8266");
            IS_CONNECTED = true;
        }
        else {
            client.print("disconnect_ed");
            client.stop();
            IS_CONNECTED = false;
        }
    }
    if (BUTTON_STATE == LOW && IS_DOWN == true) {
        IS_DOWN = false;
    }
}
