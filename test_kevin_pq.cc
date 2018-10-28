#include "kevin_pq.h"

#include <iostream>
#include <string>

using namespace std;

int main ()
{
  KevinPq<double,int,string> kpq;

  kpq.push({50.0,5,"info1"});
  kpq.push({10.0,7,"info2"});
  kpq.push({20.0,8,"info3"});

  cout << "contains(7) = " << boolalpha << kpq.contains(7) << endl;
  cout << "contains(2) = " << boolalpha << kpq.contains(2) << endl;

  auto tuple1 = kpq.pop();
  cout << "pop: " << get<0>(tuple1) << ", " << get<1>(tuple1) << ", " << get<2>(tuple1) << endl;

  auto tuple2 = kpq.remove(8);
  cout << "rem: " << get<0>(tuple2) << ", " << get<1>(tuple2) << ", " << get<2>(tuple2) << endl;

  cout << "isEmpty = " << boolalpha << kpq.isEmpty() << endl;

  auto tuple3 = kpq.pop();
  cout << "pop: " << get<0>(tuple3) << ", " << get<1>(tuple3) << ", " << get<2>(tuple3) << endl;

  cout << "isEmpty = " << boolalpha << kpq.isEmpty() << endl;
}