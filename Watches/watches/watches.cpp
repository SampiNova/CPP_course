#include "watches.hpp"
#include "../time/time.hpp"
#include <iostream>
#include <algorithm>

//////////////////////////////////////////////////
//        SIMPLE WATCH CLASS REALISATION        //
//////////////////////////////////////////////////

SimpleWatch::SimpleWatch() noexcept: Time() {
	this->is_24_format = true;
	std::cout << "\tZero constructor of SimpleWatch was called.\n";
}

SimpleWatch::~SimpleWatch() {
	std::cout << "\tDestructor of SimpleWatch was called.\n";
}

SimpleWatch::SimpleWatch(bool format24) noexcept: Time() {
	this->is_24_format = format24;
	std::cout << "\tSimple constructor of SimpleWatch was called.\n";
}

SimpleWatch::SimpleWatch(const SimpleWatch& sw) noexcept: Time(sw.get_seconds(), sw.get_minutes(), sw.get_hours()) {
	this->is_24_format = sw.get_format();
	std::cout << "\tCopy constructor of SimpleWatch was called.\n";
}

SimpleWatch::SimpleWatch(const Time& t, bool format24=true) noexcept: Time(t) {
	this->is_24_format = format24;
	std::cout << "\tOn Time constructor of SimpleWatch was called.\n";
}

