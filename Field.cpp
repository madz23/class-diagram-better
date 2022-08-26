///
/// \Authors Davis, Hunter
/// \file Field.cpp
/// \note The implentation for the field objects. Holds the field's name, type, and scope (public, private, protected)
///

#include "Field.hh"

/// Stores info about a class' field
/// Includes name, type, and scope

// Constructors
Field::Field(std::string name, Type type, std::string scope) {
    Field::name = name;
    Field::type = type;
    Field::scope = scope;
}

// Getters and Setters
std::string Field::getName(){
    return name;
}
void Field::setName(std::string name){
    Field::name = name;
}

Type Field::getType(){
    return type;
}
void Field::setType(Type type) {
    Field::type = type;
}

std::string Field::getScope(){
    return scope;
}
void Field::setScope(std::string scope) {
    Field::scope = scope;
}

