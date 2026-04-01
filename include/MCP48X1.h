/*
 * SPDX-FileCopyrightText: 2026 Lukas Bammer
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef MCP48X1_H
#define MCP48X1_H

#include "driver/spi_master.h"

typedef enum{
	GAIN_2X,
	GAIN_1X,
}mcp48x1_gain_t;

typedef enum {
	MCP4801,
	MCP4811,
	MCP4821
}mcp48x1_type_t;

typedef struct {
	spi_device_handle_t spi_handle;
	mcp48x1_type_t model;
	mcp48x1_gain_t gain;
}mcp48x1_t;


/**
 * @brief Initializes an MCP48x1 DAC device on the SPI bus.
 *
 * This function registers the DAC with the ESP32 SPI master driver and 
 * configures device-specific parameters such as the model and initial gain.
 *
 * @param mcp       Pointer to the mcp48x1_t structure
 * @param host      The SPI host to use
 * @param cs_pin    GPIO number for the Chip Select (CS) line
 * @param model     The MCP model (MCP4801, MCP4811, or MCP4821)
 * @param gain      The default gain factor
 * @param spi_freq  SPI clock frequency in Hz
 * 
 * @return
 * 		- ESP_OK: success 
 * 		- error codes from spi_bus_add_device()
 */
esp_err_t mcp48x1_init(mcp48x1_t *mcp, spi_host_device_t host, int cs_pin, 
                       mcp48x1_type_t model, mcp48x1_gain_t gain, uint32_t spi_freq);

/**
 * @brief Updates the gain factor in the local device structure.
 *
 * @param mcp   Pointer to the mcp48x1_t structure.
 * @param gain  New gain setting (GAIN_1X = 2.048V max, GAIN_2X = 4.096V max).
 */
void mcp_set_gain(mcp48x1_t *mcp, mcp48x1_gain_t gain);

/**
 * @brief Sends a raw digital value to the DAC via SPI.
 *
 * Constructs the 16-bit SPI command including configuration bits (Gain, Shutdown) 
 * and handles LSB alignment based on the specific model's resolution (8, 10, or 12-bit).
 *
 * @param mcp   Pointer to the mcp48x1_t structure.
 * @param data  Raw digital value. Higher values will be masked.
 * 
 * @return
 * 		- ESP_OK: success 
 * 		- error codes from spi_device_transmit()
 */
esp_err_t mcp_set_voltage(mcp48x1_t *mcp, uint16_t data);

/**
 * @brief Sets the output voltage using a float value.
 *
 * @param mcp      Pointer to the mcp48x1_t structure.
 * @param voltage  Desired output voltage in volts.
 * 
 * @return
 * 		- ESP_OK: success 
 * 		- error codes from spi_device_transmit()
 */
esp_err_t mcp_set_voltage_float(mcp48x1_t *mcp, float voltage);

#endif