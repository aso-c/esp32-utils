/*@file event_ctrl.hpp
 *
 * @brief Event handling classes - operating with event handlers for specified event
 *
 * @date Created on: 27 февр. 2024 г.
 * @author: aso
 */

#ifndef __EVENT_CTRL_HPP__
#define __EVENT_CTRL_HPP__

#if !defined(__cplusplus)
#error File __FILE__ is not intended to use with a pure C
#endif	// __cplusplus


#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
    // enable functionality present before in ESP-IDF v5.0
/// @brief convert enum ev_bases to esp_evnt_base_t

/// Enum for const definitions of the Event base values
enum ev_bases {any_base, wifi_base, ip_base};

///@brief convert enum ev_bases to esp_evnt_base_t
esp_event_base_t evbase(ev_bases base);

#endif	// ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)


namespace event
{

    namespace handler
    {

	///@brief pure virtual prototype for the event handling class; create public derived class for real handling the events
	class pure_base
	{
	public:

	    virtual void instance_handler(void *arg, esp_event_base_t base,
    				int32_t h_event, void *data) = 0;
	    virtual ~pure_base() {};
	}; /* handler::pure_base */




	///@brief pure virtual prototype for the event handling class with inner instance stored; derive public class for real handling the events with inner instance
	class base: public pure_base
	{
	public:
	    base(esp_event_base_t bas, uint32_t ev, void *data = nullptr): ev_base(bas), event(ev), arg(data) {};

	    esp_event_base_t ev_base;
	    uint32_t event;
	    void *arg;
	    esp_event_handler_instance_t instance = nullptr;

	}; /* handler::base */



	///@brief pure virtual prototype for the event handling class for user's event loop; derive public class for real handling events
	class loop_base: public base
	{
	public:
	    loop_base(esp_event_loop_handle_t lp, esp_event_base_t bas, uint32_t ev, void *data = nullptr): base(bas, ev, data), loop(lp){};

	    esp_event_loop_handle_t loop;
	}; /* handler::loop_base */

    }; /* namespace handler */



    ///@brief class for operating with event handlers witch explicit specification instance
    /// register or unregister handler & implement unique handler for each exemplar
    /// of the derived class from the event_handler_base;
    template <auto &handler>
    struct ctrl
    {
	///@brief Register event handler for default system loop
	/// all register values are values from instance parameters of the handling event in the handler object
	static esp_err_t enroll() {
	    return enroll(handler.ev_base, handler.event, handler.arg); };
	///@brief Register event handler for default system loop
	/// all register values are defined as procedure parameters, but default values is a stored values from instanceparameters of the handling event in the handler object
	static esp_err_t enroll(esp_event_base_t base, int32_t event = handler.event, void* data = handler.arg) {
	    return esp_event_handler_instance_register(base, event, implement_handler, data, &handler.instance); };

	///@brief Register event handler for default system loop
	/// all register values are defined as procedure parameters, but default values is a stored values from instanceparameters of the handling event in the handler object
	static esp_err_t enroll(void* data) {
	    return enroll(handler.ev_base, handler.event, data); };

	///@brief Unregister event handler for default system loop & full stored parameters of the handling event in the handler object
	static esp_err_t unreg() {
	    return unreg(handler.ev_base, handler.event);};

	///@brief Unregister event handler for default system loop & full stored parameters of the handling event in the handler object
	static esp_err_t unreg(esp_event_base_t base, int32_t event) {
	    esp_err_t err = esp_event_handler_instance_unregister(base, event, handler.instance);
	    handler.instance = nullptr;
	    return err;};


	///@brief Register event handler for specified loop
	/// all register values are defined as procedure parameters, but default values is a stored values from instanceparameters of the handling event in the handler object
	static esp_err_t enroll_to() {
//	    return esp_event_handler_instance_register_with(handler.loop, handler.ev_base, handler.event, implement_handler, data, &instance); };
	    return enroll_to(handler.loop, handler.ev_base, handler.event, handler.arg, &handler.instance); };

