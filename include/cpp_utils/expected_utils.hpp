#ifndef CPP_UTILS_EXPECTED_UTILS_HPP_INCLUDE
#define CPP_UTILS_EXPECTED_UTILS_HPP_INCLUDE

#include <expected>
#include <type_traits>

namespace ml {

    namespace detail {
        
        template <typename T>
        struct is_expected : std::false_type{};
        
        template <typename T, typename U>
        struct is_expected<std::expected<T, U>> : std::true_type{};
        
        template <typename T>
        inline constexpr bool is_expected_v = is_expected<T>::value;
        
    } // namespace detail

template <typename T, typename U>
    requires (
        detail::is_expected_v<T>
            && detail::is_expected_v<std::remove_cvref_t<U>>
    )
T transform_error(U&& value)
{
    return std::forward<U>(value).transform_error([]<typename E>(E&& error) { 
        return std::visit([]<typename X>(X&& element) {
            return typename T::error_type{ std::forward<X>(element) };
        }, std::forward<E>(error));
    });
}

} // namespace ml

#endif
