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
#include <bits/stdc++.h>
using namespace std;

struct Node {
    string data;
    //Node *right, *left;
    vector <Node> edgeList;
    int weight;
    int minDistance;
    bool visited;
    
   // Node prevNode;
}; 


class WeightedGraph {
    private: 
        vector <Node> nodeList;
        vector <bool> visitedList;
    public:

        void addNode( string nodeVal) {
            Node newNode;
            newNode.data=nodeVal;
            newNode.visited=false;

            nodeList.push_back(newNode);
            visitedList.push_back(false);
        }

        void addWeightedEdge( Node first,  Node second,  int edgeWeight) {
            int n=nodeList.size();
            bool found=false;
            int v;
            // create a new node for the second node
            Node newNode;
            newNode.data=second.data;
            
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==first.data) {
                    v=nodeList[i].edgeList.size();
                    //create an edge only if edge does not exist
                    for(int j=0; j<v; j++) {
                        if(nodeList[i].edgeList[j].data==newNode.data) {
                            found=true;
                            break;
                        }
                    }
                    if (!found) {
                        //add random weight to the edge node
                        newNode.weight = edgeWeight;
                        
                        nodeList[i].edgeList.push_back(newNode);
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
        //Graph myGraph1;
        //cout<<"1111 1111\n";
        //create n nodes with random values
        int nodesAdded=1;
        int xx = findNumberofDigits(n);
        int maxN = pow(10,xx);
        bool found;
        while (1==1) {
            
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
        vector <Node> myNodesList;
        myNodesList = myWeightedGraph.getAllNodes();

                      
        for (int j = 0; j < myNodesList.size(); j++) {
            for (int k = 0; k < myNodesList.size() ; k++) {
                if (j!=k) {
                    int weight = rand() % n + 1;
                    //cout<<"0000 j k weight: "<<myNodesList[j].data<<" "<<myNodesList[k].data<<" "<<weight<<"\n";
                    myWeightedGraph.addWeightedEdge(myNodesList[j], myNodesList[k], weight);
                }
            }
        }  
        return myWeightedGraph; 
    }

    WeightedGraph createLinkedList(int n) {
        //create n nodes with random values
        int nodesAdded=1;
        int xx = findNumberofDigits(n);
        int maxN = pow(10,xx);
        bool found;
        
        while (1==1) {
            
            int x=nodesAdded;
            
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
        
        vector <Node> myNodesList;
        myNodesList = myWeightedGraph.getAllNodes();
        //create random number of edges
        for (int i=0; i<n-1; i++) {
             myWeightedGraph.addWeightedEdge(myNodesList[i], myNodesList[i+1], 1);
        }
        return myWeightedGraph; 
    }


    map<Node,int> dijkstras(Node start) {
        queue <Node> Q;
        map<Node, int> returnMap;

        //cout<<"1111111\n";
        vector <Node> nodeList = myWeightedGraph.getAllNodes();
        //cout<<"222222222 nodeList_size start : "<<nodeList.size()<<" "<<start.data<<"\n";

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
        //cout<<"33333333\n";

        int distanceOfJ=0;
        int minDistance=0;
        int distanceOfI=0;
        int i=startIndex;

        //for (int iL=0;iL<nodeList.size();iL++) {
        Q.push(nodeList[startIndex]);
        
        while (!Q.empty()) {
        //traverse the node std::list
            Node tNode=Q.front();
            //cout<<"444444 tNode: "<<tNode.data<<"\n";
            Q.pop();
            //cout<<"5555555 tNode Qsize: "<<tNode.data<<" "<<Q.size()<<"\n";
            
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
                //if (j==0)
                    //minDistance=nodeList[i].edgeList[j];
                //else {
                    for(int k=0; k<nodeList.size(); k++) {
                        if(nodeList[k].data==edgeNode.data) {
                            
                            
                            distanceOfJ=nodeList[k].minDistance;
                            
                            //int a=distanceOfI+edgeNode.weight;
                            //int b=distanceOfJ;
                            
            //cout<<"555555 src target distanceOfI+edgeweight distanceOfJ : "<<tNode.data<<" "<<edgeNode.data<<" "<<distanceOfI+edgeNode.weight<<" "<<distanceOfJ<<"\n";
                            if (distanceOfJ > distanceOfI+edgeNode.weight) {
                            
                                nodeList[k].minDistance=distanceOfI+edgeNode.weight;
                                
                                if (!nodeList[k].visited) {
                                    Q.push(nodeList[k]);
                                    //cout<<"pushed edge Qsize:"<<nodeList[k].data<<" "<<Q.size()<<"\n";
                                }


                            }

                            break;
                        }
                    }
                    
            }//for each edgenode
            
        } //until Q is empty
  
	// Pair of Map Iterator and bool
	//std::pair<std::map<Node, int>::iterator, bool> result;
 
	
	
        int k;
        for (int i = 0; i < nodeList.size(); i++) {
            if (startIndex+i <nodeList.size())
                k=startIndex+i;
            else
                k=startIndex-i+1;
            
            returnMap[nodeList[k]]=nodeList[k].minDistance;
            
	        //returnMap.insert(std::pair<Node, int>(nodeList[k], nodeList[k].minDistance));

            //returnMap.insert(pair<Node, int>(nodeList[k], nodeList[k].minDistance)); 
            
            //cout<<nodeList[k].data<<"\t"<<nodeList[k].minDistance<<"\n"; 
        }

        
        
        return returnMap;
    }
};
void printGraph (vector <Node> v) {
    for (int i=0;i<v.size();i++) {
        cout<<v[i].data<<" : ";
        for (int j=0;j<v[i].edgeList.size();j++) {
            cout<<v[i].edgeList[j].data<<"("<<v[i].edgeList[j].weight<<") ";
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

//    cout<<"CREATE LINKEDLIST DIRECTED WEIGHTED GRAPH"<<"\n";
//   myWeightedGraph = myGraphMain.createLinkedList(5);

    printGraph(myWeightedGraph.getAllNodes()); 

    vector <Node> h=myWeightedGraph.getAllNodes();
    
    cout<<"CREATE dijkstras RANDOM DIRECTED UNWEIGHTED GRAPH"<<"\n";
    int startIndex=0;
    map<Node, int> aMap;
    aMap = myGraphMain.dijkstras(h[startIndex]);

    //print dijkstras Hashmap
    for_each(aMap.begin(),
        aMap.end(),
        [](const pair<Node, int> &p) {
            std::cout << "{" << p.first.data << ": " << p.second << "}\n";
        });
                
                
    cout<<"END"<<"\n";

    return 0;
}

