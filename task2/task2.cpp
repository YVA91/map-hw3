#include <algorithm>
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <random>

template<typename Iterator, typename T>
T para_forEach(Iterator first, Iterator last, T init)
{
	int length = std::distance(first, last);
	int max_chunk_size = std::thread::hardware_concurrency();
	if (length <= max_chunk_size)
	{
		return std::for_each(first, last, init);
	}
	else
	{
		Iterator mid_point = first;
		std::advance(mid_point, length / 2);
		std::future<T> first_half_result = std::async(para_forEach<Iterator, T>, first, mid_point, init);

		return std::for_each(mid_point, last, init);
	}
}

void fn(int x) {
	std::cout << x * 2 << std::endl;
}

int main()
{
	std::vector<int> V{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
	auto  res = para_forEach(V.begin(), V.end(), fn);

	return 0;
}