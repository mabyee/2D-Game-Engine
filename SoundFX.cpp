/*
Created by Henri Puennel, W19019002.
This file...
*/
#include "SoundFX.h"

void SoundFX::LoadSounds()
{
	MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();
	Shoot = pSoundEngine->LoadWav(L"shoot.wav");
	Thrust = pSoundEngine->LoadWav(L"thrustloop2.wav");
	Alarm = pSoundEngine->LoadWav(L"alert.wav");
	Chirp = pSoundEngine->LoadWav(L"chirp.wav");
	healthPickup = pSoundEngine->LoadWav(L"healthPickup.wav");
	stingerDrop = pSoundEngine->LoadWav(L"stingerDrop.wav");
	Explosions[0] = pSoundEngine->LoadWav(L"explosion1.wav");
	Explosions[1] = pSoundEngine->LoadWav(L"explosion2.wav");
	Explosions[2] = pSoundEngine->LoadWav(L"explosion3.wav");
	Explosions[3] = pSoundEngine->LoadWav(L"explosion4.wav");
	Explosions[4] = pSoundEngine->LoadWav(L"explosion5.wav");
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

void SoundFX::StartAlarm()
{
	MySoundEngine::GetInstance()->Play(Alarm);
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