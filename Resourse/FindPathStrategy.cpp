#include "../Header/FindPathStrategy.h"

FindPathStrategy::FindPathStrategy() { }

double FindPathStrategy::getAlgorithmTime()
{
    return this->algorithm_time;
}

std::unordered_map<size_t, float> FindPathStrategy::getPaths()
{
    return this->paths;
}

void FindPathStrategy::startPathFind(std::unordered_map<size_t, Node> nodes, size_t begin_node_id, size_t finish_node_id)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    this->paths = this->findTheShortestPath(nodes, begin_node_id, finish_node_id); // algorithm

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    this->algorithm_time = (std::chrono::duration<double>(end - begin).count());
}
