#include <obs-module.h>

/* Defines common functions (required) */
OBS_DECLARE_MODULE()

/* Implements common ini-based locale (optional) */
OBS_MODULE_USE_DEFAULT_LOCALE("my-plugin", "en-US")

// extern struct obs_source_info  my_source;  /* Defined in my-source.c  */
extern struct obs_output_info  my_output;  /* Defined in my-output.c  */
// extern struct obs_encoder_info my_encoder; /* Defined in my-encoder.c */
// extern struct obs_service_info my_service; /* Defined in my-service.c */

bool obs_module_load(void)
{
//	obs_register_source(&my_source);
	obs_register_output(&my_output);
//	obs_register_encoder(&my_encoder);
//	obs_register_service(&my_service);
	return true;
}
