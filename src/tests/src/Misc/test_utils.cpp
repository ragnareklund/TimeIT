#include <gtest/gtest.h>
#include <ctime>
#include <libtimeit/utils.h>


TEST( Utils, testGetDaysInMonth )
{
	time_t rawtime = libtimeit::to_time(2013, 0, 2, 2, 2, 2);
	ASSERT_EQ( 31, libtimeit::days_in_month(rawtime) ) << "Days in January";
	rawtime = libtimeit::to_time(2013, 1, 2, 2, 2, 2);
	ASSERT_EQ( 28, libtimeit::days_in_month(rawtime) ) << "Days in February 2013";
	rawtime = libtimeit::to_time(2016, 1, 2, 2, 2, 2);
	ASSERT_EQ( 29, libtimeit::days_in_month(rawtime) ) << "Days in February 2016";
	rawtime = libtimeit::to_time(2013, 2, 2, 2, 2, 2);
	ASSERT_EQ( 31, libtimeit::days_in_month(rawtime) ) << "Days in March 2013";
	rawtime = libtimeit::to_time(2013, 3, 2, 2, 2, 2);
	ASSERT_EQ( 30, libtimeit::days_in_month(rawtime) ) << "Days in April 2013";
	rawtime = libtimeit::to_time(2013, 4, 2, 2, 2, 2);
	ASSERT_EQ( 31, libtimeit::days_in_month(rawtime) ) << "Days in May 2013";
	rawtime = libtimeit::to_time(2013, 5, 2, 2, 2, 2);
	ASSERT_EQ( 30, libtimeit::days_in_month(rawtime) ) << "Days in June 2013";
	rawtime = libtimeit::to_time(2013, 6, 2, 2, 2, 2);
	ASSERT_EQ( 31, libtimeit::days_in_month(rawtime) ) << "Days in July 2013";
	rawtime = libtimeit::to_time(2013, 7, 2, 2, 2, 2);
	ASSERT_EQ( 31, libtimeit::days_in_month(rawtime) ) << "Days in August 2013";
	rawtime = libtimeit::to_time(2013, 8, 2, 2, 2, 2);
	ASSERT_EQ( 30, libtimeit::days_in_month(rawtime) ) << "Days in September 2013";
	rawtime = libtimeit::to_time(2013, 9, 2, 2, 2, 2);
	ASSERT_EQ( 31, libtimeit::days_in_month(rawtime) ) << "Days in October 2013";
	rawtime = libtimeit::to_time(2013, 10, 2, 2, 2, 2);
	ASSERT_EQ( 30, libtimeit::days_in_month(rawtime) ) << "Days in November 2013";
	rawtime = libtimeit::to_time(2013, 4, 2, 2, 2, 2);
	ASSERT_EQ( 31, libtimeit::days_in_month(rawtime) ) << "Days in December 2013";
}

TEST( Utils, convertSecondsToStrings )
{
	int timespan2 = 2 * 60 * 60 + 4 * 60;
	ASSERT_EQ(  std::string("\u20072 h 04 m"), libtimeit::seconds_2_hhmm(timespan2) ) <<
																					  "Converting 2 hours and 4 minutes into a txt string";
}

TEST( Utils, convertTimespanToString )
{
	time_t start = libtimeit::to_time(2013, 0, 4, 11, 0, 0);
	time_t stop = libtimeit::to_time(2013, 0, 4, 12, 0, 0);
	std::string result = libtimeit::time_span_string(start, stop);
	std::string expected = "\u200311:00 → 12:00";
	ASSERT_EQ( expected, result ) << "Converting a time span of one hour into a txt string";

	start = libtimeit::to_time(2012, 0, 4, 11, 0, 0);
	stop = libtimeit::to_time(2013, 0, 4, 12, 0, 0);
	result = libtimeit::time_span_string(start, stop);
	expected = " 11:00 → 2013-01-04 12:00";
	ASSERT_EQ( expected, result ) << "Converting a time span of one year into a txt string";
}

TEST( Utils, dayEnd )
{
	time_t testPoint = libtimeit::to_time(2013, 0, 4, 12, 0, 0);
	time_t eod = libtimeit::end_of_day(testPoint);
	struct tm *end_of_day = localtime(&eod);
	ASSERT_EQ( 113, end_of_day->tm_year ) << "Check year";
	ASSERT_EQ(   0, end_of_day->tm_mon )  << "Check month";
	ASSERT_EQ(   4, end_of_day->tm_mday ) << "Check day";
	ASSERT_EQ(  23, end_of_day->tm_hour ) << "Check hour";
	ASSERT_EQ(  59, end_of_day->tm_min )  << "Check minute";
	ASSERT_EQ(  59, end_of_day->tm_sec )  << "Check seconds";
}

TEST( Utils, beginingOfDay )
{
	time_t testPoint = libtimeit::to_time(2013, 0, 4, 12, 0, 0);
	time_t eod = libtimeit::beginning_of_day(testPoint);
	struct tm *end_of_day = localtime(&eod);
	ASSERT_EQ( 113, end_of_day->tm_year ) << "Check year";
	ASSERT_EQ(   0, end_of_day->tm_mon )  << "Check month";
	ASSERT_EQ(   4, end_of_day->tm_mday ) << "Check day";
	ASSERT_EQ(   0, end_of_day->tm_hour ) << "Check hour";
	ASSERT_EQ(   0, end_of_day->tm_min )  << "Check minute";
	ASSERT_EQ(   0, end_of_day->tm_sec )  << "Check seconds";
}

