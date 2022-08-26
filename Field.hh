///
/// \Authors Davis, Hunter
/// \file Field.hh
/// \note The definition of Field class
///

#pragma once
#include <string>
#include "Type.hh"

/// <summary>
/// Stores info about a class' field.
/// Includes name, type, and scope.
/// </summary>
class Field {
public:
    // Constructors
    Field() = default;
    Field(std::string name, Type type, std::string scope);

    // Getters and Setters
    std::string getName();
    void setName(std::string name);

    Type getType();
    void setType(Type type);

    std::string getScope();
    void setScope(std::string scope);

private:
    // Fields
    std::string name;
    Type type;
    std::string scope;
};
