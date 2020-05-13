
#include <obs-module.h>

static const char* my_output_output_getname(void* unused)
{
	UNUSED_PARAMETER(unused);
	return obs_module_text("MyOutput");
}

static void* my_output_create(obs_data_t* settings, obs_output_t* output)
{
	return NULL;
}

static void my_output_destroy(void* data)
{

}

static bool my_output_start(void* data)
{
	return true;
}

static void my_output_stop(void* data, uint64_t ts)
{

}

static void my_output_data(void* data, struct encoder_packet* packet)
{

}

static obs_properties_t* my_output_properties(void* unused)
{
	UNUSED_PARAMETER(unused);

	obs_properties_t* props = obs_properties_create();

	obs_properties_add_text(props, "path",
				obs_module_text("MyOutput.FilePath"),
				OBS_TEXT_DEFAULT);
	return props;
}

static void receive_video(void* param, struct video_data* frame)
{}

static uint64_t my_output_total_bytes(void* data)
{
	return 0;
}

struct obs_output_info my_output =
{
	.id = "my_output",
	.flags = OBS_OUTPUT_VIDEO,
	.get_name = my_output_output_getname,
	.create = my_output_create,
	.destroy = my_output_destroy,
	.start = my_output_start,
	.stop = my_output_stop,
	.raw_video = receive_video,
	.encoded_packet = my_output_data,
	.get_total_bytes = my_output_total_bytes,
};
