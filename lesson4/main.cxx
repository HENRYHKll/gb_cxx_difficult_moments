#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

template <class T>
void LogVectorParams(const std::vector<T>& v)
{
    std::cout << "Length = " << v.size() << ", "
              << "capacity = " << v.capacity() << "\n";
}

template <class T>
void PrintVector(const std::vector<T>& v)
{
    for (const auto& a : v)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;
}

void FillIntVector(std::vector<int>& v)
{
    for (auto it = v.begin(); it < v.end(); ++it)
    {
        *it = rand();
    }
};

template <class T, class CONTAINER>
void insert_sorted(CONTAINER& v, const T n)
{
    typename CONTAINER::iterator it;
    it = std::upper_bound(v.begin(), v.end(), n);
    v.insert(it, n);

    //    it = find_if(v.begin(), v.end(), [&n](int i) { return (i >= n); });
    //    if (it != v.end())
    //        v.emplace(it, n);
    //    else
    //        v.push_back(n);
}

int main(/*int argc, char* argv[]*/)
{
    std::vector<char> v{ '1', '2', '4', '5' };
    PrintVector(v);
    insert_sorted(v, '2');
    PrintVector(v);

    std::vector<double> analog_signal(100);
    std::vector<int>    digital_signal(100);
    auto input_data = []() { return 3 * sin(rand() * 2.0 * 3.14 / 100); };

    std::generate(analog_signal.begin(), analog_signal.end(), input_data);
    PrintVector(analog_signal);

    std::copy(
        analog_signal.begin(), analog_signal.end(), digital_signal.begin());
    PrintVector(digital_signal);
    auto calc_error =
        std::inner_product(analog_signal.begin(),
                           analog_signal.end(),
                           digital_signal.begin(),
                           0.0,
                           std::plus<double>{},
                           [](double a, double b) { return pow(a - b, 2); });

    std::cout << "Error " << calc_error << std::endl;
}
