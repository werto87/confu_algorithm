#ifndef D9077A7B_F0F8_4687_B460_C6D43C94F8AF
#define D9077A7B_F0F8_4687_B460_C6D43C94F8AF
#include <span>
#include <string>
#include <vector>

/**
 *
 * @param cbegin iterator to the begin of a continuous sequence
 * @param cend iterator to the last element+1 of a continuous sequence
 * @param pred predicate to evaluate when to break the chain
 * @return spans to view the chains created with the predicate pred from the sequence starting at cbegin and ending at cend
 */
auto
createChainViews (auto cbegin, auto cend, auto pred)
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

#endif /* D9077A7B_F0F8_4687_B460_C6D43C94F8AF */
