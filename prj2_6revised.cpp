#include <iostream>
#include<stdio.h> 
#include<stdlib.h> 
#include <vector>
#include <stack> 
#include <queue>
#include <unordered_map> 
#include <map> 
#include <iterator> 
#include <string>
#include <climits>
#include <cmath>
#include <algorithm>
using namespace std;

struct Coord {
    int x;
    int y;
};
struct GridNode {
    string data;
    vector <GridNode> edgeList;
    Coord coord;
}; 

class GridGraph {
    private: 
        vector <GridNode> nodeList;
        vector <bool> visitedList;
    public:
        void addGridNode(int x, int y, string nodeVal) {
            GridNode newNode;
            
            newNode.data=nodeVal;

            Coord myCoord;
            myCoord.x=x;
            myCoord.y=y;
            newNode.coord=myCoord;
            
            nodeList.push_back(newNode);
            visitedList.push_back(false);
        }  

        void addUndirectedEdge(GridNode first, GridNode second) {
            //if first and second are neighbors

            int firstIndex, secondIndex;
            int n=nodeList.size();
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==first.data) {
                    firstIndex=i;
                }
            }
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==second.data) {
                    secondIndex=i;
                }
            }

            //one of the first or second nodes have four edges/neighbours, in which case dont add new bi-directional edge
            if (nodeList[firstIndex].edgeList.size()>=4 || nodeList[secondIndex].edgeList.size()>=4)
                return;

            //only create edge between neighbors
            //  i.e. either x coord or y coord should have a difference of 1 between first and second
            //  example: if first is 2,2 second can only be 3,2 or 2,3 or 1,2 or 2,1
            if (!(
                    (nodeList[secondIndex].coord.x==nodeList[firstIndex].coord.x+1 and nodeList[secondIndex].coord.y==nodeList[firstIndex].coord.y)
                    ||
                    (nodeList[secondIndex].coord.x==nodeList[firstIndex].coord.x and nodeList[secondIndex].coord.y==nodeList[firstIndex].coord.y+1)
                    ||
                    (nodeList[secondIndex].coord.x==nodeList[firstIndex].coord.x-1 and nodeList[secondIndex].coord.y==nodeList[firstIndex].coord.y)
                    ||
                    (nodeList[secondIndex].coord.x==nodeList[firstIndex].coord.x and nodeList[secondIndex].coord.y==nodeList[firstIndex].coord.y-1)
                ))
                return;

            bool found=false;
            int v;
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==first.data) {
                    v=nodeList[i].edgeList.size();
                    //create an edge only if edge does not exist
                    for(int j=0; j<v; j++) {
                        if(nodeList[i].edgeList[j].data==second.data) {
                            found=true;
                            break;
                        }
                    }
                    if (!found) {
                        nodeList[i].edgeList.push_back(second);
                    }
                    break;
                }
                
            }
            found=false;
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==second.data) {
                    v=nodeList[i].edgeList.size();
                    //create an edge only if edge does not exist
                    for(int j=0; j<v; j++) {
                        if(nodeList[i].edgeList[j].data==first.data) {
                            found=true;
                            break;
                        }
                    }
                    if (!found) {
                        nodeList[i].edgeList.push_back(first);
                    }

                    break;
                }
                
            }
            //if they are not neighbors: do nothing
        }


        void removeUndirectedEdge( GridNode first, GridNode second) {
            int n=nodeList.size();
            
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==first.data) {
                    int v=nodeList[i].edgeList.size();
                    for(int j=0; j<v; j++) {
                        if(nodeList[i].edgeList[j].data==second.data) {
                            nodeList[i].edgeList.erase(nodeList[i].edgeList.begin()+j);
                            break;
                        }
                    }
                    break;
                }
            }
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==second.data) {
                    int v=nodeList[i].edgeList.size();
                    for(int j=0; j<v; j++) {
                        if(nodeList[i].edgeList[j].data==first.data) {
                            nodeList[i].edgeList.erase(nodeList[i].edgeList.begin()+j);
                            break;
                        }
                    }
                    break;
                }
            }
        }

        vector <GridNode> getAllNodes() {
            return nodeList;
        }
};
bool operator < (const Coord& left, const Coord& right)
{
    if (left.y < right.y)
    {
        return true;
    }
    else if (right.y < left.y)
    {
        return false;
    }
    else if (left.x < right.x)
    {
        return true;
    }
    else /* (right.x < left.x) */
    {
        return false;
    }
}

class Main {
    public:
    vector <GridNode> h;
    GridGraph myGridGraph;    
    int findNumberofDigits(int n) {
        string s = to_string(n);
        return s.length();
    }

