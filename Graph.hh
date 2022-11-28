///
/// \Authors Davis, Hunter
/// \file Grpah.hh
/// \note A class defining graph objects. Holds nodes and edges for describing a graph. Is a template class.
///

#pragma once

#include "Node.hh"
#include "Edge.hh"
#include <vector>
#include <iostream>
#include "imgui.h"

/// <summary>
/// Generic Graph data structure.
/// Contains a vector of Nodes and Edges.
/// </summary>
/// <typeparam name="T">The class type for the object held in Node->data</typeparam>
template<class T>
class Graph {
public:
    // Add and remove nodes
    void addNode(Node<T> node) {
        nodes.push_back(node);
    }
    void addNodes(std::vector<Node<T>> newNodes) {
        for (Node<T> node: newNodes) {
            addNode(node);
        }
    }
    void removeNode(Node<T> node) {
        remove(nodes.begin(), nodes.end(), node);
    }
    void setNode(Node<T> node, int ndx) {
        nodes[ndx] = node;
    }

    // Add and remove edges
    void addEdge(Edge<T> edge) {
        edges.push_back(edge);
    }
    void addEdges(std::vector<Edge<T>> newEdges) {
        for (Edge<T> edge: newEdges) {
            addEdge(edge);
        }
    }
    void removeEdge(Edge<T> edge) {
        remove(edges.begin(), edges.end(), edge);
    }

    Node<T> getNode(int ID) {
        for (Node<T> node : nodes) {
            if (node.getID() == ID) {
                return node;
            }
        }
    }

    // Getters
    std::vector<Node<T>> getNodes() {
        return nodes;
    }
    std::vector<Edge<T>> getEdges() {
        return edges;
    }

