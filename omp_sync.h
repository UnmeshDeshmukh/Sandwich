// Mutex declaration and definition

#include <omp.h>

class Mutex {
public:
	Mutex() {
		omp_init_lock(&_mutex);
	}
	~Mutex() {
		omp_destroy_lock(&_mutex);
	}
	void lock() {
		omp_set_lock(&_mutex);
	}
	void unlock() {
		omp_unset_lock(&_mutex);
	}

	static Mutex* getMutex() {
		if (mutexInstance != NULL) {
			return mutexInstance;
		} else {
			mutexInstance = new Mutex;
			return mutexInstance;
		}
	}

private:
	omp_lock_t _mutex;
	static Mutex* mutexInstance;
};

Mutex* Mutex::mutexInstance;

