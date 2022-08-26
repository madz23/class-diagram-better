///
/// \Authors Davis, Hunter
/// \file Grpah.hh
/// \note A class defining graph objects. Holds nodes and edges for describing a graph. Is a template class.
///

#pragma once

#include "Node.hh"
#include "Edge.hh"
#include <vector>

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

    // Getters
    std::vector<Node<T>> getNodes() {
        return nodes;
    }
    std::vector<Edge<T>> getEdges() {
        return edges;
    }

private:
    // Fields
    std::vector<Node<T>> nodes;
    std::vector<Edge<T>> edges;
};
