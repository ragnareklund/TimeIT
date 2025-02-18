#ifndef EDIT_TASK_DIALOG_H_
#define EDIT_TASK_DIALOG_H_

#include "parent_chooser.h"
#include <gtkmm.h>
#include <string>
#include <vector>
#include <edit_task_dialog.h>
#include <libtimeit/db/autotrack_accessor.h>
#include <libtimeit/db/settings_accessor.h>
#include <parent_chooser.h>
#include <IWidget.h>
#include <libtimeit/logic/workspace.h>
#include <libtimeit/db/database.h>
#include <glibmm/i18n.h>

namespace gui
{
using namespace std;
using namespace libtimeit;

class edit_task_dialog: public Gtk::Dialog, public IWidget
{
public:
	edit_task_dialog(database& db);

	void on_ok_button_clicked();
	void on_cancel_button_clicked();
	void on_data_changed();
	void set_task_id(const task_id& id);
	void set_parent(optional<task_id> id);

	// IWidget interface
	void show() override;
	void hide() override;
	void move(int x, int y) override;
	bool is_visible() override;
	void get_position(int& window_x, int& window_y) override;
private:
	void             create_layout();
	void             check_for_changes();
	vector<unsigned> get_ticked_workspaces();
	void             set_ticked_workspaces(vector<unsigned> workspaces );

	Gtk::Label  name_label       {_("Name: ")};
	Gtk::Label  idle_label       {_("Idle time (m): ")};

	Gtk::SpinButton   idle_time_entry;
	Gtk::CheckButton  quiet_button;
	Gtk::HBox         parent_choosing_row;
	Gtk::HBox         name_editing_row;
	Gtk::HBox         idle_editing_row;
	Gtk::HBox         quiet_row;

	Gtk::Table    workspace_table;
	Gtk::Label    workspace_label;
	Gtk::Frame    desktop_frame;

	Gtk::Button   cancel_button   {Gtk::StockID("gtk-revert-to-saved")};
	Gtk::Button   ok_button       {Gtk::StockID("gtk-apply")};
	Gtk::Entry    task_name_entry;

	// This is the Parent in the context "Parent task"
	// The parent could be be "Project A" and the children could then be "Design", "Planning", "Coding".
	// Parent task and child task.
	Gtk::Label    parent_label   {_("Parent: ")};
	parent_chooser_widget parent_chooser;

	string                  name;
	minutes                 idle_time {0min};
	bool                    quiet     {false};
	optional<task_id>       id;
	optional<task_id>       parent_id;

	vector<unsigned> workspaces;

	auto_track_accessor auto_track_table;
	task_accessor       tasks;
	settings_accessor   settings;
	x11_workspace       workspace;

	vector<shared_ptr<Gtk::CheckButton>> check_button;
};
}
#endif /*EDIT_TASK_DIALOG_H_*/
