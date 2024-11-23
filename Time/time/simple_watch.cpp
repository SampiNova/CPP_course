#include "time.hpp"
#include <iostream>
#include <algorithm>

SimpleWatch::SimpleWatch() noexcept {
	this->_time = new Time();
}

SimpleWatch::~SimpleWatch() {
	delete this->_time;
}

SimpleWatch::SimpleWatch(const Time& t) noexcept {
	this->_time = new Time(t);
}

void SimpleWatch::set_format(bool is24h) {
	this->_24h_format = is24h;
}

int SimpleWatch::format() const noexcept {
	return this->_24h_format;
}

void SimpleWatch::set_seconds(int sec) {
	if (sec < 0) throw "Wrong seconds!";
	this->_time->_seconds = sec;
	this->_time->normalize();
}

void SimpleWatch::set_minutes(int min) {
	if (min < 0) throw "Wrong minutes!";
	this->_time->_minutes = min;
	this->_time->normalize();
}

void SimpleWatch::set_hours(int hr) {
	if (hr < 0) throw "Wrong hours!";
	this->_time->_hours = hr;
	this->_time->normalize();
}

int SimpleWatch::get_seconds() const noexcept {
	return this->_time->_seconds;
}

int SimpleWatch::get_minutes() const noexcept {
	return this->_time->_minutes;
}

int SimpleWatch::get_hours() const noexcept {
	return this->_time->_hours;
}

std::ostream& operator<<(std::ostream& out, const SimpleWatch& sw) {
	if (sw.format()) {
    	out << sw.get_hours() << ":" << sw.get_minutes() << ":" << sw.get_seconds();
	}
	else {
		out << sw.get_hours() % 12 << ":" << sw.get_minutes() << ":" << sw.get_seconds();
		if (sw.get_hours() > 12) out << " PM";
		else out << " AM";
	}
   return out;
}

std::istream& operator>>(std::istream& in, SimpleWatch& sw) {
   int h, m, s;
   char tmp;
   in >> h >> tmp;
   in >> m >> tmp;
   in >> s >> tmp;

   sw = SimpleWatch(Time(s, m, h));
   return in;
}