    //Function to set positions
    //For the basic layout
    /*void setPosition(ImGuiViewport* viewport) {
        int x = viewport->Pos.x + 20;
        int y = viewport->Pos.y + 100;
        for (int i = 0; i < nodes.size(); i++) {
            nodes.at(i).setX(x);
            nodes.at(i).setY(y);

            x += 280;
            if (x > viewport->Size.x - 100) {
                x = viewport->Pos.x + 20;
                y += 280;
            }
        }

    }*/
    void setPosition(ImGuiViewport* viewport) {
        setNodeEdgeCounts();
        std::vector< std::vector<int>> layers;
        layers.push_back(getXInEdgesI(0));
        std::cout << "---------------------------" << std::endl;
        int increment = 0;
        bool moreLayers = true;
        while (moreLayers && increment < 100) {
            std::vector<int> nextVector;
            for (int i = 0; i < layers.at(increment).size(); i++) {
                std::vector<int> tempVec = getNodesToIndexes(layers.at(increment).at(i));
                for (int node : tempVec) {
                    if (std::find(nextVector.begin(), nextVector.end(), node) == nextVector.end()) {
                        nextVector.push_back(node);
                    }
                }
            }
            if (nextVector.size() > 0) {
                layers.push_back(nextVector);
                increment++;
            }
            else {
                moreLayers = false;
            }
        }
        std::reverse(layers.begin(), layers.end());


        int biggestLayerSize = 0;
        for (std::vector<int> layer : layers) {
            if (layer.size() > biggestLayerSize) {
                biggestLayerSize = layer.size();
            }
        }
        /*std::vector<int> layer2;
        for (int i = 0; i < layers.at(0).size(); i++) { 
            std::vector<int> tempVec = getNodesToIndexes(layers.at(0).at(i));
            for (int node : tempVec) {
                if (std::find(layer2.begin(), layer2.end(), node) == layer2.end()) {
                    layer2.push_back(node);
                }
            }
        }
        layers.push_back(layer2);*/
        int x = viewport->Pos.x + 20;
        int y = viewport->Pos.y + 300;
        
       /* for (int i = 0; i < nodes.size(); i++) {
            nodes.at(i).setX(x);
            nodes.at(i).setY(y);

            x += 280;
            if (x > viewport->Size.x - 100) {
                x = viewport->Pos.x + 20;
                y += 280;
            }
        }*/

        //The bellow code can be uncomented to print out the contents of the layers.
        /*for (int i = 0; i < layers.size(); i++) {
            printf("Layer %d\n", i);
            for (int j = 0; j < layers.at(i).size(); j++) {
                int pos = layers.at(i).at(j);
                std::string name = nodes.at(pos).getData().getName();
                printf("    %d\n", pos);
            }
        }*/
        //*************************************

        y = viewport->Pos.y + 100;
        for (std::vector<int> layer : layers) {
            x = viewport->Pos.x + 20;
            int mid = (biggestLayerSize / 2) - (layer.size() / 2);
            for (int i = 0; i < mid; i++) {
                x += 280;
            }
            for (int i = 0; i < layer.size(); i++) {
                if (nodes.at(layer.at(i)).getX() == 0) { // Checks to make sure node position isn't overwritten
                    nodes.at(layer.at(i)).setX(x);
                    nodes.at(layer.at(i)).setY(y);
                }

                x += 280;
                /*if (x > viewport->Size.x - 100) {
                    x = viewport->Pos.x + 20;
                    y += 280;
                }*/
            }
            y += 280;
        }

        //for (int i = 0; i < nodes.size(); i++) {
        //    printf("Node %s has %d crossings\n", nodes.at(i).getData().getName().c_str(), crossingsFrom(i));
        //}
        //printf("-----------------------\n");
        //if (nodes.size() >= 7) {
        //    //swapNodes(4, 6);
        //}
        //for (int i = 0; i < nodes.size(); i++) {
        //    printf("Node %s has %d crossings\n", nodes.at(i).getData().getName().c_str(), crossingsFrom(i));
        //}
        for (std::vector<int> layer : layers) {
            for (int i = 0; i < layer.size(); i++) {
                int crossings = crossingsFrom(layer.at(i));
                if ( crossings > 0) {
                    for (int j = 0; j < layer.size(); j++) {
                        swapNodes(layer.at(i), layer.at(j));
                        if (crossingsFrom(layer.at(i)) <= crossings) {
                            crossings = crossingsFrom(layer.at(i));
                        }
                        else {
                            swapNodes(layer.at(i), layer.at(j));
                        }
                        if (crossings == 0) {
                            break;
                        }
                    }
                }
            }
        }

    }

    //Temp logging functions - remove after graphing alg is complete
    void getCross() {
        int a = allCrossing();
        printf("Total Crossing : %d\n", a);
    }


private:
    // Fields
    std::vector<Node<T>> nodes;
    std::vector<Edge<T>> edges;

    //Metods
   