	///@brief Register event handler for specified loop
	/// all register values are defined as procedure parameters, but default values is a stored values from instanceparameters of the handling event in the handler object
	static esp_err_t enroll_to(esp_event_loop_handle_t loop) {
	    return enroll_to(loop, handler.ev_base, handler.event, handler.arg); };

	///@brief Register event handler for specified loop
	/// all register values are defined as procedure parameters, but default values is a stored values from instanceparameters of the handling event in the handler object
	static esp_err_t enroll_to(esp_event_loop_handle_t loop, void* data) {
	    return enroll_to(loop, handler.ev_base, handler.event, data); };

	///@brief Register event handler for specified loop
	/// all register values are defined as procedure parameters, but default values is a stored values from instanceparameters of the handling event in the handler object
	static esp_err_t enroll_to(esp_event_base_t base, int32_t event) {
	    return enroll_to(handler.loop, base, event, handler.arg); };

	///@brief Register event handler for specified loop
	/// all register values are defined as procedure parameters, but default values is a stored values from instanceparameters of the handling event in the handler object
	static esp_err_t enroll_to(esp_event_loop_handle_t loop, esp_event_base_t base, int32_t event) {
	    return enroll_to(loop, base, event, handler.arg); };

	///@brief Register event handler for specified loop
	/// all register values are defined as procedure parameters, but default values is a stored values from instanceparameters of the handling event in the handler object
	static esp_err_t enroll_to(esp_event_base_t base, int32_t event, void* data) {
	    return enroll_to(handler.loop, base, event, data); };

	///@brief Register event handler for specified loop
	/// all register values are defined as procedure parameters, but default values is a stored values from instanceparameters of the handling event in the handler object
	static esp_err_t enroll_to(esp_event_loop_handle_t loop, esp_event_base_t base,	int32_t event, void* data) {
	    return esp_event_handler_instance_register_with(loop, base, event, implement_handler, data, &handler.instance); };


	///@brief Unregister event handler for default system loop & full stored parameters of the handling event in the handler object
	static esp_err_t unreg_from() {
	    return unreg_from(handler.loop, handler.ev_base, handler.event); };

	///@brief Unregister event handler for default system loop & full stored parameters of the handling event in the handler object
	static esp_err_t unreg_from(esp_event_loop_handle_t loop) {
	    return unreg_from(loop, handler.ev_base, handler.event, handler.instance); };

	///@brief Unregister event handler for default system loop & full stored parameters of the handling event in the handler object
	static esp_err_t unreg_from(esp_event_base_t base, int32_t event) {
	    return unreg_from(handler.loop, base, event); };

	///@brief Unregister event handler for default system loop & full stored parameters of the handling event in the handler object
	static esp_err_t unreg_from(esp_event_loop_handle_t loop, esp_event_base_t base, int32_t event) {
	    esp_err_t err = esp_event_handler_instance_unregister_with(loop, base, event, handler.instance);
	    handler.instance = nullptr;
	    return err;};


	///@brief automatically control for the event hadlers: register event handler at the create object and unregister it at destroy
	struct automatic
	{

	    automatic(bool reg = false): handle_ref(handler), registered(reg) {if (reg) enroll(); };
	    ~automatic() { if (registered) ctrl::unreg(); };

	    esp_err_t enroll() { registered = true; return ctrl::enroll(); };
	    esp_err_t unreg()  { registered = false; return ctrl::unreg(); };

//	    auto & handle_ref;
	    typeof(handler) handle_ref;

	protected:
	    bool registered;

	}; /* struct automatic */

    protected:
	static void implement_handler(void *arg, esp_event_base_t base,
					int32_t h_event, void *data);

    }; /* event::ctrl */

    template <auto &handler>
    void ctrl<handler>::implement_handler(void *arg, esp_event_base_t base,
					int32_t event, void *data) {
	handler.instance_handler(arg, base, event, data);
    }; /* event::ctrl<handler>::implement_handler() */


}; /* namespace event */



#endif /* __EVENT_CTRL_HPP__ */
