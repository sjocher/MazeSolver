#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "deque.hpp"

TEST_CASE( "Test declaration", "[deque]" ) {
	Deque<int> d;
}

TEST_CASE("Test pushFront", "[deque]") {
	Deque<int> d;
	d.pushFront(1);
	REQUIRE(d.front() == 1);
	d.pushFront(2);
	REQUIRE(d.front() == 2);
	for (int i = 0; i < 10; i++) {
		d.pushFront(i);
	}
}

TEST_CASE("Test pushBack", "[deque]") {
	Deque<int> a;
	for (int i = 0; i < 10; i++) {
		a.pushBack(i);
	}
	REQUIRE(a.front() == 0);
	REQUIRE(a.back() == 9);
	a.popBack();
	REQUIRE(a.back() == 8);
}

TEST_CASE("Test popBack", "[deque]") {
	Deque<int> d;
	d.pushBack(1);
	REQUIRE(d.front() == 1);
	REQUIRE(d.back() == 1);
	d.popBack();
}


TEST_CASE( "Test pushBack and popFront", "[deque]" ) {
	Deque<int> a;
	for (int i = 0; i < 10; i++) {
		a.pushBack(i);
	}
	for (int i = 0; i < 10; i++) {
		assert(a.front() == i);
		a.popFront();
	}
	assert(a.isEmpty());
}

TEST_CASE("Test copy constructor", "[deque]") {
	Deque<int> d;
	for (int i = 0; i < 10; i++) {
		d.pushBack(i);
	}
	REQUIRE(d.front() == 0);
	REQUIRE(d.back() == 9);
	Deque<int> a(d);
	REQUIRE(a.front() == 0);
	REQUIRE(a.back() == 9);
	for (int i = 0; i < 10; i++) {
		assert(a.front() == i);
		a.popFront();
	}
	REQUIRE(a.isEmpty());
	REQUIRE(d.isEmpty() == false);
}

TEST_CASE("Test copy assignment operator", "[deque]") {
	Deque<int> d;
	for (int i = 0; i < 10; i++) {
		d.pushBack(i);
	}
	REQUIRE(d.front() == 0);
	REQUIRE(d.back() == 9);
	Deque<int> a = d;
	REQUIRE(a.front() == 0);
	REQUIRE(a.back() == 9);
	for (int i = 0; i < 10; i++) {
		assert(a.front() == i);
		a.popFront();
	}
	REQUIRE(a.isEmpty());
	REQUIRE(d.isEmpty() == false);
}