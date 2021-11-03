#include<iostream>
#include<vector>
#include<string>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<list>
#include<algorithm>

/*
1) �������� ���������������� �������� ��� ������� cout. �������� �� pcout. ����������, ����� ��������� ������� ����� ���������� � pcout � ���������� ���������� � �������. ����������������� ������ pcout.
2) ����������� �������, ������������ i-�� ������� ����� (��������, ���������� ������� ����� ����� 15485863). ���������� ����������� �� ��������� ������. � ������� ���������� �������� ����������.
3) ��������������� ��������� ��������. ���� ��� �������� (2 ������): ������ � ���. ������ �������� ����� ����. ��� ���� � ������ ���� ���� ���� ��������. ��� �������� ����, ������ ��� �������� ���� � ���������� ���������.
*/



std::vector<std::string> names{ "TV", "Laptop", "Cellphone", "Denture", "Child", "Fork", "Bitcoin", "Wife's photo", "Toy car", "Teethbrush", "Mom" };


struct Item
{
	Item(std::string _name, size_t _itemValue) :
		name(_name), itemValue(_itemValue) {}

	bool operator< (Item& val)
	{
		return itemValue < val.itemValue;
	}

	friend bool operator== (const Item& val, const Item& val2);

	std::string name;
	size_t itemValue;
};

bool operator== (const Item& val, const Item& val2)
{
	return val.itemValue == val2.itemValue;
}

Item generateItem()
{
	return Item(names[rand() % names.size()], rand() % 10000);
}

std::list<Item> data;
std::condition_variable notif;
std::mutex oLock;
std::mutex writeLock;

void pcout(std::string value)
{
	std::lock_guard<std::mutex> lock(writeLock);
	std::cout << value << " >:" << std::this_thread::get_id << ":< \n\n";
}

void Thief() {
	std::unique_lock<std::mutex> lock(oLock);
	notif.wait(lock, []() {return !data.empty(); });
	auto most_valueable = std::max_element(data.begin(), data.end());
	if (most_valueable != data.end())
	{

		pcout("Thief stole the " + (*most_valueable).name + " for " + std::to_string((*most_valueable).itemValue) + "$");
		data.remove(*most_valueable);
	}
};

void Owner(Item value) {
	//std::unique_lock<std::mutex> lock(oLock);
	notif.notify_one();
	data.push_back(value);
	pcout("Owner brings the " + value.name + " for " + std::to_string(value.itemValue) + "$");
};


bool isPrime(int n)
{
	if (n < 2)
	{
		return false;
	}
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

void CountPrimes(size_t limit)
{

	for (size_t i = 0; i != limit; i++)
	{
		if (isPrime(i)) {
			std::unique_lock<std::mutex> lock(oLock);
			pcout("Meanwhile, " + std::to_string(i) + " is prime!!!");
		};
	}
}

int main()
{
	std::thread thread1([]() {
		for (size_t i = 0; data.size() < 10; i++)	// �������� ��� �������. �������� ����� �������� � ���-�� 10 ��, �������, ��� ��� ��� ������� :D
		{
			Owner(generateItem());
		}
		});
	std::thread thread2([]() {
		for (size_t i = 0; data.size() < 10; i++)
		{
			Thief();
		}
		});
	std::thread thread3(CountPrimes, 500);
	thread1.join();
	thread2.join();
	thread3.join();

	return 0;
}