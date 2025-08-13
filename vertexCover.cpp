#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cstdlib>
using namespace std;

class Graph
{
  vector<int> vertexList;
  vector<pair<int, int>> edgeList;
  int numOfVer = 0;

public:
  Graph(int n)
  {
    numOfVer = n;
    addVertex();
  }

  void addVertex()
  {
    for (int i = 0; i < numOfVer; i++)
    {
      vertexList.push_back(i);
    }
  }

  void addEdge(int u, int v)
  {
    edgeList.push_back(make_pair(u, v));
  }

  void showVertices()
  {
    for (int i = 0; i < vertexList.size(); i++)
    {
      cout << i << " ";
    }
  }

  void showEdges()
  {
    for (size_t i = 0; i < edgeList.size(); i++) // size_t kind of an adaptable integer
    {
      cout << "{" << edgeList[i].first << ", " << edgeList[i].second << "}" << endl;
    }
  }

  vector<vector<int>> subset(vector<int> &vertexList)
  {
    int n = vertexList.size();
    int subsetCount = pow(2, n);
    vector<vector<int>> subsets;
    for (int mask = 0; mask < subsetCount; mask++)
    {
      vector<int> subset;
      for (int i = 0; i < n; i++)
      {
        if ((mask & (1 << i)) != 0)
        {                                  // check if i th bit is set
          subset.push_back(vertexList[i]); // add the element at ith index if it is set
        }
      }
      subsets.push_back(subset);
    }
    return subsets;
  }

  void showSubsets()
  {
    vector<vector<int>> allSubsets = subset(vertexList);
    for (auto subset : allSubsets)
    {
      for (int i = 0; i < subset.size(); i++)
      {
        cout << subset[i] << " "; // valid syntax only if i is an integer
      }
      cout << endl;
    }
  }

  bool isVertexCover(vector<int> &subset)
  {
    for (size_t i = 0; i < edgeList.size(); i++) // size_t kind of an adaptable integer
    {
      if (
          (find(subset.begin(), subset.end(), edgeList[i].first) == subset.end()) &&
          (find(subset.begin(), subset.end(), edgeList[i].second) == subset.end()))
      {
        // iterate to the end of the subset for each endpoint and if both are not found
        return false;
      }
    }
    return true;
  }

  vector<vector<int>> vertexCover()
  {
    vector<vector<int>> allSubsets = subset(vertexList);
    vector<vector<int>> vertexCovers;
    for (auto subset : allSubsets)
    {
      if (isVertexCover(subset))
      {
        vertexCovers.push_back(subset);
      }
    }

    // minimum Vertex Cover
    int minSize = vertexCovers[0].size();
    vector<vector<int>> minVertexCover;
    for (int i = 1; i < vertexCovers.size(); i++)
    {
      if (vertexCovers[i].size() < minSize)
      {
        minSize = vertexCovers[i].size();
      }
    }

    for (int i = 0; i < vertexCovers.size(); i++)
    {
      if (vertexCovers[i].size() == minSize)
      {
        minVertexCover.push_back(vertexCovers[i]);
      }
    }
    return minVertexCover;
  }
};

int main(int argc, char *argv[])
{

  if (argc < 3)
  {
    cerr << "Usage: ./demo <vertices> <edges>\n";
    return 1;
  }

  int num_vertices = stoi(argv[1]);
  int num_edges = stoi(argv[2]);

  // Decide file names based on vertices and edges
  string inputFile = "input_" + to_string(num_vertices) + "_" + to_string(num_edges) + ".txt";
  string outputFile = "output_" + to_string(num_vertices) + "_" + to_string(num_edges) + ".txt";

  // reading the input file
  ifstream input(inputFile); // open file
  int n, m;
  input >> n >> m; // read vertices and edges count
  Graph g(n);

  for (int i = 0; i < m; i++)
  {
    int u, v;
    input >> u >> v;
    g.addEdge(u, v);
  }
  input.close();

  vector<vector<int>> answer;
  cout << "Calculating vertex cover now..." << endl
       << flush;
  auto start = chrono::high_resolution_clock::now();
  answer = g.vertexCover();
  auto end = chrono::high_resolution_clock::now();
  double timeTaken = chrono::duration<double, milli>(end - start).count();
  cout << "Computed the shortest vertex cover in (ms)" << " " << timeTaken << endl
       << flush;

  // writing to the output file
  ofstream output(outputFile, ios::trunc);
  output << "\n# Results\n";
  output << "Running Time (ms): " << timeTaken << "\n";
  output << "Smallest Vertex Cover(s):\n";

  for (int i = 0; i < answer.size(); i++)
  {
    output << "{ ";
    for (size_t j = 0; j < answer[i].size(); j++)
    {
      output << answer[i][j];
      if (j != answer[i].size() - 1)
        output << ", ";
    }
    output << " }\n";
  }
  output.close();
  return 0;
}