SimpleWatch::SimpleWatch(int sec, int min, int hr, bool format24=true): Time(sec, min, hr) {
	this->is_24_format = format24;
	std::cout << "\tFull constructor of SimpleWatch was called.\n";
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

////////////////////////////////////////////////
//        WALL CLOCK CLASS REALISATION        //
////////////////////////////////////////////////

WallClock::WallClock() noexcept: SimpleWatch() {
	this->my_charge = 0;
	this->on_pin = false;
	std::cout << "\t\tZero constructor of WallClock was called.\n";
}

WallClock::~WallClock() noexcept {
	std::cout << "\t\tDestructor of WallClock was called.\n";
}

WallClock::WallClock(const SimpleWatch& sw, int charge=0, bool state=false): SimpleWatch(sw) {
	if (charge < 0 || charge > 100) throw "Wrong charge parameter!\n";
	this->my_charge = charge;
	this->on_pin = state;
	std::cout << "\t\tSimple constructor of WallClock was called.\n";
}

WallClock::WallClock(const WallClock& wc) noexcept: SimpleWatch(wc.get_seconds(), wc.get_minutes(), wc.get_hours(), wc.get_format()) {
	this->my_charge = wc.get_charge();
	this->on_pin = wc.get_state();
	std::cout << "\t\tCopy constructor of WallClock was called.\n";
}

WallClock::WallClock(int sec, int min, int hr, bool format24=true, int charge=0, bool state=false): SimpleWatch(sec, min, hr, format24) {
	if (0 < charge || charge > 100) throw "Wrong charge parameter!\n";
	this->my_charge = charge;
	this->on_pin = state;
	std::cout << "\t\tFull constructor of WallClock was called.\n";
}

void WallClock::charge() {
	this->my_charge = 100;
}

int WallClock::get_charge() const noexcept {
	return this->my_charge;
}

bool WallClock::get_state() const noexcept {
	return this->on_pin;
}

void WallClock::hang() {
	if (this->on_pin) throw "You can't hang clock, it's already on the wall.\n";
	else this->on_pin = true;
}

void WallClock::take_off() {
	if (this->on_pin) throw "You can't take off clock, it's already not on the wall.\n";
	else this->on_pin = false;
}

//////////////////////////////////////////////////
//        CUCKOO CLOCK CLASS REALISATION        //
//////////////////////////////////////////////////

CuckooClock::CuckooClock() noexcept: WallClock() {
	std::cout << "\t\t\tZero constructor of CuckooClock was called.\n";
}

CuckooClock::~CuckooClock() noexcept {
	std::cout << "\t\t\tDestructor of CuckooClock was called.\n";
}

CuckooClock::CuckooClock(const SimpleWatch& sw, int charge=0, bool state=false): WallClock(sw, charge, state) {
	std::cout << "\t\t\tSimple constructor of CuckooClock was called.\n";
}

CuckooClock::CuckooClock(const CuckooClock& cc) noexcept:  WallClock(cc) {
	std::cout << "\t\t\tCopy constructor of CuckooClock was called.\n";
}

CuckooClock::CuckooClock(int sec, int min, int hr, bool format24=true, int charge=0, bool state=false): 
WallClock(sec, min, hr, format24, charge, state) {
	std::cout << "\t\t\tFull constructor of CuckooClock was called.\n";
}

bool CuckooClock::is_it_cuckoo_time() const noexcept {
	return (this->get_minutes() == 0 && this->get_seconds() <= 3);
}

int CuckooClock::cuckoo() const noexcept {
	if (this->is_it_cuckoo_time()) {
		if (this->get_hours() % 12 == 0) return 12;
		else return this->get_hours() % 12;
	}
	return 0;
}

///////////////////////////////////////////
//        WATCH CLASS REALISATION        //
///////////////////////////////////////////

Watch::Watch() noexcept: SimpleWatch() {
	this->my_charge = 0;
	std::cout << "\t\tZero constructor of Watch was called.\n";
}

Watch::~Watch() noexcept {
	std::cout << "\t\tDestructor of Watch was called.\n";
}

Watch::Watch(const SimpleWatch& sw, int charge=0): SimpleWatch(sw) {
	if (0 < charge || charge > 100) throw "Wrong charge parameter!\n";
	this->my_charge = charge;
	std::cout << "\t\tSimple constructor of Watch was called.\n";
}

Watch::Watch(const Watch& w) noexcept: SimpleWatch(w.get_seconds(), w.get_minutes(), w.get_hours(), w.get_format()) {
	this->my_charge = w.get_charge();
	std::cout << "\t\tCopy constructor of Watch was called.\n";
}

Watch::Watch(int sec, int min, int hr, bool format24, int charge): SimpleWatch(sec, min, hr, format24) {
	if (0 < charge || charge > 100) throw "Wrong charge parameter!\n";
	this->my_charge = charge;
	std::cout << "\t\tFull constructor of Watch was called.\n";
}

void Watch::charge() {
	this->my_charge = 100;
}

int Watch::get_charge() const noexcept {
	return this->my_charge;
}

/////////////////////////////////////////////////
//        SMART WATCH CLASS REALISATION        //
/////////////////////////////////////////////////

SmartWatch::SmartWatch() noexcept: Watch() {
	this->smartphone_connection = false;
	this->theater_mode = false;
	this->brightness = 100;
	this->normal_brightness = 100;
	std::cout << "\t\t\tZero constructor of SmartWatch was called.\n";
}

SmartWatch::~SmartWatch() noexcept {
	std::cout << "\t\t\tDestructor of SmartWatch was called.\n";
}

SmartWatch::SmartWatch(const Watch& w, bool connectin=false, bool theater=false, int brightness=100): Watch(w) {
	if (0 < brightness || brightness > 100) throw "Wrong brightness parameter!\n";
	this->smartphone_connection = connectin;
	this->theater_mode = theater;
	this->brightness = theater ? 5 : brightness;
	this->normal_brightness = brightness;
	std::cout << "\t\t\tSimple constructor of SmartWatch was called.\n";
}

SmartWatch::SmartWatch(const SmartWatch& w) noexcept: 
Watch(w.get_seconds(), get_minutes(), get_seconds(), get_format(), get_charge()) {
	this->smartphone_connection = w.get_connection();
	this->theater_mode = w.get_theater_mode();
	this->brightness = this->theater_mode ? 5 : w.get_brightness();
	this->normal_brightness = w.get_brightness();
	std::cout << "\t\t\tCopy constructor of SmartWatch was called.\n";
}

SmartWatch::SmartWatch(int sec, int min, int hr, bool format24=true, int charge=0, bool connectin=false, bool theater=false, int brightness=100):
Watch(sec, min, hr, format24, charge) {
	if (0 < brightness || brightness > 100) throw "Wrong brightness parameter!\n";
	this->smartphone_connection = connectin;
	this->theater_mode = theater;
	this->brightness = theater ? 5 : brightness;
	this->normal_brightness = brightness;
	std::cout << "\t\t\tFull constructor of SmartWatch was called.\n";
}

bool SmartWatch::get_connection() const noexcept {
	return this->smartphone_connection;
}

bool SmartWatch::get_theater_mode() const noexcept {
	return this->theater_mode;
}

int SmartWatch::get_brightness() const noexcept {
	return this->brightness;
}

void SmartWatch::connect_smartphone() {
	this->smartphone_connection = true;
}

void SmartWatch::set_theater_mode(bool new_mode=true) {
	this->theater_mode = new_mode;
}

void SmartWatch::set_brightnes(int new_brightness=100) {
	if (0 < brightness || brightness > 100) throw "Wrong brightness parameter!\n";
	this->brightness = new_brightness;
}

////////////////////////////////////////////////////
//        LONGCASE CLOCK CLASS REALISATION        //
////////////////////////////////////////////////////

LongcaseClock::LongcaseClock() noexcept: SimpleWatch() {
	this->height = 200;
	this->with_pendulum = false;
	std::cout << "\t\tZero constructor of LongcaseClock was called.\n";
}

LongcaseClock::~LongcaseClock() noexcept {
	std::cout << "\t\tDestructor of LongcaseClock was called.\n";
}

LongcaseClock::LongcaseClock(const SimpleWatch& sw, int height=200, bool with_pendulum=false): SimpleWatch(sw) {
	if (height < 50 || height > 350) throw "Wrong height parameter!\n";
	this->with_pendulum = with_pendulum;
	std::cout << "\t\tSimple constructor of LongcaseClock was called.\n";
}

LongcaseClock::LongcaseClock(const LongcaseClock& lc) noexcept: 
SimpleWatch(lc.get_seconds(), lc.get_minutes(), lc.get_hours(), lc.get_format()) {
	this->height = lc.get_height();
	this->with_pendulum = lc.is_it_with_pendulum()
	std::cout << "\t\tCopy constructor of LongcaseClock was called.\n";
}

LongcaseClock::LongcaseClock(int sec, int min, int hr, bool format24=true, int height=200, bool with_pendulum=false):
SimpleWatch(sec, min, hr, format24) {
	if (height < 50 || height > 350) throw "Wrong height parameter!\n";
	this->with_pendulum = with_pendulum;
	std::cout << "\t\tFull constructor of LongcaseClock was called.\n";
}

int LongcaseClock::get_height() const noexcept {
	return this->height;
}

bool LongcaseClock::is_it_with_pendulum() const noexcept {
	return this->with_pendulum;
}
