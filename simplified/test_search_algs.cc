#include "search_problem.h"

#include "solver.h"
#include "dfs.h"
// #include "bfs.h"
// #include "ucs.h"
// #include "gbfs.h"
// #include "astar.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "types.h"

using namespace std;

int main () {
  SearchProblemBuilder spBuilder;

  spBuilder
    .addTransitions({
      {1, 2, 1.0},
      {1, 5, 1.0},
      {2, 4, 3.0},
      {2, 3, 1.0},
      {3, 4, 1.0},
      {3, 6, 1.0},
      {3, 7, 2.0},
      {5, 6, 3.0},
      {6, 7, 3.0},
      {7, 3, 2.0},
      {7, 4, 3.0},
    })
    .setStateState(1)
    .addGoalState(4)
    .addStateHeuristics({
      {1, 4.0},
      {2, 2.0},
      {3, 1.0},
      {4, 0.0},
      {5, 5.0},
      {6, 5.0},
      {7, 2.0},
    });

  auto searchProblem = spBuilder.build();

  vector<tuple<string,Solver*>> solverInfos {
    {"DFS",   new Dfs(searchProblem)},
    // {"BFS",   Bfs(searchProblem)},
    // {"UCS",   Ucs(searchProblem)},
    // {"GBFS",  Gbfs(searchProblem)},
    // {"AStar", AStar(searchProblem)},
  };

  for (auto info : solverInfos) {
    auto solverName = std::get<0>(info);
    auto pSolver     = std::get<1>(info);

    cout << "=====" << solverName << "=====" << endl;

    auto solution = pSolver->solve();

    cout << "solutionWasFound = " << boolalpha << solution.getSolutionWasFound() << endl;
    cout << "path: ";
    for (auto state : solution.getPath()) {
      cout << state << ", ";
    }
    cout << endl;
  }
#if 0
#endif
}