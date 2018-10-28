#include "search_problem.h"

#include <functional>
#include <string>

using namespace std;

int main () {
  SearchProblem<int,string> searchProblem;

  SearchProblem<int,string>::GoalTestType test1 = [] (const int& state) {
    return state == 2;
  };

  searchProblem.addTransitions({
                  {1, "goto2", 1.0, 2},
                  {1, "goto3", 2.0, 3},
                  {1, "goto4", 3.0, 4},
                  {1, "goto5", 4.0, 5}
                })
                .addTransitions({
                  {2, "goto5", 3.0, 5},
                  {2, "goto6", 4.0, 6},
                  {3, "goto2", 1.0, 2}
                })
                .addState(7)
                .addGoalTest(test1)
                .addTransition({4, "goto4", 0.1, 4})
                .setStateState(9)
                .addGoalState(5)
                .addStates({8,9,10})
                .addGoalState(15)
                .setStateState(10)
                .addTransition({5, "goto1", 4.0, 1});

  auto solution = searchProblem.solve();
}