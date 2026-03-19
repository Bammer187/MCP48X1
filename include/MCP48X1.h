/*
 * SPDX-FileCopyrightText: 2026 Lukas Bammer
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef MCP48X1_H
#define MCP48X1_H

#include "driver/spi_master.h"

typedef enum{
	VREF_INTERNAL,
	VREF_EXTERNAL,
}mcp48x1_gain_t;

typedef enum {
	MCP4801,
	MCP4811,
	MCP4821
}mcp48x1_type_t;

typedef struct {
	spi_device_handle_t spi_handle;
	mcp48x1_type_t model;
	mcp48x1_gain_t vref;
}mcp48x1_t;

esp_err_t mcp_set_voltage(mcp_48x1_t *mcp, uint16_t data);

#endif