#include "CircularBuffer.hpp"
#include <iostream>
#include <algorithm>

// Constructors and destructor
CircularBuffer::CircularBuffer() {
    /*
    Constructing empty circular buffer with every field 0
    */
    this->buffer = nullptr;
	this->buffer_size = 0;
	this->_capacity = 0;
	this->start = 0;
	this->end = 0;
	this->count = 0;
}
CircularBuffer::~CircularBuffer() {
    // delete buffer memory
	delete[] this->buffer;
}
CircularBuffer::CircularBuffer(const CircularBuffer& cb) {
    /*
    First, we make new memory for buffer.
    Second, copy data from cb to this->buffer.
    And copy every field from cd.
    */
    this->buffer = new value_type[cb.buffer_size];
    std::copy(cb.buffer, cb.buffer + cb.buffer_size, this->buffer);
	this->buffer_size = cb.buffer_size;
	this->_capacity = cb._capacity;
	this->start = cb.start;
	this->end = cb.end;
	this->count = cb.count;
}

CircularBuffer::CircularBuffer(int capacity) {
    /*
    If capacity is less then 1 we`d throw error message.
    If capacity is good we make new empty buffer
    */
	if (capacity < 1) {
		throw std::invalid_argument("Error: Wrong capacity!");
	}
	this->buffer = new value_type[capacity];
	this->buffer_size = capacity;
	this->_capacity = capacity;
	this->start = 0;
	this->end = 0;
	this->count = 0;
}

CircularBuffer::CircularBuffer(int capacity, const value_type& elem) {
    /*
    If capacity is less then 1 we`d throw error message.
    If capacity is good we make new linearized buffer filled with values elem
    */
	if (capacity < 1) {
		throw std::invalid_argument("Error: Wrong capacity!");
	}
	this->buffer = new value_type[capacity];

	for (int i = 0; i < capacity; i++) {
		this->buffer[i] = elem;
	}

	this->buffer_size = capacity;
	this->_capacity = capacity;
	this->start = 0;
	this->end = capacity - 1;
	this->count = capacity;
}

// indexed getters
// []
// returns link to element from the buffer by any integer index
value_type& CircularBuffer::operator[](int i) {
	i = (i % this->count + this->count) % this->count;
	return this->buffer[(this->start + i) % this->buffer_size];
}

const value_type& CircularBuffer::operator[](int i) const {
	i = (i % this->count + this->count) % this->count;
    return (const value_type&)this->buffer[(this->start + i) % this->buffer_size];
}

// ()
// returns link to element from the buffer by index in field this->buffer
value_type& CircularBuffer::operator()(int i) {
    return this->buffer[i];
}
const value_type& CircularBuffer::operator()(int i) const {
    return (const value_type&)this->buffer[i];
}

// at()
// return link to element from buffer by index in range [0, this->count - 1]
// if index isn`t in range we throw error message
value_type& CircularBuffer::at(int i) {
	if (i < 0 || i > this->count - 1) {
		throw std::invalid_argument("Error: Wrong index!");
	}
	return this->buffer[(this->start + i) % this->buffer_size];
}

const value_type& CircularBuffer::at(int i) const {
	if (i < 0 || i > this->count - 1) {
		throw std::invalid_argument("Error: Wrong index!");
	}
	return this->buffer[(this->start + i) % this->buffer_size];
}

// front/back links
// returns links at front or back of buffer
value_type& CircularBuffer::front() {
	return this->buffer[this->start];
}

value_type& CircularBuffer::back() {
	return this->buffer[this->end];
}

const value_type& CircularBuffer::front() const {
	return this->buffer[this->start];
}

const value_type& CircularBuffer::back() const {
	return this->buffer[this->end];
}

// linearize
value_type* CircularBuffer::linearize() {
    // if buffer is already linearized or empty we return link without changing buffer
    if (this->start == this->end || this->is_linearized()) {
        return &this->buffer[0];
    }
    /*
    First, we make temporary memory for data, then copying values in right order using [] operator.
    Delete old memory and copy temporary memory in this->buffer.
    Update start and end indexes.
    */
    value_type* temp = new value_type[this->buffer_size];
    for (int i = 0; i < this->count; i++) {
        temp[i] = (*this)[i];
    }
    delete[] this->buffer;
    this->buffer = temp;

	this->start = 0;
	this->end = this->count - 1;
	return &this->buffer[0];
}

bool CircularBuffer::is_linearized() const {
    // If start index is already 0, our buffer is learized
	return (this->start == 0);
}

void CircularBuffer::rotate(int new_begin) {
    // if buffer iss empy, we do nothing
	if (this->start == this->end) {
		return;
	}

    // we calculate an index
    new_begin = (new_begin % this->count + this->count) % this->count;
    int idx = this->buffer[(this->start + new_begin) % this->buffer_size];

    /*
    First, we make temporary memory for data, then copying values in right order using [] operator.
    Delete old memory and copy temporary memory in this->buffer.
    Update start and end indexes.
    */
    value_type* temp = new value_type[this->buffer_size];
    int j = this->buffer_size - idx;
    for (int i = 0; i < this->count; i++) {
        temp[j] = (*this)[i];
        j = (j + 1) % this->buffer_size;
    }
    delete[] this->buffer;
    this->buffer = temp;

    this->start = this->buffer_size - idx;
    this->end = (this->start + this->count) % this->buffer_size;
}

// info
int CircularBuffer::size() const {
	return this->count;
}

bool CircularBuffer::empty() const {
	return this->count == 0;
}

