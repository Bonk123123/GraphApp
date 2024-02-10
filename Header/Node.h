#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Node 
{
public:
    Node();
    Node(float x, float y, std::string name);


    
    Node(const Node&);

public:
    void setEdge(size_t, float weight);
    float getEdgeWeight(size_t);
    void deleteEdge(size_t);
    void deleteAllEdges();

    float getX();
    void setX(float x);
    float getY();
    void setY(float y);

    std::string getName();
    void setName(std::string);

    static void setNodesRadius(float);
    static float getNodesRadius();

    std::vector<std::pair<size_t, float>> getNeighbors();


private:
    float _x;
    float _y;
    std::string _name;


    std::unordered_map<size_t, float> _Neighbors;

    static float _radius;

    
};