/*
 * DaySummary.h
 *
 *  Created on: 2008-jul-12
 *      Author: hoglet
 */

#ifndef SUMMARY_H_
#define SUMMARY_H_

#include <gtkmm.h>
#include <libtimeit/db/time_accessor.h>
#include <libtimeit/db/database.h>
#include <libtimeit/db/task_accessor.h>

namespace gui
{

using namespace libtimeit;
using namespace std;

class summary;

class summary_observer
{

public:
	summary_observer() = default;
	summary_observer(const summary_observer &) = delete;
	summary_observer(summary_observer &&) = delete;
	summary_observer &operator=(const summary_observer &) = delete;
	summary_observer &operator=(summary_observer &&) = delete;
	virtual ~summary_observer();
	virtual void on_selection_changed(optional<task_id> id, time_t startTime, time_t stopTime) = 0;

	virtual void on_show_details_clicked(const task_id& /*task_id*/, time_t /*start_time*/, time_t /*stop_time*/)
	{};
	void attach(summary* subject);
	void detach(summary* subject);
private:
	bool unsubscription_allowed{true};
	std::list<summary*> subjects;
};


class summary : public Gtk::TreeView, public event_observer
{
public:
	summary(database &db, notification_manager &notifier);
	void set_references(Gtk::Calendar &calendar);
	optional<task_id> selected_id();

	time_t get_start_time() const
	{
		return start_time;
	}

	time_t get_stop_time() const
	{
		return stop_time;
	}

	void attach(summary_observer* /*observer*/);
	void detach(summary_observer* /*observer*/);
	bool on_focus(Gtk::DirectionType direction) override;

protected:
	void init();
	time_t active_day = 0; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
	time_t start_time = 0; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
	time_t stop_time = 0;  // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)

private:
	Gtk::TreeModel::Row add(const task_id& id);
	Gtk::Menu menu_popup;

	bool on_button_press_event(GdkEventButton* event) override;

	//SummaryObserver
	virtual void on_selection_changed();

	//
	void connect_signals();
	void on_date_changed();
	void on_menu_show_details();
	void on_task_updated(const task_id& id) override;
	void on_task_removed(const task& /*item*/) override;
	void on_complete_update() override;
	void on_task_name_changed(const task& /*item*/) override;
	void on_task_time_changed(const task_id& id) override;
	void populate();
	void empty();
	virtual void calculate_time_span() = 0;
	Gtk::TreeModel::iterator find_row(const task_id& id);
	Gtk::TreeModel::iterator sub_search(const task_id& id, Gtk::TreeModel::Children children);
	void assign_values_to_row(Gtk::TreeModel::Row &row, task &task_, time_t total_time) const;

	Glib::RefPtr<Gtk::TreeStore> tree_model;

	class model_columns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		model_columns()
		{

			add(col_id);
			add(col_name);
			add(col_time);
		};
		Gtk::TreeModelColumn<task_id> col_id;
		Gtk::TreeModelColumn<Glib::ustring> col_name;
		Gtk::TreeModelColumn<Glib::ustring> col_time;
	};

	Glib::RefPtr<Gtk::TreeSelection> ref_tree_selection;
	model_columns columns;
	Gtk::Calendar* calendar = nullptr;


	std::list<summary_observer*> observers;
	time_accessor times;
	task_accessor tasks;

	bool is_visible();
	bool needs_re_population = true;

	inline static optional<task_id> global_id;
	void try_set_selection();
};

}
#endif /* SUMMARY_H_ */
