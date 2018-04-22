
#include "comparatorCoordinated.h"
#include <cassert>

#include "nrf_drv_comp.h"


void eventHandler(nrf_comp_event_t event) {

}

// default configuration
// won't compile in c++
//const nrf_drv_comp_config_t defaultConfig NRF_DRV_COMP_DEFAULT_CONFIG(NRF_COMP_INPUT_0);

void ComparatorCoordinated::init() {

	ret_code_t error = nrf_drv_comp_init(nullptr,	// use default config
	                                     eventHandler);
	if (error != NRF_SUCCESS) {
		assert(false);
	}

}


void ComparatorCoordinated::start() {
	// No events, no shortcuts
    nrf_drv_comp_start(0, 0);
}


unsigned int ComparatorCoordinated::sample() {
	return nrf_drv_comp_sample();
}
