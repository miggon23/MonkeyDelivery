#pragma once
#include <memory>
#include <cassert>

template<typename T>
class Singleton {
protected:
	Singleton() {
	}

public:

	Singleton<T>& operator=(const Singleton<T>& o) = delete;
	Singleton(const Singleton<T>& o) = delete;

	virtual ~Singleton() {
	}

	template<typename ...Targs>
	inline static T* init(Targs &&...args) {
		assert(instance_.get() == nullptr);
		instance_.reset(new T(std::forward<Targs>(args)...));
		return instance_.get();
	}

	inline static void close() {
		instance_.reset();
	}

	inline static T* instance() {
		
		if (instance_.get() == nullptr) {
			init();
		}
		return instance_.get();
	}

private:
	static std::unique_ptr<T> instance_;
};

template<typename T>
std::unique_ptr<T> Singleton<T>::instance_;