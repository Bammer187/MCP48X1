/*
 * SPDX-FileCopyrightText: 2026 Lukas Bammer
 *
 * SPDX-License-Identifier: MIT
 */

#include "MCP48X1.h"

esp_err_t mcp_set_voltage(mcp_48x1_t *mcp, uint16_t data)
{
	uint16_t command = 0;

	command |= (mcp->vref << 13) // GAIN
    command |= (1 << 12); // SHDN = 1

	switch (mcp->model) {
        case MCP4821:
            command |= (data & 0x0FFF); 
            break;
        case MCP4811:
            command |= ((data & 0x03FF) << 2);
            break;
        case MCP4801:
            command |= ((data & 0x00FF) << 4);
            break;
    }

	spi_transaction_t trans = {
        .length = 16,
        .flags = SPI_TRANS_USE_TXDATA,
        .tx_data[0] = (command >> 8) & 0xFF,
        .tx_data[1] = command & 0xFF,
    };

    return spi_device_transmit(mcp->spi_handle, &trans);
}