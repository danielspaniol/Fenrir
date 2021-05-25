#pragma once

#include "fenrir-core/prelude.hpp"

#include <ostream>

namespace fenrir::core {

struct Color {
  enum T : u8 { BLACK, WHITE };

  constexpr Color() : m_data{WHITE} {}
  constexpr Color(T data) : m_data{data} {}
  constexpr operator T() const { return m_data; }

  constexpr auto flipped() const -> Color {
    return T{static_cast<u8>(1 - m_data)};
  }

  friend auto operator<<(std::ostream &stream, Color c) -> std::ostream &;
  void dump() const;

private:
  T m_data;
};

} // namespace fenrir::core