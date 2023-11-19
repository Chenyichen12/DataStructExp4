//
// Created by 陈鹏宇 on 2023/11/18.
//

#ifndef DATASTRUCTEXP4_GRAPH_H
#define DATASTRUCTEXP4_GRAPH_H

#include "list"
#include <climits>



class Graph {
private:
    struct NodeList {
        char name = '\0';
        int weight = INT_MAX; //表示权重
    };
    std::list<NodeList> *Vertex;
    int VertexSum;
    int EdgeSum;

    struct Distance {
        int index = 0;
        int weight = INT_MAX; //表示权重
        bool operator<(const Distance &a) const {
            return a.weight < this->weight;
        }
    };

public:
    void setVertex(int);

    void setEdge(char graph[][2], const int *weight, int length);

    void handleAdd();
    void prepareHandle();
    Graph();

    void Dijkstra(char start, char end);
    ~Graph();
};


#endif //DATASTRUCTEXP4_GRAPH_H
