#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <vector>

template <typename T>
void printOnlyUnique(T begin, T end)
{
    std::set<std::string> temp_str;
    copy(begin, end, inserter(temp_str, temp_str.end()));
    copy(temp_str.begin(),
         temp_str.end(),
         std::ostream_iterator<std::string>(std::cout, ", "));
}

int main(/*int argc, char* argv[]*/)
{

    std::vector<std::string> words{ "Bob", "Men", "Car", "Car", "CAr" };
    printOnlyUnique(words.begin(), words.end());
    std::cout << std::endl;

    std::list<std::string> numbers{ "HOME", "HOMe", "one", "two", "two" };
    printOnlyUnique(numbers.begin(), numbers.end());
    std::cout << std::endl;

    std::multimap<int, std::string> mm_str;
    std::string                     input_text;
    const std::string               splitter = ".!?";
    std::cout << "Enter text: ";
    std::getline(std::cin, input_text);
    while (!input_text.empty())
    {
        const size_t pos  = input_text.find_first_of(splitter);
        std::string  temp = input_text.substr(0, pos);
        input_text.erase(0, pos + 1);
        const auto key =
            std::count_if(temp.begin(), temp.end(), [](const char ch) {
                return isspace(ch);
            });
        mm_str.emplace(key, temp);
    }
    std::for_each(mm_str.begin(),
                  mm_str.end(),
                  [](const std::pair<int, std::string>& str) {
                      std::cout << str.second << std::endl;
                  });
}
