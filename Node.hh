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
    }

    // Getters and Setters
    int getID() {
        return ID;
    }
    void setID(int ID) {
        this->ID = ID;
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
};