#include <ESP8266WiFi.h>

WiFiClient client = WiFiClient();

const int BUTTON_PIN = 13;
const int LED_PIN = 2;

bool IS_DOWN = false;
bool IS_CONNECTED = false;

void setup() {
    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);
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

        if (!client.connected()) {
            client.connect((char*)"IP", (uint16_t)6060);
            client.print("hello from esp 8266");
        }
        else {
            client.print("disconnected");
            client.stop();
        }
    }
    if (BUTTON_STATE == LOW && IS_DOWN == true) {
        IS_DOWN = false;
    }


    if (client.connected()) {
        char buffer[1024];
        int id = 0;
      
        if (client.available() > 0) {
            char c = client.read();
            buffer[id] = c;
            id++;
        }

        // the led is wired backwards so the following code means 'on'
        digitalWrite(LED_PIN, LOW);
    }
    else {
        // the led is wired backwards so the following code means 'off'
        digitalWrite(LED_PIN, HIGH);
    }
}