    //returns a vector of nodes with no in edges
    std::vector<int> getXInEdgesI(int x = 0){
        std::vector<int> noInList;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes.at(i).getInEdges() == x) {
                noInList.push_back(i);
            }
        }
        return noInList;
    }

    void setNodeEdgeCounts() {
        for (int i = 0; i < nodes.size(); i++) {
            int outCount = 0;
            int inCount = 0;
            for (Edge<T> edge : edges) {
                if (edge.getStartNode() == nodes.at(i).getID()) {
                    outCount++;
                }
                if (edge.getEndNode() == nodes.at(i).getID()) {
                    inCount++;
                }
            }
            nodes.at(i).setOutEdges(outCount);
            nodes.at(i).setInEdges(inCount);
        }
    }

    std::vector<int> getNodesToIndexes(int nodeIndex) {
        int ID = nodes.at(nodeIndex).getID();
        std::vector<int> nodesTo;
        for (int i = 0; i < edges.size(); i++) {
            if (edges.at(i).getStartNode() == ID) {
                for (int j = 0; j < nodes.size(); j++) {
                    if (nodes.at(j).getID() == edges.at(i).getEndNode()) {
                        nodesTo.push_back(j);
                    }
                }
            }
        }
        return nodesTo;
    }

    //**********************************************
    //The following functions are all involved in determining the number of crossing edges.
    bool isCrossing(Edge<T> edge1, Edge<T> edge2) {
        Node<T> p1, p2, p3, p4;
        for (Node<T> node : nodes) {
            if (node.getID() == edge1.getStartNode()) {
                p1 = node;
            }if (node.getID() == edge1.getEndNode()) {
                p2 = node;
            }if (node.getID() == edge2.getStartNode()) {
                p3 = node;
            }if (node.getID() == edge2.getEndNode()) {
                p4 = node;
            }
        }
        if (p1.getID() == p3.getID() || p1.getID() == p4.getID() || p2.getID() == p3.getID() || p2.getID() == p4.getID()) {
            return false;
        }
        //printf("Nodes : (%s,%s) -> (%s,%s) \n", p1.getData().getName().c_str(), p2.getData().getName().c_str(), p3.getData().getName().c_str(), p4.getData().getName().c_str());
        /*if (p1.getData().getName() == "E" && p2.getData().getName() == "C" && p3.getData().getName() == "F" && p4.getData().getName() == "B") {
            int temp = 0;
        }*/
        int d1, d2, d3, d4;
        d1 = direction(p3, p4, p1);
        d2 = direction(p3, p4, p2);
        d3 = direction(p1, p2, p3);
        d4 = direction(p1, p2, p4);
        
        //std::cout << "    " << d1 << " : " << d2 << " : " << d3 << " : " << d4 << std::endl;

        if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
            return true;
        }
        return false;
    }

    std::vector<int> subtract(Node<T> p1, Node<T> p2) {
        std::vector<int> r;
        r.push_back(p1.getX() - p2.getX());
        r.push_back(p1.getY() - p2.getY());
        //std::cout << "         " << r.at(0) << " : " << r.at(1) << std::endl;
        return r;
    }

    int crossProduct(std::vector<int> p1, std::vector<int> p2) {/*
        std::cout << "p1x: " << p1[0] << std::endl;
        std::cout << "p1y: " << p1[1] << std::endl;
        std::cout << "p2x: " << p2[0] << std::endl;
        std::cout << "p2y: " << p2[1] << std::endl;*/

        int r = p1.at(0) * p2.at(1) - p2.at(0) * p1.at(1);
        //std::cout << "    cross product : " << p1.[0] << " * " << p2[1] << " - " << p2[0] << " * " << p1[1] << std::endl;
        return r;
    }

    int direction(Node<T> p1, Node<T> p2, Node<T> p3) {
        //std::cout << p1.getX() << " : " << p2.getX() << " : " << p3.getX() << std::endl;
        std::vector<int> a = subtract(p3, p1);
        std::vector<int> b = subtract(p2, p1);
        return  crossProduct(a,b);
    }

    int allCrossing() {
        int crossings = 0;
        for (Edge<T> edge1 : edges) {
            for (Edge<T> edge2 : edges) {
                if (isCrossing(edge1, edge2)) {
                    crossings++;
                }
            }
        }
        return crossings/2;
    }

    int crossingsFrom(int nodeIndex) {
        int nodeID = nodes.at(nodeIndex).getID();
        int crossings = 0;
        for (Edge<T> edge1 : edges) {
            if(edge1.getStartNode() == nodeID )
            for (Edge<T> edge2 : edges) {
                if (isCrossing(edge1, edge2)) {
                    crossings++;
                }
            }
        }
        return crossings ;
    }
    //This is the end of the crossing edge functions.
    //**********************************************************
    
    void swapNodes(int node1index, int node2index) {
        int tempX = nodes.at(node1index).getX();
        int tempY = nodes.at(node2index).getY();
        nodes.at(node1index).setX(nodes.at(node2index).getX());
        nodes.at(node1index).setY(nodes.at(node2index).getY());
        nodes.at(node2index).setX(tempX);  
        nodes.at(node2index).setY(tempY);
    }

};
