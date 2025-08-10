#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
using namespace std;

class Graph{
    vector<int> vertexList;
    vector<pair<int,int>> edgeList;
    int numOfVer=0;

    public:
      Graph(int n){ 
        numOfVer=n;
        addVertex();
      }

      void addVertex()
      {
         for(int i=0;i<numOfVer;i++)
         {
           vertexList.push_back(i);
         }
      }
      
      void addEdge(int u, int v)
      {
         edgeList.push_back(make_pair(u,v));
      }

      void showVertices(){
        for(int i=0; i<vertexList.size();i++){
          cout<<i<<" ";
        }
      }

      void showEdges()
      {
        for (size_t i=0; i<edgeList.size();i++)  //size_t kind of an adaptable integer
        {
          cout <<"{" << edgeList[i].first << ", " << edgeList[i].second << "}" <<endl;
        }
      }

      vector<vector<int>> subset(vector<int>& vertexList){
        int n=vertexList.size();
        int subsetCount=pow(2,n);
        vector<vector<int>> subsets;
        for(int mask=0;mask<subsetCount;mask++)
        {
           vector<int> subset;
           for(int i=0;i<n;i++){
             if((mask &(1<<i))!=0){   // check if i th bit is set
              subset.push_back(vertexList[i]); //add the element at ith index if it is set
             }
           }
           subsets.push_back(subset);
        }
        return subsets;
      }

      void showSubsets()
      {
         vector<vector<int>> allSubsets=subset(vertexList);
         for(auto subset:allSubsets){
           for(int i=0; i<subset.size();i++){
              cout<<subset[i]<<" ";  //valid syntax only if i is an integer
           }
           cout<<endl;
         }
      }

      bool isVertexCover(vector<int>& subset)
      {
        for (size_t i = 0; i < edgeList.size(); i++) // size_t kind of an adaptable integer
        {
          if(
               (find(subset.begin(), subset.end(), edgeList[i].first) == subset.end()) &&
               (find(subset.begin(), subset.end(), edgeList[i].second) == subset.end())
              )
               {
                // iterate to the end of the subset for each endpoint and if both are not found 
                 return false;
               }
        }
        return true;
      }

      void vertexCover()
      {
        vector<vector<int>> allSubsets = subset(vertexList);
        vector<vector<int>> vertexCovers;
        for (auto subset : allSubsets)
        {
           if (isVertexCover(subset)){
                vertexCovers.push_back(subset);
           }
        }
        
        // minimum Vertex Cover
        int minSize = vertexCovers[0].size();
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
            for (size_t j = 0; j < vertexCovers[i].size(); j++)
            {
              cout << vertexCovers[i][j];
            }
            cout << endl;
          }
        }
      }       
};

int main()
{
    int n=4;  //number of vertices 
    Graph g(n);
    g.addEdge(0,3);
    g.addEdge(2,3);
    g.addEdge(1,3);
    g.vertexCover();
    return 0;

}