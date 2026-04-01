/*
 * SPDX-FileCopyrightText: 2026 Lukas Bammer
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef MCP48X1_H
#define MCP48X1_H

#include "driver/spi_master.h"

typedef enum{
	GAIN_1X,
	GAIN_2X,
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

esp_err_t mcp48x1_init(mcp48x1_t *mcp, 
                       spi_host_device_t host, 
                       int cs_pin, 
                       mcp48x1_type_t model, 
                       mcp48x1_gain_t gain,
                       uint32_t spi_freq);

void mcp_set_vref(mcp_48x1_t *mcp, mcp48x1_gain_t vref);

esp_err_t mcp_set_voltage(mcp_48x1_t *mcp, uint16_t data);

#endif