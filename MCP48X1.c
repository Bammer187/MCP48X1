/*
 * SPDX-FileCopyrightText: 2026 Lukas Bammer
 *
 * SPDX-License-Identifier: MIT
 */

#include "MCP48X1.h"

esp_err_t mcp48x1_init(mcp48x1_t *mcp, 
                       spi_host_device_t host, 
                       int cs_pin, 
                       mcp48x1_type_t model, 
                       mcp48x1_gain_t gain,
                       uint32_t spi_freq)
{
    if (mcp == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    mcp->model = model;
    mcp->gain = gain;

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = spi_freq,
        .mode = 0,
        .spics_io_num = cs_pin,
        .queue_size = 7,
        .flags = SPI_DEVICE_NO_DUMMY,
    };

    esp_err_t ret = spi_bus_add_device(host, &devcfg, &mcp->spi_handle);
    
    return ret;
}

void mcp_set_gain(mcp_48x1_t *mcp, mcp48x1_gain_t gain)
{
    mcp->gain = gain;
}

esp_err_t mcp_set_voltage(mcp_48x1_t *mcp, uint16_t data)
{
	uint16_t command = 0;

	command |= (mcp->gain << 13) // GAIN
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
