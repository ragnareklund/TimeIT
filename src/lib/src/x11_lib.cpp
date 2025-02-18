/*
 * X11Property.cpp
 *
 *  Created on: May 10, 2010
 *      Author: hoglet
 */

#include "libtimeit/x11_lib.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>

namespace libtimeit
{


//LCOV_EXCL_START
x11_lib::x11_lib() : display(XOpenDisplay(nullptr))
{
	root_window = DefaultRootWindow(display); // NOLINT(cppcoreguidelines-pro-type-cstyle-cast,cppcoreguidelines-prefer-member-initializer,cppcoreguidelines-pro-bounds-pointer-arithmetic)
}

x11_lib::~x11_lib()
{
	XCloseDisplay(display);
}

int x11_lib::viewport_width()
{
	Screen *screen = DefaultScreenOfDisplay(display); // NOLINT(cppcoreguidelines-pro-type-cstyle-cast,cppcoreguidelines-pro-bounds-pointer-arithmetic)
	return screen->width;
}

int x11_lib::viewport_height()
{
	Screen *screen = DefaultScreenOfDisplay(display); // NOLINT(cppcoreguidelines-pro-type-cstyle-cast,cppcoreguidelines-pro-bounds-pointer-arithmetic)
	return screen->height;
}


long x11_lib::get_cardinal(const char *name, int offset) noexcept(false)
{
	Atom property_name = XInternAtom(display, name, False);
	Atom property_type = XA_CARDINAL;

	Atom returned_type = 0;
	int  returned_format = 0;
	unsigned long number_of_items = 0;
	unsigned long bytes_after_return = 0;
	unsigned char *returned_data = nullptr;

	long return_value;  // NOLINT

	if (XGetWindowProperty(
			display, root_window, property_name, offset, 1, False, property_type, &returned_type,
			&returned_format, &number_of_items, &bytes_after_return, &returned_data) == Success)
	{
		if (returned_format == 32 && returned_type == property_type && number_of_items > 0) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		{
			return_value = ((long *) returned_data)[0]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic,cppcoreguidelines-pro-type-cstyle-cast)
			XFree(returned_data);
		}
		else
		{
			XFree(returned_data);
			throw general_exception("get_cardinal failed: Unexpected data");

		}
	}
	else
	{
		throw general_exception("get_cardinal failed: XGetWindowProperty failed");
	}
	return return_value;
}

vector<string> x11_lib::get_strings(const char *name) noexcept(false)
{
	Atom property_name = XInternAtom(display, name, False);
	Atom property_type = XInternAtom(display, "UTF8_STRING", False);

	Atom returned_type = 0;
	int  returned_format = 0;
	unsigned long  number_of_items = 0;
	unsigned long  bytes_after_return = 0;
	unsigned char* returned_data=nullptr;
	vector<string> return_values;

	if (XGetWindowProperty(
			display, root_window, property_name, 0, 1024, False, property_type, &returned_type, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			&returned_format, &number_of_items, &bytes_after_return, &returned_data) == Success) // NOLINT(cppcoreguidelines-avoid-magic-numbers)
	{

		if (returned_type == property_type && number_of_items > 0)
		{
			unsigned int pos = 0;
			while (pos < number_of_items)
			{
				string str = (char *) (&returned_data[pos]); // NOLINT(cppcoreguidelines-pro-type-cstyle-cast,cppcoreguidelines-pro-bounds-pointer-arithmetic)
				return_values.push_back(str);
				pos += str.length() + 1;
			}
			XFree(returned_data);
		}
		else
		{
			XFree(returned_data);
			throw general_exception("get_strings failed: Unexpected data");
		}
	}
	else
	{
		throw general_exception("get_cardinal failed: XGetWindowProperty failed");
	}
	return return_values;
}
//LCOV_EXCL_STOP
}