#pragma once
class Timer{

private:
	static Timer* sInstance;

	unsigned int mStartTicks;
	unsigned int mElapsedTicks;

	float mDeltaTime;
	float mTimeScale;

public:
	static Timer* Instance();
	static void Release();

	void Reset();
	inline float DeltaTime() { return mDeltaTime; };
	inline void TimeScale(float t) { mTimeScale = t; };
	inline float TimeScale() { return mTimeScale; };
	void Update();

private:
	Timer();
	~Timer();

};