TEST( Utils, beginingOfWeek )
{
	setlocale(LC_ALL, "C");
	time_t testPoint = libtimeit::to_time(2013, 0, 4, 12, 0, 0);
	time_t eod = libtimeit::beginning_of_week(testPoint);
	struct tm *beginningOfWeek = localtime(&eod);
	ASSERT_EQ( 0, beginningOfWeek->tm_sec )    << "Check seconds";
	ASSERT_EQ( 0, beginningOfWeek->tm_min )    << "Check minute";
	ASSERT_EQ( 0, beginningOfWeek->tm_hour )   << "Check hour";
	ASSERT_EQ( 0, beginningOfWeek->tm_wday )   << "Check day of week";
	ASSERT_EQ( 30, beginningOfWeek->tm_mday)   << "Check day of month";
	ASSERT_EQ( 11, beginningOfWeek->tm_mon )   << "Check month";
	ASSERT_EQ( 112, beginningOfWeek->tm_year ) << "Check year";
}

TEST( Utils, endOfWeek )
{
	setlocale(LC_ALL, "C");
	time_t testPoint = libtimeit::to_time(2013, 0, 4, 12, 0, 0);
	time_t eod = libtimeit::end_of_week(testPoint);
	struct tm *end_of_day = localtime(&eod);
	ASSERT_EQ( 59, end_of_day->tm_sec )   << "Check seconds";
	ASSERT_EQ( 59, end_of_day->tm_min )   << "Check minute";
	ASSERT_EQ( 23, end_of_day->tm_hour )  << "Check hour";
	ASSERT_EQ( 5, end_of_day->tm_mday )   << "Check day of month";
	ASSERT_EQ( 59, end_of_day->tm_sec )   << "Check seconds";
	ASSERT_EQ( 0, end_of_day->tm_mon)     << "Check month";
	ASSERT_EQ( 113, end_of_day->tm_year ) << "Check year";
}

void Utils_endOfWeek2()
{
	time_t testPoint = libtimeit::to_time(2013, 0, 6, 12, 0, 0);
	time_t eod = libtimeit::end_of_week(testPoint);
	struct tm *end_of_day = localtime(&eod);
	ASSERT_EQ(  59, end_of_day->tm_sec )  << "Check seconds";
	ASSERT_EQ(  59, end_of_day->tm_min )  << "Check minute";
	ASSERT_EQ(  23, end_of_day->tm_hour ) << "Check hour";
	ASSERT_EQ(   6, end_of_day->tm_mday ) << "Check day of month";
	ASSERT_EQ(  59, end_of_day->tm_sec )  << "Check seconds";
	ASSERT_EQ(   0, end_of_day->tm_mon )  << "Check month";
	ASSERT_EQ( 113, end_of_day->tm_year ) << "Check year" ;
}
void Utils_beginningOfMonth()
{
	time_t testPoint = libtimeit::to_time(2013, 0, 4, 12, 0, 0);
	time_t eod = libtimeit::beginning_of_month(testPoint);
	struct tm *end_of_day = localtime(&eod);
	ASSERT_EQ( 113, end_of_day->tm_year ) << "Check year";
	ASSERT_EQ(   0, end_of_day->tm_mon )  << "Check month" ;
	ASSERT_EQ(   1, end_of_day->tm_mday ) << "Check day";
	ASSERT_EQ(   0, end_of_day->tm_hour ) << "Check hour";
	ASSERT_EQ(   0, end_of_day->tm_min )  << "Check minute";
	ASSERT_EQ(   0, end_of_day->tm_sec )  << "Check seconds";
}

TEST( Utils, endOfMonth )
{
	time_t testPoint = libtimeit::to_time(2013, 0, 4, 12, 0, 0);
	time_t eod = libtimeit::end_of_month(testPoint);
	struct tm *end_of_day = localtime(&eod);
	ASSERT_EQ( 113, end_of_day->tm_year ) << "Check year";
	ASSERT_EQ(   0, end_of_day->tm_mon )  << "Check month";
	ASSERT_EQ(  31, end_of_day->tm_mday ) << "Check day";
	ASSERT_EQ(  23, end_of_day->tm_hour)  << "Check hour";
	ASSERT_EQ(  59, end_of_day->tm_min)   << "Check minute";
	ASSERT_EQ(  59, end_of_day->tm_sec)   << "Check seconds";
}


TEST( Utils, beginningOfYear )
{
	time_t testPoint = libtimeit::to_time(2013, 0, 4, 12, 0, 0);
	time_t eod = libtimeit::beginning_of_year(testPoint);
	struct tm *end_of_day = localtime(&eod);
	ASSERT_EQ( 113, end_of_day->tm_year ) << "Check year";
	ASSERT_EQ(   0, end_of_day->tm_mon )  << "Check month";
	ASSERT_EQ(   1, end_of_day->tm_mday ) << "Check day";
	ASSERT_EQ(   0, end_of_day->tm_hour ) << "Check hour";
	ASSERT_EQ(   0, end_of_day->tm_min )  << "Check minute";
	ASSERT_EQ(   0, end_of_day->tm_sec )  << "Check seconds";
}

TEST( Utils, endOfYear )
{
	time_t testPoint = libtimeit::to_time(2013, 0, 4, 12, 0, 0);
	time_t eod = libtimeit::end_of_year(testPoint);
	struct tm *end_of_day = localtime(&eod);
	ASSERT_EQ( 113, end_of_day->tm_year ) << "Check year";
	ASSERT_EQ(  11, end_of_day->tm_mon  ) << "Check month";
	ASSERT_EQ(  31, end_of_day->tm_mday ) <<"Check day";
	ASSERT_EQ(  23, end_of_day->tm_hour ) << "Check hour";
	ASSERT_EQ(  59, end_of_day->tm_min )  << "Check minute";
	ASSERT_EQ(  59, end_of_day->tm_sec )  << "Check seconds";
}


