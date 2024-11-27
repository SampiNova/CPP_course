#include "time.hpp"
#include <iostream>
#include <algorithm>

unsigned Time::count = 0;

Time::Time() {
	this->_seconds = 0;
	this->_minutes = 0;
	this->_hours = 0;
	this->count++;
	std::cout << "Zero constructor was called.\nCount of Time: " << this->count << "\n";
}

Time::~Time() {
	this->count--;
	std::cout << "Destructor was called.\nCount of Time: " << this->count << "\n";
}

Time::Time(const Time &t) {
	this->_seconds = t.get_seconds();
	this->_minutes = t.get_minutes();
	this->_hours = t.get_hours();
	this->count++;
	std::cout << "Copying constructor was called.\nCount of Time: " << this->count << "\n";
}

Time::Time(int sec, int min, int hr) {
	this->_seconds = sec;
	this->_minutes = min;
	this->_hours = hr;
	this->normalize();
	this->count++;
	std::cout << "Full constructor was called.\nCount of Time: " << this->count << "\n";
}

int Time::to_seconds() {
	return this->_seconds + this->_minutes * 60 + this->_hours * 3600;
}

void Time::normalize() {
	int seconds = this->to_seconds();
	if (seconds < 0) {
		this->_seconds = 0;
		this->_minutes = 0;
		this->_hours = 0;
		return;
	}
	this->_hours = (seconds / 3600) % 24;
	this->_minutes = (seconds % 3600) / 60;
	this->_seconds = seconds % 60;
}

void Time::set_seconds(int sec) {
	this->_seconds = sec;
}

void Time::set_minutes(int min) {
	this->_minutes = min;
}

void Time::set_hours(int hr) {
	this->_hours = hr;
}

int Time::get_seconds() const {
	return this->_seconds;
}

int Time::get_minutes() const {
	return this->_minutes;
}

int Time::get_hours() const {
	return this->_hours;
}

Time& Time::operator+=(const Time &t) {
	this->_seconds += t.get_seconds();
	this->_minutes += t.get_minutes();
	this->_hours += t.get_hours();
	this->normalize();
	return *this;
}

Time& Time::operator+=(int s) {
	this->_seconds += s;
	this->normalize();
	return *this;
}

Time& Time::operator-=(const Time &t) {
	this->_seconds -= t.get_seconds();
	this->_minutes -= t.get_minutes();
	this->_hours -= t.get_hours();
	this->normalize();
	return *this;
}

Time& Time::operator-=(int s) {
	this->_seconds -= s;
	this->normalize();
	return *this;
}

Time operator+(const Time &t1, const Time &t2) {
	Time new_time(t1.get_seconds() + t2.get_minutes(), 
				  t1.get_minutes() + t2.get_minutes(), 
				  t1.get_hours() + t2.get_hours());
	return new_time;
}

Time operator+(const Time &t, int s) {
	Time new_time(t.get_seconds() + s, 
				  t.get_minutes(), 
				  t.get_hours());
	return new_time;
}

Time operator-(const Time &t1, const Time &t2) {
	Time new_time(t1.get_seconds() - t2.get_minutes(), 
				  t1.get_minutes() - t2.get_minutes(), 
				  t1.get_hours() - t2.get_hours());
	return new_time;
}

Time operator-(const Time &t, int s) {
	Time new_time(t.get_seconds() - s, 
				  t.get_minutes(), 
				  t.get_hours());
	return new_time;
}

bool operator==(const Time &t1, const Time &t2) {
	return (t1.get_seconds() == t2.get_seconds() && 
		    t1.get_minutes() == t2.get_minutes() && 
			t1.get_hours() == t2.get_hours());
}

bool operator!=(const Time &t1, const Time &t2) {
	return !(t1 == t2);
}

std::ostream& operator<<(std::ostream& out, const Time& t) {
   out << t.get_hours() << ":" << t.get_minutes() << ":" << t.get_seconds();
   return out;
}

std::istream& operator>>(std::istream& in, Time& t) {
   int h, m, s;
   char tmp;
   in >> h >> tmp;
   in >> m >> tmp;
   in >> s >> tmp;

   t = Time(s, m, h);
   return in;
}

