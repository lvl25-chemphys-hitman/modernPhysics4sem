#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

void myCOut(int i)
{
	std::cout << ' ' << i;
}

template<typename Iterator, typename F>
void parallelForeach(Iterator first, Iterator last, F function)
{
	unsigned long const length = std::distance(first, last);

	if (!length)
		return;

	unsigned long const per_thread = 30;
	if (length < (2 * per_thread)) {
		for_each(first, last, function);
	}
	else {
		Iterator const midle = first + length / 2;
		std::future<void> first_half =
			std::async(&parallel_for_each<Iterator, F>,
				first, midle, function);
		parallel_for_each(midle, last, function);
		first_half.get();
	}
}

int main(int arg_c, char** arg_v)
{
	std::vector<int> Vector1;
	Vector1.push_back(10);
	Vector1.push_back(20);
	Vector1.push_back(30);

	std::cout << "my vector contains of";
	parallelForeach(Vector1.begin(), Vector1.end(), myCOut);
	std::cout << endl;


}