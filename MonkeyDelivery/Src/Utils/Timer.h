#pragma once
class Timer{

private:
	static Timer* sInstance;
	
	unsigned int mStartTicks;
	unsigned int mElapsedTicks;

	float mDeltaTime;//tiempo en segundos
	float mTimeScale;//tiempo en milisegundos

public:
	static Timer* Instance();
	static void Release();

	void Reset();
	/// <summary>
	/// Nosa da el tiempo en segundos
	/// </summary>
	/// <returns></returns>
	inline float DeltaTime() { return mDeltaTime; };
	inline void TimeScale(float t) { mTimeScale = t; };
	/// <summary>
	/// tiempo en milisegundos/ticks
	/// </summary>
	/// <returns></returns>
	inline float TimeScale() { return mTimeScale; };
	void Update();

private:
	Timer();
	~Timer();

};

