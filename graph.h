//
// Created by corbi on 12/8/2021.
//

#ifndef INC_236PROJECT1_GRAPH_H
#define INC_236PROJECT1_GRAPH_H


#include "Interpreter.h"
#include <set>

class Graph {
private:
    std::vector<Rule> rules;
    std::map<int, std::set<int>> adjacencylist;
    std::map<int, std::set<int>> reverseadjacencylist;
    std::vector<int> postorder;
    std::set<int> visited;
    std::set<int> scccomponenttemp;
    std::map<int, std::set<int>> scc;
public:
    Graph(DatalogProgram datalog)
    {
        rules = datalog.getRules();
        createDependency();
        createReverseDependency();
        DepthFirstSearchForestReverse(reverseadjacencylist);
        DepthFirstSearchForestForward(adjacencylist);
    };
    ~Graph() = default;

    void createDependency();
    std::set<int> findConnections(int index);
    void createReverseDependency();
    std::set<int> findReverseConnections(int index);
    void DepthFirstSearch(int vertex, std::map<int, std::set<int>> searchgraph);
    void DepthFirstSearchForestReverse(std::map<int, std::set<int>> searchgraph);
    void DepthFirstSearchForestForward(std::map<int, std::set<int>> searchgraph);
    bool checkSelfDependency(int key);
    std::map<int, std::set<int>> getSCC()
    {
        return scc;
    };
    void PrintDependency()
    {
        for (auto it=adjacencylist.begin(); it!=adjacencylist.end(); ++it) {
            std::cout << "R" << it->first << ":";
            std::string str;
            if (it->second.empty() == false) {
                for (auto hi = it->second.begin(); hi !=
                                                   it->second.end(); ++hi) {
                    auto s = std::to_string(*hi);
                    str += "R" + s + ",";
                }
                str.pop_back();
                std::cout << str;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

};


#endif //INC_236PROJECT1_GRAPH_H
