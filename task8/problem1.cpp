#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <chrono>
#include <numeric>
#include <mutex>

using namespace std;
using namespace chrono;

std::mutex cntMutex;


static int rrand(int rangeMin, int rangeMax) {
    return rand() % (rangeMax - rangeMin + 1) + rangeMin;
}

void ThePi(unsigned n, unsigned  side, unsigned qside, unsigned &cnt) {

    for (unsigned i = 0; i < n; ++i) {
        unsigned x = rrand(0, side);
        unsigned y = rrand(0, side);

        if ((x * x + y * y) < qside) {
        	cntMutex.lock();
        	++cnt;
        	cntMutex.unlock();
        }
    }

}

int main() {
    auto start = high_resolution_clock::now();

    srand((unsigned)time(0));

    unsigned NUMBER = 300000;
    unsigned   cnt = 0;
    unsigned  side = 1000;
    unsigned qside = side * side;
    unsigned n = unsigned (NUMBER / 4);

    std::vector<std::thread> threads;
	for (unsigned i = 0; i <4; ++i) {

		threads.push_back(std::thread(ThePi, n, side, qside, ref(cnt)));

	}
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    std::cout << (double) cnt * 4 / NUMBER << "\n";

    auto end = high_resolution_clock::now();
    auto elapsedNs = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "time is " << elapsedNs.count() << " mcs\n";
}


