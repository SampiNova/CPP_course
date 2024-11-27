#pragma once
#include <iostream>

typedef int value_type;

class CircularBuffer {
private:
	value_type* buffer;
	int buffer_size;
	int _capacity;
	int start;
	int end;
	int count;
public:
	CircularBuffer();
	~CircularBuffer();
	CircularBuffer(const CircularBuffer& cb);

	explicit CircularBuffer(int capacity);
	CircularBuffer(int capacity, const value_type& elem);

	value_type& operator[](int i);
	const value_type& operator[](int i) const;

    value_type& operator()(int i);
    const value_type& operator()(int i) const;

	value_type& at(int i);
	const value_type& at(int i) const;

	value_type& front();
	value_type& back();
	const value_type& front() const;
	const value_type& back() const;

	value_type* linearize();
	bool is_linearized() const;
	void rotate(int new_begin);

	int size() const;
	bool empty() const;
	bool full() const;
	int reserve() const;
	int capacity() const;

	void set_capacity(int new_capacity);
	void resize(int new_size, const value_type& item = value_type());
	CircularBuffer& operator=(const CircularBuffer& cb);
	void swap(CircularBuffer& cb);

	void push_back(const value_type& item = value_type());
	void push_front(const value_type& item = value_type());
	void pop_back();
	void pop_front();

	void insert(int pos, const value_type& item = value_type());
	void erase(int first, int last);
	void clear();
};

std::ostream& operator<<(std::ostream& out, const CircularBuffer& cb);

bool operator==(const CircularBuffer& a, const CircularBuffer& b);
bool operator!=(const CircularBuffer& a, const CircularBuffer& b);
