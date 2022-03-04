#include "Timer.h"
#include "SDL.h"

Timer* Timer::sInstance = nullptr;

Timer* Timer::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Timer();
	} 
	return sInstance;
}

void Timer::Release(){
	delete sInstance;
	sInstance = nullptr;
}

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
