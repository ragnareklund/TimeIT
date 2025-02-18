#ifndef WINDOW_MANAGER_H_
#define WINDOW_MANAGER_H_

#include <libtimeit/db/database.h>
#include <libtimeit/logic/time_keeper.h>
#include <libtimeit/timer.h>
#include <gtkmm.h>
#include "IWidget.h"
#include "status_icon.h"
#include <gui/images.h>

namespace gui
{
using namespace libtimeit;
using namespace std;

enum EWidget
{
	MAIN_WINDOW,
	ADD_TASK_DIALOG,
	ABOUT_DIALOG,
	EDIT_TASK_DIALOG,
	ADD_TIME,
	IDLE_DIALOG,
	PREFERENCE_DIALOG,
	MAX_WIDGETS
};

using WidgetPtr = std::shared_ptr<IWidget>;

class window_manager
{
public:
	window_manager(Time_keeper&, database &database, Timer& timer, notification_manager& notifier, image_cache& images_);
	virtual WidgetPtr get_widget(EWidget widget);
	virtual status_icon_widget& get_status_icon();

	void manage_lifespan(shared_ptr<Gtk::Dialog> dialog);
	void quit();
private:
	WidgetPtr add_task_instance;
	WidgetPtr about_dialog_instance;
	WidgetPtr main_window_instance;
	WidgetPtr edit_task_dialog_instace;
	WidgetPtr add_time_dialog_instace;
	WidgetPtr preference_dialog_instance;

	void on_main_window_hide();
	void on_add_task_dialog_hide();
	void on_about_dialog_response(int);
	void on_edit_task_hide();
	void on_preference_dialog_hide();

	static void on_dialog_response(Gtk::Dialog* dialog);
	void on_dialog_hide(Gtk::Dialog* dialog);


	Time_keeper& time_keeper;
	database&    db;
	Timer&       timer;
	notification_manager&    notifier;
	image_cache&      images;
	list<shared_ptr<Gtk::Dialog>> active_dialogs;
};
}
#endif /* WINDOW_MANAGER_H_ */
