#ifndef __KEVIN_PQ__
#define __KEVIN_PQ__

#include <map>
#include <set>

template <typename PRIORITYTYPE, typename NODETYPE, typename NODEINFOTYPE>
class KevinPq
{
public:
  typedef PRIORITYTYPE PriorityType;
  typedef NODETYPE     NodeType;
  typedef NODEINFOTYPE NodeInfoType;

  typedef std::tuple<PriorityType,NodeType,NodeInfoType> TupleMapType;

  struct PrioritySetElemType {
    const PriorityType priority;
    const NodeType     node;

    bool operator< (const PrioritySetElemType& other) const {
      bool result = false;

      if (priority < other.priority) {
        result = true;
      }
      else if ( (priority == other.priority) && (node < other.node) ) {
        result = true;
      }

      return result;
    }
  };

  KevinPq ()                                = default;
  KevinPq (const KevinPq& orig)             = default;
  KevinPq (KevinPq&& orig)                  = delete;
  KevinPq& operator= (const KevinPq& orig)  = delete;
  ~KevinPq ()                               = default;

  bool isEmpty () const {
    return _prioritySet.empty();
  }

  TupleMapType pop () {
    auto setPos = _prioritySet.begin();
    auto elem = *setPos;
    _prioritySet.erase(setPos);

    auto mapPos = _tupleMap.find(elem.node);
    auto tuple = (*mapPos).second;
    _tupleMap.erase(mapPos);

    return tuple;
  }

  void push (const TupleMapType& tuple)
  {
    auto [priority, node, info] = tuple;
    PrioritySetElemType elem {priority,node};

    _prioritySet.insert(elem);
    _tupleMap.insert({node,tuple});
  }

  bool contains (const NodeType& node) const {
    return (_tupleMap.find(node) != _tupleMap.end());
  }

  TupleMapType get (const NodeType& node) const {
    auto pos = _tupleMap.find(node);
    return (*pos).second;
  }

  TupleMapType remove (const NodeType& node) {
    auto mapPos = _tupleMap.find(node);
    auto tuple = (*mapPos).second;
    _tupleMap.erase(mapPos);

    auto [priority, tnode, info] = tuple;

    auto setPos = _prioritySet.find({priority,node});
    auto elem = *setPos;
    _prioritySet.erase(setPos);

    return tuple;
  }

private:
  std::set<PrioritySetElemType>   _prioritySet;
  std::map<NodeType,TupleMapType> _tupleMap;
};

#endif // __KEVIN_PQ__
