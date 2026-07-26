# STM32 Reflex Game

A Simon Says / rhythm memory game built on the **Nucleo-F401RE**, using bare peripherals through the HAL layer.

## Hardware

| Component | Connection | Role |
|---|---|---|
| **8 LEDs** via 74HC595 shift register | PA6 (DS), PA7 (SHCP), PA8 (STCP) | Visual pattern display |
| **Passive buzzer** via TIM2 PWM | PA1 (TIM2_CH2) | Musical note feedback |
| **8 tactile buttons** (pull-up, active-LOW) | PA10, PB3, PB5, PB4, PB10, PA9, PC7, PB6 | Player input |
| **SSD1306 OLED** 128x64 via I2C1 | PB8 (SCL), PB9 (SDA) | Score / UI display (WIP) |
| **Onboard LED** | PA5 | Status indicator |
| **TIM5** (32-bit, 1 us ticks) | Internal | Reaction timing + RNG seed |

### 74HC595 Wiring

```
STM32          74HC595         LEDs
PA6  --------  DS  (pin 14)
PA7  --------  SHCP (pin 11)   Q0-Q7 -> 8 LEDs (with 330 Ohm resistors)
PA8  --------  STCP (pin 12)
GND  --------  OE   (pin 13)   active-LOW: tie to GND to enable outputs
3.3V --------  MR   (pin 10)   active-LOW: tie to VCC to prevent reset
3.3V --------  VCC  (pin 16)
GND  --------  GND  (pin 8)
```

### Button Wiring

Each button connects its STM32 pin to GND. Internal pull-ups are enabled in software (released = HIGH, pressed = LOW).

```
STM32 pin (pull-up) ---- button ---- GND
```

| Button | STM32 Pin | Arduino Label | LED / Note |
|--------|-----------|---------------|------------|
| 0 | PA10 | D2 | Q0 / C4 |
| 1 | PB3 | D3 | Q1 / D4 |
| 2 | PB5 | D4 | Q2 / E4 |
| 3 | PB4 | D5 | Q3 / F4 |
| 4 | PB10 | D6 | Q4 / G4 |
| 5 | PA9 | D8 | Q5 / A4 |
| 6 | PC7 | D9 | Q6 / B4 |
| 7 | PB6 | D10 | Q7 / C5 |

## Game Modes

### Simon Says (in progress)
The system plays an LED + note sequence. The player repeats it using the matching buttons. Each round adds one step. Wrong press or timeout = game over.

### Speed Round (planned)
LEDs light up one at a time, faster and faster. Press the matching button while it's lit. Miss one = game over. Score = rounds survived.

## Project Structure

```
Core/
  Inc/
    buzzer.h         Buzzer API + note frequency definitions
    ssd1306.h        SSD1306 OLED driver API
    main.h           CubeMX-generated pin/peripheral defines
  Src/
    main.c           Game logic, GPIO init, timer init
    buzzer.c         PWM-based buzzer driver (TIM2)
    ssd1306.c        I2C-based OLED driver (buffer + page update)
Drivers/             ST HAL + CMSIS (CubeMX-managed)
STM32_Reflex_Game.ioc   CubeMX project file
```

## Clock Configuration

- HSE: 25 MHz (Nucleo onboard crystal)
- PLL: SYSCLK = 72 MHz
- APB1: 36 MHz (timers get 72 MHz due to prescaler doubling)
- APB2: 72 MHz

## Tools

- **Board:** Nucleo-F401RE (STM32F401RET6)
- **IDE:** STM32CubeIDE
- **Code generation:** STM32CubeMX

## Status

- [x] Toolchain + clock config
- [x] 74HC595 shift register LED bar
- [x] I2C + SSD1306 OLED driver
- [x] PWM buzzer with musical notes
- [x] Microsecond timer (TIM5)
- [ ] Button input (GPIO configured, game logic WIP)
- [ ] Simon Says game mode
- [ ] Speed round game mode
- [ ] OLED score display
- [ ] ADC + photoresistor (stretch goal)
