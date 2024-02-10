#pragma once
#ifndef FINDPATHSTRATEGY
#define FINDPATHSTRATEGY

#include <vector>
#include <chrono>
#include <unordered_map>
#include "Node.h"

class FindPathStrategy 
{
public:

    void startPathFind(std::unordered_map<size_t, Node> nodes, size_t begin_node_id, size_t finish_node_id);

    double getAlgorithmTime();
    std::unordered_map<size_t, float> getPaths();

protected:
    FindPathStrategy();

    virtual std::unordered_map<size_t, float> findTheShortestPath(std::unordered_map<size_t, Node> nodes, size_t begin_node_id, size_t finish_node_id) = 0;

    double algorithm_time;
    std::unordered_map<size_t, float> paths;
};

#endif