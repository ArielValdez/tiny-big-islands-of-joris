#pragma once
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
	ThreadPool(size_t threads)
	{
		for (size_t i = 0; i < threads; i++)
		{
			Workers.emplace_back([this]
				{
					while (true)
					{
						std::function<void()> job;

						{
							std::unique_lock<std::mutex> lock(QueueMutex);

							Condition.wait(lock, [this] { return Stop || !Jobs.empty(); });

							if (Stop && Jobs.empty()) {
								return;
							}

							job = std::move(Jobs.front());
							Jobs.pop();
						}

						job();
					}
				});
		}
	}

	void Enqueue(std::function<void()> job)
	{
		{
			std::unique_lock<std::mutex> lock(QueueMutex);
			Jobs.push(job);
		}

		Condition.notify_one();
	}

	~ThreadPool()
	{
		std::unique_lock<std::mutex> lock(QueueMutex);
		Stop = true;

		Condition.notify_all();

		for (std::thread& worker : Workers) {
			worker.join();
		}
	}

private:
	std::vector<std::thread> Workers;
	std::queue<std::function<void()>> Jobs;

	std::mutex QueueMutex;
	std::condition_variable Condition;

	bool Stop = false;
};