#include <iostream>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "ArcGraph.h"
#include "SetGraph.h"

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;
    
    while (!qu.empty())
    {
        int currentVertex = qu.front();
        qu.pop();
        
        func(currentVertex);
        
        for (int nextVertex: graph.GetNextVertices(currentVertex))
        {
            if (!visited[nextVertex])
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph &graph, const std::function<void(int)> &func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            BFS(graph, i, visited, func);
        }
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
    visited[vertex] = true;
    func(vertex);
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            DFS(graph, nextVertex, visited, func);
        }
    }
}

void mainDFS(const IGraph &graph, const std::function<void(int)> &func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            DFS(graph, i, visited, func);
        }
    }
}

void topologicalSortInternal(const IGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted)
{
    visited[vertex] = true;
    
    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            topologicalSortInternal(graph, nextVertex, visited, sorted);
        }
    }
    
    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph &graph)
{
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            topologicalSortInternal(graph, i, visited, sorted);
        }
    }
    
    return sorted;
}

int main(int argc, const char * argv[]) {
    ArcGraph arcGraph(7);
    arcGraph.AddEdge(0, 1);
    arcGraph.AddEdge(0, 5);
    arcGraph.AddEdge(1, 2);
    arcGraph.AddEdge(1, 3);
    arcGraph.AddEdge(1, 5);
    arcGraph.AddEdge(1, 6);
    arcGraph.AddEdge(3, 2);
    arcGraph.AddEdge(3, 4);
    arcGraph.AddEdge(3, 6);
    arcGraph.AddEdge(5, 4);
    arcGraph.AddEdge(5, 6);
    arcGraph.AddEdge(6, 4);

    ListGraph listGraph = arcGraph;
    MatrixGraph matrixGraph = listGraph;
    SetGraph setGraph = matrixGraph;


    std::cout << "BFS arcGraph" << std::endl;
    mainBFS(arcGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;
    
    std::cout << "BFS listGraph" << std::endl;
    mainBFS(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;
    
    std::cout << "BFS matrixGraph" << std::endl;
    mainBFS(matrixGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;
    
    std::cout << "BFS setGraph" << std::endl;
    mainBFS(setGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl << std::endl;
    

    std::cout << "DFS arcGraph" << std::endl;
    mainDFS(arcGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;

    std::cout << "DFS listGraph" << std::endl;
    mainDFS(listGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;

    std::cout << "DFS matrixGraph" << std::endl;
    mainDFS(matrixGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;

    std::cout << "DFS setGraph" << std::endl;
    mainDFS(setGraph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;
    
    return 0;
}