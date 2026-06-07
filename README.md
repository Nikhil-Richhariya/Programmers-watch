# ESP32 Minimalist 10-LED Binary Watch
A minimalist, Wi-Fi-synchronized binary clock built with an ESP32. This project fetches the exact time from an NTP server and displays it using pure binary math, driven directly by the ESP32's GPIO pins without the need for complex multiplexing or external shift registers.

📉 The Design Evolution: From 71 to 10 LEDs
The core philosophy of this project was hardware minimalism. The design went through three major iterations to reduce the component count, wiring complexity, and power draw, ultimately arriving at a perfectly optimized 10-LED layout.

## Phase 1: The 71-LED Behemoth
The initial concept was a traditional analog-style ring layout using discrete LEDs:

12 LEDs for the hours.

59 LEDs for the individual minutes.

Total: 71 LEDs.

The Problem: The ESP32 does not have anywhere near 71 available GPIO pins. This design required multiple daisy-chained shift registers (like the 74HC595), complex breadboard wiring, and a massive physical footprint. It was too bulky to be considered a "watch."

## Phase 2: The 24-LED Compromise
To reduce the hardware overhead, the minute display was grouped into 5-minute intervals:

1 LED for Hour's first digit 
9 LED for Hour's second digit
5 LED for Minute's first digit 
9 LED for Minute's first digit

Total: 24 LEDs.

The Problem: While smaller, 24 LEDs still maxed out the safe usable pins on the ESP32. It required avoiding essential strapping pins and boot pins, making the wiring incredibly cramped and frustrating for a breadboard prototype. It also lost the precision of showing the exact minute.

## Phase 3: True Binary Zen (10 LEDs)
By completely abandoning base-10 analog representations and embracing the way the microcontroller actually "thinks," the hardware was drastically simplified:

4 LEDs for Hours (1 to 12): Represented in binary up to 1100.

6 LEDs for Minutes (0 to 59): Represented in binary up to 111011.

Total: 10 LEDs.

The Solution: A perfect fit. Exactly 10 safe, non-interfering GPIO pins can be used. No shift registers, no matrices, no complex wiring. Just 10 LEDs, 10 resistors, and the ESP32.

## Features
NTP Synchronization: Automatically fetches the precise time over Wi-Fi (No RTC module required).

Direct GPIO Drive: No shift registers or external driver chips needed.

Timezone Configurable: Easily adjust standard time and daylight saving offsets in the code.

Breadboard Friendly: Fits easily on standard development breadboards using the common ground rail technique.

##  Hardware Requirements
1x ESP32 Development Board

10x LEDs (Recommended: 4 Red for Hours, 6 Green for Minutes)

10x Resistors (220Ω or 330Ω)

Jumper Wires & Breadboard

##  How to Read the Watch
The time is displayed in a 12-hour format across two arrays. Read the LEDs from left to right (Most Significant Bit to Least Significant Bit).

Hour Row Values: 8 | 4 | 2 | 1

Minute Row Values: 32 | 16 | 8 | 4 | 2 | 1

Example:
If the Hour LEDs show ON | OFF | ON | OFF (8 + 2) = 10
If the Minute LEDs show ON | OFF | ON | ON | OFF | ON (32 + 8 + 4 + 1) = 45
The time is 10:45.
