#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <ostream>
#include "Header/Node.h"
#include "Header/Graph.h"
#include "Header/Strategys.h"
#include "Header/GraphWindow.h"

using namespace std;

int main()
{
    auto graph = Graph::Instance();

    size_t id1 = graph->addNode(10, 10, "art");
    size_t id15 = graph->addNode(0, 150, "rat");
    size_t id2 = graph->addNode(100, 100, "tra");
    size_t id3 = graph->addNode(142, 500, "rta");

    graph->setEdge(id1, id15, 10);
    graph->setEdge(id1, id2, 6);
    graph->setEdge(id2, id3, 7);
    graph->setEdge(id1, id3, 4);
    graph->setEdge(id15, id2, 3);

    graph->setBeginNodeById(id15);

    graph->setFindPathStrategy(new DijkstraStrategy());


    GraphWindow w = GraphWindow("GraphApp", "Roboto-Bold.ttf", graph);

    w.displayPaths();

    w.init();

    // sf::Color bg(30, 30, 30);

    // sf::RenderWindow window(sf::VideoMode(800, 800), "GraphApp");
    // sf::CircleShape shape(20.f);
    // sf::RectangleShape rect(sf::Vector2f{200, 500});

    // float x = 0;
    // float y = 0;

    // bool mouse_clicked = false;
    
    // shape.setPosition(100, 100);

    // sf::View view = window.getDefaultView();

    // while (window.isOpen())
    // {   

    //     sf::Vector2i position = sf::Mouse::getPosition();
 
    //     // set mouse position relative to a window
    //     // sf::Mouse::setPosition(sf::Vector2i(100, 200), window);

    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();

    //         if (event.type == sf::Event::Resized) {
    //             view = sf::View(sf::FloatRect(0.5f, 0.f, event.size.width, event.size.height));

    //             rect.setPosition(0, 0);
    //         }

    //         if (event.type == sf::Event::MouseMoved && mouse_clicked)
    //         {
    //             view.move(x - position.x, y - position.y);
                

    //             sf::Vector2f positionrect = rect.getPosition();

    //             rect.setPosition(positionrect.x + x - position.x, positionrect.y + y - position.y);

    //             x = position.x;
    //             y = position.y;

                
    //         }

    //         if (event.type == sf::Event::MouseButtonPressed)
    //         {
    //             mouse_clicked = true;

    //             x = position.x;
    //             y = position.y;
    //         }

    //         if (event.type == sf::Event::MouseButtonReleased)
    //         {
    //             mouse_clicked = false;
    //         }
    //     }

    //     window.setView(view);
    //     window.clear(bg);


    //     window.draw(shape);
    //     window.draw(rect);
        
        
    //     window.display();
    // }

    // Node node{}; // 1
    // Node node1{100, 100, "2"}; // 2
    // Node node2{50, 50, "3"}; // 3
    // Node node3{50, 50, "4"}; // 4
    
    // node.setEdge(2, 11);
    // node.setEdge(4, 18);
    // node1.setEdge(1, 3);
    // node3.setEdge(2, 1);
    // node1.setEdge(3, 8);
    // node3.setEdge(3, 1);
    // node1.setEdge(4, 2);

    // auto graph = Graph::Instance();

    // auto algo = new DijkstraStrategy();

    // graph->setFindPathStrategy(algo);

    // // graph->addNode(node);
    // // graph->addNode(node1);
    // // graph->addNode(node2);
    // // graph->addNode(node3);

    // Node::setNodesRadius(10);
    

    // graph->setBeginNodeById(4);

    // unordered_map<size_t, float> strategy(graph->findTheShortestPath());

    // for (std::pair<size_t, float> element : strategy)
    // {
    //     cout << "id: " << element.first << "\tpath from begin node: " << element.second << endl;
    // }


    // cout << "algorithm time: " << algo->getAlgorithmTime() << "s" << endl;

    return 0;
}