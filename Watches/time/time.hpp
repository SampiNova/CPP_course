#pragma once
#include <iostream>

//////////////////////////////////////////
//                                      //
//        TIME CLASS REALISATION        //
//                                      //
//////////////////////////////////////////

class Time {
private:
	int _id;
	static unsigned count;
	static unsigned actual_id;
	static bool simple_output;
protected:
	int _seconds;
	int _minutes;
	int _hours;
public:
	Time() noexcept;
	~Time();
	Time(const Time& t) noexcept;
	Time(int sec, int min, int hr);

	int to_seconds();
	void normalize();

	void set_seconds(int sec);
	void set_minutes(int min);
	void set_hours(int hr);

	int get_seconds() const noexcept;
	int get_minutes() const noexcept;
	int get_hours() const noexcept;

	Time& operator+=(const Time& t);
	Time& operator+=(int s);
	Time& operator-=(const Time& t);
	Time& operator-=(int s);
};

Time operator+(const Time &t1, const Time &t2);
Time operator+(const Time &t, int s);
Time operator-(const Time &t1, const Time &t2);
Time operator-(const Time &t, int s);

bool operator==(const Time &t1, const Time &t2);
bool operator!=(const Time &t1, const Time &t2);

std::ostream& operator<<(std::ostream& out, const Time& t);
std::istream& operator>>(std::istream& in, Time& t);
