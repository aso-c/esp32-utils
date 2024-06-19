/*@file sync.hpp
 *
 * @brief Syncronization utilily: combined the semaphore cless asemaphore, handler procedure for give the semaphore and event registration for this, header template file
 *
 * @date Created on: 22 февр. 2024 г.
 * @author: aso
 */

#ifndef __SYNC_HPP__
#define __SYNC_HPP__

#if !defined(__cplusplus)
#error File __FILE__ is not intended to use with a pure C
#endif	// __cplusplus



///@brief milliseconds in second
constexpr unsigned int SEC2mSEC = 1000;


inline TickType_t msticks(TickType_t millisec) {
    return millisec * portTICK_PERIOD_MS; }


inline TickType_t secticks(TickType_t sec) {
    return msticks(sec * portTICK_PERIOD_MS); }


namespace event
{

    struct sync: handler::base
    {
	sync(esp_event_base_t ev_base, uint32_t ev, void *data = nullptr): handler::base(ev_base, ev, data) {};

	asemaphore wait;

	///@brief reset/give the inner semaphore
	void instance_handler(void *arg, esp_event_base_t ev_base, int32_t h_event, void *data) override {
	    ESP_LOGI(__PRETTY_FUNCTION__, "Now We Give (Released) the Semaphore");
	    wait.Give();
	}; /* instance_handler() */

	/// Statically implementation of syncronizer
	struct stat: handler::base
	{
		stat(esp_event_base_t ev_base, uint32_t ev, void *data = nullptr): handler::base(ev_base, ev, data) {};

		asemaphore::stat wait;

		///@brief reset/give the inner semaphore
		void instance_handler(void *arg, esp_event_base_t ev_base, int32_t h_event, void *data) override {
		    wait.Give();
		}; /* instance_handler() */
	}; /* event::sync::stat */

    }; /* event::sync */

}; /* namespace event */






#endif /* __SYNC_HPP__ */
