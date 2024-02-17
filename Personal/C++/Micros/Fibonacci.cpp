#include <iostream>
#include <chrono>
#include <iterator>
#include <utility>
#include <ranges>
#include <algorithm>

struct fib_iterator
{

    using value_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    const std::size_t &operator*() const { return cur_; }

    fib_iterator &operator++()
    {
        cur_ = std::exchange(next_, cur_ + next_);
        return *this;
    }

    fib_iterator &operator++(int)
    {
        auto temp = *this;
        ++*this;
        return temp;
    }

    bool operator==(const fib_iterator &) const = default;

private:
    std::size_t cur_ = 0;
    std::size_t next_ = 1;
};

struct unreachable_sentinel_t
{
};

template <typename T>
bool operator==(const T &, unreachable_sentinel_t) { return false; }

namespace views
{
    constexpr auto fibonacci =
        std::ranges::subrange<fib_iterator, unreachable_sentinel_t>{};
} // namespace views

template <typename Func>
void MeasureAverageFunctionRuntime(Func func, int n, int k)
{
    auto start_time = std::chrono::steady_clock::now();

    std::cout.setstate(std::ios_base::failbit);

    for (int i = 0; i < 1000000; i++)
        func(n, k);

    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

    std::cout.clear();
    std::cout << "Execution time per one function call: " << duration.count() / 1000000 << " nanoseconds" << std::endl;
}

void Fibonacci1(int n, int k)
{

    int a = 0;
    int curr = 0;
    int next = 1;

    while (a < n)
    {
        if (curr % k == 0)
            a++, std::cout << curr << ", ";
        curr = std::exchange(next, curr + next);
    }
    std::cout << std::endl;
}

void Fibonacci2(int n, int k)
{

    auto view =
        views::fibonacci |
        std::views::filter([k](auto i)
                           { return i % k == 0; }) |
        std::views::take(n);

    std::ranges::copy(view, std::ostream_iterator<std::size_t>(std::cout, ", "));
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{

    // MeasureAverageFunctionRuntime(Fibonacci1, 3, 5);
    // MeasureAverageFunctionRuntime(Fibonacci2, 3, 5);

    Fibonacci1(47, 1);
    Fibonacci2(47, 1);

    return 0;
}
