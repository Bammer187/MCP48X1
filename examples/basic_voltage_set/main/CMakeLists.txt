idf_component_register(
                    SRCS "basic_voltage_set.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_driver_spi
                    PRIV_REQUIRES mcp48x1)
