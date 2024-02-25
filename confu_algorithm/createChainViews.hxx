//
// Created by walde on 12/16/23.
//

#pragma once
#include <__iterator/concepts.h>
#include <iterator>
#include <span>
#include <vector>

// TODO add option to short cut this function for example for return a chain with length of 3 or more if there is not one with length 3 or more return the longest
//  In this case it would be nice to stop looking for more chains and just return
/**
 * breaks the chain if pred evaluates to false does contain the breaking element
 * @param cbegin iterator to the begin of a continuous sequence
 * @param cend iterator to the last element+1 of a continuous sequence
 * @param pred predicate to evaluate when to break the chain. The predicate gets called with a subsequence representing the current chain.
 * @return spans to view the chains created with the predicate pred from the sequence starting at cbegin and ending at cend
 *
 * example input:
 * sequence [0,0,1,1,1]
 * pred next number should be the same as current number
 * example output:
 * [[0,0],[1,1,1]]
 */
namespace confu_algorithm
{

auto
createChainViewsIncludeBreakingElement (std::contiguous_iterator auto cbegin, std::contiguous_iterator auto cend, auto pred)
{
  if (std::span{ cbegin, cend }.size () == 1)
    {
      return std::vector<decltype (std::span{ cbegin, cend })>{ { cbegin, cend } };
    }
  else
    {
      auto result = std::vector<decltype (std::span{ cbegin, cend })>{};
      auto subsequenceBegin = cbegin;
      for (auto itr = cbegin; itr != cend; ++itr)
        {
          if (not pred (std::span{ subsequenceBegin, itr + 1 }))
            {
              result.push_back ({ subsequenceBegin, itr + 1 });
              subsequenceBegin = itr + 1;
            }
          else if (cend - 1 == itr)
            {
              result.push_back ({ subsequenceBegin, itr + 1 });
            }
        }
      return result;
    }
}

/**
 * breaks the chain if pred evaluates to false does NOT contain the breaking element
 * @param cbegin iterator to the begin of a continuous sequence
 * @param cend iterator to the last element+1 of a continuous sequence
 * @param pred predicate to evaluate when to break the chain. The predicate gets called with a subsequence representing the current chain.
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
  if (std::span{ cbegin, cend }.size () == 1)
    {
      return std::vector<decltype (std::span{ cbegin, cend })>{ { cbegin, cend } };
    }
  else
    {
      auto result = std::vector<decltype (std::span{ cbegin, cend })>{};
      auto subsequenceBegin = cbegin;
      for (auto itr = cbegin + 1; itr != cend; ++itr)
        {
          if (not pred (std::span{ subsequenceBegin, itr + 1 }))
            {
              result.push_back ({ subsequenceBegin, itr });
              subsequenceBegin = itr;
            }
          if (cend - 1 == itr)
            {
              result.push_back ({ subsequenceBegin, cend });
            }
        }
      return result;
    }
}
}