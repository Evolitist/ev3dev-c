#include "ev3_speaker.h"

#include <stdio.h>

#include "ev3.h"

#define PATH_TONE   "/sys/devices/platform/snd-legoev3/tone"
#define PATH_VOLUME "/sys/devices/platform/snd-legoev3/volume"

void speaker_play_tone(int freq, int timeMs)
{
	if(freq < 30 || freq >= 8000 || timeMs <= 0) return;
	char path[] = PATH_TONE;
	char str[17];
	sprintf(str, "%d %d", freq, timeMs);
	ev3_write_char_array(path, str);
}

void speaker_set_volume(int vol)
{
	if(vol < 0 || vol > 100) return;
	char path[] = PATH_VOLUME;
	ev3_write_int(path, vol);
}

int speaker_get_volume()
{
	char path[] = PATH_VOLUME;
	int buf = 0;
	ev3_read_int(path, &buf);
	return buf;
}
