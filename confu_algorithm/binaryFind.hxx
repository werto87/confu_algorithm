#pragma once
#include <algorithm>
#include <cassert>
#include <complex>
#include <iostream>
#include <iterator>
#include <optional>
#include <type_traits>
#include <vector>

namespace confu_algorithm
{
template <typename ValueType>
std::optional<typename std::vector<ValueType>::iterator>
binaryFind (std::vector<ValueType> const &vec, ValueType const &valueToLookFor)
{
  auto pos = std::lower_bound (std::begin (vec), std::end (vec), valueToLookFor);

  if (pos != std::end (vec) and !(valueToLookFor < *pos))
    {
      return pos;
    }
  else
    {
      return std::nullopt;
    }
}
}