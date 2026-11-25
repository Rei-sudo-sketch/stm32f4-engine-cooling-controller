# stm32f4-engine-cooling-controller
STM32 HAL STM32F4 engine thermal management firmware featuring a hysteresis state machine, sensor fault fail-safe, PWM fan control, and non-blocking HAL_GetTick scheduling.

## System Architecture

* **Hardware Abstraction (`main.c`):** Handles peripheral initialization (`ADC1`, `TIM2` PWM, `USART2`) and executes a non-blocking cooperative scheduler via `HAL_GetTick()`, decoupling a **20 Hz (50 ms)** sensor/control loop from a **2 Hz (500 ms)** UART telemetry stream.
* **Control & Safety Module (`cooling.c` / `cooling.h`):** C modules encapsulating ADC-to-temperature scaling, out-of-range fault detection, and a 4-state thermal state machine with hysteresis.

## Control Logic & State Table

| State | Trigger Condition | PWM Fan Duty Cycle | Behavior |
| :--- | :--- | :---: | :--- |
| **NORMAL** | Temp < 90.0 °C (and valid ADC) | 0% | Fan off; normal operating range |
| **WARNING** | 90.0 °C ≤ Temp < 110.0 °C | 50% | Moderate cooling active |
| **OVERHEAT** | Temp ≥ 110.0 °C (exits below 100.0 °C) | 100% | Full cooling with 10 °C hysteresis band |
| **FAULT** | ADC < 50 or ADC > 4045 (12-bit) | 100% | Fail-safe full cooling on open/short circuit |



