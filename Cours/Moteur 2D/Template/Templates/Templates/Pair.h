#pragma once
template<typename T, typename U>
class Pair
{
public:

	T first;
	U second;

	Pair(T f, U s) : first(f), second(s) {}
};

