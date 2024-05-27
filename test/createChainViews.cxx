#include "confu_algorithm/createChainViews.hxx"
#include <catch2/catch.hpp>
#include <cstdint>
#include <vector>

using namespace confu_algorithm;

TEST_CASE ("createChainViews create same number chain")
{
  auto nums = std::vector{ 1, 1, 1, 2, 2, 3, 3, 3 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto const &, auto const &cend) {
    auto const &lastItem = *(cend - 1);
    auto const &secondLastItem = *(cend - 2);
    return lastItem == secondLastItem;
  });
  REQUIRE (result.size () == 3);
  REQUIRE (result.at (0).size () == 3);
  REQUIRE (result.at (1).size () == 2);
  REQUIRE (result.at (2).size () == 3);
}

TEST_CASE ("createChainViews first 2 true rest false")
{
  auto nums = std::vector{ 1, 1, 3, 4, 5, 6, 7, 8 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto const &, auto const &cend) {
    auto const &lastItem = *(cend - 1);
    auto const &secondLastItem = *(cend - 2);
    return lastItem == secondLastItem;
  });
  REQUIRE (result.size () == 7);
  REQUIRE (result.at (0).size () == 2);
  REQUIRE (result.at (0)[0] == 1);
  REQUIRE (result.at (0)[1] == 1);
  REQUIRE (result.at (6).size () == 1);
}

TEST_CASE ("createChainViews greater by one chain")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5, 6, 7, 8 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto const &, auto const &cend) {
    auto const &lastItem = *(cend - 1);
    auto const &secondLastItem = *(cend - 2);
    return lastItem - secondLastItem == 1;
  });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0).size () == 8);
}

TEST_CASE ("createChainViews last two false")
{
  auto nums = std::vector{ 1, 1, 1, 1, 1, 1, 7, 8 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto const &, auto const &cend) {
    auto const &lastItem = *(cend - 1);
    auto const &secondLastItem = *(cend - 2);
    return lastItem - secondLastItem == 1;
  });
  REQUIRE (result.size () == 7);
  REQUIRE (result.at (6).size () == 2);
}

TEST_CASE ("createChainViews sum less than 4")
{
  auto nums = std::vector{ 1, 1, 1, 1, 1, 1, 3, 2 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto const &cbegin, auto const &cend) { return std::accumulate (cbegin, cend, 0) < 4; });
  REQUIRE (result.size () == 4);
  REQUIRE (result.at (0).size () == 3);
  REQUIRE (result.at (1).size () == 3);
  REQUIRE (result.at (2).size () == 1);
  REQUIRE (result.at (2)[0] == 3);
  REQUIRE (result.at (3).size () == 1);
  REQUIRE (result.at (3)[0] == 2);
}

TEST_CASE ("createChainViews empty vector")
{
  auto vec = std::vector<uint8_t>{};
  REQUIRE (createChainViews (vec.cbegin (), vec.cend (), [] (auto const &cbegin, auto const &cend) { return std::vector (cbegin, cend).front () % 2; }).empty ());
}

TEST_CASE ("createChainViews one element all true")
{
  auto nums = std::vector{ 1 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto, auto) { return true; });
  REQUIRE (result.size () == 1);
}

TEST_CASE ("createChainViews one element all false")
{
  auto nums = std::vector{ 1 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto, auto) { return false; });
  REQUIRE (result.size () == 1);
}

TEST_CASE ("createChainViews two elements all true")
{
  auto nums = std::vector{ 1, 1 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto, auto) { return true; });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0).size () == 2);
}

TEST_CASE ("createChainViews two elements only first true second false")
{
  auto nums = std::vector{ 3, 3 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto const &cbegin, auto const &cend) { return std::accumulate (cbegin, cend, 0) < 4; });
  REQUIRE (result.size () == 2);
  REQUIRE (result.at (0).size () == 1);
}
// TODO the tests names got to long for catch2
TEST_CASE ("createChainViews pred evals to true all the time returns a vector")
{
  auto nums = std::vector{ 1, 2 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto, auto) { return true; });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0)[0] == 1);
  REQUIRE (result.at (0)[1] == 2);
}

