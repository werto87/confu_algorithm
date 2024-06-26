#pragma once
#include <algorithm>
#include <cassert>
#include <complex>
#include <functional>
#include <iostream>
#include <iterator>
#include <optional>
#include <ranges>
#include <type_traits>
#include <vector>
namespace confu_algorithm
{

// Copied from https://en.cppreference.com/w/cpp/algorithm/ranges/lower_bound
template <std::forward_iterator I, std::sentinel_for<I> S, class T, class Proj = std::identity, std::indirect_strict_weak_order<const T *, std::projected<I, Proj> > Comp = std::ranges::less>
constexpr I
binaryFind (I first, S last, const T &value, Comp comp = {}, Proj proj = {})
{
  first = std::ranges::lower_bound (first, last, value, comp, proj);
  return first != last && !comp (value, std::invoke (proj, *first)) ? first : last;
}
}