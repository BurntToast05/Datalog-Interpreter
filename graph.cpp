//
// Created by corbi on 12/8/2021.
//

#include "graph.h"

void Graph::createDependency() {
    for (size_t i = 0; i < rules.size(); ++i)
    {
        std::set<int> emptyset = findConnections(i);
        adjacencylist.insert ( std::pair<int,std::set<int>>(i, emptyset) );
    }
    /*for (auto it=adjacencylist.begin(); it!=adjacencylist.end(); ++it) {
        std::cout << "R" << it->first << ":";
        for (auto hi = it->second.begin(); hi !=
                                      it->second.end(); ++hi) {
            std::cout << "R" << *hi << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/
}

std::set<int> Graph::findConnections(int index) {
    std::set<int> settoreturn;
        Rule currentrule = rules.at(index);
        std::vector<Predicate> bodyPredicates = currentrule.getBodyPredicates();
        for (size_t j = 0; j < bodyPredicates.size(); ++j)
        {
            for (size_t k = 0; k < rules.size(); ++k) {
                if (bodyPredicates.at(j).getId() == rules.at(k).getHeadPredicate().getId())
                {
                    settoreturn.insert(k);
                }
            }
        }
    return settoreturn;
}

void Graph::createReverseDependency() {
    for (size_t i = 0; i < rules.size(); ++i)
    {
        std::set<int> emptyset = findReverseConnections(i);
        reverseadjacencylist.insert ( std::pair<int,std::set<int>>(i, emptyset) );
    }
    /*for (auto it=reverseadjacencylist.begin(); it!=reverseadjacencylist.end(); ++it) {
        std::cout << "R" << it->first << ":";
        for (auto hi = it->second.begin(); hi !=
                                           it->second.end(); ++hi) {
            std::cout << "R" << *hi << ",";
        }
        std::cout << std::endl;
    }*/
}

std::set<int> Graph::findReverseConnections(int index) {
    std::set<int> settoreturn;
    Rule currentrule = rules.at(index);
    for (size_t k = 0; k < rules.size(); ++k) {
        for (size_t j = 0; j < rules.at(k).getBodyPredicates().size(); ++j) {
            if (rules.at(k).getBodyPredicates().at(j).getId() == currentrule.getHeadPredicate().getId())
            {
                settoreturn.insert(k);
            }
        }
    }
    return settoreturn;
}

void Graph::DepthFirstSearch(int vertex, std::map<int, std::set<int>> searchgraph) {
    if (vertex <= static_cast<int>(rules.size())) {
        visited.insert(vertex);
        std::set<int> searchset = searchgraph.find(vertex)->second;
        for (int i : searchset) {
            if (visited.count(i) == 0) {
                DepthFirstSearch(i, searchgraph);
            }
        }
        postorder.push_back(vertex);
        scccomponenttemp.insert(vertex);
    }
}

void Graph::DepthFirstSearchForestReverse(std::map<int, std::set<int>> searchgraph) {
    for (auto it=searchgraph.begin(); it!=searchgraph.end(); ++it) {
        if (visited.count(it->first) == 0 )
        {
            DepthFirstSearch(it->first, searchgraph);
        }
    }
    visited.clear();
}

void Graph::DepthFirstSearchForestForward(std::map<int, std::set<int>> searchgraph) {
    int sccindex = 0;
    if (scccomponenttemp.size() != 0) {
        scccomponenttemp.clear();
    }
    for (int i = postorder.size() - 1; i >= 0; --i)
    {
        if (visited.count(postorder.at(i)) == 0)
        {
            DepthFirstSearch(postorder.at(i), searchgraph);
            scc.insert ( std::pair<int,std::set<int>>(sccindex, scccomponenttemp) );
            scccomponenttemp.clear();
            sccindex++;
        }
    }

    /*std::cout << std::endl;
    for (auto it=scc.begin(); it!=scc.end(); ++it) {
        std::cout << "SCC" << it->first << ":";
        for (auto hi = it->second.begin(); hi !=
                                           it->second.end(); ++hi) {
            std::cout << "R" << *hi << ",";
        }
        std::cout << std::endl;
    }*/
}

bool Graph::checkSelfDependency(int key) {
    std::set<int> check = adjacencylist.find(key)->second;
    if (check.count(key) > 0)
    {
        return true;
    }
    return false;
}