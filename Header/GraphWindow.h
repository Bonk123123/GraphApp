#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iomanip>
#include "Graph.h"

struct EdgeWindow
{
    sf::Vertex line[2] = { sf::Vertex(sf::Vector2f(0, 0)), sf::Vertex(sf::Vector2f(0, 0)) };
    sf::Text weight_text = sf::Text();
    sf::Color color = sf::Color::Green;
};

struct NodeWindow
{
    sf::CircleShape shape = sf::CircleShape(Node::getNodesRadius());
    sf::Text name_text = sf::Text();
    sf::Text path_text = sf::Text();
    std::unordered_map<size_t, EdgeWindow> neighbors;
};


class GraphWindow
{
public:
    GraphWindow(std::string window_name, std::string font_path, Graph* graph);

public:
    void setBgColor(sf::Color);
    void setNodesTexturePath(std::string);

    void displayPaths();  

    void init();

    void interfaceSwitch();

private:
    size_t addNode(float x, float y, size_t node_id, std::string name = "");
    void deleteNode(size_t id);

    void setEdge(size_t id1, size_t id2, float weight = 1);
    void deleteEdge(size_t id1, size_t id2);

private:
    std::string _nodes_texture_path;
    sf::Color _bg_color = sf::Color(30, 30, 30);

    sf::RenderWindow _w = sf::RenderWindow(sf::VideoMode(800, 800), "GraphApp");
    Graph* _graph;
    sf::View _camera;
    sf::Font font;

    std::unordered_map<size_t, NodeWindow> _node_shapes;

    bool _interface;

};