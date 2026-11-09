#include "uincampus/version.hpp"

namespace uin {
std::string_view version()
{
    return UIN_VERSION; // macro fournie par CMake
}
} // namespace uin
