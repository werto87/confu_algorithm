#include "confu_algorithm/constrainedNumber.hxx"
#include <catch2/catch.hpp>
#include <cstdint>
#include <vector>
using namespace confu_algorithm;

TEST_CASE ("ConstrainedNumber")
{
  SECTION ("applies predicate", "[ConstrainedNumber]") { ConstrainedNumber<int, notZero, 1>{}; }

  SECTION ("copy", "[ConstrainedNumber]")
  {
    auto original = ConstrainedNumber<int, notZero, 1>{};
    auto copy = original;
    REQUIRE (original == copy);
  }

  SECTION ("compare", "[ConstrainedNumber]")
  {
    auto x = ConstrainedNumber<int, notZero, 1>{};
    auto y = ConstrainedNumber<int, notZero, 1>{ 42 };
    REQUIRE (x < y);
  }

  SECTION ("greater2", "[ConstrainedNumber]") { ConstrainedNumber<int, greaterSomeValue<2>, 3>{}; }

  SECTION ("set to not allowed value", "[ConstrainedNumber]")
  {
    auto test = ConstrainedNumber<int, notZero, 1>{};
    REQUIRE_THROWS (test.setValue (0));
  }
}