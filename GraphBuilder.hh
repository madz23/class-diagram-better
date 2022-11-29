//
///
/// \Authors Davis, Hunter
/// \file GraphBuilder.hh
/// \note Definitiono and immplementation for the GraphBuilder class. Constructs a graph of edges and nodes from the parsed classes found using the directory iterator
///

#pragma once
#include "Graph.hh"
#include "ClassInfo.hh"
#include "FileManager.hh"
#include "ClassParser.hh"
#include <string>
#include <vector>
#include <unordered_map>

/// <summary>
/// Builds the graph data structure for the class diagram.
/// Contains only a static build method.
/// </summary>
class GraphBuilder {
public:
    // Static Methods

    /// <summary>
    /// Given a directory for the source files of a project, creates a Graph
    /// and adds Nodes and Edges to represent class diagram
    /// </summary>
    /// <param name="srcDirectory">The path to the c++ project's source directory</param>
    /// <param name="recursive">Whether or not to recursively search subdirectories</param>
    /// <returns>the graph data structure contain nodes with class information</returns>
    static Graph<ClassInfo> build(std::string srcDirectory, bool recursive, int distance = 120) {
        Graph<ClassInfo> graph;
        graph.setDistance(distance);
        std::vector<std::string> paths = FileManager::getFilePaths(srcDirectory, recursive);
        std::unordered_map<std::string, ClassInfo> classMap;

        int ID = 0;
        for (std::string path : paths) {
            std::string fileContents = FileManager::readFile(path);
            std::vector<ClassInfo> classInfos = ClassParser::parseClasses(fileContents);
            for (auto& classInfo : classInfos) {
                Node<ClassInfo> node(ID, classInfo);
                graph.addNode(node);
                classMap[classInfo.getName()] = classInfo;
                ID++;
            }
        }

        // Adding edges for inheritance and associations
        for (std::pair<std::string, ClassInfo> element : classMap) {

            // Find Inheritance
            for (std::string baseClass : element.second.getBases()) {
                if (classMap.count(baseClass)) {
                    int startNodeId = findNodeByClassName(graph.getNodes(), element.second.getName());
                    int endNodeId = findNodeByClassName(graph.getNodes(), baseClass);
                    if (startNodeId != -1 && endNodeId != -1) {
                        Edge<ClassInfo> edge(startNodeId, endNodeId, Edge<ClassInfo>::Type::INHERITANCE, Edge<ClassInfo>::Multiplicity::NONE);
                        graph.addEdge(edge);
                    }
                }
            }

            // Find Associations
            for (Field field : element.second.getFields()) {
                std::string fieldClass = field.getType().getName();
                if (classMap.count(fieldClass)) {
                    int startNodeId = findNodeByClassName(graph.getNodes(), element.second.getName());
                    int endNodeId = findNodeByClassName(graph.getNodes(), fieldClass);
                    if (startNodeId != -1 && endNodeId != -1) {
                        if (field.getType().getIsCollection()) {
                            Edge<ClassInfo> edge(startNodeId, endNodeId, Edge<ClassInfo>::Type::ASSOCIATION, Edge<ClassInfo>::Multiplicity::ONE_TO_MANY);
                            graph.addEdge(edge);
                        }
                        else {
                            Edge<ClassInfo> edge(startNodeId, endNodeId, Edge<ClassInfo>::Type::ASSOCIATION, Edge<ClassInfo>::Multiplicity::ONE_TO_ONE);
                            graph.addEdge(edge);
                        }
                    }
                }
            }
        }

        return graph;
    }

private:
    // Helper Methods

    /// <summary>
    /// Finds the id of a node in a list of nodes by the class name of the node's data
    /// </summary>
    /// <param name="nodes">A list of nodes to search through</param>
    /// <param name="className">The name of the class to search for</param>
    /// <returns>The id of the node that contains a classInfo object with name className</returns>
    static int findNodeByClassName(std::vector<Node<ClassInfo>> nodes, std::string className) {
        int retNodeId = -1;
        for (Node<ClassInfo> node : nodes) {
            if (node.getData().getName() == className) {
                retNodeId = node.getID();
            }
        }
        return retNodeId;
    }
};



