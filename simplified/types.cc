#include "types.h"

#include <tuple>

bool operator< (const StateAction& lhs, const StateAction& rhs) {
  // return (  std::tie(std::get<0>(lhs),std::get<1>(lhs)) <
  //           std::tie(std::get<0>(rhs),std::get<1>(rhs)) );

  bool result = false;
  if (std::get<0>(lhs) < std::get<0>(rhs)) {
    result = true;
  }
  else if (std::get<0>(lhs) == std::get<0>(rhs)) {
    result = (std::get<1>(lhs) < std::get<1>(rhs));
  }
  return result;
}