TEST_CASE ("createChainViewsIncludeBreakingElement all true")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5 };
  auto result = createChainViewsIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto, auto) { return true; });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0).size () == 5);
  REQUIRE (result.at (0)[0] == 1);
  REQUIRE (result.at (0)[1] == 2);
  REQUIRE (result.at (0)[2] == 3);
  REQUIRE (result.at (0)[3] == 4);
  REQUIRE (result.at (0)[4] == 5);
}

TEST_CASE ("createChainViewsIncludeBreakingElement all false")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5 };
  auto result = createChainViewsIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto, auto) { return false; });
  REQUIRE (result.size () == 5);
  REQUIRE (result.at (0)[0] == 1);
  REQUIRE (result.at (1)[0] == 2);
  REQUIRE (result.at (2)[0] == 3);
  REQUIRE (result.at (3)[0] == 4);
  REQUIRE (result.at (4)[0] == 5);
}

TEST_CASE ("createChainViewsIncludeBreakingElement first two true rest false")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5 };
  auto result = createChainViewsIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto const &cbegin, auto const &cend) {
    auto vec = std::vector<int>{ cbegin, cend };
    auto sum = std::accumulate (vec.cbegin (), vec.cend (), 0);
    return sum < 3;
  });
  REQUIRE (result.size () == 4);
  REQUIRE (result.at (0).size () == 2);
  REQUIRE (result.at (0)[0] == 1);
  REQUIRE (result.at (0)[1] == 2);
  REQUIRE (result.at (1)[0] == 3);
  REQUIRE (result.at (2)[0] == 4);
  REQUIRE (result.at (3)[0] == 5);
}

TEST_CASE ("createChainViewsIncludeBreakingElement first two true and")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5 };
  auto result = createChainViewsIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto const &cbegin, auto const &cend) {
    auto vec = std::vector<int>{ cbegin, cend };
    auto sum = std::accumulate (vec.cbegin (), vec.cend (), 0);
    return sum < 3 || vec.back () == 5;
  });
  REQUIRE (result.size () == 4);
  REQUIRE (result.at (0).size () == 2);
  REQUIRE (result.at (0)[0] == 1);
  REQUIRE (result.at (0)[1] == 2);
  REQUIRE (result.at (1)[0] == 3);
  REQUIRE (result.at (2)[0] == 4);
  REQUIRE (result.at (3)[0] == 5);
}

TEST_CASE ("createChainViewsIncludeBreakingElement last two true rest false")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5 };
  auto result = createChainViewsIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto const &cbegin, auto const &cend) {
    auto vec = std::vector (cbegin, cend);
    return vec.back () == 4 || vec.back () == 5;
  });
  REQUIRE (result.size () == 4);
  REQUIRE (result.at (3).size () == 2);
  REQUIRE (result.at (0)[0] == 1);
  REQUIRE (result.at (1)[0] == 2);
  REQUIRE (result.at (2)[0] == 3);
  REQUIRE (result.at (3)[0] == 4);
  REQUIRE (result.at (3)[1] == 5);
}

TEST_CASE ("createChainViewsIncludeBreakingElement empty vector")
{
  auto vec = std::vector<uint8_t>{};
  REQUIRE (createChainViewsIncludeBreakingElement (vec.cbegin (), vec.cend (), [] (auto const &cbegin, auto const &cend) { return std::vector (cbegin, cend).front () % 2; }).empty ());
}

TEST_CASE ("chainBreaks all false")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5, 6, 7, 8 };
  auto result = chainBreaks (nums.cbegin (), nums.cend (), [] (auto, auto) { return false; });
  REQUIRE (result.size () == 8);
  REQUIRE (result.at (0) == 1);
  REQUIRE (result.at (1) == 2);
  REQUIRE (result.at (2) == 3);
  REQUIRE (result.at (3) == 4);
  REQUIRE (result.at (4) == 5);
  REQUIRE (result.at (5) == 6);
  REQUIRE (result.at (6) == 7);
  REQUIRE (result.at (7) == 8);
}

