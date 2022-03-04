#include "Timer.h"
#include "SDL.h"

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

void Timer::Update(){
	mElapsedTicks = SDL_GetTicks()-mStartTicks; //miliseconds
	mDeltaTime = mElapsedTicks * 0.001f; //seconds
}

Timer::Timer(){
	Reset();
	mTimeScale = 1.0f;
}

Timer::~Timer()
{
}
