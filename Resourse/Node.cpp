#include "../Header/Node.h"

float Node::_radius = 10;

Node::Node() : _x(0), _y(0),  _name("") { }

Node::Node(float x, float y, std::string name) : _x(x), _y(y), _name(name) { }

Node::Node(const Node& node)
{
    this->_x = node._x;
    this->_y = node._y;
    this->_name = node._name;
    for (std::pair<size_t, float> element : node._Neighbors)
    {
        this->_Neighbors[element.first] = element.second;
    }
}

void Node::setEdge(size_t id, float weight) 
{
    this->_Neighbors[id] = weight;
}

float Node::getEdgeWeight(size_t id) 
{
    return this->_Neighbors[id];
}

void Node::deleteEdge(size_t id) 
{
    this->_Neighbors.erase(id);
}

void Node::deleteAllEdges()
{
    this->_Neighbors.clear();
}


float Node::getX() { return this->_x; }
void Node::setX(float x) { this->_x = x; }
float Node::getY() { return this->_y; }
void Node::setY(float y) { this->_y = y; }


std::string Node::getName() { return this->_name; }
void Node::setName(std::string name) { this->_name = name; }

float Node::getNodesRadius() { return Node::_radius; }
static float getNodesRadius() { return Node::getNodesRadius(); }

void Node::setNodesRadius(float radius) { Node::_radius = radius; }
static void setNodesRadius(float radius) { return Node::setNodesRadius(radius); }

std::vector<std::pair<size_t, float>> Node::getNeighbors()
{
    std::vector<std::pair<size_t, float>> neighbors;
    for (std::pair<size_t, float> element : this->_Neighbors)
    {
        neighbors.push_back(std::pair<size_t, float>{element.first, element.second});
    }

    return neighbors;
}
