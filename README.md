# ESP32-S3 Weather Station

## Project Overview

This project is an embedded weather station developed for the ELTC H3023 Interfacing Assignment 2026.

The system uses an ESP32-S3 microcontroller to read atmospheric pressure and temperature from a BMP280 sensor and display the results on a TFT screen. A KY-023 joystick will be used to navigate between different pages.

## Hardware

- ESP32-S3-DevKitC-1
- BMP280 Pressure and Temperature Sensor
- GMT020-02-7P TFT Display (ST7789)
- KY-023 Analog Joystick

## Software

- Visual Studio Code
- PlatformIO
- C++
- Git and GitHub

## Development Progress

### Stage 1 — TFT Display
Status: Working

The TFT display has been connected to the ESP32-S3 and tested.

### Stage 2 — BMP280 Sensor
Status: Not started

Connect the sensor using I2C and read pressure and temperature measurements.

### Stage 3 — Joystick
Status: Not started

Read joystick movements and detect button presses.

### Stage 4 — Menu System
Status: Not started

Create an interactive menu with pressure and temperature pages.

### Stage 5 — Elevation Tracking
Status: Not started

Implement sea-level pressure calibration and calculate elevation.

### Stage 6 — Schematic and PCB
Status: Not started

Design the circuit schematic and custom PCB layout.

## Git Branches

- `main` — Stable version of the project.

Feature branches will be created as development progresses.

## Project Status

Currently working on the TFT display and preparing BMP280 integration.