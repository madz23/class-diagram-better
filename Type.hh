///
/// \Authors Hunter
/// \file Type.hh
/// \note Definition for the Type class. Holds name, collection type, namespace name and whether the type is a collection or not.
///

#pragma once
#include <string>

/// <summary>
/// Stores information about a class' method.
/// Includes method name, return type, scope, and parameters.
/// </summary>
class Type {
public:
    // Constructors
    Type();
    Type(std::string name);
    Type(std::string name, std::string namespaceName);
    Type(std::string name, std::string namespaceName, std::string collectionType);

    // Getters and Setters
    std::string getName();
    void setName(std::string name);

    bool getIsCollection();
    void setIsCollection(bool isCollection);

    std::string getCollectionType();
    void setCollectionType(std::string collectionType);

    std::string getNamespaceName();
    void setNamespaceName(std::string namespaceName);

    // Methods
    std::string toString();

private:
    // Fields
    std::string name;
    bool isCollection;
    std::string collectionType;
    std::string namespaceName;
};