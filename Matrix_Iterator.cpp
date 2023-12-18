#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

template<typename T>
class Matrix
{
private:
    T** matrix;
    int rows;
    int columns;
public:
    Matrix(int r, int c)
    {
        rows = r;
        columns = c;
        matrix = new T*[r];
        for (int i = 0; i < r; ++i)
        {
            matrix[i] = new T[c];
        }
    }

    ~Matrix()
    {
        for (int i = 0; i < rows; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    T* operator[] (int i)
    {
        return matrix[i];
    }

    class SnailIterator
    {
    private:
        T** data;
        int i;
        int j;
        int rows;
        int columns;
        int k = 0;
        long long steps = 0;   
    public:
        SnailIterator(T** data_, int i_, int j_, int rows_, int columns_)
            : data(data_)
            , i(i_)
            , j(j_)
            , rows(rows_)
            , columns(columns_)
        {}

        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::random_access_iterator_tag;

        SnailIterator& operator ++()
        {
            if (j == columns - 1 - k && i != rows - 1 - k)
            {
                ++i;
            }
            else if (j == k && i == 1 + k)
            {
                ++k;
                ++j;
            }
            else if (j == k && i != k)
            {
                --i;
            }
            else if (j != columns - 1 - k && i == k)
            {
                ++j;
            }
            else if (i == rows - 1 - k && j != k)
            {
                --j;
            }
            ++steps;
            return *this;
        }

        SnailIterator& operator --()
        {
            if (j == columns - 1 - k && i != k)
            {
                --i;
            }
            else if (j == k && i == k)
            {
                --k;
                --j;
            }
            else if (j == k && i != rows - 1 - k)
            {
                ++i;
            }
            else if (j != k && i == k)
            {
                --j;
            }
            else if (i == rows - 1 - k && j != columns - 1 - k)
            {
                ++j;
            }
            --steps;
            return *this;
        }

        SnailIterator operator+(const int b) const
        {
            SnailIterator temp(*this);
            for (int i = 0; i < b; ++i)
            {
                ++temp;
            }
            return temp;
        }

        SnailIterator& operator +=(const int b)
        {
            for (int i = 0; i < b; ++i)
            {
                ++(*this);
            }
            return *this;
        }

        SnailIterator operator-(const int b) const
        {
            SnailIterator temp(*this);
            for (int i = 0; i < b; ++i)
            {
                --temp;
            }
            return temp;
        }

        using difference_type = std::ptrdiff_t;
        difference_type operator -(const SnailIterator& it2) const
        {
            return (steps - it2.steps);
        }

        bool operator ==(const SnailIterator& it2) const
        {
            return ((i == it2.i && j == it2.j) && (data == it2.data) && (steps == it2.steps));
        }

        bool operator !=(const SnailIterator& it2) const
        {
            return !(*this == it2);
        }

        bool operator >=(const SnailIterator& it2) const
        {
            return (steps >= it2.steps);
        }

        bool operator >(const SnailIterator& it2) const
        {
            return (steps > it2.steps);
        }

        bool operator <(const SnailIterator& it2) const
        {
            return (steps < it2.steps);
        }

        T& operator*() const
        {
            return data[i][j];
        }
    };

    SnailIterator begin()
    {
        return SnailIterator(matrix, 0, 0, rows, columns);
    }

    SnailIterator end()
    {
        int length = rows * columns;
        SnailIterator end(matrix, 0, 0, rows, columns);
        for (int i = 0; i < length; ++i)
        {
            ++end;
        }
        return end;
    }
};

void FillMatrix(Matrix<int>& matrix, int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            matrix[i][j] = rand() % 100;
        }
    }
}

void PrintOut(Matrix<int>& matrix, int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            std::cout << matrix[i][j] << std::setw(5);
        }
        std::cout << std::setw(2);
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void SortedOrder(Matrix<int>& matrix)
{
    for (Matrix<int>::SnailIterator it = matrix.begin(); it != matrix.end(); ++it)
    {
        std::cout << *it << "  ";
    }
}

int main()
{
    int rows = 0;
    int columns = 0;

    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> columns;

    Matrix<int> matrix(rows, columns);

    FillMatrix(matrix, rows, columns);
    PrintOut(matrix, rows, columns);

    std::sort(matrix.begin(), matrix.end());

    PrintOut(matrix, rows, columns);
    SortedOrder(matrix);
}
