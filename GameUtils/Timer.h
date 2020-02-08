#ifndef _H_TIMER_
#define _H_TIMER_

#include <memory>

class Timer {
private:
    double m_dSecondsPerCount = 0.0;
    double m_dDeltaTime = -1.0;

    __int64 m_nBaseTime = 0;
    __int64 m_nPausedTime = 0;
    __int64 m_nStopTime = 0;
    __int64 m_nPrevTime = 0;
    __int64 m_nCurrTime = 0;
 
    bool m_bStopped = false;

public:
    static Timer& Instance();

    Timer() = default;
    ~Timer() = default;

    void Initialize();

    float GetTotalTime() const;
    float GetDeltaGame() const;

    void Reset();
    void Start();
    void Stop();
    void Update();
};

#endif // !_H_TIMER_
