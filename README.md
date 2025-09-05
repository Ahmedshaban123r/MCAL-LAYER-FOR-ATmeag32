# ⚡ ATmega32 MCAL – ADC & Timer Drivers

This repository contains the **ADC (Analog-to-Digital Converter)** and **Timer drivers** for the **ATmega32** microcontroller.  
It is part of the **MCAL (Microcontroller Abstraction Layer)**, which provides direct access to MCU peripherals.  

I’m building this step by step as part of my **MCAL learning journey**.  

---

## 🏗️ Layered Architecture
Application Layer  
⬇  
MCAL Layer  
├── ADC Driver  
├── Timer0 Driver (legacy, first step)  
└── Unified Timer Driver (Timer0/1/2)  
⬇  
Hardware (ATmega32)  

- **Application Layer**: Uses ADC/Timer drivers to implement higher-level functionality.  
- **MCAL Layer**: Provides reusable, configurable low-level drivers.  
- **Hardware Layer**: ATmega32 peripherals (ADC, Timer0/1/2).  

---

## 📜 Driver Features

### 🔹 ADC Driver
- Configurable **reference voltage** (AREF, AVCC, Internal 2.56V).  
- Selectable **input channel** (ADC0 – ADC7).  
- Adjustable **prescaler** for conversion speed.  
- Supports **polling-based ADC conversion**.  

### 🔹 Timer0 Driver (First Version)
- Supports **Normal, CTC, Fast PWM, and Phase Correct PWM modes**.  
- Configurable **clock source / prescaler**.  
- Supports **Compare Match Output (OC0)** on PB3.  
- **PWM generation** for LED brightness control.  
- Optional **interrupt enable**.  

✅ This was my **first attempt at a timer driver**, focused only on **Timer0**.  

### 🔹 Unified Timer Driver (Latest Version)
- One driver supports **Timer0, Timer1, and Timer2**.  
- Configurable **modes**:
  - Normal  
  - CTC (Clear Timer on Compare)  
  - Fast PWM  
  - Phase Correct PWM  
- Configurable **clock source / prescaler** for each timer.  
- Configurable **Compare Match Output modes**:
  - Toggle, Clear, Set.  
- **PWM generation** on multiple channels (OC0, OC1A, OC1B, OC2).  
- Support for **interrupts**: Overflow, Compare Match, Input Capture (Timer1).  
- Unified **configuration struct** to keep all timer options consistent.  

✅ This marks a **big improvement in modularity**: instead of writing three separate drivers, one interface handles all timers.  

---

## 📂 Project Structure
/MCAL
├── ADC
│ ├── ADC_program.c # ADC implementation
│ ├── ADC_interface.h # ADC public API
│ └── ADC_private.h # ADC registers & macros
├── TIMER0 # Old version (Timer0 only)
│ ├── TIMER0_program.c
│ ├── TIMER0_interface.h
│ └── TIMER0_private.h
├── TIMER # Unified Timer Driver (Timer0/1/2)
│ ├── TIMER_program.c
│ ├── TIMER_interface.h
│ └── TIMER_private.h
/APP
└── main.c # Example usage

---

## ⚙️ Configuration Guide

### 🔹 ADC Configuration
Defined in `ADC_interface.h`

**Reference Voltage:**
| Macro              | Description                          |
|--------------------|--------------------------------------|
| `ADC_REF_AREF`     | External AREF pin, internal Vref off |
| `ADC_REF_AVCC`     | AVCC with external capacitor at AREF |
| `ADC_REF_INT_2_56` | Internal 2.56V reference             |

**Prescaler:**
| Macro               | Division Factor |
|---------------------|-----------------|
| `ADC_PRESCALER_2`   | 2               |
| `ADC_PRESCALER_4`   | 4               |
| `ADC_PRESCALER_8`   | 8               |
| `ADC_PRESCALER_16`  | 16              |
| `ADC_PRESCALER_32`  | 32              |
| `ADC_PRESCALER_64`  | 64              |
| `ADC_PRESCALER_128` | 128             |

