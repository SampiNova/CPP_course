#include "watches.hpp"
#include "../time/time.hpp"
#include <iostream>
#include <algorithm>

SimpleWatch::SimpleWatch() noexcept {
	Time();
}

SimpleWatch::~SimpleWatch() {

}

SimpleWatch::SimpleWatch(bool format24) noexcept {
	Time();
	this->is_24_format = format24;
}

SimpleWatch::SimpleWatch(const SimpleWatch& sw) noexcept {
	Time(sw.get_seconds(), sw.get_minutes(), sw.get_hours());
	this->is_24_format = sw.get_format();
}

SimpleWatch::SimpleWatch(const Time& t, bool format24=true) noexcept: Time(t) {
	this->is_24_format = format24;
}

SimpleWatch::SimpleWatch(int sec, int min, int hr, bool format24=true): Time(sec, min, hr) {
	this->is_24_format = format24;
}

void SimpleWatch::set_format(bool format24) {
	this->is_24_format = format24;
}

bool SimpleWatch::get_format() const noexcept {
	return this->is_24_format;
}

std::ostream& operator<<(std::ostream& out, const SimpleWatch& sw) {
	if (sw.get_format()) {
		out << sw.get_hours() << ":" << sw.get_minutes() << ":" << sw.get_seconds();
	}
	else {
		out << sw.get_hours() % 12 << ":" << sw.get_minutes() << ":" << sw.get_seconds();
		if (sw.get_hours() >= 12) out << " PM";
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

  	Time temp(s, m, h);
  	sw = SimpleWatch(temp);
   return in;
}
