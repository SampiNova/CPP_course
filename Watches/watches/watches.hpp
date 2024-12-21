#pragma once
#include "../time/time.hpp"
#include <iostream>

//////////////////////////////////////////////////
//        SIMPLE WATCH CLASS REALISATION        //
//////////////////////////////////////////////////

class SimpleWatch {
private:
	bool is_24_format;	
    Time _time;
public:
	SimpleWatch() noexcept;
	~SimpleWatch();
	SimpleWatch(bool format24) noexcept;
	SimpleWatch(const SimpleWatch& sw) noexcept;
	SimpleWatch(const Time& t, bool format24) noexcept;
	SimpleWatch(int sec, int min, int hr, bool format24);

	void set_format(bool format24);
	bool get_format() const noexcept;
};

std::ostream& operator<<(std::ostream& out, const SimpleWatch& t);
std::istream& operator>>(std::istream& in, SimpleWatch& t);

////////////////////////////////////////////////
//        WALL CLOCK CLASS REALISATION        //
////////////////////////////////////////////////

class WallClock: public SimpleWatch {
protected:
	int my_charge;
	bool on_pin;
public:
	WallClock() noexcept;
	~WallClock() noexcept;
	WallClock(const SimpleWatch& sw, int charge, bool state);
	WallClock(const WallClock& wc) noexcept;
	WallClock(int sec, int min, int hr, bool format24, int charge, bool state);

	void charge();
	int get_charge() const noexcept;
	bool get_state() const noexcept;
	void hang();
	void take_off();
};

//////////////////////////////////////////////////
//        CUCKOO CLOCK CLASS REALISATION        //
//////////////////////////////////////////////////

class CuckooClock: public WallClock {
public:
	CuckooClock() noexcept;
	~CuckooClock() noexcept;
	CuckooClock(const SimpleWatch& sw, int charge, bool state);
	CuckooClock(const CuckooClock& cc) noexcept;
	CuckooClock(int sec, int min, int hr, bool format24, int charge, bool state);

	bool is_it_cuckoo_time() const noexcept;
	int cuckoo() const noexcept;
};

///////////////////////////////////////////
//        WATCH CLASS REALISATION        //
///////////////////////////////////////////

class Watch: public SimpleWatch {
protected:
	int my_charge;
public:
	Watch() noexcept;
	~Watch() noexcept;
	Watch(const SimpleWatch& sw, int charge);
	Watch(const Watch& w) noexcept;
	Watch(int sec, int min, int hr, bool format24, int charge);

	void charge();
	int get_charge() const noexcept;
};

/////////////////////////////////////////////////
//        SMART WATCH CLASS REALISATION        //
/////////////////////////////////////////////////

class SmartWatch: public Watch {
protected:
	bool smartphone_connection;
	bool theater_mode;
	int brightness;
	int normal_brightness;
public:
	SmartWatch() noexcept;
	~SmartWatch() noexcept;
	SmartWatch(const Watch& w, bool connectin, bool theater, int brightness);
	SmartWatch(const SmartWatch& w) noexcept;
	SmartWatch(int sec, int min, int hr, bool format24, int charge, bool connectin, bool theater, int brightness);

	bool get_connection() const noexcept;
	bool get_theater_mode() const noexcept;
	int get_brightness() const noexcept;

	void connect_smartphone();
	void set_theater_mode(bool new_mode);
	void set_brightnes(int new_brightness);
};

////////////////////////////////////////////////////
//        LONGCASE CLOCK CLASS REALISATION        //
////////////////////////////////////////////////////

class LongcaseClock: public SimpleWatch {
protected:
	int height;
	bool with_pendulum;
public:
	LongcaseClock() noexcept;
	~LongcaseClock() noexcept;
	LongcaseClock(const SimpleWatch& sw, int height, bool with_pendulum);
	LongcaseClock(const LongcaseClock& lc) noexcept;
	LongcaseClock(int sec, int min, int hr, bool format24, int height, bool with_pendulum);

	int get_height() const noexcept;
	bool is_it_with_pendulum() const noexcept;
};
