///
/// \Authors Davis, Hunter
/// \file Edge.hh
/// \note The description and implementation for the edge objects. Implemntation is in header file due to templating
///

#pragma once
#include "Node.hh"

/// <summary>
/// Generic Edge class for the Graph data structure.
/// Contains a startNode and endNode, as well as type and multiplicity.
/// </summary>
/// <typeparam name="T">The class type for the object held in Node->data</typeparam>
template<class T>
class Edge {
public:

    /// Describe the type of relationship between classes
    enum class Type {
        ASSOCIATION, AGGREGATION, COMPOSITION, INHERITANCE, IMPLEMENTATION
    };
    /// Describe the multiplicity of the relationship between classes
    enum class Multiplicity {
        NONE, ONE_TO_ONE, ONE_TO_MANY, MANY_TO_ONE, MANY_TO_MANY
    };

    // Constructors
    Edge() = default;
    Edge(int startNodeId, int endNodeId, Edge<T>::Type type, Edge<T>::Multiplicity multiplicity) {
        this->startNodeId = startNodeId;
        this->endNodeId = endNodeId;
        this->type = type;
        this->multiplicity = multiplicity;
    }

    // Getters and Setters
    int getStartNode() {
        return startNodeId;
    }
    void setStartNode(int startNodeId) {
        this->startNodeId = startNodeId;
    }

    int getEndNode() {
        return endNodeId;
    }
    void setEndNode(int endNodeId) {
        this->endNodeId = endNodeId;
    }

    Type getType() {
        return type;
    }
    void setType(Type type) {
        this->type = type;
    }

    Multiplicity getMultiplicity() {
        return multiplicity;
    }
    void setMultiplicity(Multiplicity multiplicity) {
        this->multiplicity = multiplicity;
    }

private:
    // Fields
    int startNodeId;
    int endNodeId;
    Type type;
    Multiplicity multiplicity;
};