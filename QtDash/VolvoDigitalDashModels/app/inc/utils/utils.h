#ifndef UTILS_H
#define UTILS_H

#include <type_traits>

namespace DashUtils {
    template <typename E>
    constexpr auto to_underlying(E e) noexcept {
        return static_cast<std::underlying_type_t<E>>(e);
    }
}

#endif // UTILS_H
