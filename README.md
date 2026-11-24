# Flame Sensor Fire Alarm (Arduino Uno / AVR)

Group project by Shweta Awasthi and Anuva.

A fire detection system using a flame sensor. When a flame is detected, the buzzer sounds, the LED turns on and the 16x2 LCD shows a warning. Otherwise the LCD shows that the system is safe.

## Files
- `main.c` : AVR C code for Microchip Studio (ATmega328P, 16 MHz)
- `flame_sensor.ino` : Arduino IDE version
- `demo.mp4` : working demo video

## Components
Arduino Uno, flame sensor module, IO board with buzzer, 16x2 LCD, 10k potentiometer, 220 ohm resistor.

## Connections
| Part | Pin | Arduino |
|---|---|---|
| Flame sensor | VCC / GND / DO | 5V / GND / D2 |
| Buzzer (IO board) | input | D7 |
| LCD | RS / E | D8 / D9 |
| LCD | D4 / D5 / D6 / D7 | A0 / A1 / A2 / A3 |
| LCD | VSS, RW, K | GND |
| LCD | VDD | 5V |
| LCD | V0 | 10k pot middle pin (contrast) |
| LCD | A | 5V through 220 ohm |

All GND connections must be common.

## Output
| State | LCD | Buzzer / LED |
|---|---|---|
| Safe | System: SAFE / No Fire Detected | Off |
| Fire | FIRE DETECTED!! / Move to safety! | On |

## Upload
- **Microchip Studio:** new GCC C Executable Project (ATmega328P), paste `main.c`, build (F7), upload the `.hex`.
- **Arduino IDE:** open `flame_sensor.ino`, select Arduino Uno, upload.

This is a learning project, not a real fire alarm.
