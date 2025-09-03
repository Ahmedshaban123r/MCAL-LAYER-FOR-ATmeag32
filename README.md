# ⚡ ATmega32 MCAL – ADC & Timer0 Drivers

This repository contains the **ADC (Analog-to-Digital Converter)** and **Timer0** drivers for the **ATmega32** microcontroller.  
It is part of the **MCAL (Microcontroller Abstraction Layer)**, which provides direct access to MCU peripherals.  

---

## 🏗️ Layered Architecture
Application Layer
|
v
MCAL Layer
├── ADC Driver
└── Timer0 Driver
Hardware (ATmega32)

- **Application Layer**: Uses ADC/Timer0 drivers to implement higher-level functionality.  
- **MCAL Layer**: Provides reusable, configurable low-level drivers.  
- **Hardware Layer**: ATmega32 peripherals (ADC & Timer0).  

---

## 📜 Driver Features

### 🔹 ADC Driver
- Configurable **reference voltage** (AREF, AVCC, Internal 2.56V).  
- Selectable **input channel** (ADC0 – ADC7).  
- Adjustable **prescaler** for conversion speed.  
- Supports **polling-based ADC conversion**.  

### 🔹 Timer0 Driver
- Supports **Normal, CTC, Fast PWM, and Phase Correct PWM modes**.  
- Configurable **clock source / prescaler**.  
- Supports **Compare Match Output (OC0)** in toggle, set, or clear modes.  
- **PWM generation** for LED brightness control, motor speed, etc.  
- Optional **interrupt enable** for overflow or compare match.  

---

## 📂 Project Structure
/MCAL
├── ADC
│ ├── ADC_program.c # ADC implementation
│ ├── ADC_interface.h # ADC public API
│ └── ADC_private.h # ADC registers & macros
├── TIMER0
│ ├── TIMER0_program.c # Timer0 implementation
│ ├── TIMER0_interface.h # Timer0 public API
│ └── TIMER0_private.h # Timer0 registers & macros
/APP
└── main.c # Example usage of ADC + Timer0

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

### 🔹 Timer0 Configuration
Defined in `TIMER0_interface.h`

**Modes of Operation:**
| Macro                     | Description                |
|----------------------------|----------------------------|
| `TIMER0_MODE_NORMAL`       | Overflow Mode              |
| `TIMER0_MODE_CTC`          | Clear Timer on Compare     |
| `TIMER0_MODE_FAST_PWM`     | Fast PWM Mode              |
| `TIMER0_MODE_PHASE_PWM`    | Phase Correct PWM          |

**Clock Selection:**
| Macro                     | Clock Source                |
|----------------------------|-----------------------------|
| `TIMER0_NO_CLOCK`          | No clock (stopped)          |
| `TIMER0_PRESCALER_1`       | F_CPU / 1                  |
| `TIMER0_PRESCALER_8`       | F_CPU / 8                  |
| `TIMER0_PRESCALER_64`      | F_CPU / 64                 |
| `TIMER0_PRESCALER_256`     | F_CPU / 256                |
| `TIMER0_PRESCALER_1024`    | F_CPU / 1024               |

**Compare Match Output (OC0 pin PB3):**
| Macro                   | Description                         |
|--------------------------|-------------------------------------|
| `TIMER0_OC0_DISCONNECTED`| Normal port operation (no PWM)      |
| `TIMER0_OC0_TOGGLE`      | Toggle OC0 on compare match         |
| `TIMER0_OC0_CLEAR`       | Clear OC0 on compare (non-inverting)|
| `TIMER0_OC0_SET`         | Set OC0 on compare (inverting)      |

---

## 🔧 Public APIs

### ADC
```c
void ADC_init(const ADC_Config_t *cfg);   // Initialize ADC
uint16_t ADC_readBlocking(uint8_t ch);    // Read 10-bit value from channel
uint8_t  ADC_read8(uint8_t ch);           // Read 8-bit (left adjusted)
void TIMER0_init(const TIMER0_Config_t *cfg);  // Initialize Timer0
void TIMER0_setCompareValue(uint8_t value);    // Set OCR0 compare value
void TIMER0_enableInterrupt(void);             // Enable interrupts
void TIMER0_disableInterrupt(void);            // Disable interrupts
#include "ADC_interface.h"
#include "TIMER0_interface.h"
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

    // Timer0 config
    TIMER0_Config_t timer_cfg = {
        .mode = TIMER0_MODE_FAST_PWM,
        .clock = TIMER0_PRESCALER_64,
        .oc0_mode = TIMER0_OC0_CLEAR,
        .interrupt_enable = 0
    };
    TIMER0_init(&timer_cfg);

    while (1) {
        uint8_t ldr_val = ADC_read8(ADC_CHANNEL_0);
        TIMER0_setCompareValue(ldr_val);
        _delay_ms(20);
    }
}
