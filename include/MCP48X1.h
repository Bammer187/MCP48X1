/*
 * SPDX-FileCopyrightText: 2026 Lukas Bammer
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef MCP48X1_H
#define MCP48X1_H

typedef enum {
	MCP4801,
	MCP4811,
	MCP4821
}mcp48x1_type_t;

typedef struct {
	spi_device_handle_t spi_handle;
	mcp48x1_type_t model;
}mcp48x1_t;

#endif