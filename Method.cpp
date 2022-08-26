///
/// \Authors Davis, Hunter
/// \file Method.cpp
/// \note Implementation for the Method class. Holds name, type, scope, and parameters for a method object.
///

#include "Method.hh"
#include  <string>

/// Stores information about a class' method
/// Includes method name, return type, scope, and parameters

// Constructors
Method::Method(std::string name, Type type, std::string scope, std::string parameters){
    Method::name = name;
    Method::type = type;
    Method::scope = scope;
    Method::parameters = parameters;
}

// Getters and Setters
std::string Method::getName(){
    return name;
}
void Method::setName(std::string name){
    Method::name = name;
}

Type Method::getType(){
    return type;
}
void Method::setType(Type type) {
    Method::type = type;
}

std::string Method::getScope(){
    return scope;
}
void Method::setScope(std::string scope) {
    Method::scope = scope;
}

std::string Method::getParameters(){
    return parameters;
}
void Method::setParameters(std::string parameters){
    Method::parameters = parameters;
}