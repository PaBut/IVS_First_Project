//======== Copyright (c) 2023, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"


Graph::Graph(){}

Graph::~Graph(){clear();}

std::vector<Node*> Graph::nodes() {
    std::vector<Node*> nodes = _nodes;
    return nodes;
}

std::vector<Edge> Graph::edges() const{
    std::vector<Edge> edges = _edges;
    return edges;
}

Node* Graph::addNode(size_t nodeId) {
    if(getNode(nodeId) != nullptr){
        return nullptr;
    }
    Node* node = new Node;
    node->id = nodeId;
    node->color=0;
    _nodes.push_back(node);
    return node;
}

bool Graph::addEdge(const Edge& edge){
    if(containsEdge(edge) || edge.a == edge.b){
        return false;
    }

    addNode(edge.a);
    addNode(edge.b);

    getNode(edge.a)->neighbors.push_back(getNode(edge.b));
    getNode(edge.b)->neighbors.push_back(getNode(edge.a));
    _edges.push_back(edge);
    return true;
}

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for(Edge tmpEdge : edges){
        addEdge(tmpEdge);
    }
}

Node* Graph::getNode(size_t nodeId) const{
    for(Node* node : _nodes){
        if(node->id == nodeId){
            return node;
        }
    }
    return nullptr;
}

bool Graph::containsEdge(const Edge& edge) const{
    for(Edge tmpEdge : _edges){
        if(edge == tmpEdge){
            return true;
        }
    }
    return false;
}

void Graph::removeNode(size_t nodeId){
    std::vector<Edge> edgesToRemove;

    for (Edge& edge : _edges) {
        if (edge.a == nodeId || edge.b == nodeId) {
            edgesToRemove.push_back(edge);
        }
    }

    for (const Edge& edge : edgesToRemove) {
        removeEdge(edge);
    }

    for (int i = 0; i < _nodes.size(); i++) {
        if (_nodes[i]->id == nodeId) {
            _nodes.erase(_nodes.begin() + i);
            return;
        }
    }

    throw std::out_of_range("Index out of range");

}

void Graph::removeEdge(const Edge& edge){
    for(int i = 0; i < _edges.size(); i++){
        if(_edges[i] == edge){
            _edges.erase(_edges.begin() + i);
            return;
        }
    }
    throw std::out_of_range("Index out of range");
}

size_t Graph::nodeCount() const{
    return _nodes.size();
}

size_t Graph::edgeCount() const{
    return _edges.size();
}

size_t Graph::nodeDegree(size_t nodeId) const{
    Node* tmpNode = getNode(nodeId);
    if(tmpNode == nullptr){
        throw std::out_of_range("Index out of range");
    }
    return tmpNode->neighbors.size();
}


size_t Graph::graphDegree() const{
    size_t max = 0;
    for(Node* tmpNode : _nodes){
        size_t tmpDegree = tmpNode->neighbors.size();
        if(tmpDegree > max){
            max = tmpDegree;
        }
    }
    return max;
}


void Graph::coloring(){
    size_t maxColors = graphDegree() + 1;
    for(Node* node : _nodes){
        for(size_t i = 1; i <= maxColors; i++){
            bool isColorUnique = true;
            for(Node* neighbor : node->neighbors){
                if(neighbor->color == i){
                    isColorUnique = false;
                    break;
                }
            }
            if(isColorUnique){
                node->color = i;
            }
        }
    }
}

void Graph::clear() {
    _edges.clear();
    _nodes.clear();
}

/*** Konec souboru tdd_code.cpp ***/
