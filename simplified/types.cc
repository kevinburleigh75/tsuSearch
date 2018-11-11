#include "types.h"

#include <sstream>
#include <tuple>

using namespace std;

string StateInfo::toString () const {
  ostringstream ostr;
  State pred = -1;
  if (predecessor) {
    pred = *predecessor;
  }
  ostr << "SI<" << state << "," << pred << "," << pathCost << "," << heuristic << ">";
  return ostr.str();
}

bool operator< (const StateAction& lhs, const StateAction& rhs) {
  return (  std::tie(std::get<0>(lhs),std::get<1>(lhs)) <
            std::tie(std::get<0>(rhs),std::get<1>(rhs)) );
}
