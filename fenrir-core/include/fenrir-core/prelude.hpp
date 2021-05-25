#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>

#define FENRIR_UNREACHABLE fenrir::_unreachable(__FILE__, __LINE__)

namespace fenrir::core {

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using usize = size_t;

using cstr = const char *;

[[noreturn]] void _unreachable(cstr file, i32 line);

} // namespace fenrir::core