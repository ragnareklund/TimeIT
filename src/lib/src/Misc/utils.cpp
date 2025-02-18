#include <libtimeit/utils.h>
#include <sys/types.h>
#include <libtimeit/os_abstraction.h>
#include <ctime>
#include <iomanip>
#include <langinfo.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <cstring>
#include <fmt/core.h>
#include <fmt/ranges.h>

//using namespace Glib;
using namespace std;

namespace libtimeit
{
constexpr auto SECOND_PER_DAY = 24 * 60 * 60;

//LCOV_EXCL_START

string ISO_639_language_string()
{
	string return_value = setlocale(LC_ALL, nullptr);
	return_value = return_value.substr(0, 2);
	return return_value;
}

time_point<system_clock> beginning_of_day( time_point<system_clock> time_stamp)
{
	auto raw_time = system_clock::to_time_t(time_stamp);
	struct tm *time_info = localtime(&raw_time);
	time_info->tm_sec = 0;
	time_info->tm_min = 0;
	time_info->tm_hour = 0;
	time_info->tm_isdst = -1;
	auto result = mktime(time_info);
	return system_clock::from_time_t(result);
}

time_t beginning_of_day( time_t raw_time)
{
	auto time_stamp = system_clock::from_time_t(raw_time);
	auto result     = beginning_of_day(time_stamp);
	return system_clock::to_time_t(result);
}

time_t end_of_day( time_t raw_time)
{
	auto time_stamp = system_clock::from_time_t(raw_time);
	auto result     = end_of_day(time_stamp);
	return system_clock::to_time_t(result);
}

time_point<system_clock> end_of_day( time_point<system_clock> time_stamp)
{
	auto raw_time = system_clock::to_time_t(time_stamp);
	struct tm * time_info = localtime(&raw_time);
	time_info->tm_sec = 59;  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_min = 59;  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_hour = 23; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_isdst = -1;
	auto result = mktime(time_info);
	return system_clock::from_time_t(result);
}


int get_day_of_week(time_t raw_time)
{
	struct tm *time_info = localtime(&raw_time);
	int dow = time_info->tm_wday;
	int return_value = dow;

	int week_starts_on_day = *(nl_langinfo(_NL_TIME_FIRST_WEEKDAY)) - 1;
	return_value = return_value - week_starts_on_day;
	if (return_value < 0)
	{
		return_value = return_value + 7; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	}
	return return_value;
}

time_t beginning_of_week( time_t raw_time)
{
	long day_of_week = get_day_of_week(raw_time);
	time_t bow = raw_time - (day_of_week) * SECOND_PER_DAY;
	struct tm * time_info = localtime(&bow);
	time_info->tm_sec = 0;
	time_info->tm_min = 0;
	time_info->tm_hour = 0;
	time_info->tm_wday = 1;
	time_info->tm_isdst = -1;
	return mktime(time_info);
}

time_t end_of_week( time_t raw_time)
{

	long day_of_week = get_day_of_week(raw_time);
	time_t eow = raw_time + (6 - day_of_week) * SECOND_PER_DAY;  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	struct tm * time_info = localtime(&eow);
	time_info->tm_sec = 59;   // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_min = 59;   // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_hour = 23;  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_isdst = -1;
	return mktime(time_info);
}
time_t beginning_of_month( time_t raw_time)
{
	struct tm *time_info = localtime(&raw_time);
	time_info->tm_sec = 0;
	time_info->tm_min = 0;
	time_info->tm_hour = 0;
	time_info->tm_mday = 1;
	time_info->tm_isdst = -1;
	return mktime(time_info);
}
time_t end_of_month( time_t raw_time)
{
	struct tm *time_info = localtime(&raw_time);
	time_info->tm_sec = 59;    // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_min = 59;    // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_hour = 23;   // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_mday = days_in_month(raw_time);
	time_info->tm_isdst = -1;
	return mktime(time_info);
}



time_point<system_clock> beginning_of_year( time_point<system_clock> time_stamp)
{
	auto raw_time = system_clock::to_time_t(time_stamp);
	struct tm *time_info = localtime(&raw_time);
	time_info->tm_sec = 0;
	time_info->tm_min = 0;
	time_info->tm_hour = 0;
	time_info->tm_mday = 1;
	time_info->tm_mon = 0;
	time_info->tm_isdst = -1;
	auto temp_result = mktime(time_info);
	return system_clock::from_time_t( temp_result );
}

time_t beginning_of_year( time_t raw_time)
{
	auto result = beginning_of_year( system_clock::from_time_t(raw_time) );
	return system_clock::to_time_t( result );
}
time_t end_of_year( time_t raw_time)
{
	struct tm *time_info = localtime(&raw_time);
	time_info->tm_sec = 59;    // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_min = 59;    // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_hour = 23;   // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_mday = 31;   // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_mon = 11;    // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_isdst = -1;
	return mktime(time_info);
}

int days_in_month( time_t raw_time)
{
	struct tm *time_info = localtime(&raw_time);
	time_info->tm_sec = 59;    // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_min = 59;    // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_hour = 23;   // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	switch (time_info->tm_mon)
	{
	case 1:
		if ((time_info->tm_year % 4 == 0 && time_info->tm_year % 100 != 0) || time_info->tm_year % 400 == 0) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		{
			time_info->tm_mday = 29; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
		else
		{
			time_info->tm_mday = 28; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		}
		break;
	case 3:
	case 5:    // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	case 8:    // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	case 10:   // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		time_info->tm_mday = 30;  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		break;
	default:
		time_info->tm_mday = 31;  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		break;
	}
	return time_info->tm_mday;
}

static const int YEAR_ZERO = 1900;

time_t to_time(int year, int month, int day, int hour, int min, int sec)
{
	time_t raw_time = 0;
	time(&raw_time);
	struct tm*	time_info = localtime(&raw_time);
	time_info->tm_year = year - YEAR_ZERO;  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	time_info->tm_mon = month;
	time_info->tm_mday = day;
	time_info->tm_hour = hour;
	time_info->tm_min = min;
	time_info->tm_sec = sec;
	time_info->tm_isdst = -1;
	return mktime(time_info);
}

bool is_on_different_days( time_t one, time_t other)
{
	struct tm one_time = *localtime(&one);
	struct tm other_time = *localtime(&other);
	return one_time.tm_year != other_time.tm_year || one_time.tm_mon != other_time.tm_mon || one_time.tm_mday != other_time.tm_mday;
}

string day_of_week_abbreviation( time_t raw_time)
{
	struct tm *time_info = localtime(&raw_time);
	array<char,15> abbreviation{};              // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	int length = (int)strftime(abbreviation.data(), abbreviation.size(), "%a", time_info);
	return length>0 ? abbreviation.data() : "☼";
}


string hh_mm( seconds time_span )
{
	if( time_span >= minutes( 1) )
	{
		auto hh = duration_cast<hours>(time_span);
		auto mm = duration_cast<minutes>( time_span - hh );
		return fmt::format("{:02}:{:02}", hh.count(), mm.count());
	}
	return "";
}

string seconds_2_hhmm(int64_t s)
{
	stringstream return_value;
	auto hours = s / (60 * 60);  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	s -= hours * (60 * 60);      // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	auto minutes = s / 60;      // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	if( hours < 10 )            // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	{
		return_value << "\u2007";
	}
	return_value << hours << " h ";
	if (minutes < 10) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	{
		return_value <<  "\u2007";
	}
	return_value << minutes << " m";

	return return_value.str();
}

string small_numbers(const string& s)
{
	stringstream return_value;
	for (auto c: s)
	{
		switch (c) {
			case '0': return_value << "₀"; break;
			case '1': return_value << "₁"; break;
			case '2': return_value << "₂"; break;
			case '3': return_value << "₃"; break;
			case '4': return_value << "₄"; break;
			case '5': return_value << "₅"; break;
			case '6': return_value << "₆"; break;
			case '7': return_value << "₇"; break;
			case '8': return_value << "₈"; break;
			case '9': return_value << "₉"; break;
			case '-': return_value << "₋"; break;
			default: return_value << c;
		}
	}
	return return_value.str();
}


string date_string(time_point<system_clock> time_stamp)
{
	auto raw_time = system_clock::to_time_t(time_stamp);
	auto day = *localtime(&raw_time);
	stringstream date_string;
	date_string << (day.tm_year + YEAR_ZERO)   // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	<< "-"
	<< setfill('0') << setw(2) << day.tm_mon + 1
	<< "-"
	<< setfill('0') << setw(2) << day.tm_mday;
	return date_string.str();
}


string date_string(time_t raw_time)
{
	auto time_stamp = system_clock::from_time_t(raw_time);
	return  date_string(time_stamp);
}

string time_span_string( time_t from, time_t to)
{
	stringstream return_value;
	struct tm from_time = *localtime(&from);
	struct tm to_time = *localtime(&to);
	return_value << "\u2003"
	             << setfill('0') << setw(2) << from_time.tm_hour
	             << ":"
	             << setfill('0') << setw(2) << from_time.tm_min
	             << " → ";
	if (is_on_different_days(from,to))
	{
		return_value << (to_time.tm_year + YEAR_ZERO)  // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		             << "-"
					 << setfill('0') << setw(2) << to_time.tm_mon + 1
					 << "-"
					 << setfill('0') << setw(2) << to_time.tm_mday << " ";
	}
	return_value << setfill('0') << setw(2) << to_time.tm_hour
	             << ":"
	             << setfill('0') << setw(2) << to_time.tm_min;
	return return_value.str();
}

string duration_string( time_t from, time_t to)
{
	stringstream return_value;
	return_value <<" = " << seconds_2_hhmm((int64_t)difftime(to, from))
	             <<" ";
	return return_value.str();
}

string idling_string( time_t to, time_t next)
{
	stringstream return_value;
	auto to_next_min = (int64_t)difftime(next, to) / 60;    // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	return_value << "⇣ " << small_numbers(to_string(to_next_min)) << " ₘ";
	return return_value.str();
}

time_t now()
{
	return time(nullptr);
}

int safe_strcpy(char* dest, const char* src, size_t size)
{
	if(src == nullptr || dest == nullptr || size==0)
	{
		return 1;
	}
	auto src_len= strlen(src);
	if(src_len<size)
	{
		memcpy(dest, src, src_len+1);
		return 0;
	}
	return 2;
}


[[maybe_unused]] uint64_t milliseconds_since_epoch()
{
	struct timeval tv{};
	gettimeofday(&tv, nullptr);

	return uint64_t(tv.tv_sec) * 1000 + tv.tv_usec / 1000; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
}

string_view trim_left(string_view str)
{
	auto pos(str.find_first_not_of(" \t\n\r\f\v"));
	str.remove_prefix(std::min(pos, str.length()));
	return str;
}

string_view trim_right(string_view str)
{
	auto pos(str.find_last_not_of(" \t\n\r\f\v"));
	str.remove_suffix(std::min(str.length() - pos - 1, str.length()));
	return str;
}

string_view trim(string_view str)
{

	return trim_right(trim_left(str));
}

string abbreviate_string(string_view original, long unsigned i)
{
	constexpr string_view DOTS = " ...";
	string result(trim(original));
	auto end_of_first_line = result.find('\n');

	if(
		end_of_first_line == string::npos &&
		result.length() < i
			)
	{
		return result;
	}

	auto cut_position = min(end_of_first_line, i - DOTS.length()) ;
	result = result.substr(0,cut_position);
	result.append(DOTS);

	return result;
}

optional<task_id> optional_task_id(const string& basic_string)
{
	auto optional_uuid = UUID::from_string(basic_string);
	if( optional_uuid.has_value())
	{
		return task_id(optional_uuid.value());
	}
	return {};
}

}
