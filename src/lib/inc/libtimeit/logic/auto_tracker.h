#ifndef AUTO_TRACKER_H_
#define AUTO_TRACKER_H_
#include <iostream>
#include <libtimeit/timer.h>
#include <libtimeit/logic/time_keeper.h>
#include <libtimeit/db/database.h>
#include <libtimeit/db/autotrack_accessor.h>
#include <libtimeit/logic/workspace.h>
#include <climits>

namespace libtimeit
{
using namespace std;

class auto_tracker : public timer_observer
{
public:
	auto_tracker(
			Time_keeper& time_keeper_,
			database&    db,
			Timer&       timer_
			);

private:
	void check_for_changes();
	void do_task_switching(unsigned new_workspace);
	//TimerObserver
	void on_signal_1_second() override;

	unsigned old_workspace {UINT_MAX};

	Time_keeper        &time_keeper;

	auto_track_accessor  auto_track;
	task_accessor        tasks;
	x11_workspace            workspace;
	bool                 old_user_is_active{false};
};

}
#endif /*AUTO_TRACKER_H_*/
