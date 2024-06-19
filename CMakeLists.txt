idf_component_register(SRCS "astring.cpp" "asemaphore.cpp" "sync.cpp" "event_ctrl.cpp"
                    INCLUDE_DIRS .
		    #PRIV_REQUIRES extrstream
		    REQUIRES esp_event #console driver sdmmc spi_flash fatfs cxx
		    )

