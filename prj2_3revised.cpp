#include <iostream>
#include<stdio.h> 
#include<stdlib.h> 
#include <vector>
#include <stack> 
#include <queue>
#include <string>
#include <cmath>
using namespace std;

struct Node {
    string data;
    vector <Node> edgeList;
}; 

class Graph {

    private: 
        vector <Node> nodeList;
        vector <bool> visitedList;
    public:
        
        //add a new vertex with a value
        void addNode ( string nodeVal) {
            
            Node newNode;
            newNode.data=nodeVal;
            nodeList.push_back(newNode);
            visitedList.push_back(false);
        }

        //create a bi-directional edge between nodes
        void addUndirectedEdge( Node first,  Node second) {
            int n=nodeList.size();
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
                    if (!found) 
                        nodeList[i].edgeList.push_back(second);
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
                    if (!found) 
                        nodeList[i].edgeList.push_back(first);
                    break;
                }
                
            }
        }
        //add a single edge between nodes for linked lists
        void addSingleEdge( Node first,  Node second) {
             //vector <int> adjacenyList;
            int n=nodeList.size();
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
                    if (!found) 
                        nodeList[i].edgeList.push_back(second);
                    break;
                }
                
            }
        }
        //remove edges between nodes
        void removeUndirectedEdge(Node first,  Node second) {
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
        
       
        vector <Node> getAllNodes() {
            return nodeList;
        }
        void clearAllNodes() {
            nodeList.clear();
        }
        vector <bool> getVisited() {
            return visitedList;
        }
};

class GraphSearch {
    public:
        int V;
        Graph myGraph;
        vector <Node> myArrayList;
        vector <bool> visited;

    //DFS Recursive helper function
    void DFSUtil(int startIndex, int endIndex) 
    { 
        vector <Node> myset=myGraph.getAllNodes();
        int v = startIndex;
        
        if (v<=endIndex && !visited[v]) {
            visited[v] = true; 
            myArrayList.push_back(myset[v]);
            
            for(int j=0; j<myset[v].edgeList.size(); j++) {
                
                for  (int k = 0; k < myset.size(); k++) {
                    if (myset[k].data==myset[v].edgeList[j].data) {
    
                        if(!visited[k]) {
                            DFSUtil(k, endIndex);
                            break;
                         }
                    }
                }
            }
        }
                
    } 
    vector <Node> DFSRec( Node start,  Node end) {

        vector <Node> myset=myGraph.getAllNodes();
        myArrayList.clear();
        visited.clear();
        
        int startIndex;
        int endIndex;
        Node newNode;
        vector <Node> x;
        for(int i=0; i<myset.size();i++) {
            if(myset[i].data==start.data) {
                startIndex=i;
            }
            if(myset[i].data==end.data) {
                endIndex=i;
            }
        }
        for (int i = 0; i < myset.size(); i++) 
            visited.push_back(false); 
        
        // Call the recursive helper function to get DFS traversal
        for (int i = startIndex; i <= endIndex; i++) {
            DFSUtil(i, endIndex); 
        }
            
        return myArrayList;
    }
 
    vector <Node> DFSIter( Node start,  Node end) {
        stack <Node> S;

        vector <Node> myset=myGraph.getAllNodes();
        myArrayList.clear();
        visited.clear();
        
        int startIndex;
        int endIndex;
        if (myset.size()>0) {
            for(int i=0; i<myset.size();i++) {
                if(myset[i].data==start.data) {
                    startIndex=i;
                }
                if(myset[i].data==end.data) {
                    endIndex=i;
                }
            }
            for (int i = 0; i < myset.size(); i++) 
                visited.push_back(false);       
            for(int i=startIndex; i<=endIndex;i++) {
                if(!visited[i]) {
                    visited[i]=true;
                    S.push(myset[i]);
                    while (!S.empty()) {
                        Node cur=S.top();
                        S.pop(); 
                        myArrayList.push_back(cur);
                        for (int j=0; j<cur.edgeList.size();j++) {
                            //find the vertex from the edge nodes
                            for  (int k = 0; k < myset.size(); k++) {
                                if (myset[k].data==cur.edgeList[j].data) {
                                    if(!visited[k]) {
                                        visited[k]=true;
                                        S.push(myset[k]);
                                        break;
                                    }
                                }
                                
                            }
                        }
                       
                    }
                }
                
            }
        }  
       return myArrayList; 
    }

