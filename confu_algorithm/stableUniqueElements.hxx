//
// Created by walde on 12/16/23.
//
#include <ranges>
#include <set>
#pragma once
namespace confu_algorithm{
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
  for (auto num : sequence | std::views::filter (onlyUniqueNumbers))
    {
      result.push_back (num);
    }
  return result;
}
}