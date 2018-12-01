#include <iostream>

#include "types.h"
#include "scratchpad.h"

using namespace std;

int main ()
{
  Scratchpad scratchpad;
  scratchpad.frontierPush(5, {5, {}, 100.0, 45.3});
  scratchpad.frontierPush(3, {2, {},  10.0,  6.3});
  scratchpad.frontierPush(4, {1, {},  80.0, 20.1});

  {
    auto thingy = scratchpad.frontierPop();
    cout << "priority = " << std::get<0>(thingy) << endl;
  }

  {
    auto thingy = scratchpad.frontierPop();
    cout << "priority = " << std::get<0>(thingy) << endl;
  }

  {
    auto thingy = scratchpad.frontierPop();
    cout << "priority = " << std::get<0>(thingy) << endl;
  }

  cin.get();
}

#if 0
  SearchProblemBuild spBuilder;

  spBuilder
    .addTransitions({
      {1, 2, 1.0},
      ...
    })
    .setStartState(1)
    .addGoalState(4)
    .addStateHeuristics({
      {1, 4.0},
      {2, 2.0},
      ...
    });

  SearchProblem searchProblem = spBuilder.build();

  vector<tuple<string,Solver>> solverInfos {
    {"DFS", Dfs(searchProblem)},
    {"BFS", Bfs(searchProblem)},
    ...
  };

  for (auto info : solverInfos) {
    auto solverName = std::get<0>(info);
    auto solver     = std::get<1>(info);

    cout << "=====" << solverName << "=====" << endl;

    auto solution = solver.solve();

    cout << "solutionWasFound = "
         << boolalpha
         << solution.getSolutionWasFound()
         << endl;

    cout << "path = " << endl;
    // print path
  }
#endif
