///
/// \Authors Davis
/// \file Node.hh
/// \note Definition and implementation of Node class. Holds a generic type of data as well as the ID of the given node.
///

#pragma once

/// 

/// <summary>
/// Generic Node class for the Graph data structure.
/// Stores data of any type.
/// </summary>
/// <typeparam name="T">The class type for the object held in Node->data</typeparam>
template<class T>
class Node {
public:
    // Constructors
    Node() = default;
    Node(int ID, T data) {
        this->ID = ID;
        this->data = data;
        this->x = 100;
        this->y = 100;
        this->inEdges = 0;
        this->outEdges = 0;
    }

    // Getters and Setters
    int getID() {
        return ID;
    }
    void setID(int ID) {
        this->ID = ID;
    }

    int getX() {
        return  x;
    }
    int getY() {
        return y;
    }
    void setX(int value) {
        this->x = value;
    }
    void setY(int value) {
        this->y = value;
    }


    int getInEdges() {
        return inEdges;
    }
    int getOutEdges() {
        return outEdges;
    }
    void setInEdges(int value) {
        this->inEdges = value;
    }
    void setOutEdges(int value) {
        this->outEdges = value;
    }
    
    T getData() {
        return data;
    }
    void setData(T data) {
        this->data = data;
    }

private:
    // Fields
    int ID;
    T data;
    int x;
    int y;
    int inEdges;
    int outEdges;
};