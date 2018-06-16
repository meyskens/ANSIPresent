#include <SoftwareSerial.h>

// TODO: do not use serial for comminucation over the air
SoftwareSerial radioSerial(3, 4); // RX, TX, RX isn't used here

const int backPin = 8;
const int forwardPin = 11;

int backState = 1;
int forwardState = 1;


void setup() {
  Serial.begin(115200);
  Serial.println("ANSIRemote");

  pinMode(backPin, INPUT_PULLUP);
  pinMode(forwardPin, INPUT_PULLUP);
}

void loop() {
  int back = digitalRead(backPin);
  int forward = digitalRead(forwardPin);

  if (back == HIGH && back != backState) {
    Serial.println("back");
    transmitCommand("back");
    delay(100);
  }

  if (forward == HIGH && forward != forwardState) {
    Serial.println("forward");
    transmitCommand("forward");
    delay(100);
  }

  backState = back;
  forwardState = forward;
}

void transmitCommand(String in) {
   radioSerial.begin(2400);
   radioSerial.println("ansiremote:");
   radioSerial.println(in);
   radioSerial.end();
   digitalWrite(4, LOW);
}
