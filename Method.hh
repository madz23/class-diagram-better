///
/// \Authors Davis, Hunter
/// \file Method.hh
/// \note Definition of the Method class. Holds name, type, scope, and parameters for a given method.
///

#pragma once
#include <string>
#include "Type.hh"

/// <summary>
/// Stores information about a class' method.
/// Includes method name, return type, scope, and parameters.
/// </summary>
class Method {
public:
    // Constructors
    Method(std::string name, Type type, std::string scope, std::string parameters);

    // Getters and Setters
    std::string getName();
    void setName(std::string name);

    Type getType();
    void setType(Type type);

    std::string getScope();
    void setScope(std::string scope);

    std::string getParameters();
    void setParameters(std::string parameters);

private:
    // Fields
    std::string name;
    Type type;
    std::string scope;
    std::string parameters;
};