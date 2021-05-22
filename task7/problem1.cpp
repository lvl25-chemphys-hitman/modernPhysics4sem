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

using namespace std;
using namespace chrono;


static int r_rand(int minRange, int maxRange) {
	return rand() % (maxRange - minRange + 1) + minRange;
}

void computePi(unsigned n, unsigned  side, unsigned qSide, unsigned& count) {
	for (int i = 0; i < n; i++) {
		unsigned x = r_rand(0, side);
		unsigned y = r_rand(0, side);
		if ((x * x + y * y) < qSide) {
			count++;
		}
	}

}

int main() {
    
    unsigned num = 300000;
	unsigned count = 0;
	unsigned side = 1000;
	unsigned sqrSide = side * side;
	unsigned n = unsigned int(num / 4);
	vector<unsigned int> data{0, 0, 0, 0};


	auto start = high_resolution_clock::now();

	srand( (unsigned) time(0));

	

	std::vector<std::thread> threads;

	for (unsigned i = 0; i < 4; i++) {
		threads.push_back(std::thread(computePi, n, side, sqrSide, ref(data[i])));
	}

	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	count = std::accumulate(data.begin(), data.end(), 0);
	std::cout << double(count * 4) / num << endl;

	auto end = high_resolution_clock::now();
	auto elapsedNs = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << elapsedNs.count() << " mcs";

}