    void BFTRecUtil(queue<Node> &q)
    {
    	if (q.empty())
    		return;
    
    	// pop front node from queue and print it
    	Node cur = q.front();
    	q.pop();
    	myArrayList.push_back(cur);
    	vector <Node> myset = myGraph.getAllNodes();

    	// do for every edge (v -> u)
    	for (int u; u<cur.edgeList.size();u++)
    	{

            for  (int k = 0; k < myset.size(); k++) {
                if (myset[k].data==cur.edgeList[u].data) {
                    if(!visited[k]) {
                        visited[k]=true;
                        q.push(myset[k]);
                    }
                    break;
                }
                
            }
   	    }
    
    	BFTRecUtil(q);
    }

    vector <Node> BFTRec( Graph graph) {
    	// create a queue used to do BFS
        myArrayList.clear();
        visited.clear();
        myGraph = graph;
            
        queue<Node> q;
        vector <Node> nl;
        nl = graph.getAllNodes();
        for (int i = 0; i < nl.size(); i++) 
            visited.push_back(false); 
            
    	// Do BFS traversal from all undiscovered nodes to
    	// cover all unconnected components of graph
    	for (int i = 0; i < nl.size(); i++) {
    		if (!visited[i])
    		{
    			// mark source vertex as discovered
    			visited[i] = true;
    
    			// push source vertex into the queue
    			q.push(nl[i]);
    
    			// start BFS traversal from vertex i
    			BFTRecUtil(q);
    		}
    	}    
    	
    	return myArrayList;
    } 

    vector <Node> BFTIter( Graph graph) {
        myGraph = graph;
        queue<Node> Q;
        myArrayList.clear();
        visited.clear();
        
        vector <Node> myset=myGraph.getAllNodes();
        for (int i = 0; i < myset.size(); i++) 
            visited.push_back(false); 
            
        int startIndex;
        int endIndex;
        vector <Node> nl = graph.getAllNodes();
        
        Node start=nl[0];
        Node end=nl[nl.size()-1];
        
        for(int i=0; i<myset.size();i++) {
            if(myset[i].data==start.data) {
                startIndex=i;
            }
            if(myset[i].data==end.data) {
                endIndex=i;
            }
        }
      
        for(int i=startIndex; i<=endIndex;i++) {
            if(!visited[i]) {
                visited[i]=true;
                Q.push(myset[i]);
                
                while (!Q.empty()) {
                    Node cur=Q.front();
                    myArrayList.push_back(cur);
                    Q.pop();
                    for (int j=0; j<cur.edgeList.size();j++) {

                        for  (int k = 0; k < myset.size(); k++) {
                            if (myset[k].data==cur.edgeList[j].data) {
                                if(!visited[k]) {
                                    visited[k]=true;
                                    Q.push(myset[k]);
                                    break;
                                }
                            }
                            
                        }

                   }
                   
                }
            }
            
        }
        
       return myArrayList; 
    } 
};
bool operator<(const Node& n1, const Node& n2)
{
    return n1.data < n2.data;
};
class Main {
   public:
    vector <Node> h;
    Graph myGraph;    
    Main() {
        h=myGraph.getAllNodes();
    }
    int findNumberofDigits(int n) {
        string s = to_string(n);
        return s.length();
    }
    Graph createRandomUnweightedGraphIter(int n) {
        myGraph.clearAllNodes();
 
 
        int nodesAdded=1;
        int xx = findNumberofDigits(n);
        int maxN = pow(10,xx);
        bool found;
        while (true) {
            
            int x=rand() % maxN + 1;
            
            vector <Node> nl = myGraph.getAllNodes();
            
            found=false;
            for (int j=0;j<nl.size();j++) {
                if (nl[j].data == to_string(x)) {
                    found=true;
                    break;
                }
            }
            if (!found) {
                myGraph.addNode(to_string(x));
                nodesAdded++;
                if (nodesAdded>n)
                    break;
            }

        }
 
        int maxEdges=0;
        for (int i=n-1; i>=1; i--) {
            maxEdges=maxEdges+i;
        }
        //create random edges
        vector <Node> myNodesList;
        myNodesList = myGraph.getAllNodes();
        for (int i=0; i<maxEdges; i++) {
            int x=rand() % (n-1);
            int y=rand() % (n-1);

            myGraph.addUndirectedEdge(myNodesList[x], myNodesList[y]);
        }
        return myGraph; 
    }

