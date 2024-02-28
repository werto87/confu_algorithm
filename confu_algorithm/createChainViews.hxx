//
// Created by walde on 12/16/23.
//

#pragma once
#include <algorithm>
#include <boost/numeric/conversion/cast.hpp>
#include <cstdint>
#include <iterator>
#include <span>
#include <type_traits>
#include <vector>

namespace confu_algorithm
{
// TODO add option to short cut this function for example for return a chain with length of 3 or more if there is not one with length 3 or more return the longest
/**
 * @brief returns vector with indexes where a chain will break. Does NOT contain the index of the breaking element.
 * @param cbegin iterator to the begin of a sequence
 * @param cend iterator to the last element+1 of a sequence
 * @param pred predicate to evaluate when to break the chain. The predicate gets called with a beginning and end of a sequence representing the current chain.
 * @return returns vector with indexes where a chain will break
 *
 * example input:
 * sequence [0,0,1,1,1]
 * pred next number should be the same as current number
 * example output:
 * [2,5]
 * this means:
 * the chain starts from index 0 goes to index 2 [0,0] index 2 marks the end which is the last element plus one
 * the second chain starts from index 2 goes to index 5 [1,1,1] index 5 marks the end which is the last element plus one
 */
template <typename T = uint64_t>
std::vector<T>
chainBreaks (auto cbegin, auto cend, auto pred)
{
  auto const containerSize = std::distance (cbegin, cend);
  if (containerSize == 0)
    {
      return std::vector<T>{};
    }
  else if (containerSize == 1)
    {
      return std::vector<T>{ 0 };
    }
  else
    {
      auto result = std::vector<T>{};
      auto subsequenceBegin = cbegin;
      for (auto itr = cbegin + 1; itr != cend; ++itr)
        {
          if (not pred (subsequenceBegin, itr + 1))
            {
              result.push_back (boost::numeric_cast<T> (std::distance (cbegin, itr)));
              subsequenceBegin = itr;
            }
          if (cend - 1 == itr)
            {
              result.push_back (boost::numeric_cast<T> (std::distance (cbegin, cend)));
            }
        }
      return result;
    }
}

/**
 * @brief returns vector with indexes where a chain will break. Does contain the index of the breaking element.
 * @param cbegin iterator to the begin of a sequence
 * @param cend iterator to the last element+1 of a sequence
 * @param pred predicate to evaluate when to break the chain. The predicate gets called with a beginning and end of a sequence representing the current chain.
 * @return returns vector with indexes where a chain will break
 *
 * example input:
 * sequence [0,0,1,1,1]
 * pred next number should be the same as current number
 * example output:
 * [3,5]
 * this means:
 * the chain starts from index 0 goes to index 3 [0,0,1] index 3 marks the end which is the last element plus one
 * the second chain starts from index 3 goes to index 5 [1,1] index 5 marks the end which is the last element plus one
 */
template <typename T = uint64_t>
std::vector<T>
chainBreaksIncludeBreakingElement (auto cbegin, auto cend, auto pred)
{
  auto const containerSize = std::distance (cbegin, cend);
  if (containerSize == 1)
    {
      return std::vector<T>{ 0 };
    }
  else
    {
      auto result = std::vector<T>{};
      auto subsequenceBegin = cbegin;
      for (auto itr = cbegin; itr != cend; ++itr)
        {
          if (not pred (subsequenceBegin, itr + 1))
            {
              result.push_back (boost::numeric_cast<T> (std::distance (cbegin, itr + 1)));
              subsequenceBegin = itr + 1;
            }
          else if (cend - 1 == itr)
            {
              result.push_back (boost::numeric_cast<T> (std::distance (cbegin, cend)));
            }
        }
      return result;
    }
}

/**
 * breaks the chain if pred evaluates to false does NOT contain the breaking element
 * @param cbegin iterator to the begin of a continuous sequence
 * @param cend iterator to the last element+1 of a continuous sequence
 * @param pred predicate to evaluate when to break the chain. The predicate gets called with a beginning and end of a sequence representing the current chain.
 * @return spans to view the chains created with the predicate pred from the sequence starting at cbegin and ending at cend
 *
 * example input:
 * sequence [0,0,1,1,1]
 * pred next number should be the same as current number
 * example output:
 * [[0,0],[1,1,1]]
 */

auto
createChainViews (std::contiguous_iterator auto cbegin, std::contiguous_iterator auto cend, auto pred)
{
  auto _chainBreaks = chainBreaks (cbegin, cend, pred);
  auto result = std::vector<decltype (std::span{ cbegin, cend })>{};
  std::ranges::for_each (_chainBreaks, [beginOfChain = uint64_t{}, &result, cbegin] (auto const &value) mutable {
    result.push_back ({ cbegin + boost::numeric_cast<int64_t> (beginOfChain), cbegin + boost::numeric_cast<int64_t> (value) });
    beginOfChain = value;
  });
  return result;
}

//  In this case it would be nice to stop looking for more chains and just return
/**
 * breaks the chain if pred evaluates to false does contain the breaking element
 * @param cbegin iterator to the begin of a continuous sequence
 * @param cend iterator to the last element+1 of a continuous sequence
 * @param pred predicate to evaluate when to break the chain. The predicate gets called with a beginning and end of a sequence representing the current chain.
 * @return spans to view the chains created with the predicate pred from the sequence starting at cbegin and ending at cend
 *
 * example input:
 * sequence [0,0,1,1,1]
 * pred next number should be the same as current number
 * example output:
 * [[0,0,1],[1,1]]
 */

auto
createChainViewsIncludeBreakingElement (std::contiguous_iterator auto cbegin, std::contiguous_iterator auto cend, auto pred)
{
  auto _chainBreaks = chainBreaksIncludeBreakingElement (cbegin, cend, pred);
  auto result = std::vector<decltype (std::span{ cbegin, cend })>{};
  std::ranges::for_each (_chainBreaks, [beginOfChain = uint64_t{}, &result, cbegin] (auto const &value) mutable {
    result.push_back ({ cbegin + boost::numeric_cast<int64_t> (beginOfChain), cbegin + boost::numeric_cast<int64_t> (value) });
    beginOfChain = value;
  });
  return result;
}

}