#pragma once
#include "FindPathStrategy.h"
#include <vector>
#include <iostream>
#include <map>
#include <set>

class DijkstraStrategy : public FindPathStrategy
{
public:
    DijkstraStrategy();
    virtual std::unordered_map<size_t, float> findTheShortestPath(std::unordered_map<size_t, Node> nodes, size_t begin_node_id, size_t finish_node_id) override;

private:
    size_t findMin(std::unordered_map<size_t, float>, std::set<size_t>);
};





class AStarStrategy : public FindPathStrategy
{
public:
    AStarStrategy();
    virtual std::unordered_map<size_t, float> findTheShortestPath(std::unordered_map<size_t, Node> nodes, size_t begin_node_id, size_t finish_node_id) override;

private:
    size_t findMin(std::unordered_map<size_t, float>, std::map<size_t, float>);

    float euristic_function(Node, Node);
};