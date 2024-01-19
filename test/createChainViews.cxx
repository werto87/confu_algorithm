#include "confu_algorithm/createChainViews.hxx"
#include <catch2/catch.hpp>

TEST_CASE ("createChainViews create same number chain")
{
  auto nums = std::vector{ 1, 1, 1, 2, 2, 3, 3, 3 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto sequence) {
    auto const &lastItem = *(sequence.end () - 1);
    auto const &secondLastItem = *(sequence.end () - 2);
    return lastItem == secondLastItem;
  });
  REQUIRE (result.size () == 3);
  REQUIRE (result.at (0).size () == 3);
  REQUIRE (result.at (1).size () == 2);
  REQUIRE (result.at (2).size () == 3);
}

TEST_CASE ("createChainViews all false")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5, 6, 7, 8 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto) { return false; });
  REQUIRE (result.size () == 8);
  REQUIRE (result.at (0).size () == 1);
  REQUIRE (result.at (7).size () == 1);
}

TEST_CASE ("createChainViews first 2 true rest false")
{
  auto nums = std::vector{ 1, 1, 3, 4, 5, 6, 7, 8 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto sequence) {
    auto const &lastItem = *(sequence.end () - 1);
    auto const &secondLastItem = *(sequence.end () - 2);
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
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto sequence) {
    auto const &lastItem = *(sequence.end () - 1);
    auto const &secondLastItem = *(sequence.end () - 2);
    return lastItem - secondLastItem == 1;
  });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0).size () == 8);
}

TEST_CASE ("createChainViews last two false")
{
  auto nums = std::vector{ 1, 1, 1, 1, 1, 1, 7, 8 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto sequence) {
    auto const &lastItem = *(sequence.end () - 1);
    auto const &secondLastItem = *(sequence.end () - 2);
    return lastItem - secondLastItem == 1;
  });
  REQUIRE (result.size () == 7);
  REQUIRE (result.at (6).size () == 2);
}

TEST_CASE ("createChainViews sum less than 4")
{
  auto nums = std::vector{ 1, 1, 1, 1, 1, 1, 3, 2 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto sequence) { return std::accumulate (sequence.begin (), sequence.end (), 0) < 4; });
  REQUIRE (result.size () == 4);
  REQUIRE (result.at (0).size () == 3);
  REQUIRE (result.at (1).size () == 3);
  REQUIRE (result.at (2).size () == 1);
  REQUIRE (result.at (2)[0] == 3);
  REQUIRE (result.at (3).size () == 1);
  REQUIRE (result.at (3)[0] == 2);
}

TEST_CASE ("createChainViews one element all true")
{
  auto nums = std::vector{ 1 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto) { return true; });
  REQUIRE (result.size () == 1);
}

TEST_CASE ("createChainViews one element all false")
{
  auto nums = std::vector{ 1 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto) { return false; });
  REQUIRE (result.size () == 1);
}

TEST_CASE ("createChainViews two elements all true")
{
  auto nums = std::vector{ 1, 1 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto) { return true; });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0).size () == 2);
}

TEST_CASE ("createChainViews two elements only first true second false")
{
  auto nums = std::vector{ 3, 3 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto sequence) { return std::accumulate (sequence.begin (), sequence.end (), 0) < 4; });
  REQUIRE (result.size () == 2);
  REQUIRE (result.at (0).size () == 1);
}

TEST_CASE ("createChainViews pred evals to true all the time returns a vector wit one span containing all elements")
{
  auto nums = std::vector{ 1, 2 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto) { return true; });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0)[0] == 1);
  REQUIRE (result.at (0)[1] == 2);
}

TEST_CASE ("createChainViewsIncludeBreakingElement all true")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5 };
  auto result = createChainViewsIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto) { return true; });
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
  auto result = createChainViewsIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto) { return false; });
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
  auto result = createChainViewsIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto sequence) {
    auto vec = std::vector<int>{ sequence.begin (), sequence.end () };
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

TEST_CASE ("createChainViewsIncludeBreakingElement first two true and last true rest false")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5 };
  auto result = createChainViewsIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto sequence) {
    auto vec = std::vector<int>{ sequence.begin (), sequence.end () };
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
  auto result = createChainViewsIncludeBreakingElement (nums.cbegin (), nums.cend (), [] (auto sequence) { return sequence.back () == 4 || sequence.back () == 5; });
  REQUIRE (result.size () == 4);
  REQUIRE (result.at (3).size () == 2);
  REQUIRE (result.at (0)[0] == 1);
  REQUIRE (result.at (1)[0] == 2);
  REQUIRE (result.at (2)[0] == 3);
  REQUIRE (result.at (3)[0] == 4);
  REQUIRE (result.at (3)[1] == 5);
}