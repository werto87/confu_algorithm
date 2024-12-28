#include "confu_algorithm/stableUniqueElements.hxx"
#include <catch2/catch.hpp>
using namespace confu_algorithm;

TEST_CASE ("stableUniqueElements user defined type removes duplicates")
{
  SECTION ("int removes duplicates but with out altering order")
  {
    auto result = stableUniqueElements (std::vector{ 3, 2, 1, 1, 2 });
    REQUIRE (result.size () == 3);
    REQUIRE (result.at (0) == 3);
    REQUIRE (result.at (1) == 2);
    REQUIRE (result.at (2) == 1);
  }
  SECTION ("user defined type removes duplicates")
  {
    struct Student
    {
      // clang-format off
    [[nodiscard]]
    auto operator<=> (const Student &) const = default;
      // clang-format on
      int id{};
    };
    auto result = stableUniqueElements (std::vector<Student>{ { 3 }, { 2 }, { 1 }, { 1 }, { 2 } });
    REQUIRE (result.size () == 3);
    REQUIRE (result.at (0) == Student{ 3 });
    REQUIRE (result.at (1) == Student{ 2 });
    REQUIRE (result.at (2) == Student{ 1 });
    REQUIRE (result.at (0).id != result.at (1).id);
  }
}