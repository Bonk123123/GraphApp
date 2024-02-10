#pragma once
#ifndef GRAPH
#define GRAPH

#include <unordered_map>
#include <vector>
#include <memory>
#include <cmath>
#include "Node.h"
#include "FindPathStrategy.h"

class Graph 
{
public:
    static Graph* Instance();

public:
    std::vector<size_t> getNodesIds();

    void setEdge(size_t node_id_1, size_t node_id_2, float weight = 1, bool oriented = false);
    void deleteEdge(size_t node_id_1, size_t node_id_2, bool oriented = false);

    size_t addNode(float x, float y, std::string name = "");
    void deleteNodeById(size_t);

    size_t getNodesQuanity();
    std::string getErrorMessage();

    Node getNodeById(size_t);
    std::vector<size_t> getNodeIdsByCoord(float x, float y);

    void setFindPathStrategy(FindPathStrategy*);

    std::unordered_map<size_t, float> findTheShortestPath();

    void setBeginNodeById(size_t);
    size_t getBeginNodeId();
    

private:
    Graph();
    ~Graph();

    static Graph* _instance;

private:
    size_t _begin;
    std::unordered_map<size_t, Node> _nodes;

    static unsigned int _max_nodes;

    static size_t _id_generator;

    FindPathStrategy* _strategy;

    std::string _error_message = "";

};

#endif