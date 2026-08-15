/*
  ESP8266 + TTP223 Touch Sensor + 2x Generic ESC + 2x Generic BLDC Motor
  ------------------------------------------------------------------
  Behavior: Touch once -> both motors spin at RUN_SPEED. Touch again -> both stop.
  (This is "toggle" behavior done in software. See note at bottom for
   "spin only while touching" / momentary behavior instead.)

  Wiring:
    TTP223  VCC -> ESP8266 3.3V
    TTP223  GND -> ESP8266 GND
    TTP223  OUT -> ESP8266 D5 (GPIO14)

    ESC1 Signal -> ESP8266 D1 (GPIO5)
    ESC2 Signal -> ESP8266 D2 (GPIO4)
    ESC1/ESC2 GND -> ESP8266 GND   (COMMON GROUND IS REQUIRED)
    ESC1/ESC2 Power (thick red/black wires) -> Battery pack directly,
        NOT from the ESP8266's own supply.

  Board assumed: NodeMCU / Wemos D1 mini style pin labels (D1, D2, D5).
  If you're on a different ESP8266 board, just swap the GPIO numbers below.
*/

#include <Servo.h>

// ---------- Pin assignments ----------
const int TOUCH_PIN = 14;   // D5
const int ESC1_PIN  = 5;    // D1
const int ESC2_PIN  = 4;    // D2

// ---------- ESC signal values (microseconds, standard servo/ESC PWM range) ----------
const int ESC_MIN   = 1000; // throttle off / arm signal
const int ESC_MAX   = 2000; // full throttle (don't jump straight here without testing!)
const int RUN_SPEED = 2000; // speed used when "on" -- tune this for your ESC/motor combo

Servo esc1;
Servo esc2;

bool motorsRunning  = false;
bool lastTouchState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(TOUCH_PIN, INPUT);

  esc1.attach(ESC1_PIN);
  esc2.attach(ESC2_PIN);

  // Arm the ESCs: most generic ESCs require a min-throttle signal held for
  // a few seconds right after power-up before they'll accept commands.
  // Listen for the ESC's beep sequence to confirm it's armed.
  esc1.writeMicroseconds(ESC_MIN);
  esc2.writeMicroseconds(ESC_MIN);
  Serial.println("Arming ESCs...");
  delay(3000);
  Serial.println("Ready. Touch the sensor to start motors.");
}
/*
void loop() {
  bool touchState = digitalRead(TOUCH_PIN);

  // Detect a fresh press (LOW -> HIGH edge) and flip the running state.
  if (touchState == HIGH && lastTouchState == LOW) {
    motorsRunning = !motorsRunning;
    Serial.println(motorsRunning ? "Motors ON" : "Motors OFF");
    delay(50); // basic debounce
  }
  lastTouchState = touchState;

  if (motorsRunning) {
    esc1.writeMicroseconds(RUN_SPEED);
    esc2.writeMicroseconds(RUN_SPEED);
  } else {
    esc1.writeMicroseconds(ESC_MIN);
    esc2.writeMicroseconds(ESC_MIN);
  }
}
*/


  void loop() {
    bool touchState = digitalRead(TOUCH_PIN);
    if (touchState == HIGH) {
      esc1.writeMicroseconds(RUN_SPEED);
      esc2.writeMicroseconds(RUN_SPEED);
    } else {
      esc1.writeMicroseconds(ESC_MIN);
      esc2.writeMicroseconds(ESC_MIN);
    }
  }