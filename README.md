# SecureParkingZone
An ATmega32-based parking system featuring keypad access, an LCD display, and alarm functionalities. It incorporates IR sensor utilization, PWM control, and secure ID entry.

![P](/App/p.jpg)

### Hardware Test Video :
  (Link): [drive.google.com/file/d/1L0I4FkAT](https://drive.google.com/file/d/1L0I4FkAT0mFpcvqkXXb6IjquDgcDakBg/view?usp=sharing)


## Modules

### App
- **[App](App/app.c):** The main application file responsible for orchestrating program flow, managing the user interface, and handling interactions.

### HAL (Hardware Abstraction Layer)
- **[IR_SENSOR](HAL/IR_SENSOR/):** Manages the functionality of the Infrared (IR) sensor.
- **[KEYPAD](HAL/KEYPAD/):** Handles keypad input for user ID entry.
- **[LCD](HAL/LCD/):** Provides functions for interfacing with the LCD display.

### MCAL (MicroController Abstraction Layer)
- **[DIO](MCAL/DIO/):** Direct Input/Output module, used for controlling LEDs and the buzzer.
- **[EXTI](MCAL/EXTI/):** External Interrupt module, utilized for handling IR sensor interrupts.
- **[TIMER1](MCAL/TIMER0/):** Timer0 module, employed for controlling PWM signals for Alarm System.
- **[TIMER1](MCAL/TIMER1/):** Timer1 module, employed for controlling PWM signals for ServoMotor.

## Libraries
- **[BIT_MATH.h](Libraries/BIT_MATH.h):** A header file defining common bitwise manipulation macros.
- **[STD_TYPES.h](Libraries/STD_TYPES.h):** A header file defining standard data types.
