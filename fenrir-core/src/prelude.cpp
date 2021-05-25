#include "fenrir-core/prelude.hpp"

#include <cstdlib>
#include <iostream>

namespace fenrir::core {

[[noreturn]] void _unreachable(cstr file, i32 line) {
  std::cerr << "Unreachable code reached " << file << '.' << line << std::endl;
  std::exit(EXIT_FAILURE);
}

} // namespace fenrir::core