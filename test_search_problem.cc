#include "search_problem.h"

#include <iostream>
#include <functional>
#include <string>

using namespace std;

int main () {
  SearchProblem<int,string>::Builder spBuilder;

  SearchProblem<int,string>::GoalTestType test1 = [] (const int& state) {
    return state == 2;
  };

  spBuilder
    .addTransitions({
      {1, "goto2", 1.0, 2},
      {1, "goto3", 2.0, 3},
      {1, "goto4", 3.0, 4},
      {1, "goto5", 4.0, 5}
    })
    .addTransitions({
      {2, "goto5", 3.0, 5},
      {2, "goto6", 4.0, 6},
      {3, "goto2", 1.0, 2},
      {3, "goto2", 1.0, 10}
    })
    .addTransition({5, "goto1", 4.0, 1})
    .addState(7)
    .addGoalTest(test1)
    .setStateState(9)
    .addTransition({4, "goto4", 0.1, 4})
    .addGoalState(5)
    .addStates({8,9,10})
    .addGoalState(15)
    .setStateState(10);

  auto searchProblem = spBuilder.build();


  for (auto state : searchProblem.getStates()) {
    cout << "state: " << state << endl;
    cout << "  actions:" << endl;
    for (auto action : searchProblem.getActionsForState(state)) {
      cout << "    action: " << action << endl;

      auto successor = searchProblem.getActionSuccessor(state, action);
      cout << "      successor: " << successor << endl;

      auto cost = searchProblem.getActionCost(state, action);
      cout << "      cost: " << cost << endl;
    }
  }
}