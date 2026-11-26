# Contributing

Thanks for helping with the Flame Sensor Fire Alarm project.

## Workflow

1. Pull the latest `main`: `git pull origin main`
2. Create a branch for your change: `git checkout -b feature/short-name`
3. Make small, focused commits with clear messages.
4. Push the branch: `git push -u origin feature/short-name`
5. Open a pull request on GitHub and ask a teammate to review it.
6. Merge only after at least one review.

Do not push directly to `main`.

## Code style (`avr/flame_sensor_lcd/main.c`)

- Bare-metal AVR C only: no Arduino libraries.
- Use the existing macros for pins (`BUZZER_ON()`, `LED_ON()`, `LCD_E_HIGH()` etc.).
- Short comments after `//`; keep 4-space indentation.
- Keep the file building in **both** MPLAB X (XC8) and Microchip Studio (avr-gcc).

## Before opening a pull request

- [ ] Code builds with no warnings in at least one toolchain
- [ ] Tested on hardware (or say that it was not)
- [ ] README updated if pins, behaviour or steps changed

## Reporting bugs

Use the **Bug report** issue template and include your IDE, OS, wiring changes and what the LCD, buzzer and LED did.
