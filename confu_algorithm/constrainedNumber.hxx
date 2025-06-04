#pragma once
#include <algorithm>
#include <functional>
namespace confu_algorithm
{
enum class ConstrainedNumberError
{
  UnaryPredicateReturnedFalse
};

template <typename T, auto UnaryPredicate, T defaultValue = {}> requires (std::invoke (UnaryPredicate, defaultValue)) class ConstrainedNumber
{
public:
  using value_type = T;

  operator T () const { return value; }

  void
  setValue (T const &_value)
  {
    if (not std::invoke (UnaryPredicate, _value)) throw ConstrainedNumberError::UnaryPredicateReturnedFalse;
    value = _value;
  }

  void
  setValue (T &&_value)
  {
    if (not std::invoke (UnaryPredicate, _value)) throw ConstrainedNumberError::UnaryPredicateReturnedFalse;
    value = std::move (_value);
  }

  [[nodiscard]] T const &
  getValue () const
  {
    return value;
  }

private:
  T value = defaultValue;
};

inline auto constexpr notZero = [] (auto const &value) { return value != 0; };
template <auto NumberToCompareTo> auto constexpr greaterSomeValue = [] (auto const &value) { return value > NumberToCompareTo; };
template <auto min, auto max> auto constexpr inBetween = [] (auto const &value) { return value >= min && value <= max; };
}