///
/// \Authors Davis, Hunter
/// \file ClassInfo.cpp
/// \note The implementation for the class info objects. Holds fields, methods, and base classes for a class.
///

#include "ClassInfo.hh"
#include "Field.hh"
#include "Method.hh"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

/// Holds necessary class data for the Class Diagram
/// Contains a name and vectors of Fields and Methods

// Constructors
ClassInfo::ClassInfo() = default;

ClassInfo::ClassInfo(std::string name) {
    ClassInfo::name = name;
}

// Add fields and methods
void ClassInfo::addField(Field field) {
    fields.push_back(field);
}
void ClassInfo::addMethod(Method method) {
    methods.push_back(method);
}
void ClassInfo::addBase(std::string base) {
    bases.push_back(base);
}

// Getters and Setters
std::string ClassInfo::getName() {
    return name;
}
void ClassInfo::setName(std::string name) {
    ClassInfo::name = name;
}

std::vector<Field> ClassInfo::getFields() {
    return fields;
}

std::vector<Method> ClassInfo::getMethods() {
    return methods;
}

std::vector<std::string> ClassInfo::getBases() {
    return bases;
}

/// <summary>
/// Neatly prints the the info of the class
/// </summary>
void ClassInfo::prettyPrint() {
    std::cout << "==========================" << std::endl;
    std::cout << getName() << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << std::endl;
    std::cout << "Methods" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    unsigned long long scopeWidth = 0;
    unsigned long long typeWidth = 0;
    unsigned long long nameWidth = 0;
    unsigned long long parameterWidth = 0;
    for (Method method: getMethods()) {
        scopeWidth = scopeWidth < method.getScope().length() ? method.getScope().length() : scopeWidth;
        typeWidth = typeWidth < method.getType().toString().length() ? method.getType().toString().length() : typeWidth;
        nameWidth = nameWidth < method.getName().length() ? method.getName().length() : nameWidth;
        parameterWidth = parameterWidth < method.getParameters().length() ? method.getParameters().length() : parameterWidth;
    }
    for (Method method: getMethods()) {
        std::cout << std::setw(scopeWidth + 2) << std::left << method.getScope() << " ";
        std::cout << std::setw(typeWidth + 2) << std::left << method.getType().toString() << " ";
        std::cout << std::setw(nameWidth + 2) << std::left << method.getName() << " ";
        std::cout << std::setw(parameterWidth + 2) << std::left << method.getParameters() << std::endl;
    }
    std::cout << "``````````````````````````" << std::endl;
    std::cout << std::endl;
    std::cout << "Fields" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    scopeWidth = 0;
    typeWidth = 0;
    nameWidth = 0;
    for (Field field: getFields()) {
        scopeWidth = scopeWidth < field.getScope().length() ? field.getScope().length() : scopeWidth;
        typeWidth = typeWidth < field.getType().toString().length() ? field.getType().toString().length() : typeWidth;
        nameWidth = nameWidth < field.getName().length() ? field.getName().length() : nameWidth;
    }
    for (Field field: getFields()) {
        std::cout << std::setw(scopeWidth + 2) << std::left << field.getScope() << " ";
        std::cout << std::setw(typeWidth + 2) << std::left << field.getType().toString() << " ";
        std::cout << std::setw(nameWidth + 2) << std::left << field.getName() << std::endl;
    }
    std::cout << "``````````````````````````" << std::endl;
    std::cout << std::endl << std::endl;
}
