#include <maze/common.h>

namespace cm {

/**
 * @brief Convert char to represent maze into pretty unicode
 */
std::string common::unicode_characters(const char characters)
{
    switch (characters) {
        case empty_value:
            return " ";
        case border:
            return border_unicode;
        case cross:
            return cross_unicode;
        case vertical:
            return vertical_unicode;
        case horizontal:
            return horizontal_unicode;
        case visited_value:
            return visited_value_unicode;
        default:
            return visited_value_unicode;
    }
}

/**
 * @brief Add color for each character type
 */
void common::term_color(const char characters)
{
    switch (characters) {
        case border:
            std::cout << termcolor::green;
            break;
        case empty_value:
        case cross:
        case vertical:
        case horizontal:
            std::cout << termcolor::cyan;
            break;
        case visited_value:
            std::cout << termcolor::yellow;
            break;
        case input:
        case output:
            std::cout << termcolor::red;
            break;
        default:
            std::cout << termcolor::green;
            break;
    }
}

/**
 * @brief Random number generator
 *
 * @param min Minimum bound
 * @param max Maximum boud
 */
uint32_t common::random_number(const uint32_t min, const uint32_t max)
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);
    return dist(rng);
}

} // namespace cm

