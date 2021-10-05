#include <algorithm>
#include <any>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <tuple>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>

struct Person
{
    std::string                m_last_name, m_first_name;
    std::optional<std::string> m_patronymic_name;

    Person(const std::string          first_name,
           const std::string          last_name,
           std::optional<std::string> patronymic_name)
        : m_last_name(last_name)
        , m_first_name(first_name)
        , m_patronymic_name(patronymic_name)
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Person& person);
    friend bool operator==(const Person& person1, const Person& person2);
    friend bool operator==(const Person& person1, const std::string& str);
    friend bool operator<(const Person& person1, const Person& person2);
};

std::ostream& operator<<(std::ostream& out, const Person& person)
{
    out << person.m_last_name << " " << person.m_first_name << " ";
    if (person.m_patronymic_name)
        out << *person.m_patronymic_name;

    return out;
}

bool operator==(const Person& person1, const Person& person2)
{
    return std::tie(person1.m_last_name,
                    person1.m_first_name,
                    person1.m_patronymic_name) ==
           std::tie(person2.m_last_name,
                    person2.m_first_name,
                    person2.m_patronymic_name);
}
bool operator==(const Person& person1, const std::string& str)
{
    return person1.m_last_name == str;
}

bool operator<(const Person& person1, const Person& person2)
{
    return std::tie(person1.m_last_name,
                    person1.m_first_name,
                    person1.m_patronymic_name) <
           std::tie(person2.m_last_name,
                    person2.m_first_name,
                    person2.m_patronymic_name);
    ;
}

struct PhoneNumber
{
    int                m_country_code_numder, m_city_code_numder;
    std::optional<int> m_add_number;
    std::string        m_tel_numder;
    PhoneNumber()
        : m_country_code_numder(0)
        , m_city_code_numder(0)
        , m_add_number(std::nullopt)
    {
    }
    PhoneNumber(int                country_code_numder,
                int                city_code_numder,
                const std::string& tel_numder,
                std::optional<int> add_number)
        : m_country_code_numder(country_code_numder)
        , m_city_code_numder(city_code_numder)
        , m_tel_numder(tel_numder)
        , m_add_number(add_number)
    {
    }

    friend std::ostream& operator<<(std::ostream&      out,
                                    const PhoneNumber& phone_n);
    friend bool operator<(const PhoneNumber& pn1, const PhoneNumber& pn2);
};

bool operator<(const PhoneNumber& pn1, const PhoneNumber& pn2)
{
    return std::tie(pn1.m_country_code_numder,
                    pn1.m_city_code_numder,
                    pn1.m_tel_numder,
                    pn1.m_add_number) < std::tie(pn2.m_country_code_numder,
                                                 pn2.m_city_code_numder,
                                                 pn2.m_tel_numder,
                                                 pn2.m_add_number);
    ;
}
std::ostream& operator<<(std::ostream& out, const PhoneNumber& phone_n)
{
    out << "+" << phone_n.m_country_code_numder << "("
        << phone_n.m_city_code_numder << ")" << phone_n.m_tel_numder;
    if (phone_n.m_add_number)
    {
        out << " " << *phone_n.m_add_number;
    }

    return out;
}

class PhoneBook
{

    std::vector<std::pair<Person, PhoneNumber>> book;

public:
    PhoneBook(std::ifstream& file)
    {
        if (!file.is_open())
            std::cout << "NOT FILE!" << std::endl;
        std::string line;
        while (std::getline(file, line))
        {
            std::string        f_name, l_name, patronymic, number, add_number;
            uint16_t           country_code, city_code;
            std::istringstream list(line);
            list >> l_name >> f_name >> patronymic >> country_code >>
                city_code >> number >> add_number;
            std::optional<uint16_t> t_add_number;

            if (patronymic == "-")
                patronymic = "";

            if (add_number == "-")
                t_add_number = std::nullopt;
            else
                t_add_number = std::stoi(add_number);

            book.push_back(std::make_pair(
                Person(l_name, f_name, patronymic),
                PhoneNumber(country_code, city_code, number, t_add_number)));
        }
        file.close();
    }

    // void                 print() { std::cout << book.size(); }

    void SortByName()
    {
        std::sort(book.begin(),
                  book.end(),
                  [](const std::pair<Person, PhoneNumber>& pair1,
                     const std::pair<Person, PhoneNumber>& pair2) {
                      return pair1.first < pair2.first;
                  });
    }
    void SortByPhone()
    {
        std::sort(book.begin(),
                  book.end(),
                  [](const std::pair<Person, PhoneNumber>& pair1,
                     const std::pair<Person, PhoneNumber>& pair2) {
                      return pair1.second < pair2.second;
                  });
    }

    friend std::ostream&                 operator<<(std::ostream&    out,
                                    const PhoneBook& PhoneBook);
    std::tuple<std::string, PhoneNumber> GetPhoneNumber(
        const std::string& surname)
    {
        PhoneNumber phone_number;
        int16_t     counter = 0;

        auto find_surname = [surname, &counter, &phone_number](
                                const std::pair<Person, PhoneNumber>& pair1) {
            if (pair1.first == surname)
            {
                ++counter;
                phone_number = pair1.second;
            }
        };

        std::for_each(book.begin(), book.end(), find_surname);

        std::string output = "";
        if (!counter)
            output = "entry not found";
        else if (counter > 1)
            output = "several entries";
        return { output, phone_number };
    }
    void ChangePhoneNumber(const Person&      person,
                           const PhoneNumber& phone_number)
    {
        auto find_person =
            [&person](const std::pair<Person, PhoneNumber>& pair1) {
                return pair1.first == person;
            };
        auto output = std::find_if(book.begin(), book.end(), find_person);
        if (output != book.end())
            output->second = phone_number;
    }
};
std::ostream& operator<<(std::ostream& out, const PhoneBook& pb)
{
    for (auto [first, second] : pb.book)
        std::cout << first << " " << second << std::endl;
    return out;
}
int main()
{

    std::ifstream file("PhoneBook.txt"); // file("../data/PhoneBook.txt"); unix
                                         // путь к файлу PhoneBook.txt
    PhoneBook book(file);
    std::cout << book;

    std::cout << "------SortByPhone-------" << std::endl;
    book.SortByPhone();
    std::cout << book;

    std::cout << "------SortByName--------" << std::endl;
    book.SortByName();
    std::cout << book;

    std::cout << "-----GetPhoneNumber-----" << std::endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона этого
    // человека, либо строку с ошибкой
    auto print_phone_number = [&book](const std::string& surname) {
        std::cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (std::get<0>(answer).empty())
            std::cout << std::get<1>(answer);
        else
            std::cout << std::get<0>(answer);
        std::cout << std::endl;
    };

    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");

    std::cout << "----ChangePhoneNumber----" << std::endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
                           PhoneNumber{ 7, 123, "15344458", std::nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
                           PhoneNumber{ 16, 465, "9155448", 13 });
    std::cout << book;
    return std::cout.good() ? 0 : 1;
}