**Channels:**
| Macro              | Pin  |
|--------------------|------|
| `ADC_CHANNEL_0`    | PA0  |
| `ADC_CHANNEL_1`    | PA1  |
| `ADC_CHANNEL_2`    | PA2  |
| `ADC_CHANNEL_3`    | PA3  |
| `ADC_CHANNEL_4`    | PA4  |
| `ADC_CHANNEL_5`    | PA5  |
| `ADC_CHANNEL_6`    | PA6  |
| `ADC_CHANNEL_7`    | PA7  |

---

### 🔹 Timer0 Driver (Legacy)
Defined in `TIMER0_interface.h`  

**Modes of Operation:**
| Macro                  | Description                |
|-------------------------|----------------------------|
| `TIMER0_MODE_NORMAL`    | Overflow Mode              |
| `TIMER0_MODE_CTC`       | Clear Timer on Compare     |
| `TIMER0_MODE_FAST_PWM`  | Fast PWM Mode              |
| `TIMER0_MODE_PHASE_PWM` | Phase Correct PWM          |

**Compare Match Output (OC0 pin PB3):**
| Macro                      | Description                         |
|-----------------------------|-------------------------------------|
| `TIMER0_OC0_DISCONNECTED`   | Normal port operation (no PWM)      |
| `TIMER0_OC0_TOGGLE`         | Toggle OC0 on compare match         |
| `TIMER0_OC0_CLEAR`          | Clear OC0 on compare (non-inverting)|
| `TIMER0_OC0_SET`            | Set OC0 on compare (inverting)      |

---

### 🔹 Unified Timer Driver
Defined in `TIMER_interface.h`  

**Timer Selection:**
| Macro      | Description        |
|------------|--------------------|
| `TIMER_0`  | Use Timer0         |
| `TIMER_1`  | Use Timer1         |
| `TIMER_2`  | Use Timer2         |

**Modes of Operation (all timers):**
| Macro                  | Description                |
|-------------------------|----------------------------|
| `TIMER_MODE_NORMAL`     | Overflow Mode              |
| `TIMER_MODE_CTC`        | Clear Timer on Compare     |
| `TIMER_MODE_FAST_PWM`   | Fast PWM Mode              |
| `TIMER_MODE_PHASE_PWM`  | Phase Correct PWM          |

**Clock Selection:**
| Macro                 | Clock Source              |
|-----------------------|---------------------------|
| `TIMER_NO_CLOCK`      | No clock (stopped)        |
| `TIMER_PRESCALER_1`   | F_CPU / 1                 |
| `TIMER_PRESCALER_8`   | F_CPU / 8                 |
| `TIMER_PRESCALER_64`  | F_CPU / 64                |
| `TIMER_PRESCALER_256` | F_CPU / 256               |
| `TIMER_PRESCALER_1024`| F_CPU / 1024              |

**Compare Match Output Modes:**
| Macro             | Description                         |
|-------------------|-------------------------------------|
| `TIMER_OC_DISCONNECTED` | Normal port operation (no PWM) |
| `TIMER_OC_TOGGLE`       | Toggle on compare match        |
| `TIMER_OC_CLEAR`        | Clear on compare (non-inverting)|
| `TIMER_OC_SET`          | Set on compare (inverting)     |

---

## 🔧 Example Code

```c
#include "ADC_interface.h"
#include "TIMER_interface.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << PB3); // OC0 pin as output

    // ADC config
    ADC_Config_t adc_cfg = {
        .ref = ADC_REF_AVCC,
        .align = ADC_ALIGN_LEFT,
        .prescaler = 6,
        .auto_trigger = 0,
        .trigger_src = ADC_TRIG_FREE_RUNNING,
        .interrupt_enable = 0,
        .didr_mask = (1<<ADC0D)
    };
    ADC_init(&adc_cfg);

    // Timer config (using unified driver for Timer0)
    TIMER_Config_t timer_cfg = {
        .timer = TIMER_0,
        .mode = TIMER_MODE_FAST_PWM,
        .clock = TIMER_PRESCALER_64,
        .oc_mode = TIMER_OC_CLEAR,
        .interrupt_enable = 0
    };
    TIMER_init(&timer_cfg);

    while (1) {
        uint8_t ldr_val = ADC_read8(ADC_CHANNEL_0);
        TIMER_setCompareValue(TIMER_0, ldr_val);
        _delay_ms(20);
    }
}
