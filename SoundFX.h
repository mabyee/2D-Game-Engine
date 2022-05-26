/*
Created by Henri Puennel, W19019002.
This file...
*/
#pragma once
#include "mysoundengine.h"

class SoundFX
{
private:
	int const NUMEXPLOSIONSOUNDS = 5;
	int nextExplosion;
	SoundIndex Explosions[5];
	SoundIndex Shoot;
	SoundIndex Chirp;
	SoundIndex stingerDrop;
	SoundIndex healthPickup;
	SoundIndex AccessDenied;
	SoundIndex Zap;

public:
	void LoadSounds();
	void PlayShot();
	void PlayExplosion();
	void PlayChirp();
	void PlayStingerDrop();
	void PlayHealthPickup();
	void PlayAccessDenied();
	void PlayZap();
};

