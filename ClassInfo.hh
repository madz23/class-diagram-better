///
/// \Authors Davis, Hunter
/// \file ClassInfo.hh
/// \note The initialization for the class info class
///

#pragma once
#include "Field.hh"
#include "Method.hh"
#include <iostream>
#include <string>
#include <vector>

/// <summary>
/// Holds necessary class data for the Class Diagram
/// Contains a name and vectors of Fields and Methods
/// </summary>
class ClassInfo {
public:
    // Constructors
    ClassInfo();
    ClassInfo(std::string name);

    // Add fields and methods
    void addField(Field field);
    void addMethod(Method method);
    void addBase(std::string base);

    // Getters and Setters
    std::string getName();
    void setName(std::string name);

    std::vector<Field> getFields();

    std::vector<Method> getMethods();
    
    std::vector<std::string> getBases();

    /// Neatly prints the the info of the class
    void prettyPrint();

private:
    // Fields
    std::string name;
    std::vector<Field> fields;
    std::vector<Method> methods;
    std::vector<std::string> bases;
};