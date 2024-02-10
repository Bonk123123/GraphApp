#include "../Header/Graph.h"


Graph* Graph::_instance = 0;
unsigned int Graph::_max_nodes = 255;
size_t Graph::_id_generator = 1;


Graph::Graph() { this->_strategy = nullptr; this->_begin = 0; }

Graph::~Graph() 
{ 
    delete this->_strategy;
    delete this->_instance; 
}

Graph* Graph::Instance() 
{
    if (_instance == 0)
    {
        _instance = new Graph();
    }
    return _instance;
}

std::vector<size_t> Graph::getNodesIds()
{
    std::vector<size_t> ids;

    for (std::pair<size_t, Node> element : this->_nodes)
    {
        ids.push_back(element.first);
    }
    
    return ids;
}

void Graph::setEdge(size_t node_id_1, size_t node_id_2, float weight, bool oriented)
{
    if(this->_nodes.contains(node_id_1) && this->_nodes.contains(node_id_2))
    {
        this->_nodes[node_id_1].setEdge(node_id_2, weight);
        if(oriented)
        {
            this->_nodes[node_id_2].setEdge(node_id_1, weight);
        }
    }
    
}

void Graph::deleteEdge(size_t node_id_1, size_t node_id_2, bool oriented)
{
    this->_nodes[node_id_1].deleteEdge(node_id_2);
    if(oriented)
    {
        this->_nodes[node_id_2].deleteEdge(node_id_1);
    }
}


size_t Graph::addNode(float x, float y, std::string name)
{
    size_t new_id = Graph::_id_generator;
    
    if (this->_nodes.size() < _max_nodes) 
    {
        this->_nodes[new_id] = Node(x, y, name);
        Graph::_id_generator += 1;
    }
    else
    {
        this->_error_message = "maximum number of nodes - 255";
        return 0;
    }

    return new_id;
}

void Graph::deleteNodeById(size_t id)
{
    this->_nodes.erase(id);
}

Node Graph::getNodeById(size_t id)
{
    if (this->_nodes.contains(id)) 
    {
        return this->_nodes[id];
    } 
    else
    {
        this->_error_message = "no such node";
    }
    return Node();
}

size_t Graph::getNodesQuanity()
{
    return this->_nodes.size();
}

std::string Graph::getErrorMessage()
{
    return this->_error_message;
}

std::vector<size_t> Graph::getNodeIdsByCoord(float x, float y) 
{
    float node_radius = Node::getNodesRadius();
    std::vector<size_t> ids;
    for (std::pair<size_t, Node> element : this->_nodes)
    {
        float node_center_x = element.second.getX() + node_radius;
        float node_center_y = element.second.getY() + node_radius;

        float length = sqrt(pow(abs(node_center_x - x), 2) + pow(abs(node_center_y - y), 2));

        if (length <= node_radius) ids.push_back(element.first);
    }

    return ids;
}

void Graph::setFindPathStrategy(FindPathStrategy* strategy)
{
    this->_strategy = strategy;
}


std::unordered_map<size_t, float> Graph::findTheShortestPath()
{

    if (this->_strategy && this->_begin)
    {
        this->_strategy->startPathFind(this->_nodes, this->_begin);
        return this->_strategy->getPaths();
    }
    else 
    {
        this->_error_message = "set strategy and begin node";
        std::unordered_map<size_t, float> no_strategy;
        return no_strategy;
    }
}



void Graph::setBeginNodeById(size_t id)
{
    if(this->_nodes.contains(id))
    {
        this->_begin = id;
    }
    else
    {
        this->_error_message = "no such node";
    }
}

size_t Graph::getBeginNodeId()
{
    return this->_begin;
}

