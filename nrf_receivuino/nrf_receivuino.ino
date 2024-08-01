#include <SPI.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "2Node";
char payload[32];

void setup() {
  Serial.begin(115200);
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}
  }
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(32);
  radio.openReadingPipe(1, address);
  radio.setChannel(100);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&payload, sizeof(payload));
    payload[31] = '\0';
    Serial.println(payload);
  }
}
