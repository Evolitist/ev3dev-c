#ifndef EV3_SPEAKER_H
#define EV3_SPEAKER_H

#ifdef __cplusplus
extern "C" {
#endif

void speaker_play_tone(int freq, int timeMs);
void speaker_set_volume(int vol);
int speaker_get_volume();

#ifdef __cplusplus
}
#endif

#endif

