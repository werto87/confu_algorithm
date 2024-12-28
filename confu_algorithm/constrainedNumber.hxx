#pragma once
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
  ConstrainedNumber () = default;

  ConstrainedNumber (T const &_value) { setValue (_value); };
  ConstrainedNumber (T &&_value) { setValue (std::move (_value)); };

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

  // clang-format off
  auto operator<=>(const ConstrainedNumber&) const = default;
  // clang-format on
private:
  T value = defaultValue;
};

auto constexpr notZero = [] (auto const &value) { return value != 0; };
template <auto NumberToCompareTo> auto constexpr greaterSomeValue = [] (auto const &value) { return value > NumberToCompareTo; };
}