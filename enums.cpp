#include <cassert>
#include <type_traits>
#include <iostream>

enum class Color
{
    Red,
    Green,
    Blue
};

enum class Shape
{
    Square,
    Circle,
    Triangle
};

enum class DrawObject
{
    Square,
    Circle,
    Triangle
};

void doSomething(DrawObject draw)
{
}

template <typename T>
concept Enum = std::is_enum_v<T>;

// Primarily for type deduction help -- see makeEnumIndex<>()
template <Enum E, typename T>
struct EnumConstructorHelper
{
    using EnumType = E;
    using DataType = T;

    EnumType mEnum;
    DataType mData;

    constexpr bool operator==(const EnumConstructorHelper& other) const
    {
        return this->mEnum == other.mEnum;
    }
};

template<auto First, auto... Rest>
constexpr auto first_value = First;

template <EnumConstructorHelper... Helpers>
consteval auto makeEnumIndex()
{
    using FirstType = std::remove_cvref_t<decltype(first_value<Helpers...>)>;
    using EnumType = FirstType::EnumType;
    using DataType = FirstType::DataType;
    return [](const EnumType e){
        DataType result;
            ((e == Helpers.mEnum ? (result = Helpers.mData, true) : false), ...);
        return result;
    };
}

int main (int argc, char *argv[]) {
    constexpr auto index = makeEnumIndex<
    {Color::Blue, Shape::Triangle}
            >();
    std::cout << static_cast<int>(index(Color::Blue));
    return 0;
}
