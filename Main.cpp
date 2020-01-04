#include <stdio.h>
#include <conio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Music* music;

int volume = 128;

int main(int argc, char* argv[])
{

	if (argc < 2) goto exit_;

	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_Init(MIX_INIT_MID);
	Mix_AllocateChannels(16);

	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);

	Mix_SetSoundFonts(argv[2]);
	music = Mix_LoadMUS(argv[1]);

	printf("Loaded MIDI: %s, SF2: %s\n", argv[1], argv[2]);

	if (music)
	{
		Mix_FadeInMusic(music, 1, 1000);
	}
	else
	{
		printf("Music failed to load!\n");
	}
	printf("Press q to exit playback.\nHit the spacebar to pause/play\nPress R to restart playback.\n");

	printf("Volume: %i%%", Mix_VolumeMusic(-1));

	while (true) {
		char input = _getch();
		if (input == 'q')
		{
			Mix_HaltMusic();
		}
		if (input == 'r')
		{
			Mix_SetMusicPosition(0);
		}
		if (input == ' ')
		{
			if (Mix_PausedMusic()) Mix_ResumeMusic();
			else Mix_PauseMusic();
		}
		if (input == 'i')
		{
			if (volume == 128) continue;
			volume++;
			Mix_VolumeMusic(volume);
			printf("\rVolume: %i%%", Mix_VolumeMusic(-1));
		}
		if (input == 'k')
		{
			if (volume == 1) continue;
			volume--;
			Mix_VolumeMusic(volume);
			printf("\rVolume: %i%% ", Mix_VolumeMusic(-1));
		}
		if (!Mix_PlayingMusic()) break;
	}

	Mix_FreeMusic(music);
exit_:
	Mix_Quit();
	SDL_Quit();

	return 0;
}