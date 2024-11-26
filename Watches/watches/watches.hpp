#pragma once
#include "../time/time.hpp"
#include <iostream>

class SimpleWatch: public Time {
private:
	bool is_24_format;	
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


class WallClock: public SimpleWatch {
protected:
	int my_charge;
	bool on_pin;
public:
	void charge();
	int get_charge() noexcept;
	void get_state() noexcept;
	void hang();
	void take_off();
};

class CuckooClock: public WallClock {
public:
	bool is_it_cuckoo_time() noexcept;
	int cuckoo() noexcept;
};

class Watch: public SimpleWatch {
protected:
	int my_charge;
public:
	void charge();
	int get_charge() noexcept;
};

class SmartWatch: public Watch {
protected:
	bool smartphone_connection;
	bool theater_mode;
	bool vibration_mode;
	int brightness;
public:
	bool get_connection() noexcept;
	bool get_smartphone_connection() noexcept;
	bool get_theater_mode() noexcept;
	bool get_vibration_mode() noexcept;
	int get_brightness() noexcept;

	void connect_smartphone();
	void set_theater_mode(bool new_mode);
	void set_vibration_mode(bool new_mode);
	void set_brightnes(int new_brightness);
};

class LongcaseClock: public SimpleWatch {
protected:
	int height;
	bool with_pendulum;
public:
	int get_height() noexcept;
	bool is_it_with_pendulum() noexcept;

	void set_height(int new_height);
};
