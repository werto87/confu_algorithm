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
template <typename Iterator>
Iterator
binaryFind (Iterator first, Iterator last, auto const &valueToLookFor)
{
  auto pos = std::lower_bound (first, last, valueToLookFor);
  if (pos != last and !(valueToLookFor < *pos))
    {
      return pos;
    }
  else
    {
      return last;
    }
}
}