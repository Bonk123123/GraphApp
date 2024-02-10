#include "../Header/Strategys.h"

DijkstraStrategy::DijkstraStrategy() { }

std::unordered_map<size_t, float> DijkstraStrategy::findTheShortestPath(std::unordered_map<size_t, Node> nodes, size_t begin_node_id, size_t finish_node_id)
{
    std::unordered_map<size_t, float> paths;
    std::set<size_t> completed_nodes_ids;
    std::set<size_t> nearest_nodes_ids;
    nearest_nodes_ids.insert(begin_node_id);
    paths[begin_node_id] = 0;

    do
    {
        size_t current_node_id = this->findMin(paths, nearest_nodes_ids);

        nearest_nodes_ids.erase(current_node_id);

        for (auto & neighbor : nodes[current_node_id].getNeighbors())
        {
            if(paths.contains(neighbor.first))
            {
                if(paths[current_node_id] + neighbor.second < paths[neighbor.first] && !completed_nodes_ids.contains(neighbor.first))
                {
                    paths[neighbor.first] = paths[current_node_id] + neighbor.second;
                }
            }
            else
            {
                paths[neighbor.first] = paths[current_node_id] + neighbor.second;
            }

            if(!completed_nodes_ids.contains(neighbor.first)) nearest_nodes_ids.insert(neighbor.first);

        }

        completed_nodes_ids.insert(current_node_id);
        
    } 
    while(!nearest_nodes_ids.empty());

    return paths;

}

size_t DijkstraStrategy::findMin(std::unordered_map<size_t, float> paths, std::set<size_t> nearest_nodes_ids)
{
    size_t min = -1;
    size_t id = 0;

    for(std::pair<size_t, float> node : paths)
    {
        if(node.second < min && nearest_nodes_ids.contains(node.first))
        {
            min = node.second;
            id = node.first;
        } 
    }

    return id;
}










AStarStrategy::AStarStrategy() { }

std::unordered_map<size_t, float> AStarStrategy::findTheShortestPath(std::unordered_map<size_t, Node> nodes, size_t begin_node_id, size_t finish_node_id)
{
    std::unordered_map<size_t, float> paths;
    std::set<size_t> completed_nodes_ids;
    std::map<size_t, float> euristic_nodes_ids;
    euristic_nodes_ids[begin_node_id] = 0;
    paths[begin_node_id] = 0;


    do
    {
        size_t current_node_id = this->findMin(paths, euristic_nodes_ids);

        if(current_node_id == finish_node_id) break;

        euristic_nodes_ids.erase(current_node_id);

        for (auto & neighbor : nodes[current_node_id].getNeighbors())
        {
            if(paths.contains(neighbor.first))
            {
                if(paths[current_node_id] + neighbor.second < paths[neighbor.first] && !completed_nodes_ids.contains(neighbor.first))
                {
                    paths[neighbor.first] = paths[current_node_id] + neighbor.second;
                }
            }
            else
            {
                paths[neighbor.first] = paths[current_node_id] + neighbor.second;
            }

            float euristic_distance = euristic_nodes_ids[neighbor.second] + this->euristic_function(nodes[current_node_id], nodes[neighbor.first]);

            if(!completed_nodes_ids.contains(neighbor.first)) euristic_nodes_ids[neighbor.first] = euristic_distance;

        }

        completed_nodes_ids.insert(current_node_id);
        
    } 
    while(!euristic_nodes_ids.empty());

    return paths;
}

size_t AStarStrategy::findMin(std::unordered_map<size_t, float> paths, std::map<size_t, float> euristic_nodes_ids)
{
    size_t min = -1 ;
    size_t id = 0;

    for(std::pair<size_t, float> node : paths)
    {
        if(node.second < min && euristic_nodes_ids.contains(node.first))
        {
            min = node.second;
            id = node.first;
        } 
    }

    return id;
}

float AStarStrategy::euristic_function(Node current, Node neighbor)
{
    return abs(current.getX() - neighbor.getX()) + abs(current.getY() - neighbor.getY());
}





