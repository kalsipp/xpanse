#pragma once
#include "../basics/timer.hpp"
namespace transition {

class Transition {
public:
	Transition() = 0;
	virtual ~Transition();
	virtual void start() {}
	virtual bool transit() {return false;}
	virtual void stop() {}
private:
};

class AfterTime: public Transition {
public:
	AfterTime(float duration);
	virtual void start() override;
	virtual void transit() override;
private:
	float m_duration;
	Timer m_timer;
}

class NoTransition: public Transition {};

}