#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "AutoTrackerTest.h"
#include "AutoTracker.h"

#include "Mock/MockTimeKeeper.h"
#include "Mock/MockDatabase.h"

namespace Test
{

class AutoTrackerTest
{
public:
	AutoTrackerTest() :
			timeKeeper(std::shared_ptr<ITimeKeeper>(new MockTimeKeeper())), database(
					std::shared_ptr<IDatabase>(new MockDatabase()))
	{
		tracker = new AutoTracker(timeKeeper, database, timer);
	}

	~AutoTrackerTest()
	{
		delete tracker;
	}

private:
	AutoTracker* tracker;
	Timer timer;
	std::shared_ptr<ITimeKeeper> timeKeeper;
	std::shared_ptr<IDatabase> database;

};

void WorkspaceSwitchTest()
{
	AutoTrackerTest test;
	/*		database->get
	 set task 2 to start on workspace 2
	 set workspace 1
	 Check no starts
	 Set workspace 2
	 Check that task 2 was started
	 ASSERTM("Write test", false);
	 */
}

cute::suite make_suite_AutoTrackerTest()
{
	cute::suite s;
	//s.push_back(CUTE(WorkspaceSwitchTest));
	return s;
}

}

