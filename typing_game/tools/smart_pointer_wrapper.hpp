#pragma once

#include "memory"

template<class T>

class Wrapper {
public:
	Wrapper(std::unique_ptr<T> owner, std::shared_ptr<T> user);
	~Wrapper();
	void bar() const;

private:
	std::unique_ptr<T> owner; 
	std::shared_ptr<T> user;
};
