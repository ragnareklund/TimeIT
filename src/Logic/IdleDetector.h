/*
 * IdleDetector.h
 *
 *  Created on: 2008-aug-27
 *      Author: hoglet
 */

#ifndef IDLEDETECTOR_H_
#define IDLEDETECTOR_H_
#include <Timer.h>
#include <boost/shared_ptr.hpp>
#include <time.h>

class IdleDetector : public TimerObserver
{
public:
	IdleDetector(const boost::shared_ptr<Timer>& timer);
	virtual ~IdleDetector();
	int minutesIdle();
	time_t timeIdle();
	//TimerObserver interface
	virtual void on_signal_1_second() {};
	virtual void on_signal_10_seconds();
	//
private:
	void pollStatus();
	bool IdleDetectionPossible;
	long getTimestamp();
	time_t idleSeconds;
	boost::shared_ptr<Timer> m_timer;
};

#endif /* IDLEDETECTOR_H_ */
