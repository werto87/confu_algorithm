#include "confu_algorithm/stableUniqueElements.hxx"
#include <catch2/catch.hpp>

TEST_CASE ("stableUniqueElements int removes duplicates but with out altering order")
{
  auto result = stableUniqueElements (std::vector{ 3, 2, 1, 1, 2 });
  REQUIRE (result.size () == 3);
  REQUIRE (result.at (0) == 3);
  REQUIRE (result.at (1) == 2);
  REQUIRE (result.at (2) == 1);
}
TEST_CASE ("stableUniqueElements user defined type removes duplicates but with out altering order")
{
  struct Student
  {
    auto operator<=> (const Student &) const = default;
    int id{};
  };
  auto result = stableUniqueElements (std::vector<Student>{ { 3 }, { 2 }, { 1 }, { 1 }, { 2 } });
  REQUIRE (result.size () == 3);
  REQUIRE (result.at (0) == Student{ 3 });
  REQUIRE (result.at (1) == Student{ 2 });
  REQUIRE (result.at (2) == Student{ 1 });
}