    Graph createLinkedList(int n) {
        //create nodes
        myGraph.clearAllNodes();
        for (int i=0; i<n; i++) {
            myGraph.addNode(to_string(i));
        }
        
        vector <Node> myNodesList;
        myNodesList = myGraph.getAllNodes();
        //create edges
        for (int i=0; i<n-1; i++) {
             myGraph.addSingleEdge(myNodesList[i], myNodesList[i+1]);
        }
        return myGraph; 
    }

    vector <Node> BFTRecLinkedList( Graph graph) {
        GraphSearch myGraphSearch;
        vector <Node> myArrayList;
        
        graph=createLinkedList(10); 

        myArrayList = myGraphSearch.BFTRec(graph);
       
        return myArrayList;
    }

    vector <Node> BFTIterLinkedList( Graph graph) {
        GraphSearch myGraphSearch;
        vector <Node> myArrayList;
        
        graph=createLinkedList(10);

        myArrayList = myGraphSearch.BFTIter(graph);
       
        return myArrayList;
    }
    
};



void printGraph (vector <Node> v) {
    for (int i=0;i<v.size();i++) {
        cout<<v[i].data<<": ";
        for (int j=0;j<v[i].edgeList.size();j++) {
            cout<<v[i].edgeList[j].data<<" ";
        }
        cout<<"\n";
    }
}
void printArray (vector <Node> v) {
    for (int i=0;i<v.size();i++) {
        cout<<v[i].data<<" ";
    }
    cout<<"\n";
}
int main() {
    Graph myGraph;
    GraphSearch myGraphSearch;
    Main myGraphMain;
    vector <Node> myArrayList;
    
    cout<<"START"<<"\n";

    cout<<"CREATE RANDOM UNWEIGHTED GRAPH"<<"\n";
    myGraphSearch.myGraph=myGraphMain.createRandomUnweightedGraphIter(7);
    
    vector <Node> h=myGraphSearch.myGraph.getAllNodes();

    // DFS Iterative
    cout<<"PRINT ORIGINAL GRAPH"<<"\n";
    printGraph(h);
    
    cout<<"EXECUTE DFS ITERATIVE"<<"\n";
    myArrayList = myGraphSearch.DFSIter(h[0], h[h.size()-1]);
   
    cout<<"PRINT DFS ITERATIVE"<<"\n";
    printArray(myArrayList);

    cout<<"EXECUTE DFS RECURSIVE"<<"\n";
    myArrayList = myGraphSearch.DFSRec(h[0], h[h.size()-1]);
   
    cout<<"PRINT DFS RECURSIVE"<<"\n";
    printArray(myArrayList);

    cout<<"EXECUTE BFT ITERATIVE"<<"\n";
    myArrayList = myGraphSearch.BFTIter(myGraphSearch.myGraph);
   
    cout<<"PRINT BFT ITERATIVE"<<"\n";
    printArray(myArrayList);

    cout<<"EXECUTE BFT RECURSIVE"<<"\n";
    myArrayList = myGraphSearch.BFTRec(myGraphSearch.myGraph);
   
    cout<<"PRINT BFT RECURSIVE"<<"\n";
    printArray(myArrayList);

  
    cout<<"EXECUTE BFT RECURSIVE LINKEDLIST"<<"\n";
    myArrayList = myGraphMain.BFTRecLinkedList(myGraph);

    cout<<"PRINT BFT RECURSIVE LINKEDLIST"<<"\n";
    printArray(myArrayList);


    cout<<"EXECUTE BFT ITERATIVE LINKEDLIST"<<"\n";
    myArrayList = myGraphMain.BFTIterLinkedList(myGraph);

    cout<<"PRINT BFT ITERATIVE LINKEDLIST"<<"\n";
    printArray(myArrayList);

    cout<<"END"<<"\n";

    return 0;
    
}