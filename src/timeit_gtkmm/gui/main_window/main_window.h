#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <gtkmm.h>
#include <IWidget.h>
#include <main_window/main_window.h>
#include "task_list.h"
#include <libtimeit/db/extended_task.h>
#include <libtimeit/db/settings_accessor.h>
#include "summary_views.h"
#include "about_dialog.h"
#include "details.h"
#include "menu.h"
#include "toolbar.h"
#include "calendar.h"

namespace gui
{
using namespace libtimeit;
using namespace std;

class main_window : public Gtk::Window, public action_observer, public IWidget
{
public:
	~main_window() override;
	main_window(
			database &db,
			Time_keeper &timeKeeper,
			notification_manager &notifier,
			window_manager &window_manager,
			image_cache &images);
	main_window(const main_window &) = delete;
	main_window(main_window &&) = delete;
	main_window &operator=(const main_window &) = delete;
	main_window &operator=(main_window &&) = delete;

	// IWidget interface
	void show() override
	{
		Gtk::Window::deiconify();
		Gtk::Window::show();
	}

	void hide() override
	{
		Gtk::Window::hide();
	}

	bool is_visible() override
	{
		return Gtk::Window::is_visible();
	};

	void move(int x, int y) override
	{
		Gtk::Window::move(x, y);
	};

	void get_position(int &Window_x, int &Window_y) override
	{
		Gtk::Window::get_position(Window_x, Window_y);
	};

	virtual void attach(summary_observer* observer);
	virtual void detach(summary_observer* observer);
	void attach(action_observer* /*observer*/) override;
	void detach(action_observer* /*observer*/) override;

	calendar_widget &get_calendar();

	void on_show() override;
	void on_running_tasks_changed();

private:
	//Action observer
	void on_action_task_selection_changed(optional<task_id> selected_task_id) override;
	void on_action_remove_task() override;

	virtual void on_settings_changed(string name);


//	virtual void on_selection_changed(int64_t id, time_t startTime, time_t stopTime) {};
//	virtual void on_showDetailsClicked(ISummary* summary, int64_t taskId, time_t startTime, time_t stopTime);
	//
	void create_layout();
	void relate_widgets();
	void set_calendar();

	void default_layout();
	void classic_layout();
	void save_size();

	static void remove_children(Container &container);
	void empty_containers();
	void do_layout();

	task_list_widget task_list;
	day_summary_widget day_summary;
	week_summary_widget week_summary;
	month_summary_widget month_summary;
	year_summary_widget year_summary;
	calendar_widget calendar;
	Gtk::Notebook summary_tabs;

	menu_bar menubar;
	toolbar_widget toolbar;

	Gtk::ScrolledWindow task_list_container;
	Gtk::ScrolledWindow day_summary_container;
	Gtk::Label label_day;
	Gtk::ScrolledWindow week_summary_container;
	Gtk::Label label_week;
	Gtk::ScrolledWindow month_summary_container;
	Gtk::Label label_month;
	Gtk::ScrolledWindow year_summary_container;
	Gtk::Label label_year;
	Gtk::ScrolledWindow details_window;
	Gtk::VPaned v_paned;
	details details_view;

	Gtk::VBox secondary_v_box; //on right side
	Gtk::HPaned h_paned;
	Gtk::Statusbar statusbar;
	Gtk::VBox main_v_box;

	time_accessor times;
	extended_task_accessor tasks;
	settings_accessor settings;
	vector<summary*> summaries;
};
}
#endif // MAIN_WINDOW_HPP_
