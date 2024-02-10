#include "../Header/GraphWindow.h"

const int FONT_SIZE = 10;

std::string precision( float f, int places )
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(places) << f;
    std::string mystring = ss.str();
    return mystring;
}

GraphWindow::GraphWindow(std::string window_name, std::string font_path, Graph* graph)
{
    this->_graph = graph;
    this->_camera = this->_w.getDefaultView();

    if(!this->font.loadFromFile(font_path)) std::cout << "error with font" << std::endl;

    for(auto & node_id : this->_graph->getNodesIds())
    {
        Node node = this->_graph->getNodeById(node_id);

        this->addNode(node.getX(), node.getY(), node_id, node.getName());


        for(auto neighbor : node.getNeighbors())
        {
            this->setEdge(node_id, neighbor.first, neighbor.second);
        }
    }

}


void GraphWindow::setBgColor(sf::Color color)
{
    this->_bg_color = color;
}

void GraphWindow::setNodesTexturePath(std::string texture_path) 
{
    this->_nodes_texture_path = texture_path;
}

void GraphWindow::displayPaths()
{
    std::unordered_map<size_t, float> paths(this->_graph->findTheShortestPath());

    for (auto & node_path : paths)
    {
        if(this->_node_shapes.contains(node_path.first))
        {
            Node node = this->_graph->getNodeById(node_path.first);
            this->_node_shapes[node_path.first].path_text.setString(precision(node_path.second, 2));
            this->_node_shapes[node_path.first].path_text.setPosition(node.getX(), node.getY() - Node::getNodesRadius() - 5);
            this->_node_shapes[node_path.first].path_text.setFont(this->font);
            this->_node_shapes[node_path.first].path_text.setCharacterSize(FONT_SIZE);
        }
    }
    
}

size_t GraphWindow::addNode(float x, float y, size_t node_id, std::string name)
{
    Node node = this->_graph->getNodeById(node_id);
    this->_node_shapes[node_id] = NodeWindow();
    this->_node_shapes[node_id].shape.setPosition(node.getX(), node.getY());
    this->_node_shapes[node_id].name_text.setPosition(node.getX(), node.getY() + Node::getNodesRadius() + 10);
    this->_node_shapes[node_id].name_text.setFont(this->font);
    this->_node_shapes[node_id].name_text.setString(name);
    this->_node_shapes[node_id].name_text.setCharacterSize(FONT_SIZE);
    return node_id;
}

void GraphWindow::deleteNode(size_t id)
{
    this->_graph->deleteNodeById(id);
    this->_node_shapes.erase(id);
}

void GraphWindow::setEdge(size_t id1, size_t id2, float weight)
{
    Node node1 = this->_graph->getNodeById(id1);
    Node node2 = this->_graph->getNodeById(id2);
    this->_node_shapes[id1].neighbors[id2].weight_text.setString(precision(weight, 2));
    this->_node_shapes[id1].neighbors[id2].weight_text.setFont(this->font);
    this->_node_shapes[id1].neighbors[id2].weight_text.setPosition(node1.getX() + (node2.getX() - node1.getX()) / 2, node1.getY() + (node2.getY() - node1.getY()) / 2);
    this->_node_shapes[id1].neighbors[id2].weight_text.setCharacterSize(FONT_SIZE);

    this->_node_shapes[id1].neighbors[id2].line[0] = sf::Vertex(sf::Vector2f(node1.getX() + Node::getNodesRadius(), node1.getY() + Node::getNodesRadius()), this->_node_shapes[id1].neighbors[id2].color);
    this->_node_shapes[id1].neighbors[id2].line[1] = sf::Vertex(sf::Vector2f(node2.getX() + Node::getNodesRadius(), node2.getY() + Node::getNodesRadius()), this->_node_shapes[id1].neighbors[id2].color); 

    
    
    // maybe do shorter? maybe do Arrow?

    
}

void GraphWindow::deleteEdge(size_t id1, size_t id2)
{
    this->_graph->deleteEdge(id1, id2);
    this->_node_shapes[id1].neighbors.erase(id2);
}

void GraphWindow::init()
{
    float x = 0;
    float y = 0;

    
    

    bool mouse_clicked = false;

    while (this->_w.isOpen())
    {   

        sf::Vector2i position = sf::Mouse::getPosition();

        sf::Event event;
        while (this->_w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->_w.close();

            if (event.type == sf::Event::Resized) {
                this->_camera = sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height));
            }

            if (event.type == sf::Event::MouseMoved && mouse_clicked)
            {
                this->_camera.move(x - position.x, y - position.y);
                
                x = position.x;
                y = position.y;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                mouse_clicked = true;

                x = position.x;
                y = position.y;
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                mouse_clicked = false;
            }
        }

        this->_w.setView(this->_camera);
        this->_w.clear(this->_bg_color);


        // draw
        for (auto node : this->_node_shapes)
        {
            this->_w.draw(node.second.shape);
            this->_w.draw(node.second.name_text);
            this->_w.draw(node.second.path_text);

            for (auto edge : node.second.neighbors)
            {
                this->_w.draw(edge.second.line, 2, sf::Lines);
                this->_w.draw(edge.second.weight_text);
            }
            
        }


        
        
        
        this->_w.display();
    }
}

void GraphWindow::interfaceSwitch() { this->_interface = !this->_interface; }