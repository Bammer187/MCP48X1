/*
 * SPDX-FileCopyrightText: 2026 Lukas Bammer
 *
 * SPDX-License-Identifier: MIT
 */

#include "freertos/FreeRTOS.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "mcp48x1.h"

#define SCL_GPIO  26
#define SDI_GPIO  25
#define CS_GPIO   33

#define MCP_SPI_HOST SPI2_HOST

static const char *TAG = "MCP_TEST";

uint32_t spi_freq = 10 * 1000 * 1000; // 10 MHz

void app_main(void)
{
    spi_bus_config_t buscfg = {
        .mosi_io_num = SDI_GPIO,
        .sclk_io_num = SCL_GPIO,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };

    esp_err_t ret = spi_bus_initialize(MCP_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "BUS INIT COMPLETE");

    mcp48x1_t mcp;

    ret = mcp48x1_init(&mcp, MCP_SPI_HOST, CS_GPIO, MCP4821, GAIN_2X, spi_freq);
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "MCP INIT COMPLETE");

    uint32_t counter = 0;
    while(1) {
        if(counter >= 4000) counter = 0;
        mcp_set_voltage(&mcp, counter);
        ESP_LOGI(TAG, "DAC VALUE: %d", counter);
        counter = counter + 10;
        vTaskDelay(pdMS_TO_TICKS(500));
    }
} 