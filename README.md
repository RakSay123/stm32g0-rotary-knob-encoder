# STM32G070 Bare-Metal Timer Encoder Driver

[demo gif when finished]

### Overview
This project implements a bare-metal quadrature encoder driver for the STM32G070 using only the CMSIS device headers. No HAL or LL libraries are used.

The driver configures an STM32 timer in hardware encoder mode, allowing the timer peripheral to decode quadrature signals directly from a rotary encoder.

The timer automatically:
- tracks encoder position
- detects rotation direction
- increments/decrements the counter
- filters noisy inputs
- operates entirely in hardware with essentially zero CPU overhead
---
### Features
- CMSIS register-level implementation
- Hardware quadrature decoding
- Channel configuration
- Input capture configuration
- Configurable digital filters
- Configurable input prescalers
- Configurable polarity
- Encoder modes
   - TI1
   - TI2
   - TI1 + TI2
- Position counter API
- Direction API
- Rotary encoder abstraction layer
---

### Driver Architecture
```
Application
     │
     ▼
rotary_encoder.c
     │
     ▼
timer_encoder.c
     │
     ▼
TIM3 Hardware Encoder Mode
     │
     ▼
Rotary Encoder
```
---

### Hardware Used
- STM32G070 Nucleo
- Mechanical rotary knob encoder
- UART debugging
---

### What I learned
While implementing this driver I learned:
- How quadrature encoders generate A/B waveforms
- How timer input capture channels become encoder inputs
- How the timer determines rotation direction
- How encoder modes affect counting
- How input filters remove noise
- How alternate-function routing affects peripheral operation
- How hardware peripherals can eliminate software processing
---

### Example Output
```
[ROTARY_ENCODER] Count: 2145
[ROTARY_ENCODER] Direction: UP

[ROTARY_ENCODER] Count: 2202
[ROTARY_ENCODER] Direction: DOWN
```
---

### Future Work
- Angular position
- Rotational velocity
- RPM calculation
- Degrees/sec
- Radians/sec
- Integration with DC motors
- Closed-loop PID motor control