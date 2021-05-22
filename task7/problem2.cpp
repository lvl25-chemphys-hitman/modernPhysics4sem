#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

using namespace chrono;


template<typename Iterator, typename T>
struct accumulate_block {
	void operator()(Iterator first, Iterator last, T& result) {
		result = std::accumulate(first, last, result);
	}
};


template<typename Iterator, typename T>
T parallelAccumulate(Iterator first, Iterator last, T init, unsigned long const numThreads) {
	unsigned long const length = std::distance(first, last);
	if (!length)
		return init;

	unsigned long const blockSize = length / numThreads;

	std::vector<T> results(numThreads);
	std::vector<std::thread> threads(numThreads - 1);

	Iterator blockStart = first;
	for (unsigned long i = 0; i < (numThreads - 1); ++i) {
		Iterator blockEnd = blockStart;
		std::advance(blockEnd, blockSize);
		threads[i] = std::thread(accumulate_block<Iterator, T>(), blockStart, blockEnd, std::ref(results[i]));
		blockStart = blockEnd;
	}

	accumulate_block<Iterator, T>() (blockStart, last, results[numThreads - 1]);

	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	return
		std::accumulate(results.begin(), results.end(), init);
};

int main(void)
{
	std::vector < int > vect(100);

	std::iota(vect.begin(), vect.end(), 1);

	float x;
	HDC hDC = GetDC(GetConsoleWindow());
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hDC, Pen);
	MoveToEx(hDC, 10, 0, NULL);
	LineTo(hDC, 10, 260);
	MoveToEx(hDC, 0, 250, NULL);
	LineTo(hDC, 200, 250);

	auto s = high_resolution_clock::now();
	parallelAccumulate(vect.begin(), vect.end(), 0, 1);
	auto e = high_resolution_clock::now();
	auto oldtime = std::chrono::duration_cast<std::chrono::microseconds>(e - s);

	for (unsigned long i = 2; i < 15; i++)
	{
		auto start = high_resolution_clock::now();
		parallelAccumulate(vect.begin(), vect.end(), 0, i);
		auto end = high_resolution_clock::now();
		auto elapsedNs = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		MoveToEx(hDC, 10 * (i - 1) + 10, -0.2 * oldtime.count() + 250, NULL);
		LineTo(hDC, 10 * i + 10, -0.2 * elapsedNs.count() + 250);
		oldtime = elapsedNs;
	}
	std::cin.clear();
	std::cin.ignore(32767, '\n');
	std::cin.get();
	return 0;

}