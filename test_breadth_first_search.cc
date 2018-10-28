#include "breadth_first_search.h"

#include "search_problem.h"

#include <iostream>

using namespace std;

int main () {
  SearchProblem<int,string>::Builder spBuilder;

  spBuilder
    .addTransitions({
      {1, "to2", 1.0, 2},
      {1, "to3", 2.0, 3},
      {2, "to4", 4.0, 4},
      {2, "to5", 1.0, 5},
      {3, "to6", 2.0, 6},
      {4, "to7", 3.0, 7},
      {5, "to4", 1.0, 4},
      {5, "to7", 1.0, 7},
      {5, "to6", 1.0, 6},
      {6, "to7", 1.0, 7},
      {7, "to4", 3.0, 4},
      {7, "to6", 1.0, 6},
    })
    .setStateState(1)
    .addGoalState(4);

  auto searchProblem = spBuilder.build();

  auto bfs = BreadthFirstSearch(searchProblem);
  auto soln = bfs.solve();

  cout << "solutionWasFound = " << boolalpha << soln.getSolutionWasFound() << endl;
  cout << "path: ";
  for (auto state : soln.getPath()) {
    cout << state << ", ";
  }
  cout << endl;
}
