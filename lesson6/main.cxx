#include <cmath>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex m;

bool isPrime(uint64_t n)
{
    if (n == 2)
        return true;
    if (n < 2 || n % 2 == 0)
        return false;
    for (uint64_t i = 3; i <= sqrt(n); ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

uint64_t fPrime(uint32_t n, uint32_t& count)
{
    uint64_t current = 0;
    while (count < n)
    {
        ++current;
        if (isPrime(current))
            ++count;
    }
    return current;
}

uint16_t findPrimeNumber(uint32_t n)
{
    uint32_t              conter = 0;
    std::future<uint64_t> prime_nuber =
        std::async(std::launch::async, fPrime, n, std::ref(conter));
    while (conter * 100 / n < 100)
    {
        std::cout << conter * 100 / n << "% " << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    return prime_nuber.get();
}

void pcout(const int n)
{
    std::lock_guard m_loock(m);
    std::cout << "thread is " << n << std::endl;
}

int main(/*int argc, char* argv[]*/)
{

    std::thread thread1(pcout, 1);
    std::thread thread2(pcout, 2);
    thread1.join();
    thread2.join();

    const auto prime_number = findPrimeNumber(1'000'000);
    std::cout << "Prime number = " << prime_number << std::endl;
}
