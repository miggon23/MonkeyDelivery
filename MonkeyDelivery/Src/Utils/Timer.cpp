#include "Timer.h"
#include "SDL.h"
#include <iostream>

Timer* Timer::sInstance = nullptr;
/// <summary>
/// Crear la instancia del timer
/// </summary>
/// <returns></returns>
Timer* Timer::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Timer();
	} 
	return sInstance;
}
/// <summary>
/// Elimina el timer
/// </summary>
void Timer::Release(){
	delete sInstance;
	sInstance = nullptr;
}
/// <summary>
/// Resetea el timer
/// </summary>
void Timer::Reset(){
	mStartTicks = SDL_GetTicks();
	mElapsedTicks = 0;
	mDeltaTime = 0.0f;
}

float Timer::TimeScale(){
	mTimeScale = SDL_GetTicks() - startGame;
	return mTimeScale;
}

void Timer::Update(){
	mElapsedTicks = SDL_GetTicks()-mStartTicks; //miliseconds
	mDeltaTime = mElapsedTicks * 0.001f; //seconds
	//std::cout << mTimeScale << std::endl;
	//mTimeScale += mDeltaTime*0.005f;
	mTimeScale = SDL_GetTicks() - startGame;
	std::cout << mTimeScale << std::endl;
}

Timer::Timer(){
	Reset();
	mTimeScale = 1.0f;
	startGame = SDL_GetTicks();
}

Timer::~Timer()
{
}
