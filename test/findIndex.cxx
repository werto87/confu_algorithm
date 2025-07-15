#include "confu_algorithm/findIndex.hxx"
#include <catch2/catch.hpp>
#include <cstdint>
#include <vector>

using namespace confu_algorithm;

TEST_CASE ("findIndex")
{
  auto vec = std::vector<int>{ 0, 1, 2, 3, 4, 5, 6 };
  SECTION ("0")
  {
    auto const &numerToCheck = 0;
    auto const &result = findIndex (vec, numerToCheck);
    REQUIRE (result);
    REQUIRE (result.value () == numerToCheck);
  }
  SECTION ("1")
  {
    auto const &numerToCheck = 1;
    auto const &result = findIndex (vec, numerToCheck);
    REQUIRE (result);
    REQUIRE (result.value () == numerToCheck);
  }
  SECTION ("5")
  {
    auto const &numerToCheck = 5;
    auto const &result = findIndex (vec, numerToCheck);
    REQUIRE (result);
    REQUIRE (result.value () == numerToCheck);
  }
  SECTION ("6")
  {
    auto const &numerToCheck = 6;
    auto const &result = findIndex (vec, numerToCheck);
    REQUIRE (result);
    REQUIRE (result.value () == numerToCheck);
  }
}

struct NestedInt
{
  int nestedInt{};
};

TEST_CASE ("findIndex with pred")
{
  auto vec = std::vector<NestedInt>{ { 0 }, { 1 }, { 2 }, { 3 }, { 4 }, { 5 }, { 6 } };
  SECTION ("0")
  {
    auto const &numerToCheck = 0;
    auto const &result = findIndex (vec, numerToCheck, &NestedInt::nestedInt);
    REQUIRE (result);
    REQUIRE (result.value () == numerToCheck);
  }
  SECTION ("1")
  {
    auto const &numerToCheck = 1;
    auto const &result = findIndex (vec, numerToCheck, &NestedInt::nestedInt);
    REQUIRE (result);
    REQUIRE (result.value () == numerToCheck);
  }
  SECTION ("5")
  {
    auto const &numerToCheck = 5;
    auto const &result = findIndex (vec, numerToCheck, &NestedInt::nestedInt);
    REQUIRE (result);
    REQUIRE (result.value () == numerToCheck);
  }
  SECTION ("6")
  {
    auto const &numerToCheck = 6;
    auto const &result = findIndex (vec, numerToCheck, &NestedInt::nestedInt);
    REQUIRE (result);
    REQUIRE (result.value () == numerToCheck);
  }
}