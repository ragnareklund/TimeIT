/*
 * StatusIcon.h
 *
 *  Created on: 21-Jun-08
 *      Author: hoglet
 */

#ifndef STATUS_ICON_H_
#define STATUS_ICON_H_

#include <gtkmm.h>

#include "libtimeit/logic/time_keeper.h"
#include <libtimeit/db/task_accessor.h>
#include <libtimeit/db/time_accessor.h>
#include <gui/images.h>
#include "action_observer.h"

namespace gui
{
using namespace libtimeit;

class status_icon_widget: public time_keeper_observer, public event_observer
{
public:
	status_icon_widget(
			Time_keeper&,
			database&,
			notification_manager&   notifier,
			image_cache&     images);

	void show()
	{
	}
	; //Shown directly on creation. Might change
	void attach(action_observer *observer);
	void detach(action_observer *observer);
private:
	void on_activate();
	void set_icon();
	void set_tooltip();
	void on_running_changed() override;

	void on_popup_menu(guint button, guint32 activate_time);
	void toggle_main_window();
	void on_menu_file_popup_quit();
	void on_menu_file_popup_open();
	void on_menu_stop_all_timers();
	void on_menu_about();
	void on_menu_preferences();
	void on_menu_toggle_task1();
	void on_menu_toggle_task2();
	void on_menu_toggle_task3();
	void on_menu_toggle_task4();
	void on_menu_toggle_task5();
	void populate_context_menu();
	void toggle_task(const task_id& id);
	string complete_task_path(const task_id& id);

	void on_task_updated(const task_id& id) override;
	void on_task_name_changed(const task& item) override;
	void on_task_time_changed(const task_id& item) override;

	void on_complete_update() override;
	Glib::RefPtr<Gtk::StatusIcon> status_icon_instance;
	Glib::RefPtr<Gdk::Pixbuf> default_icon;
	Glib::RefPtr<Gdk::Pixbuf> running_icon;
	Glib::RefPtr<Gdk::Pixbuf> idle_icon_small;
	Glib::RefPtr<Gdk::Pixbuf> running_icon_small;

	Gtk::Menu menu_popup;
	Time_keeper&  m_time_keeper;
	task_accessor tasks;
	time_accessor times;

	std::list<action_observer*> observers;
	std::vector<task_id> latest_tasks;

};

}
#endif /* STATUS_ICON_H_ */
