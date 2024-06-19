/*
 * @file event_ctrl.cpp
 *
 * @brief Event handling class - registring or unregistring hanler for desired event
 *
 * @date Created on: 27 февр. 2024 г.
 * @author: aso
 */

#include "esp_idf_version.h"

#include <esp_event.h>
#include <esp_log.h>

#include "asemaphore"
#include "event_ctrl.hpp"



#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
    // enable functionality present before in ESP-IDF v5.0
/// @brief convert enum ev_bases to esp_evnt_base_t
esp_event_base_t evbase(ev_bases base)
{
    switch (base)
    {

    case wifi_base:
	return WIFI_EVENT;

    case ip_base:
	return IP_EVENT;

    case any_base:
    default:
	return ESP_EVENT_ANY_BASE;
    }; /* switch event */
}; /* evbase */
#endif	// ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)



//--[ event_ctrl.cpp ]-------------------------------------------------------------------------------------------------
