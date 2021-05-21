#include <mutex>
#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

using namespace std;

struct Element {
	int value;
	int priority;
	Element(int v = 0, int p = 0){
		value = v;
		priority = p;
	}
};

class PriorityQueue {
	static const int MAX_SIZE = 10;

	Element a[MAX_SIZE];
	int size;
	mutex ch;
	condition_variable bell;

	void up(int i) 	{
		while (i != 0 && a[i].priority > a[(i - 1) / 2].priority) {
			swap(a[i], a[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
	}

	void down(int i) {
		while (i < size / 2) {
			int maxI = 2 * i + 1;
			if (2 * i + 2 < size && a[2 * i + 2].priority > a[2 * i + 1].priority)
				maxI = 2 * i + 2;
			if (a[i].priority >= a[maxI].priority)
				return;
			swap(a[i], a[maxI]);
			i = maxI;
		}
	}

public:

	PriorityQueue()	{
		size = 0;
	}

	void enqueue(int value, int priority) {
		unique_lock<mutex> ul(ch);
		bell.wait(ul, [=]()	{return size + 1 < MAX_SIZE;});

		a[size++] = Element(value, priority);
		up(size - 1);

		bell.notify_all();
	}

	Element dequeue() {
		unique_lock<mutex> ul(ch);
		bell.wait(ul, [=]() {	return size > 0;});

		swap(a[0], a[--size]);
		down(0);

		bell.notify_all();
		return a[size];
	}

	bool isEmpty() {
		return size == 0;
	}

};

int main() {
	PriorityQueue myQueue;

	cout << "+/- | value | priority" << endl;

	thread adding([](PriorityQueue &myQueue) {
		for (int i = 0; i < 1000000000; ++i) {
			this_thread::sleep_for (chrono::milliseconds(rand() % 1000));
			int val = 0x7fffff & (i << i);
			int priority = (i << 5) * (i >> 2);
			cout << "+ " << val<<" " << priority<< endl;
			myQueue.enqueue(val, priority);
		}
	}, ref(myQueue));

	thread removing([](PriorityQueue &myQueue) {
		for (int i = 0; i < 1000000000; ++i){
			this_thread::sleep_for (chrono::milliseconds(rand() % 1000));
			Element e = myQueue.dequeue();
			cout <<"- " << e.val <<" "<< e.priority << endl;
		}
	}, ref(myQueue));

	if (adding.joinable())
		adding.join();
	if (removing.joinable())
		removing.join();

	return 0;
}
