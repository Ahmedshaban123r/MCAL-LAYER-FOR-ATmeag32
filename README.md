# ⚡ ATmega32 MCAL – ADC Driver

This repository contains the **ADC (Analog-to-Digital Converter) driver** implementation for the **ATmega32** microcontroller.  
It is part of the **MCAL (Microcontroller Abstraction Layer)**, which provides direct access to MCU peripherals.  

---

## 🏗️ Layered Architecture
Application Layer
|
V
MCAL Layer
└── ADC Driver
Hardware (ATmega32)


- **Application Layer**: Uses the ADC driver to implement higher-level functionality.  
- **MCAL Layer**: Provides a reusable, configurable ADC driver.  
- **Hardware Layer**: ATmega32 ADC peripheral (10-bit, up to 8 channels).  

---

## 📜 Driver Features
- Configurable **reference voltage** (AREF, AVCC, Internal 2.56V).  
- Selectable **input channel** (ADC0 – ADC7).  
- Adjustable **prescaler** for conversion speed.  
- Supports **polling-based ADC conversion**.  

---

## 📂 Project Structure
/MCAL
├── ADC
│ ├── ADC_program.c # Driver implementation
│ ├── ADC_interface.h # Public API for application layer
│ └── ADC_private.h # Registers and internal macros
/APP
└── main.c # Example usage of ADC driver

---

## ⚙️ Configuration Guide

You can configure the ADC driver using the enums and macros defined in **ADC_interface.h**.  

### 🔹 Reference Voltage Selection
| Macro              | Description                          |
|--------------------|--------------------------------------|
| `ADC_REF_AREF`     | External AREF pin, internal Vref off |
| `ADC_REF_AVCC`     | AVCC with external capacitor at AREF |
| `ADC_REF_INT_2_56` | Internal 2.56V reference             |

### 🔹 Prescaler (ADC Clock Division Factor)
| Macro                 | Division Factor |
|-----------------------|-----------------|
| `ADC_PRESCALER_2`     | 2               |
| `ADC_PRESCALER_4`     | 4               |
| `ADC_PRESCALER_8`     | 8               |
| `ADC_PRESCALER_16`    | 16              |
| `ADC_PRESCALER_32`    | 32              |
| `ADC_PRESCALER_64`    | 64              |
| `ADC_PRESCALER_128`   | 128             |

### 🔹 ADC Channels
| Channel Macro | Pin   |
|---------------|-------|
| `ADC_CHANNEL_0` | PA0 |
| `ADC_CHANNEL_1` | PA1 |
| `ADC_CHANNEL_2` | PA2 |
| `ADC_CHANNEL_3` | PA3 |
| `ADC_CHANNEL_4` | PA4 |
| `ADC_CHANNEL_5` | PA5 |
| `ADC_CHANNEL_6` | PA6 |
| `ADC_CHANNEL_7` | PA7 |

---

## 🔧 Public APIs
```c
void ADC_init(void);              // Initialize ADC with config (ref, prescaler)
uint16_t ADC_read(uint8_t ch);    // Read from a specific ADC channel

---

## 🔧 Public APIs
```c
void ADC_init(void);              // Initialize ADC with config (ref, prescaler)
uint16_t ADC_read(uint8_t ch);    // Read from a specific ADC channel

#include "ADC_interface.h"

int main(void) {
    uint16_t ldr_value;

    ADC_init();                   // Initialize ADC

    while (1) {
        ldr_value = ADC_read(0);  // Read from channel 0 (PA0)
        // Application can now use ldr_value
    }
}


