#include <SPI.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "1Node";

void setup() {
  Serial.begin(115200);
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}
  }
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(32);
  radio.openWritingPipe(address);
  radio.setChannel(0);
  radio.stopListening();
}

void loop() {
  if (Serial.available() > 0) {
    String receivedData = Serial.readStringUntil('\n');
    char payload[32] = {0};
    receivedData.toCharArray(payload, receivedData.length() + 1);
    if (radio.write(&payload, sizeof(payload))) {
      Serial.println(F("Transmission successful!"));
      Serial.println(payload);
    } else {
      Serial.println(F("Transmission failed or timed out"));
    }
  }
}
