#pragma once
#include <iostream>

class Time {
private:
	int _seconds;
	int _minutes;
	int _hours;
	static unsigned count;
public:
	Time();
	~Time();
	Time(const Time &t);
	Time(int sec, int min, int hr);

	int to_seconds();
	void normalize();

	void set_seconds(int sec);
	void set_minutes(int min);
	void set_hours(int hr);

	int get_seconds() const;
	int get_minutes() const;
	int get_hours() const;

	Time& operator+=(const Time &t);
	Time& operator+=(int s);
	Time& operator-=(const Time &t);
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
