//
// Created by 陈鹏宇 on 2023/11/18.
//

#include <queue>
#include "Graph.h"
#include "iostream"

using namespace std;

void Graph::setVertex(int length) {
    this->Vertex = new std::list<NodeList>[length];
    this->VertexSum = length;
}

void Graph::setEdge(char (*graph)[2], const int *lengthWeight, const int *timeWeight, int length) {
    this->EdgeSum = length;
    for (int i = 0; i < length; ++i) {
        int start = graph[i][0] - 'A';
        NodeList temp = NodeList();
        temp.name = graph[i][1];
        temp.lengthWeight = lengthWeight[i];
        temp.timeWeight = timeWeight[i];
        this->Vertex[start].push_back(temp);
    }
}

void Graph::handleAdd() {
    cout << "输入节点数量" << endl;
    int num;
    cin >> num;
    this->setVertex(num);
    cout << "输入边数量" << endl;
    int edgeNum;
    cin >> edgeNum;
    cout << "输入边的连接和权重" << endl;
    char graph[edgeNum][2];
    int weight[edgeNum];
    int timeWeight[edgeNum];
    for (int i = 0; i < edgeNum; ++i) {
        cin >> graph[i][0] >> graph[i][1] >> weight[i] >> timeWeight[i];
    }

    this->setEdge(graph, weight, timeWeight, edgeNum);
}

Graph::Graph() { // NOLINT(*-pro-type-member-init)
    this->prepareHandle();
}

void Graph::Dijkstra(char start, char end) {
    int startNum = start - 'A';
    int endNum = end - 'A';
    auto *distance = new Distance[this->VertexSum];
    int *path = new int[this->VertexSum];
    bool *visited = new bool[this->VertexSum];
    for (int i = 0; i < this->VertexSum; ++i) {
        distance[i].index = i;
        visited[i] = false;
    }
    path[startNum] = -1;
    distance[startNum].index = startNum;
    distance[startNum].weight = 0;
    priority_queue<Distance> queue;
    queue.push(distance[startNum]);
    while (!queue.empty()) {
        Distance temp = queue.top();
        queue.pop();
        int index = temp.index;
        if (visited[index]) {
            continue;
        }
        visited[index] = true;
        for (auto i = this->Vertex[temp.index].begin(); i != this->Vertex[temp.index].end(); ++i) {
            if (!visited[i->name - 'A'] && distance[i->name - 'A'].weight > temp.weight + i->lengthWeight) {
                distance[i->name - 'A'].weight = temp.weight + i->lengthWeight;
                queue.push(distance[i->name - 'A']);
                path[i->name - 'A'] = temp.index;
            }
        }
    }
    cout<< "最短路径为" << endl;
    cout << end << " ";
    int pathMap = path[endNum];
    while (pathMap != -1) {
        cout << char(pathMap + 'A') << " ";
        pathMap = path[pathMap];
    }
    cout << endl;
    cout << distance[endNum].weight << endl;

    queue = priority_queue<Distance>();
    for (int i = 0; i < this->VertexSum; ++i) {
        distance[i].index = i;
        distance[i].weight = INT_MAX;
        visited[i] = false;
    }
    path[startNum] = -1;
    distance[startNum].index = startNum;
    distance[startNum].weight = 0;
    queue.push(distance[startNum]); // 重新初始化
    while (!queue.empty()) {
        Distance temp = queue.top();
        queue.pop();
        int index = temp.index;
        if (visited[index]) {
            continue;
        }
        visited[index] = true;
        for (auto i = this->Vertex[temp.index].begin(); i != this->Vertex[temp.index].end(); ++i) {
            if (!visited[i->name - 'A'] && distance[i->name - 'A'].weight > temp.weight + i->timeWeight) {
                distance[i->name - 'A'].weight = temp.weight + i->timeWeight;
                queue.push(distance[i->name - 'A']);
                path[i->name - 'A'] = temp.index;
            }
        }
    }
    cout<< "最短时间为" << endl;
    cout << end << " ";
    pathMap = path[endNum];
    while (pathMap != -1) {
        cout << char(pathMap + 'A') << " ";
        pathMap = path[pathMap];
    }
    cout << endl;
    cout << distance[endNum].weight << endl;

    delete[] distance;
    delete[] path;
    delete[] visited;
}

void Graph::prepareHandle() {
    setVertex(5);
    char graph[7][2] = {{'A', 'B'},
                        {'A', 'C'},
                        {'B', 'C'},
                        {'B', 'D'},
                        {'C', 'D'},
                        {'C', 'E'},
                        {'D', 'E'}};
    int weight[7] = {1, 3, 1, 2, 1, 3, 1};
    int timeWeight[7] = {2, 6, 3, 8, 5, 2, 10};
    setEdge(graph, weight, timeWeight, 7);
}

Graph::~Graph() {
    delete[] this->Vertex;
}

