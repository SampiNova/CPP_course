#include "time.hpp"
#include <iostream>
#include <algorithm>

//////////////////////////////////////////
//                                      //
//        WATCH CLASS REALISATION       //
//                                      //
//////////////////////////////////////////

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


//////////////////////////////////////////
//                                      //
//        TIME CLASS REALISATION        //
//                                      //
//////////////////////////////////////////

unsigned Time::count = 0;
unsigned Time::actual_id = 0;

Time::Time() noexcept{
	this->_seconds = 0;
	this->_minutes = 0;
	this->_hours = 0;
	this->count++;
	this->_id = this->actual_id;
	this->actual_id++;
	std::cout << "Zero constructor was called. New object Id: " << this->_id << "\nCount of Time: " << this->count << "\n";
}

Time::~Time() {
	this->count--;
	std::cout << "Destructor was called. Object Id: " << this->_id << "\nCount of Time: " << this->count << "\n";
}

Time::Time(const Time &t) noexcept{
	this->_seconds = t.get_seconds();
	this->_minutes = t.get_minutes();
	this->_hours = t.get_hours();
	this->count++;
	this->_id = this->actual_id;
	this->actual_id++;
	std::cout << "Copying constructor was called. New object Id: " << this->_id << "\nCount of Time: " << this->count << "\n";
}

Time::Time(int sec, int min, int hr) {
	if (sec < 0) throw "Wrong seconds argument!";
	if (min < 0) throw "Wrong minutes argument!";
	if (hr < 0) throw "Wrong hours argument!";
	this->_seconds = sec;
	this->_minutes = min;
	this->_hours = hr;
	this->normalize();
	this->count++;
	this->_id = this->actual_id;
	this->actual_id++;
	std::cout << "Full constructor was called. New object Id: " << this->_id << "\nCount of Time: " << this->count << "\n";
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
	if (sec < 0) throw "Wrong seconds!";
	this->_seconds = sec;
	this->normalize();
}

void Time::set_minutes(int min) {
	if (min < 0) throw "Wrong minutes!";
	this->_minutes = min;
	this->normalize();
}

void Time::set_hours(int hr) {
	if (hr < 0) throw "Wrong hours!";
	this->_hours = hr;
	this->normalize();
}

int Time::get_seconds() const noexcept {
	return this->_seconds;
}

int Time::get_minutes() const noexcept {
	return this->_minutes;
}

int Time::get_hours() const noexcept {
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

//////////////////////////////////////////////////
//                                              //
//        SIMPLE WATCH CLASS REALISATION        //
//                                              //
//////////////////////////////////////////////////

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
