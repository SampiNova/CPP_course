#include "time.hpp"
#include <iostream>
#include <algorithm>

Watch::Watch() noexcept {
	this->_time = new Time();
}

Watch::~Watch() {
	delete this->_time;
}

Watch::Watch(const Time& t) noexcept {
	this->_time = new Time(t);
}

void Watch::set_format(bool is24h) {
	this->_24h_format = is24h;
}

int Watch::format() const noexcept {
	return this->_24h_format;
}

void Watch::set_seconds(const Time& t, int sec) {

}

void Watch::set_minutes(const Time& t, int min) {

}

void Watch::set_hours(const Time& t, int hr) {

}

int Watch::get_seconds(const Time& t) const noexcept {
	return t._seconds;
}

int Watch::get_minutes(const Time& t) const noexcept {
	return t._minutes;
}

int Watch::get_hours(const Time& t) const noexcept {
	return t._hours;
}

std::ostream& operator<<(std::ostream& out, const Watch& w) {
	if (w.format()) {
    	out << w.get_hours() << ":" << w.get_minutes() << ":" << w.get_seconds();
	}
	else {
		out << w.get_hours() % 12 << ":" << w.get_minutes() << ":" << w.get_seconds();
		if (w.get_hours() > 12) out << " PM";
		else out << " AM";
	}
   return out;
}

std::istream& operator>>(std::istream& in, Watch& w) {
   int h, m, s;
   char tmp;
   in >> h >> tmp;
   in >> m >> tmp;
   in >> s >> tmp;

   w = Watch(Time(s, m, h));
   return in;
}

