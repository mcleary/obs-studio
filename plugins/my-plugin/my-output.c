
#include <obs-module.h>
#include <util/threading.h>

struct image_sequence_output
{
	obs_output_t* output;
	volatile bool active;

	pthread_t start_thread;

	uint64_t total_bytes;

	os_event_t* stop_event;
};

static const char* image_sequence_output_getname(void* unused)
{
	UNUSED_PARAMETER(unused);
	return obs_module_text("ImageSequence");
}

static void* image_sequence_output_create(obs_data_t* settings, obs_output_t* output)
{
	UNUSED_PARAMETER(settings);

	struct image_sequence_output* data = bzalloc(sizeof(struct image_sequence_output));
	data->output = output;

	if (os_event_init(&data->stop_event, OS_EVENT_TYPE_AUTO) != 0)
		goto fail;

	return data;

fail:
	os_event_destroy(data->stop_event);
	bfree(data);
	return NULL;
}

static void image_sequence_output_destroy(void* data)
{
	struct image_sequence_output* output = data;
	if (output) {
		os_event_destroy(output->stop_event);
		bfree(data);
	}
}

static bool image_sequence_output_start(void* data)
{
	struct image_sequence_output* output = data;
	obs_output_begin_data_capture(output->output, 0);
	return true;
}

static void image_sequence_output_stop(void* data, uint64_t ts)
{
	(void) data;
}

static void YUV_to_RGB(uint8_t y, uint8_t u, uint8_t v, uint8_t* r, uint8_t* g, uint8_t* b)
{
	int32_t c = y - 16;
	int32_t d = u - 128;
	int32_t e = v - 128;

	*r = clip((int32_t) (298 * c + 409 * e + 128) >> 8);
	*g = clip((int32_t) (298 * c - 100 * d - 208 * e + 128) >> 8);
	*b = clip((int32_t) (298 * c + 516 * d + 128) >> 8);
}

static void receive_video(void* param, struct video_data* frame)
{
	blog("%d\n", frame->data[0]);

	uint32_t width, height;

	/*if (data->video->codec->pix_fmt == AV_PIX_FMT_NV12) {
		uint8_t *LumaData = frame->data[0];
		uint8_t *ChromaData = frame->data[1];

		for (size_t RowIndex = 0; RowIndex < height; ++RowIndex) {
			size_t ChromaRowIndex = RowIndex / 2;

			uint8_t *LumaLine = &LumaData[RowIndex * width];
			uint8_t *ChromaLine =
				&ChromaData[ChromaRowIndex * width];

			for (size_t ColumnIndex = 0; ColumnIndex < width;
			     ++ColumnIndex) {
				size_t ChromaColumnIndex = ColumnIndex / 2;

				uint8_t Y = LumaLine[ColumnIndex];
				uint8_t U =
					ChromaLine[ChromaColumnIndex * 2 + 0];
				uint8_t V =
					ChromaLine[ChromaColumnIndex * 2 + 1];

				uint8_t R, G, B;
				YUV_to_RGB(Y, U, V, &R, &G, &B);

				fprintf(out, "%d %d %d\n", R, G, B);
			}
		}
	}*/
}

static uint64_t image_sequence_output_total_bytes(void* data)
{
	return 1024;
}

struct obs_output_info my_output =
{
	.id = "image_sequence_output",
	.flags = OBS_OUTPUT_VIDEO,
	.get_name = image_sequence_output_getname,
	.create = image_sequence_output_create,
	.destroy = image_sequence_output_destroy,
	.start = image_sequence_output_start,
	.stop = image_sequence_output_stop,
	.raw_video = receive_video,
	.get_total_bytes = image_sequence_output_total_bytes,
};
