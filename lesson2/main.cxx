#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Timer
{
private:
    using clock_t  = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;

    std::string                      m_name;
    std::chrono::time_point<clock_t> m_beg;
    double                           elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg)
            .count();
    }

public:
    Timer()
        : m_beg(clock_t::now())
    {
    }
    Timer(std::string name)
        : m_name(name)
        , m_beg(clock_t::now())
    {
    }

    void start(std::string name)
    {
        m_name = name;
        m_beg  = clock_t::now();
    }
    void print() const
    {
        std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
    }
};

template <typename T>
T Swap(T& first, T& second)
{
    const T temp = first;
    first        = second;
    second       = temp;
}

template <typename T>
void SortPointers(std::vector<T*>& ptr_arr)
{
    size_t size = ptr_arr.size();
    for (size_t i = 0; i < size - 1; ++i)
    {
        for (size_t j = 0; j < size - 1; ++j)
        {
            if (*ptr_arr[j] > *ptr_arr[j + 1])
            {
                Swap(ptr_arr[j], ptr_arr[j + 1]);
            }
        }
    }
}

template <typename T>
void Print(const std::vector<T*>& ptr_arr)
{
    for (auto ptr : ptr_arr)
        std::cout << *ptr << ' ';
    std::cout << std::endl;
}

void lettersCounCIFFind(std::ifstream&     file,
                        int64_t&           count,
                        const std::string& letters)
{

    for (std::string word; file >> word;)
        count += std::count_if(word.begin(), word.end(), [&](const char& ch) {
            return letters.find(ch) != std::string::npos;
        });
}
void lettersCounterCIFFor(std::ifstream&     file,
                          int64_t&           count,
                          const std::string& letters)
{
    for (std::string word; file >> word;)
    {
        count += std::count_if(word.begin(), word.end(), [&](const char& ch) {
            for (char vowel : letters)
                if (vowel == ch)
                    return true;
            return false;
        });
    }
}
void lettersCounterForFind(std::ifstream&     file,
                           int64_t&           counter,
                           const std::string& letters)
{

    for (char ch; file.get(ch);)
    {
        const auto got = letters.find(ch);
        if (got != std::string::npos)
            ++counter;
    }
}

void VovelConterForFor(std::ifstream& file, int64_t& counter)
{
    for (std::string word; file >> word;)
        for (char ch : word)
        {
            if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' ||
                ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
                ++counter;
        }
}

void PrintCount(int64_t& counter)
{
    std::cout << "Total vowel characters:\t" << counter << std::endl;
}

int main(int argc, char* argv[])
{
    const std::string vowels("AEIOUYaeiouy");
    std::ifstream     file("war-and-peace.txt");
    if (!file.is_open())
    {
        std::cout << "ERROR FILE OR NOT FILE" << std::endl;
        return std::cout.good() ? 0 : 1;
    }

    int64_t     counter = 0;
    const Timer timerForCifFind("Count_If and Find");
    lettersCounCIFFind(file, counter, vowels);
    timerForCifFind.print();
    PrintCount(counter);
    file.close();

    counter = 0;
    file.open("war-and-peace.txt");
    const Timer timerForCifFor("Count_If and For");
    lettersCounterCIFFor(file, counter, vowels);
    timerForCifFor.print();
    PrintCount(counter);
    file.close();

    counter = 0;
    file.open("war-and-peace.txt");
    const Timer timerForFind("For and Find");
    lettersCounterForFind(file, counter, vowels);
    timerForFind.print();
    PrintCount(counter);
    file.close();

    counter = 0;
    file.open("war-and-peace.txt");
    const Timer timerForFor("For and For");
    VovelConterForFor(file, counter);
    timerForFor.print();
    PrintCount(counter);
    file.close();

    return std::cout.good() ? 0 : 1;
}
