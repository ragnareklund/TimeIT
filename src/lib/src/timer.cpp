/*
 * Timer.cpp
 *
 *  Created on: 2008-jul-04
 *      Author: hoglet
 */

#include "libtimeit/timer.h"

namespace libtimeit
{


//LCOV_EXCL_START
Timer_observer::Timer_observer(Timer& publisher) : timer(publisher )
{
	publisher.attach(this);
}


Timer_observer::~Timer_observer()
{
	timer.detach(this);
}

void Timer_observer::on_signal_1_second()
{

}

void Timer_observer::on_signal_10_seconds()
{

}
//LCOV_EXCL_STOP

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::attach(Timer_observer *observer)
{
	observers.push_back(observer);
}

void Timer::detach(Timer_observer *observer)
{
	observers.remove(observer);
}

bool Timer::on_signal_1_second()
{
	signalSender();
	return true;
}

//This function is called every second
void Timer::signalSender()
{
	static int TenSecondCounter = 10;
	TenSecondCounter--;
	bool signal10Seconds = false;
	if (TenSecondCounter < 1)
	{
		signal10Seconds = true;
		TenSecondCounter = 10;
	}
	if (observers.size() > 0)
	{
		for (Timer_observer *observer : observers)
		{
			observer->on_signal_1_second();
			if (signal10Seconds)
			{
				observer->on_signal_10_seconds();
			}
		}
	}

}

}
