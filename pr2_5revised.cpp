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

struct Node {
    string data;
    vector <Node> edgeList;
    vector <int> weightList;
    int minDistance;
    bool visited;
}; 


class WeightedGraph {
    private: 
        vector <Node> nodeList;
        vector <bool> visitedList;
    public:

        //add a node
        void addNode( string nodeVal) {
            Node newNode;
            newNode.data=nodeVal;
            newNode.visited=false;

            nodeList.push_back(newNode);
            visitedList.push_back(false);
        }
        //add weighted edge to a node
        void addWeightedEdge(  Node &first,   Node second,  int edgeWeight) {
            bool found=false;
            int v;

            int n=nodeList.size();
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
                        nodeList[i].weightList.push_back(edgeWeight);
                    }
                    break;
                }
                
            }
        }

 
        void removeDirectedEdge( Node first, Node second) {
            //have to do something about the weights
            int n=nodeList.size();
            
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==first.data) {
                    int v=nodeList[i].edgeList.size();
                    for(int j=0; j<v; j++) {
                        if(nodeList[i].edgeList[j].data==second.data) {
                            nodeList[i].edgeList.erase(nodeList[i].edgeList.begin()+j);
                            nodeList[i].weightList.erase(nodeList[i].weightList.begin()+j);
                            break;
                        }
                    }
                    break;
                }
            }
        }

        vector <Node> getAllNodes() {
            return nodeList;
        }
        vector <bool> getVisited() {
          return visitedList;
        }
        void clearAllNodes() {
            nodeList.clear();
            visitedList.clear();
        }
    
};

bool operator<(const Node& n1, const Node& n2)
{
    return n1.data < n2.data;
};

class Main {
    public:
        vector <Node> h;
        WeightedGraph myWeightedGraph;

    int findNumberofDigits(int n) {
        string s = to_string(n);
        return s.length();
    }
    WeightedGraph createRandomCompleteWeightedGraph(int n) {
        myWeightedGraph.clearAllNodes();

        //create n nodes with random values
        int nodesAdded=1;
        int xx = findNumberofDigits(n);
        int maxN = pow(10,xx);
        bool found;
        while (true) {
            
            int x=rand() % maxN + 1;
            
            vector <Node> nl = myWeightedGraph.getAllNodes();
            
            found=false;
            for (int j=0;j<nl.size();j++) {
                if (nl[j].data == to_string(x)) {
                    //cout<<" true ";
                    found=true;
                    break;
                }
            }
            if (!found) {
                myWeightedGraph.addNode(to_string(x));
                nodesAdded++;
                if (nodesAdded>n)
                    break;
            }

        }
        for (int j = 0; j < myWeightedGraph.getAllNodes().size(); j++) {
            for (int k = 0; k < myWeightedGraph.getAllNodes().size() ; k++) {
                if (j!=k) {
                    int weight = rand() % n + 1;
                    myWeightedGraph.addWeightedEdge((myWeightedGraph.getAllNodes())[j], (myWeightedGraph.getAllNodes())[k], weight);
                }
            }
        }  
        return myWeightedGraph; 
    }

    WeightedGraph createLinkedList(int n) {
        //create nodes
        myWeightedGraph.clearAllNodes();
        for (int i=0; i<n; i++) {
            myWeightedGraph.addNode(to_string(i));
        }
        
        vector <Node> myNodesList;
        myNodesList = myWeightedGraph.getAllNodes();
        //create edges
        for (int i=0; i<n-1; i++) {
             myWeightedGraph.addWeightedEdge(myNodesList[i], myNodesList[i+1],1);
        }
        return myWeightedGraph; 
    }
    

    map<Node,int> dijkstras(Node start) {
        queue <Node> Q;
        map<Node, int> returnMap;

        vector <Node> nodeList = myWeightedGraph.getAllNodes();

        int startIndex=0;
        for (int i=0;i<nodeList.size();i++) {
            if (nodeList[i].data == start.data) {
                startIndex=i;
                nodeList[i].minDistance=0;
            }
            else {
                nodeList[i].minDistance=INT_MAX;    
            }
        }

        int distanceOfJ=0;
        int minDistance=0;
        int distanceOfI=0;
        int i=startIndex;

        Q.push(nodeList[startIndex]);
        
        while (!Q.empty()) {
        //traverse the node std::list
            Node tNode=Q.front();
            Q.pop();

            distanceOfI=tNode.minDistance;
            
            for(int k=0; k<nodeList.size(); k++) {
                if(nodeList[k].data==tNode.data) {
                    i=k;
                }
            }
            nodeList[i].visited=true;
            
            int v=nodeList[i].edgeList.size();
            //create an edge only if edge does not exist
            
            for(int j=0; j<v; j++) {
                Node edgeNode = tNode.edgeList[j];
                int edgeNodeWeight = tNode.weightList[j];
                for(int k=0; k<nodeList.size(); k++) {
                    if(nodeList[k].data==edgeNode.data) {
                        
                        
                        distanceOfJ=nodeList[k].minDistance;
                        
                        if (distanceOfJ > distanceOfI+edgeNodeWeight) {
                        
                            nodeList[k].minDistance=distanceOfI+edgeNodeWeight;
                            
                            if (!nodeList[k].visited) {
                                Q.push(nodeList[k]);
                            }


                        }

                        break;
                    }
                }
                    
            }//for each edgenode
            
        } //until Q is empty
  
        int k;
        for (int i = 0; i < nodeList.size(); i++) {
            if (startIndex+i <nodeList.size())
                k=startIndex+i;
            else
                k=startIndex-i+1;
            
            returnMap[nodeList[k]]=nodeList[k].minDistance;
        }
        return returnMap;
    }
};
void printGraph (vector <Node> v) {
    for (int i=0;i<v.size();i++) {
        cout<<v[i].data<<" : ";
        for (int j=0;j<v[i].edgeList.size();j++) {
            cout<<v[i].edgeList[j].data<<"("<<v[i].weightList[j]<<") ";
        }
        cout<<"\n";
    }
}
int main() {
    WeightedGraph myWeightedGraph;
    
    Main myGraphMain;
    vector <Node> nodeList;
    
    cout<<"START"<<"\n";
    
    cout<<"CREATE RANDOM DIRECTED WEIGHTED GRAPH"<<"\n";
    myWeightedGraph = myGraphMain.createRandomCompleteWeightedGraph(5);

    printGraph(myWeightedGraph.getAllNodes()); 

    cout<<"CREATE dijkstras RANDOM DIRECTED UNWEIGHTED GRAPH"<<"\n";
    vector <Node> h=myWeightedGraph.getAllNodes();
    int startIndex=0;
    map<Node, int> aMap;
    aMap = myGraphMain.dijkstras(h[startIndex]);

    for_each(aMap.begin(),
        aMap.end(),
        [](const pair<Node, int> &p) {
            std::cout << "{" << p.first.data << ": " << p.second << "}\n";
        });


    cout<<"CREATE LINKEDLIST DIRECTED WEIGHTED GRAPH"<<"\n";
    myWeightedGraph = myGraphMain.createLinkedList(5);

    printGraph(myWeightedGraph.getAllNodes()); 

    cout<<"CREATE dijkstras RANDOM DIRECTED UNWEIGHTED GRAPH"<<"\n";
    h=myWeightedGraph.getAllNodes();
    startIndex=0;
    aMap = myGraphMain.dijkstras(h[startIndex]);

    for_each(aMap.begin(),
        aMap.end(),
        [](const pair<Node, int> &p) {
            std::cout << "{" << p.first.data << ": " << p.second << "}\n";
        });

    cout<<"END"<<"\n";

    return 0;
}