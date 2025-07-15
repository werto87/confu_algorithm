#pragma once

#include <optional>

namespace confu_algorithm
{
[[nodiscard]]
std::optional<int64_t>
findIndex (auto const &vec, auto const &value)
{
  auto it = std::ranges::find (vec, value);
  if (it != vec.end ())
    {
      return std::ranges::distance (vec.begin (), it);
    }
  else
    {
      return std::nullopt;
    }
}
[[nodiscard]]
std::optional<int64_t>
findIndex (auto const &vec, auto const &value, auto pred)
{
  auto it = std::ranges::find (vec, value, pred);
  if (it != vec.end ())
    {
      return std::ranges::distance (vec.begin (), it);
    }
  else
    {
      return std::nullopt;
    }
}
}