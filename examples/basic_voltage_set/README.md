# MCP4821 Example

This example demonstrates how to use the MCP48X1 DAC driver to set a specific 12-bit output voltage.

## Pin Mapping


| MCP4821 Pin | ESP32 Pin (GPIO) | Function          | Notes                               |
| :---------- | :--------------- | :---------------- | :---------------------------------- |
| **VDD**     | 5V               | Power             | Stable 5V Supply                    |
| **VSS**     | GND              | Ground            | Common Ground                       |
| **SCK**     | GPIO 26          | SPI Clock         | -                                   |
| **SDI**     | GPIO 25          | SPI MOSI          | -                                   |
| **CS**      | GPIO 33          | SPI CS            | 10k Pull-up to 3.3V                 |
| **SHDN**    | 5V               | Hardware Shutdown | -                                   |
| **LDAC**    | GND              | Latch DAC         | Updates output channel immediately  |
