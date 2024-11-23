#pragma once
#include <iostream>

class Time;

class Watch {
private:
	bool _24h_format;
	Time* _time;
public:
	Watch() noexcept;
	~Watch();
	Watch(const Time& t) noexcept;

	void set_format(bool is24h);
	int format() const noexcept;

	void set_seconds(const Time& t, int sec);
	void set_minutes(const Time& t, int min);
	void set_hours(const Time& t, int hr);

	int get_seconds(const Time& t) const noexcept;
	int get_minutes(const Time& t) const noexcept;
	int get_hours(const Time& t) const noexcept;
};

std::ostream& operator<<(std::ostream& out, const Watch& w);
std::istream& operator>>(std::istream& in, Watch& w);


class Time {
private:
	int _seconds;
	int _minutes;
	int _hours;
	int _id;
	static unsigned count;
	static unsigned actual_id;
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

	friend class SimpleWatch;
};

Time operator+(const Time &t1, const Time &t2);
Time operator+(const Time &t, int s);
Time operator-(const Time &t1, const Time &t2);
Time operator-(const Time &t, int s);

bool operator==(const Time &t1, const Time &t2);
bool operator!=(const Time &t1, const Time &t2);

std::ostream& operator<<(std::ostream& out, const Time& t);
std::istream& operator>>(std::istream& in, Time& t);


class SimpleWatch {
private:
	bool _24h_format;
	Time* _time;
public:
	SimpleWatch() noexcept;
	~SimpleWatch();
	SimpleWatch(const Time& t) noexcept;

	void set_format(bool is24h);
	int format() const noexcept;

	void set_seconds(int sec);
	void set_minutes(int min);
	void set_hours(int hr);

	int get_seconds() const noexcept;
	int get_minutes() const noexcept;
	int get_hours() const noexcept;
};

std::ostream& operator<<(std::ostream& out, const SimpleWatch& sw);
std::istream& operator>>(std::istream& in, SimpleWatch& sw);