TEST_CASE ("chainBreaks first 2 true rest false")
{
  auto nums = std::vector{ 1, 1, 3, 4, 5, 6, 7, 8 };
  auto result = chainBreaks (nums.cbegin (), nums.cend (), [] (auto, auto cend) {
    auto const &lastItem = *(cend - 1);
    auto const &secondLastItem = *(cend - 2);
    return lastItem == secondLastItem;
  });
  REQUIRE (result.size () == 7);
  REQUIRE (result.at (0) == 2);
  REQUIRE (result.at (1) == 3);
  REQUIRE (result.at (2) == 4);
  REQUIRE (result.at (3) == 5);
  REQUIRE (result.at (4) == 6);
  REQUIRE (result.at (5) == 7);
  REQUIRE (result.at (6) == 8);
}

TEST_CASE ("chainBreaks last two false")
{
  auto nums = std::vector{ 1, 1, 1, 1, 1, 1, 7, 8 };
  auto result = chainBreaks (nums.cbegin (), nums.cend (), [] (auto, auto cend) {
    auto const &lastItem = *(cend - 1);
    auto const &secondLastItem = *(cend - 2);
    return lastItem == secondLastItem;
  });
  REQUIRE (result.size () == 3);
  REQUIRE (result.at (0) == 6);
  REQUIRE (result.at (1) == 7);
  REQUIRE (result.at (2) == 8);
}

TEST_CASE ("chainBreaks sum less than 4")
{
  auto nums = std::vector{ 1, 1, 1, 1, 1, 1, 3, 2 };
  auto result = chainBreaks (nums.cbegin (), nums.cend (), [] (auto const &cbegin, auto const &cend) { return std::accumulate (cbegin, cend, 0) < 4; });
  REQUIRE (result.size () == 4);
  REQUIRE (result.at (0) == 3);
  REQUIRE (result.at (1) == 6);
  REQUIRE (result.at (2) == 7);
  REQUIRE (result.at (3) == 8);
}

TEST_CASE ("chainBreaks one element all true")
{
  auto nums = std::vector{ 1 };
  auto result = chainBreaks (nums.cbegin (), nums.cend (), [] (auto, auto) { return true; });
  REQUIRE (result.size () == 1);
}

TEST_CASE ("chainBreaks one element all false")
{
  auto nums = std::vector{ 1 };
  auto result = chainBreaks (nums.cbegin (), nums.cend (), [] (auto, auto) { return false; });
  REQUIRE (result.size () == 1);
}

TEST_CASE ("chainBreaks two elements all true")
{
  auto nums = std::vector{ 1, 1 };
  auto result = chainBreaks (nums.cbegin (), nums.cend (), [] (auto, auto) { return true; });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0) == 2);
}

TEST_CASE ("chainBreaks two elements only first true second false")
{
  auto nums = std::vector{ 3, 3 };
  auto result = chainBreaks (nums.cbegin (), nums.cend (), [] (auto const &cbegin, auto const &cend) { return std::accumulate (cbegin, cend, 0) < 4; });
  REQUIRE (result.size () == 2);
  REQUIRE (result.at (0) == 1);
}

TEST_CASE ("chainBreaks pred evals to true all the time returns a vector")
{
  auto nums = std::vector{ 1, 2 };
  auto result = chainBreaks (nums.cbegin (), nums.cend (), [] (auto, auto) { return true; });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0) == 2);
}

TEST_CASE ("chainBreaks empty vector")
{
  auto vec = std::vector<uint8_t>{};
  REQUIRE (chainBreaks (vec.cbegin (), vec.cend (), [] (auto const &cbegin, auto const &cend) { return std::vector (cbegin, cend).front () % 2; }).empty ());
}

TEST_CASE ("chainBreaksIncludeBreakingElement all false")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5, 6, 7, 8 };
  auto result = chainBreaksIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto, auto) { return false; });
  REQUIRE (result.size () == 8);
  REQUIRE (result.at (0) == 1);
  REQUIRE (result.at (1) == 2);
  REQUIRE (result.at (2) == 3);
  REQUIRE (result.at (3) == 4);
  REQUIRE (result.at (4) == 5);
  REQUIRE (result.at (5) == 6);
  REQUIRE (result.at (6) == 7);
  REQUIRE (result.at (7) == 8);
}

TEST_CASE ("chainBreaksIncludeBreakingElement sum less than 4")
{
  auto nums = std::vector{ 1, 1, 1, 1, 1, 1, 3, 2 };
  auto result = chainBreaksIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto const &cbegin, auto const &cend) { return std::accumulate (cbegin, cend, 0) < 4; });
  REQUIRE (result.size () == 3);
  REQUIRE (result.at (0) == 4);
  REQUIRE (result.at (1) == 7);
  REQUIRE (result.at (2) == 8);
}

