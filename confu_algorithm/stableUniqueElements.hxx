//
// Created by walde on 12/16/23.
//
#pragma once
#include <algorithm>
#include <ranges>
#include <set>

namespace confu_algorithm
{
/**
 * requires: the elements of the sequence to be comparable using <
 * @param sequence a sequence
 * @return copy of sequence minus duplicate elements
 */
template <typename T>
T
stableUniqueElements (T const &sequence)
{
  auto result = T{};
  using sequencElementType = typename std::decay<decltype (result.front ())>::type;
  auto const onlyUniqueNumbers = [mySet = std::set<sequencElementType>{}] (auto num) mutable { return mySet.insert (num).second; };
  std::ranges::copy_if (sequence, std::back_inserter (result), onlyUniqueNumbers);
  return result;
}
}