# STM32G0 Bare-Metal Project Template

## Overview

This repository provides a reusable starting point for bare-metal STM32 firmware development using CMSIS and STM32CubeIDE.

The goal is to separate hardware-specific initialization from application logic while encouraging reusable peripheral and device drivers.

The template currently targets the STM32G070 Nucleo board but can be adapted for other STM32 devices.

---

## Architecture
```
Core/
    Firmware entry point

App/
    Application logic

Board/
    Hardware configuration
    Hardware initialization
    Device instances

Drivers/
    Peripheral drivers

Devices/
    Device drivers
```

Dependency direction:
```
Application
        │
        ▼
Device Drivers
        │
        ▼
Peripheral Drivers
        │
        ▼
STM32 Registers
```
---

## Folder Layout
```
Core/
    main.c
    syscalls.c
    sysmem.c

App/
    app.c
    app.h

Board/
    board_config.h
    board_init.c
    board_init.h
    device_instances.c
    device_instances.h

Drivers/
    gpio/
    uart/
    timer/
    systick/
    ...

Devices/
    led/
    servo/
    pulse_width_sensor/
    ...
```
---

## Firmware Flow

```
main()

↓

board_init()

↓

app_init()

↓

while (1)
{
    app_update();
}
```
---
## Design Philosophy
This project follows a layered architecture intended to minimize coupling between application code and hardware implementation.

Peripheral drivers directly configure STM32 peripherals.

Device drivers combine peripherals into reusable hardware abstractions.

The board layer describes the physical hardware present on the PCB.

The application layer contains only firmware behavior.

This separation allows new projects to reuse the same drivers while keeping application logic clean and portable.

---

## Current Features
### Peripheral Drivers:
- GPIO Driver
- UART Driver
- General Timer Driver
- PWM Driver
- Input Capture Driver
- Encoder Driver (in development)
- SysTick Driver

### Device Drivers:
- LED Device Driver
- Servo Device Driver
- BNO055 Device Driver
- Pulse Width Sensor Device Driver
- PWM Monitor Device Driver

---

## Planned Features
- ADC
- SPI
- DMA / DMAMUX
- Advanced Timers
- Motor Driver
- Quadrature Encoder Support
- Micromouse Platform

---

## Version
**Template Version 1.0**