bool CircularBuffer::full() const {
	return this->count == this->_capacity;
}

int CircularBuffer::reserve() const {
	return this->_capacity - this->count;
}

int CircularBuffer::capacity() const {
	return this->_capacity;
}

// memory
void CircularBuffer::set_capacity(int new_capacity) {
    // capacity needs to be in range [this->count, this->buffer_size]
	if (new_capacity <= this->buffer_size && new_capacity >= this->count) {
		this->_capacity = new_capacity;
	}
	else {
		throw std::invalid_argument("Error: Wrong capacity!");
	}
}

void CircularBuffer::resize(int new_size, const value_type& item) {
    // if size is less than 1 we throw error message
	if (new_size < 1) {
		throw std::invalid_argument("Error: Wrong size!");
	}

    /*
    First, linearizing buffer, then copy old data in temporary memory and filling new elements with item value.
    Upadting other fields.
     */
	value_type* tmp = this->linearize();
	value_type* new_buffer = new value_type[new_size];
	for (int i = 0; i < new_size; i++) {
		if (i > this->count - 1)
			new_buffer[i] = item;
		else
			new_buffer[i] = this->buffer[i];
	}
	delete[] this->buffer;
	this->buffer = new_buffer;
	this->count = this->count <= new_size ? this->count : new_size;
	this->buffer_size = new_size;
	this->_capacity = this->_capacity <= new_size ? this->_capacity : new_size;
	this->end = this->count <= new_size ? this->end : new_size - 1;
}

CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb) {
    // if we have self object, we do nothing
	if (this == &cb) return *this;
    // delete old buffer
    // allocating new memory and copy data from cb
    // copy other fields
	delete[] this->buffer;
	this->buffer = new value_type[cb.buffer_size];
	std::copy(cb.buffer, cb.buffer + cb.buffer_size, this->buffer);
	this->buffer_size = cb.buffer_size;
	this->_capacity = cb._capacity;
	this->start = cb.start;
	this->end = cb.end;
	this->count = cb.count;
	return *this;
}

void CircularBuffer::swap(CircularBuffer& cb) {
    // swap all fields with std::swap
	std::swap(this->buffer, cb.buffer);
	std::swap(this->buffer_size, cb.buffer_size);
	std::swap(this->_capacity, cb._capacity);
	std::swap(this->start, cb.start);
	std::swap(this->count, cb.count);
	std::swap(this->end, cb.end);
}

// push/pop
void CircularBuffer::push_back(const value_type& item) {
	if (this->empty()) {
		this->buffer[this->start] = item;
		this->count++;
		return;
	}
	if (this->full())
		this->buffer[this->start] = item;
	else {
		this->end = (this->end + 1) % this->buffer_size;
		this->buffer[this->end] = item;
		this->count++;
	}
}

void CircularBuffer::push_front(const value_type& item) {
	if (this->empty()) {
		this->buffer[this->start] = item;
		this->count++;
		return;
	}
	if (this->full())
		this->buffer[this->end] = item;
	else {
		this->start = (this->buffer_size + (this->start - 1) % this->buffer_size) % this->buffer_size;
		this->buffer[this->start] = item;
		this->count++;
	}
}

void CircularBuffer::pop_back() {
	if (this->empty()) {
		throw;
	}
	this->end = (this->buffer_size + (this->end - 1) % this->buffer_size) % this->buffer_size;
	this->count--;
}

void CircularBuffer::pop_front() {
	if (this->empty()) {
		throw;
	}
	this->start = (this->start + 1) % this->buffer_size;
	this->count--;
}

// insert/erase/clear
void CircularBuffer::insert(int pos, const value_type& item) {
	// testing capacity
	if (this->full()) {
		throw std::invalid_argument("Error: circular buffer is full!");
	}
    // testing index
	if (pos < 0 || pos > this->count - 1 || this->empty()) {
		throw std::invalid_argument("Error: Wrong index!");
	}
    // set new value
    this->count++;
    for (int i = this->count - 1; i >= pos; i--) {
		(*this)[i] = (*this)[i - 1];
	}
	(*this)[pos] = item;
	
	this->end = (this->end + 1) % this->buffer_size;
}

void CircularBuffer::erase(int first, int last) {
    // testing arguments
	if (last < 0 || last > this->count - 1 ||
		first < 0 || first > this->count - 1 ||
		first >= last ||
		this->empty()) {
		throw std::invalid_argument("Error: Wrong arguments!");
	}
	int j = first;
    for (int i = last; i < count; i++) {
		(*this)[j] = (*this)[i];
	}
	this->count -= last - first;
	this->end = (this->start + this->count) % this->buffer_size;
}

void CircularBuffer::clear() {
    // delete old memory then making new memory
    // updating other fields
	delete[] this->buffer;
	this->buffer = new value_type[this->buffer_size];
	this->start = 0;
	this->end = 0;
	this->count = 0;
}

// output
std::ostream& operator<<(std::ostream& out, const CircularBuffer& cb) {
	for (int i = 0; i < cb.size(); i++) {
		out << cb[i] << " ";
	}
	out << std::endl;
	return out;
}

// compare
bool operator==(const CircularBuffer& a, const CircularBuffer& b) {
    // if size isn`t equal then buffers isn`t equal too
	if (a.size() != b.size()) return false;
    // else compare buffers by elements
	int j = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) return false;
	}
	return true;
}
bool operator!=(const CircularBuffer& a, const CircularBuffer& b) {
    // just not for operator ==
	return !(a == b);
}
