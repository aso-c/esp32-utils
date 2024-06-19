/**
 * @file asemaphore.cpp
 *
 * @brief Envelope on the ESP semaphores api
 *
 *	Need pre-included including file semphr.h
 *
 * @date   Created on: 25 февр. 2024 г.
 * @author aso
 */


#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <esp_log.h>

#include "asemaphore"



//--[ class asemaphore_base ]------------------------------------------------------------------------------------------
///@brief Base of the asemapfore types;


///@brief Destructor for Base of the asemapfore types; clear the semaphore handler
asemaphore_base::~asemaphore_base()
{
    free();
}; /* asemaphore_base::~asemaphore_base() */


///@brief initialize semaphore as the binary semaphore
///@parameter [in] opened	- is the created semaphore are opened at the initial state?
bool asemaphore_base::Init(bool opened)
{
    instance = InitBinCore();
    if (opened)
	Give();

    return created();
} /* bool asemaphore_base::Init(bool) */


///@brief Take (block) the semaphore
BaseType_t asemaphore_base::Take(TickType_t ticks)
{
    // Initialize semaphore as binary semaphore if it is not initialized
    if (!created())
	InitBinary();

    ESP_LOGW("asemaphore::Take(ticks)", "Take the semaphore handle with brake ticks is %lu", ticks);
    BaseType_t res = xSemaphoreTake(instance, ticks);
    return res;
}; /* asemaphore_base::Take(TickType_t) */

///@brief Give (release) the semaphore
BaseType_t asemaphore_base::Give()
{
    // Initialize semaphore as binary semaphore if it is not initialized
    if (!created())
	InitBinary();

    BaseType_t tmp = xSemaphoreGive(instance);
    return tmp;
//    return xSemaphoreGive(instance);
}; /* asemaphore_base::Give() */


///@brief Get current count value if the semaphore is a counting semaphore
UBaseType_t asemaphore_base::count()
{
    return created()? uxSemaphoreGetCount(instance): -1;
}; /* asemaphore_base::count() */


///@brief clear/delete semaphore handler; after it - semaphore is in not created state
void asemaphore_base::del()
{
    if (created())
	vSemaphoreDelete(instance);
    instance = nullptr;
}; /* asemaphore_base::del() */



//--[ class asemaphore ]-----------------------------------------------------------------------------------------------

///@brief Create the binary semaphore
///@parameter [in] waited - if true, semafore is not opened (released) after creation
asemaphore::asemaphore(bool opened)
{
    Init(opened);
}; /* asemaphore::asemaphore(bool) */

///@brief Create the binary semaphore
///@parameter [in] init	- is the created semaphore are opened at the initial state?
asemaphore::asemaphore(semaphore::init init)
{
    Init(init);
    ESP_LOGW("asemaphore::asemaphore(semaphore::init)", "Semaphore handle was %s", created()? "Created": "Not created");
}; /* asemaphore::asemaphore(semaphore::init) */

///@brief Create the counting semaphore
///@parameter [in] maxc  - maximum count value that can be reached: when the semaphore reaches this value it can no longer be ‘given’.
///@parameter [in] initc - initial count value assigned to the semaphore
asemaphore::asemaphore(UBaseType_t maxc, UBaseType_t initc)
{
    ESP_LOGW("asemaphore::asemaphore(maxc, initc)", "Semaphore handle was %s", created()? "Created": "Not created");
    Init(maxc, initc);
}; /* asemaphore::asemaphore(UBaseType_t, UBaseType_t) */


///@brief Create the counting semaphore
///@parameter [in] maxc  - maximum count value that can be reached: when the semaphore reaches this value it can no longer be ‘given’.
///@parameter [in] initc - initial count value assigned to the semaphore
bool asemaphore::Init(UBaseType_t maxc, UBaseType_t initc)
{
    instance = xSemaphoreCreateCounting(maxc, initc);
    return created();
}; /* asemaphore::Init(UBaseType_t, UBaseType_t) */


///@brief core of initializing binary semaphore - simply create of it & return result
///@parameter [in] opened	- is the created semaphore are opened at the initial state?
SemaphoreHandle_t asemaphore::InitBinCore()
{
    return xSemaphoreCreateBinary();
}; /* asemaphore::InitBinCore() */



//--[ class asemaphore::stat ]-----------------------------------------------------------------------------------------


///@brief Create the binary semaphore
///@parameter [in] opened	- is the created semaphore are opened at the initial state?
asemaphore::stat::stat(bool opened)
{
    Init(opened);
    ESP_LOGW("asemaphore::stat::stat(bool)", "Semaphore handle was %s", created()? "Created": "Not created");
}; /* asemaphore::asemaphore(bool) */

///@brief Create the binary semaphore with the enum semaphore::init
///@parameter [in] init	- is the created semaphore are opened at the initial state?
asemaphore::stat::stat(semaphore::init init)
{
    Init(init);
    ESP_LOGW("asemaphore::stat::stat(semaphore::init)", "Semaphore handle was %s", created()? "Created": "Not created");
}; /* asemaphore::stat::stat(semaphore::init) */

///@brief Create the counting semaphore
///@parameter [in] maxc  - maximum count value that can be reached: when the semaphore reaches this value it can no longer be ‘given’.
///@parameter [in] initc - initial count value assigned to the semaphore
asemaphore::stat::stat(UBaseType_t maxc, UBaseType_t initc)
{
    Init(maxc, initc);
    ESP_LOGW("asemaphore::stat::stat(UBaseType_t, UBaseType_t)", "Semaphore handle was %s", created()? "Created": "Not created");
}; /* asemaphore::asemaphore(UBaseType_t, UBaseType_t) */



///@brief Create the counting semaphore
///@parameter [in] maxc  - maximum count value that can be reached: when the semaphore reaches this value it can no longer be ‘given’.
///@parameter [in] initc - initial count value assigned to the semaphore
bool asemaphore::stat::Init(UBaseType_t maxc, UBaseType_t initc)
{
    instance = xSemaphoreCreateCountingStatic(maxc, initc, &body);
    return created();
}; /* asemaphore::stat::Init(UBaseType_t, UBaseType_t) */


///@brief core of initializing binary semaphore - simply create of it & return result
///@parameter [in] opened	- is the created semaphore are opened at the initial state?
SemaphoreHandle_t asemaphore::stat::InitBinCore()
{
    return xSemaphoreCreateBinaryStatic(&body);
}; /* asemaphore::stat::InitBinCore() */


//-[ EoF asemaphore.cpp ]----------------------------------------------------------------------------------------------
