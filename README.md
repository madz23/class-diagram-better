# Class Diagram Tool
The Class Diagram Tool is meant to aide in the creation of UML diagrams from predefined projects. The tool takes in a source directory and associated header and source files to map classes, fields, and methods onto a graph according to their inheritance and multiplicity.

## How it works
Given a source directory, the tool extracts the class name, methods, fields, and inheritance structure using regex straight from the header file. It aggregates the classes and associated data into a vector of classes and maps them in a hash table according to their relations to other classes.

## Building

Open the `.sln` in Visual Studio 2019 or 2022 and build using the built in tools.

## Library Structure
The repository is divided into several main directories:
+ root: Contains the source code for all Class Diagram Tool related implementation.
+ [Examples](./Examples): Contains an example directory to exhibit the tool's usage.

## Developers
This project was created by:
+ [Davis Bolt](mailto:davisbolt@isu.edu)
+ [Hunter Harris](mailto:hunterharris@isu.edu)
+ [Patience Lamb](mailto:patiencelamb@isu.edu)

For Idaho State University's CS 4488: Senior Capstone Project taught by David Beard in Spring 2022.
