// wrapper class for using smart pointers with external libraies
#include "smart_pointer_wrapper.hpp"

template<class T>
Wrapper<T>::Wrapper(std::unique_ptr<T> owner, std::shared_ptr<T> user) {
	owner(std::move(owner)), user(std::move(user));
	user.startUsing(owner.get());
}

template<class T>
void Wrapper<T>::bar() const {
	user.bar(owner.get());
}

template<class T>
Wrapper<T>::~Wrapper() {
	user.finishUsing(owner.get());
}
