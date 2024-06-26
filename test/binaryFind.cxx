#include "confu_algorithm/binaryFind.hxx"
#include <catch2/catch.hpp>
#include <cstdint>
#include <iterator>
#include <vector>

using namespace confu_algorithm;

TEST_CASE ("binaryFind")
{
  SECTION ("data [1,2,3]")
  {
    auto data = std::vector{ 1, 2, 3 };
    SECTION ("element at begin")
    {
      auto result = binaryFind (data.begin (), data.end (), 1);
      REQUIRE (std::distance (data.begin (), result) == 0);
    }
    SECTION ("element in the middle")
    {
      auto result = binaryFind (data.begin (), data.end (), 2);
      REQUIRE (std::distance (data.begin (), result) == 1);
    }
    SECTION ("element at the end")
    {
      auto result = binaryFind (data.begin (), data.end (), 3);
      REQUIRE (std::distance (data.begin (), result) == 2);
    }
    SECTION ("not in array number is to small")
    {
      auto result = binaryFind (data.begin (), data.end (), 0);
      REQUIRE (data.end () == result);
    }
    SECTION ("not in array number is to large")
    {
      auto result = binaryFind (data.begin (), data.end (), 42);
      REQUIRE (data.end () == result);
    }
  }
  SECTION ("data []")
  {
    auto data = std::vector<int>{};
    SECTION ("not in array")
    {
      auto result = binaryFind (data.begin (), data.end (), 0);
      REQUIRE (data.end () == result);
    }
  }
}
struct Student
{
  // clang-format off
    [[nodiscard]]
  auto operator<=> (const Student &) const = default;
  // clang-format on
  int id{};
  std::string name{};
};
TEST_CASE ("binaryFindWithProjection")
{
  SECTION ("data Student[1 2 3]")
  {
    auto data = std::vector<Student>{ { 1, "" }, { 2, "" }, { 3, "" } };
    SECTION ("element at begin")
    {
      auto result = binaryFind (data.begin (), data.end (), 1, {}, &Student::id);
      REQUIRE (std::distance (data.begin (), result) == 0);
    }
    SECTION ("element in the middle")
    {
      auto result = binaryFind (data.begin (), data.end (), 2, {}, &Student::id);
      REQUIRE (std::distance (data.begin (), result) == 1);
    }
    SECTION ("element at the end")
    {
      auto result = binaryFind (data.begin (), data.end (), 3, {}, &Student::id);
      REQUIRE (std::distance (data.begin (), result) == 2);
    }
    SECTION ("not in array number is to small")
    {
      auto result = binaryFind (data.begin (), data.end (), 0, {}, &Student::id);
      REQUIRE (data.end () == result);
    }
    SECTION ("not in array number is to large")
    {
      auto result = binaryFind (data.begin (), data.end (), 42, {}, &Student::id);
      REQUIRE (data.end () == result);
    }
  }
  SECTION ("data []")
  {
    auto data = std::vector<Student>{};
    SECTION ("not in array")
    {
      auto result = binaryFind (data.begin (), data.end (), 0, {}, &Student::id);
      REQUIRE (data.end () == result);
    }
  }
}