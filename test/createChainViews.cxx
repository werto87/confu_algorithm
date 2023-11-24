#include "src/util.hxx"
#include <catch2/catch.hpp>

TEST_CASE ("createChainViews1", "[create same number chain]")
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

TEST_CASE ("createChainViews2", "[create same number chain]")
{
  auto nums = std::vector{ 1, 2, 3, 4, 5, 6, 7, 8 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto sequence) {
    auto const &lastItem = *(sequence.end () - 1);
    auto const &secondLastItem = *(sequence.end () - 2);
    return lastItem == secondLastItem;
  });
  REQUIRE (result.size () == 8);
  REQUIRE (result.at (0).size () == 1);
  REQUIRE (result.at (7).size () == 1);
}

TEST_CASE ("createChainViews3", "[create same number chain]")
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

TEST_CASE ("createChainViews4", "[greater by one chain]")
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

TEST_CASE ("createChainViews5", "[greater by one chain]")
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

TEST_CASE ("createChainViews6", "[sum less than 4]")
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

TEST_CASE ("createChainViews7", "[sum less than 4 only one element]")
{
  auto nums = std::vector{ 1 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto sequence) { return std::accumulate (sequence.begin (), sequence.end (), 0) < 4; });
  REQUIRE (result.size () == 1);
}

TEST_CASE ("createChainViews8", "[sum less than 4 two elements]")
{
  auto nums = std::vector{ 1, 1 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto sequence) { return std::accumulate (sequence.begin (), sequence.end (), 0) < 4; });
  REQUIRE (result.size () == 1);
  REQUIRE (result.at (0).size () == 2);
}

TEST_CASE ("createChainViews9", "[sum less than 4 two elements]")
{
  auto nums = std::vector{ 3, 3 };
  auto result = createChainViews (nums.cbegin (), nums.cend (), [] (auto sequence) { return std::accumulate (sequence.begin (), sequence.end (), 0) < 4; });
  REQUIRE (result.size () == 2);
  REQUIRE (result.at (0).size () == 1);
}