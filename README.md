# Candyman1 — Touch-Triggered Dual BLDC Rig

An ESP8266-based controller that spins up two BLDC motors (via generic ESCs), triggered by a single capacitive touch sensor.

## How it works

Touch the TTP223 sensor once and both motors ramp to full throttle. Touch it again and they stop. It's a toggle, not a hold — you don't need to keep your finger on the sensor.

## Hardware

| Part | Qty |
|---|---|
| ESP8266 (NodeMCU / Wemos D1 mini) | 1 |
| Generic BLDC motor | 2 |
| Generic ESC | 2 |
| TTP223 capacitive touch sensor | 1 |
| Battery pack (for ESCs/motors, matched to motor voltage) | 1 |

## Wiring

**Touch sensor**
- VCC → ESP8266 3.3V
- GND → ESP8266 GND
- OUT → ESP8266 D5 (GPIO14)

**ESCs**
- ESC1 Signal → D1 (GPIO5)
- ESC2 Signal → D2 (GPIO4)
- ESC1/ESC2 GND → ESP8266 GND
- ESC1/ESC2 power leads → battery pack directly (not from the ESP8266)

All grounds (ESP8266, ESCs, battery) must be tied together.

## Setup

1. Install the ESP8266 board package in Arduino IDE (Boards Manager URL: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`)
2. Select your board under **Tools → Board** (e.g. "NodeMCU 1.0 (ESP-12E Module)")
3. Wire everything per the diagram above
4. Upload `candyman1.ino`
5. On power-up, the ESCs arm for ~3 seconds (listen for their beep sequence) before the sensor becomes active

## Safety

- Keep clear of the motors/props while testing — full throttle triggers instantly on touch

## Customizing

- `RUN_SPEED` in the sketch controls motor speed (currently set to `ESC_MAX` for full throttle)
- Swap the toggle-on-touch logic for hold-to-run by using the alternate `loop()` shown commented at the bottom of the sketch