TEST_CASE ("chainBreaksIncludeBreakingElement one element all true")
{
  auto nums = std::vector{ 1 };
  auto result = chainBreaksIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto, auto) { return true; });
  REQUIRE (result.size () == 1);
}

TEST_CASE ("chainBreaksIncludeBreakingElement one element all false")
{
  auto nums = std::vector{ 1 };
  auto result = chainBreaksIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto, auto) { return false; });
  REQUIRE (result.size () == 1);
}

TEST_CASE ("chainBreaksIncludeBreakingElement two elements all true")
{
  auto nums = std::vector{ 1, 1 };
  auto result = chainBreaksIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto, auto) { return true; });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0) == 2);
}

TEST_CASE ("chainBreaksIncludeBreakingElement two elements only first true second false")
{
  auto nums = std::vector{ 3, 3 };
  auto result = chainBreaksIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto const &cbegin, auto const &cend) { return std::accumulate (cbegin, cend, 0) < 4; });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0) == 2);
}

TEST_CASE ("chainBreaksIncludeBreakingElement pred evals to true all the time returns")
{
  auto nums = std::vector{ 1, 2 };
  auto result = chainBreaksIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto, auto) { return true; });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0) == 2);
}

TEST_CASE ("chainBreaksIncludeBreakingElement empty vector")
{
  auto vec = std::vector<uint8_t>{};
  REQUIRE (chainBreaksIncludeBreakingElement (vec.cbegin (), vec.cend (), [] (auto const &cbegin, auto const &cend) { return std::vector (cbegin, cend).front () % 2; }).empty ());
}

TEST_CASE ("chainBreaks different number")
{
  auto nums = std::vector{ 0, 0, 1, 1, 1 };
  auto result = chainBreaks (nums.cbegin (), nums.cend (), [lastValueOld = nums.front ()] (auto const &, auto const &cend) mutable {
    auto const &lastValueNew = *(cend - 1);
    auto result = lastValueOld == lastValueNew;
    lastValueOld = lastValueNew;
    return result;
  });
  REQUIRE (result.size () == 2);
  REQUIRE (result.at (0) == 2);
  REQUIRE (result.at (1) == 5);
}

TEST_CASE ("chainBreaksIncludeBreakingElement different number")
{
  auto nums = std::vector{ 0, 0, 1, 1, 1 };
  auto result = chainBreaksIncludeBreakingElement (nums.cbegin (), nums.cend (), [lastValueOld = nums.front ()] (auto const &, auto const &cend) mutable {
    auto const &lastValueNew = *(cend - 1);
    auto result = lastValueOld == lastValueNew;
    lastValueOld = lastValueNew;
    return result;
  });
  REQUIRE (result.size () == 2);
  REQUIRE (result.at (0) == 3);
  REQUIRE (result.at (1) == 5);
}

TEST_CASE ("createChainViews different number")
{
  auto nums = std::vector{ 0, 0, 1, 1, 1 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [lastValueOld = nums.front ()] (auto const &cbegin, auto const &cend) mutable {
    auto const lastValueNew = std::vector (cbegin, cend).back ();
    auto result = lastValueOld == lastValueNew;
    lastValueOld = lastValueNew;
    return result;
  });
  REQUIRE (result.size () == 2);
  REQUIRE (result.at (0).size () == 2);
  REQUIRE (result.at (1).size () == 3);
}

TEST_CASE ("createChainViewsIncludeBreakingElement different number")
{
  auto nums = std::vector{ 0, 0, 1, 1, 1 };
  auto result = createChainViewsIncludeBreakingElement (nums.cbegin (), nums.cend (), [lastValueOld = nums.front ()] (auto const &cbegin, auto const &cend) mutable {
    auto const lastValueNew = std::vector (cbegin, cend).back ();
    auto result = lastValueOld == lastValueNew;
    lastValueOld = lastValueNew;
    return result;
  });
  REQUIRE (result.size () == 2);
  REQUIRE (result.at (0).size () == 3);
  REQUIRE (result.at (1).size () == 2);
}