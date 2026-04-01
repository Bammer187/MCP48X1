# MCP48X1

A lightweight, efficient C driver for the **Microchip MCP4801 (8-bit), MCP4811 (10-bit), and MCP4821 (12-bit)** Digital-to-Analog Converters. This component is designed for the ESP32 series using the ESP-IDF SPI master driver.

## Table of Contents
  - [Features](#features)
  - [Installation](#installation)
  - [License](#license)

## Features
- Supports all variants: MCP4801 (8-bit), MCP4811 (10-bit), and MCP4821 (12-bit).

- Automatic Scaling: Handles bit-alignment (LSB padding) automatically based on the selected model.

- Dual Gain Support: Easy switching between 1x (2.048V) and 2x (4.096V) internal gain.

- Float API: Set voltages directly in Volts without manual bit calculation.

## Installation

### Manual Integration

Copy the source files (`mcp48x1.c`, `mcp48x1.h`, `CMakeLists.txt`) into your project's components or main directory. Ensure the header file is accessible within your include path

### ESP-IDF Component Manager
`idf.py add-dependency "bammer187/mcp48x1^1.0.0"`

### Add as submodule
`git submodule add https://github.com/Bammer187/MCP48X1.git components/mcp48x1`

Don't forget to update your `CMakeLists.txt`!

## License

[MIT License](LICENSE)
