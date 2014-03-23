/*
 * IdleDialog.h
 *
 *  Created on: 2008-sep-06
 *      Author: hoglet
 */

#ifndef IDLEDIALOG_H_
#define IDLEDIALOG_H_

#include <gtkmm.h>
#include <Timer.h>
#include <IIdleDialog.h>
#include <IWidget.h>
#include <memory>

namespace GUI
{
namespace Internal
{

enum IdleDialogResponse{
	RESPONSE_REVERT=1,
	RESPONSE_REVERTANDCONTINUE =2,
	RESPONSE_CONTINUE=3
} ;

class IdleDialog : public Gtk::Dialog, public TimerObserver, public IIdleDialog, public IWidget
{
public:
	IdleDialog(std::shared_ptr<Timer>& timer);
	virtual void setIdleStartTime(time_t idleStartTime);
	virtual void setActiveTaskList(std::shared_ptr<std::vector<DB::ExtendedTask>> activeTasks);
	virtual ~IdleDialog();
	virtual void attach(IActionObserver*);
	virtual void detach(IActionObserver*);
	// IWidget interface
	virtual void show();
	virtual void hide() { Gtk::Dialog::hide(); }
	virtual void move(int x, int y) { Gtk::Dialog::move(x,y); };
	virtual bool is_visible() { return Gtk::Dialog::is_visible(); } ;
	virtual void get_position(int& Window_x, int& Window_y) { Gtk::Dialog::get_position(Window_x, Window_y); };
private:
	virtual void on_signal_1_second() {};
	virtual void on_signal_10_seconds();
	void setText();
	void updater();
	void run();
	Gtk::Label  text;
	Gtk::Button revertButton;
	Gtk::Button revertAndContinueButton;
	Gtk::Button continueButton;
	std::shared_ptr<Timer> m_timer;
	time_t m_idleStartTime;
	std::string taskString;

	std::list<IActionObserver*> observers;
	void responseHandler(int result);
};

}
}
#endif /* IDLEDIALOG_H_ */
