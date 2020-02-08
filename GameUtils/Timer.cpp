#include "Timer.h"
#include <Windows.h>

Timer& Timer::Instance() {
    static Timer tTimer;
    return tTimer;
}

float Timer::GetTotalTime() const {
    if (m_bStopped) {
        return static_cast<float>(((m_nStopTime - m_nPausedTime) - m_nBaseTime) * m_dSecondsPerCount);
    } else {
        return static_cast<float>(((m_nCurrTime - m_nPausedTime) - m_nBaseTime) * m_dSecondsPerCount);
    }
}

float Timer::GetDeltaGame() const {
    return static_cast<float>(m_dDeltaTime);
}

void Timer::Initialize() {
    __int64 nCountsPerSec;
    QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&nCountsPerSec));
    m_dSecondsPerCount = 1.0 / static_cast<double>(nCountsPerSec);
}

void Timer::Update() {
    if (m_bStopped) {
        m_dDeltaTime = 0;
        return;
    }

    __int64 nCurTime;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&nCurTime));
    m_nCurrTime = nCurTime;

    m_dDeltaTime = (m_nCurrTime - m_nPrevTime) * m_dSecondsPerCount;

    m_nPrevTime = m_nCurrTime;

    if (m_dDeltaTime < 0.0) {
        m_dDeltaTime = 0.0;
    }
}

void Timer::Reset() {
    __int64 nCurTime;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&nCurTime));
    
    m_nCurrTime = nCurTime;
    m_nPrevTime = nCurTime;
    m_nStopTime = 0;
    m_bStopped = false;
}

void Timer::Start() {
    if (m_bStopped) {
	    __int64 nStartTime;
    	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&nStartTime));

        m_nPausedTime += (nStartTime - m_nStopTime);
        m_nStopTime = 0;
        m_bStopped = false;
    }
}

void Timer::Stop() {
    if (!m_bStopped) {
		__int64 nCurrTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&nCurrTime);
		m_nStopTime = nCurrTime;
        m_bStopped = true;
    }
}
