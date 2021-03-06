#include <iostream>
#include <vector>
#include <cassert>
#include <string>

template <typename T, typename Cont = std::vector<T>>
class Stack
{
    public:
        Stack() = default;

        Stack(T elem) :
            elems({std::move(elem)})
        { }

        auto push(T const& elem)       -> void;
        auto pop()                     -> void;
        auto top()               const -> T const&;
        auto empty()             const -> bool
        {
            return elems.empty();
        }

    private:
        Cont elems;
};

Stack(char const*) -> Stack<std::string>;

template <typename T, typename Cont>
auto Stack<T, Cont>::push(T const& elem) -> void
{
    elems.push_back(elem);
}

template <typename T, typename Cont>
auto Stack<T, Cont>::pop() -> void
{
    assert(!elems.empty());
    elems.pop_back();
}

template <typename T, typename Cont>
auto Stack<T, Cont>::top() const -> T const&
{
    assert(!elems.empty());
    return elems.back();
}

auto main() -> int
{
    Stack stack_string {"hello"};
    std::cout << stack_string.top().size() << std::endl;
}
