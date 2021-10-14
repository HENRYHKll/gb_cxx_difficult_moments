#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <list>
#include <numeric>
#include <string>
#include <vector>

template <class T>
class Iter
{
private:
    T it;

public:
    Iter(const T position = 0)
        : it(position)
    {
    }
    bool  operator!=(const Iter<T>& obj) const { return it != obj.it; }
    bool  operator==(const Iter<T>& obj) const { return it == obj.it; }
    Iter& operator++()
    {
        ++it;
        return *this;
    }
    T operator*() const { return it; }
};

template <class T>
class Range
{
private:
    T m_from;
    T m_to;

public:
    Range(T from, T to)
        : m_from(from)
        , m_to(to)
    {
    }
    Iter<T> begin() const { return Iter<T>(m_from); }
    Iter<T> end() const { return Iter<T>(m_to); }
};

void ListPushBeck(std::list<double>& l)
{

    const double sum = std::accumulate(l.begin(), l.end(), 0.0);
    l.push_back(sum / l.size());
}
void PrintList(std::list<double>& l)
{
    for (int n : l)
    {
        std::cout << n << ", ";
    }
    std::cout << std::endl;
}

class Matrix
{
    std::vector<std::vector<int>> m_matrix;
    std::size_t                   m_size;
    int                           m_det;
    int Det(std::vector<std::vector<int>> matrix, size_t size)
    {
        if (size == 1)
            return matrix[0][0];
        if (size == 2)
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        else
        {
            std::vector<std::vector<int>> minor;
            minor.assign(size - 1, { 0 });
            std::for_each(
                minor.begin(), minor.end(), [size](std::vector<int>& m_rows) {
                    m_rows.assign(size - 1, 0);
                });
            for (size_t k = 0; k < size; ++k)
            {
                int a = 0;
                for (size_t i = 1; i < size; ++i)
                {
                    int b = 0;
                    for (size_t j = 0; j < size; ++j)
                    {
                        if (j != k)
                        {
                            minor[a][b] = matrix[i][j];
                            ++b;
                        }
                    }
                    ++a;
                }
                m_det += static_cast<int>(pow(-1, k + 2)) * matrix[0][k] *
                         Det(minor, size - 1);
            }
            return m_det;
        }
    }

public:
    Matrix(std::vector<std::vector<int>> matrix)
        : m_matrix(matrix)
        , m_size(matrix.size())
        , m_det(0)
    {
    }
    int getDeterminant() { return Det(m_matrix, m_size); }
};

int main(int argc, char* argv[])
{
    //    std::list<double>             l{ 1, 2, 3 };
    //    std::vector<std::vector<int>> my_matrix{ { 1, 2, 3 },
    //                                             { 3, 8, 2 },
    //                                             { 7, 2, 2 } };
    //    Matrix                        m(my_matrix);
    //    std::cout << "Determinant: " << m.getDeterminant() << std::endl;

    for (auto i : Range<int>{ 10, 20 })
        std::cout << i << " ";
    std::cout << std::endl;

    return std::cout.good() ? 0 : 1;
}
