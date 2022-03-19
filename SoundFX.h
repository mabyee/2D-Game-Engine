#pragma once
#include "mysoundengine.h"

class SoundFX
{
private:
	int const NUMEXPLOSIONSOUNDS = 5;
	int nextExplosion;
	SoundIndex Explosions[5];
	SoundIndex Thrust;
	SoundIndex Shoot;
	SoundIndex Alarm;
	SoundIndex Chirp;
public:
	void LoadSounds();
	void PlayShot();
	void PlayExplosion();
	void StartThrust();
	void StopThrust();
	void StartAlarm();
	void PlayChirp();
};

