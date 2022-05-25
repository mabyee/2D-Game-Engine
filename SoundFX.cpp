/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "SoundFX.h"

void SoundFX::LoadSounds()
{
	MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();
	Shoot = pSoundEngine->LoadWav(L"Sounds/shoot.wav");
	Thrust = pSoundEngine->LoadWav(L"Sounds/thrustloop2.wav");
	Chirp = pSoundEngine->LoadWav(L"Sounds/chirp.wav");
	healthPickup = pSoundEngine->LoadWav(L"Sounds/healthPickup.wav");
	stingerDrop = pSoundEngine->LoadWav(L"Sounds/stingerDrop.wav");
	Explosions[0] = pSoundEngine->LoadWav(L"Sounds/explosion1.wav");
	Explosions[1] = pSoundEngine->LoadWav(L"Sounds/explosion2.wav");
	Explosions[2] = pSoundEngine->LoadWav(L"Sounds/explosion3.wav");
	Explosions[3] = pSoundEngine->LoadWav(L"Sounds/explosion4.wav");
	Explosions[4] = pSoundEngine->LoadWav(L"Sounds/explosion5.wav");
	AccessDenied = pSoundEngine->LoadWav(L"Sounds/accessDenied.wav");
	Zap = pSoundEngine->LoadWav(L"Sounds/zap.wav");
}

void SoundFX::PlayShot()
{
	MySoundEngine::GetInstance()->Play(Shoot);
}

void SoundFX::PlayExplosion()
{
	MySoundEngine::GetInstance()->Play(Explosions[nextExplosion]);
	nextExplosion++;
	if (nextExplosion >= NUMEXPLOSIONSOUNDS)
	{
		nextExplosion = 0;
	}
}

void SoundFX::StartThrust()
{
	MySoundEngine::GetInstance()->Play(Thrust, true);
}

void SoundFX::StopThrust()
{
	MySoundEngine::GetInstance()->Stop(Thrust);
}

void SoundFX::PlayChirp()
{
	MySoundEngine::GetInstance()->Play(Chirp);
}

void SoundFX::PlayStingerDrop()
{
	MySoundEngine::GetInstance()->Play(stingerDrop);
}

void SoundFX::PlayHealthPickup()
{
	MySoundEngine::GetInstance()->Play(healthPickup);
}

void SoundFX::PlayAccessDenied()
{
	MySoundEngine::GetInstance()->Play(AccessDenied);
}

void SoundFX::PlayZap()
{
	MySoundEngine::GetInstance()->Play(Zap);
}