    GridGraph createRandomGridGraph(int n) {
        int nodesAdded=1;
        int xx = findNumberofDigits(n);
        int maxN = pow(10,xx);
        bool found;

        for (int y=0;y<n;y++) {
            for (int x=0;x<n;x++) {
                vector <GridNode> nl = myGridGraph.getAllNodes();
                while (true) {
                    int val=rand() % ((int)pow(n,3)) + 1;
                    
                    
                    found=false;
                    for (int j=0;j<nl.size();j++) {
                        if (nl[j].data == to_string(val)) {
                            found=true;
                            break;
                        }
                    }
                    if (!found) {
                        myGridGraph.addGridNode(x, y, to_string(val));
                        nodesAdded++;
                        break;
                    }
                }
                if (nodesAdded>pow(n,2))
                    break;
            }
            if (nodesAdded>pow(n,2))
                break;
        }

        //create adjacent neighbours
        vector <GridNode> myNodesList;
        myNodesList = myGridGraph.getAllNodes();
        
        //create edges across x-axis        
        int y=0;
        while (y<pow(n,2)) {
            for (int x=0;x<n;x++) {
                if ((x+y+1)<(n+y)) {
                    int createTheEdge = 1;
                    if (createTheEdge==1) {
                        myGridGraph.addUndirectedEdge(myNodesList[x+y], myNodesList[x+y+1]);
                    }
                }
            }
            y=y+n;
        }
        
        //create edges across y-axis
        for (int x=0;x<n;x++) {
            y=0;
            while (y<pow(n,2)) {
                if ((x+y+3)<(pow(n,2))) { //< 7 8 9
                    int createTheEdge = 1;//rand() % 1;
                    if (createTheEdge==1) {
                        myGridGraph.addUndirectedEdge(myNodesList[x+y], myNodesList[x+y+3]);
                    }
                }
                y=y+n;
                
            }
            
        }
        return myGridGraph;
    }

    vector <GridNode> astar(GridNode sourceNode, GridNode destNode) {
        
        vector <GridNode> nodeList = myGridGraph.getAllNodes();
        
        //create a map of Coordinates to Nodes
        map<Coord, GridNode> mp;
        
        for (int i = 0; i < nodeList.size(); i++) {
            Coord coord;
            coord.x=nodeList[i].coord.x;
            coord.y=nodeList[i].coord.y;
            
            mp[coord] = nodeList[i];
        }
        
        int n=sqrt(nodeList.size());

        bool goRight=false;
        if (destNode.coord.x>sourceNode.coord.x)
            goRight=true;
        bool goUp=false;
        if (destNode.coord.y>sourceNode.coord.y)
            goUp=true;
        
        vector <GridNode> myArrayList;
        
        if (goRight) {
            int y=sourceNode.coord.y;
            for (int x=sourceNode.coord.x;x<=destNode.coord.x;x++) {
                Coord coord;
                coord.x=x;
                coord.y=y;
                auto itr = mp.find(coord);
                myArrayList.push_back((GridNode) itr->second);
            }
        }
        else {// go left or stay there
            int y=sourceNode.coord.y;
            for (int x=sourceNode.coord.x;x>=destNode.coord.x;x--) {
                Coord coord;
                coord.x=x;
                coord.y=y;
                auto itr = mp.find(coord);
                myArrayList.push_back((GridNode) itr->second);
            }
        }
        if (goUp) {
            int x=destNode.coord.x;
            for (int y=sourceNode.coord.y+1;y<=destNode.coord.y;y++) {
                Coord coord;
                coord.x=x;
                coord.y=y;
                auto itr = mp.find(coord);
                myArrayList.push_back((GridNode) itr->second);
                
            }
        }
        else {
            int x=destNode.coord.x;
            for (int y=sourceNode.coord.y-1;y>=destNode.coord.y;y--) {
                Coord coord;
                coord.x=x;
                coord.y=y;
                auto itr = mp.find(coord);
                myArrayList.push_back((GridNode) itr->second);
            }
        }
        
        return myArrayList;
    }
};
void printGraph (vector <GridNode> v) {
   for (int i=0;i<v.size();i++) {
        cout<<i<<" : ";
        for (int j=0;j<v[i].edgeList.size();j++) {

            for(int k=0; k<v.size(); k++) {
                if(v[k].data==v[i].edgeList[j].data) {

            cout<<k<<" ";
                break;
                }
            }
        }
        cout<<"\n";
    }
}
void printArray (vector <GridNode> v) {
    for (int i=0;i<v.size();i++) {
        cout<<"("<<v[i].coord.x<<","<<v[i].coord.y<<") ";
    }
    cout<<"\n";
}


int main() {
    GridGraph myGraph;
    
    Main myGraphMain;
    vector <GridNode> nodeList;
    
    cout<<"START"<<"\n";
    
    cout<<"CREATE RANDOM GRAPH"<<"\n";
    myGraph = myGraphMain.createRandomGridGraph(3);
    vector <GridNode> h=myGraph.getAllNodes();
    printGraph(h); 

    
    cout<<"PERFORM ASTAR SEARCH"<<"\n";
    nodeList = myGraphMain.astar(h[0],h[h.size()-1]);

    printArray(nodeList); 

    cout<<"END"<<"\n";

    return 0;
}