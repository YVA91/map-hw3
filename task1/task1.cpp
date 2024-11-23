#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <chrono>

int find_min(std::vector<int> v, int item)
{
	size_t size = v.size();
	int min = item;

	for (int i = item; i < size; i++) {
		if (v[i] < v[min])
		{
			min = i;
		}
	}
	return min;
}

void sort(std::vector<int>& v, std::promise<std::vector<int>> prom) {

	int min = 0;
	int item = 0;

	for (int i = 0; i < v.size(); i++)
	{
		auto f = std::async(std::launch::async, find_min, v, item);
		min = f.get();

		item++;
		int p = v[min];
		v[min] = v[i];
		v[i] = p;
	}
}



int main()
{
	std::vector<int> v{ 8, 2, 4, 6, 9, 3, 1, 5, 7 };

	auto start = std::chrono::steady_clock::now();

	std::promise<std::vector<int>> prom;
	std::future<std::vector<int>> ft_res = prom.get_future();
	sort(std::ref(v), std::move(prom));

	auto end = std::chrono::steady_clock::now();
	auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Time slow: " << diff.count() << std::endl;

	for (const auto& i : v)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return 0;
}