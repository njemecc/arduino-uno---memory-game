# Memory Game Project

## Overview

This project involves creating a system consisting of 4 buttons and 7 LEDs (5 green, 1 yellow, and 1 red). The goal of the system is to play a sequence repetition game. At the start of the program, a sequence of 2 numbers is generated. This sequence contains numbers from 1 to 4, where each number represents one of the 4 LEDs arranged in order. The sequence is displayed by sequentially lighting up the corresponding LED. After displaying the sequence, the user is required to repeat the sequence by pressing the corresponding buttons. While the user repeats the sequence, a yellow LED should be lit. The user can attempt to repeat the sequence three times. If the user makes a mistake during the first attempt, the red LED should start blinking. If the user makes mistakes three times in a row, the system enters an error state, and the red LED remains constantly on. When the user correctly repeats the sequence, an additional green LED lights up for 1 second, then the sequence expands by one more element, and the process repeats until the user makes three consecutive mistakes.

## Requirements

- Microcontroller: PIC18 or Arduino Uno
- External components: 4 buttons, 7 LEDs
- Usage of at least 2 external interrupts for buttons and timer interrupts for timing measurements
- Implementation of a finite state machine

## Usage

1. Connect the components according to the pin configuration defined in the code.
2. Upload the provided code to the microcontroller.
3. Run the system and follow the game instructions as described above.

## Additional Notes

- Adjust the pin configuration and timing parameters as needed for your specific setup.
- Ensure proper connection of buttons and LEDs to the microcontroller.
- Debug and test the system thoroughly before deploying it in your application.
