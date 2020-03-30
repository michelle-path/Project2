#include <iostream>
#include<stdio.h> 
#include<stdlib.h> 
#include <vector>
#include <stack> 
#include <queue>
#include <string>
#include <bits/stdc++.h>
using namespace std;

struct Node {
    string data;
    //Node *right, *left;
    vector <Node> edgeList;
    

}; 
/*
void printAdjacenyList(vector <int> adjList, int x) {
    x=adjList.size();
    for(int i=0; i<x;i++) {
        cout<<"adjaceny list of vertex"<<x<<"\n head";
        for(auto x: adjList[v]) {


        }

    }
}
*/
class Graph {

    private: 
        vector <Node> nodeList;
        vector <bool> visitedList;
    public:
        
        void addNode ( string nodeVal) {
            Node newNode;
            newNode.data=nodeVal;
            nodeList.push_back(newNode);
            visitedList.push_back(false);
        }
        void addUndirectedEdge( Node first,  Node second) {
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
        void removeUndirectedEdge(Node first,  Node second) {
            int n=nodeList.size();
            
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==first.data) {
                    int v=nodeList[i].edgeList.size();
                    for(int j=0; j<v; j++) {
                        if(nodeList[i].edgeList[j].data==second.data) {
                            nodeList[i].edgeList.erase(nodeList[i].edgeList.begin()+j-1);
                            break;
                        }
                    }
                    break;
                       //nodeList[i]->edgeList.push_back(second);
                }
            }
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==second.data) {
                    int v=nodeList[i].edgeList.size();
                    for(int j=0; j<v; j++) {
                        if(nodeList[i].edgeList[j].data==first.data) {
                            nodeList[i].edgeList.erase(nodeList[i].edgeList.begin()+j-1);
                            break;
                        }
                    }
                    break;
                }
            }
    
    
        }
        vector <Node> getAllNodes() {
            /*set <Node> nodeset;
            int n=nodeList.size();
            for(int i=0; i<n;i++) {
                nodeset.insert(nodeList[i]);
            }
            */
            return nodeList;
        }
        vector <bool> getVisited() {
            /*set <Node> nodeset;
            int n=nodeList.size();
            for(int i=0; i<n;i++) {
                nodeset.insert(nodeList[i]);
            }
            */
            return visitedList;
        }
};

class GraphSearch {
    public:
        int V;
        Graph myGraph;
        vector <Node> myArrayList;
        vector <bool> visited;
        //vector <Node> h;
        
        //GraphSearch() {
            //h=myGraph.getAllNodes();
            //cout<<"inside GraphSearch constructor: "<<"\n";
            //for (int i=0;i<myGraph.getAllNodes().size();i++)
             //   visited.push_back(false);
       // }
        //vector <bool> visited(V, false);    
        //vector <int> adjacenyList;
    void DFSUtil(int startIndex, int endIndex) 
    { 
        // Mark the current node as visited and 
        // print it 
        vector <Node> myset=myGraph.getAllNodes();
        int v = startIndex;
        
        //cout << "3333 3333 visited size: "<<visited.size()<<"\n";
        //for (int i=0;i<visited.size();i++)
         //   cout << visited[i]<<" ";
        //cout <<"\n";
        
        if (v<=endIndex && !visited[v]) {
            //vector <bool> visited=myGraph.getVisited();
            visited[v] = true; 
            //cout << "3333 4444 startIndex, endIndex, v pushing: "<<startIndex<<" "<<endIndex<<" "<<v<<" "<<myset[v].data<<"\n"; 
            myArrayList.push_back(myset[v]);
            
            for(int j=0; j<myset[v].edgeList.size(); j++) {
                
                for  (int k = 0; k < myset.size(); k++) {
                    //cout<<"5555 44444 222 k: "<<k<<"\n";
                    if (myset[k].data==myset[v].edgeList[j].data) {
    
                        if(!visited[k]) {
                            DFSUtil(k, endIndex);
                            break;
                         }
                    }
                }
            }
        }
                
        // Recur for all the vertices adjacent 
        // to this vertex 
        //list<int>::iterator i; 
        //for (i = adj[v].begin(); i != adj[v].end(); ++i) 
            //if (!visited[*i]) 
                //DFSUtil(*i, visited); 
    } 
    vector <Node> DFSRec( Node start,  Node end) {
        //Graph myGraph1;
       //Main graph1;
      /*if v is unvisited
        mark v as visited
        for each edge vw (v→w)
            DFS(w)*/
        
        vector <Node> myset=myGraph.getAllNodes();
        //vector <bool> visited=myGraph.getVisited();
        myArrayList.clear();
        visited.clear();
        
        //cout<<"3333 11111 myset size:"<<myset.size()<<"\n";
        int startIndex;
        int endIndex;
        Node newNode;
        vector <Node> x;
        for(int i=0; i<myset.size();i++) {
            if(myset[i].data==start.data) {
                //int v=nodeList[i]->edgeList.size();
                startIndex=i;
                   //nodeList[i]->edgeList.push_back(second);
            }
            if(myset[i].data==end.data) {
                //int v=nodeList[i]->edgeList.size();
                endIndex=i;
                   //nodeList[i]->edgeList.push_back(second);
            }
        }
        //cout<<"3333 2222 startIndex, endIndex: "<<startIndex<<" "<<endIndex<<"\n";
            
            
        //bool *visited = new bool[V]; 
        for (int i = 0; i < myset.size(); i++) 
            visited.push_back(false); 
        
        //cout << "3333 2222 1111  visited size: "<<visited.size()<<"\n";
        
        
        // Call the recursive helper function 
        // to print DFS traversal 
        for (int i = startIndex; i <= endIndex; i++) {
            //cout<<"3333 3333 i: "<<i<<"\n";
            DFSUtil(i, endIndex); 
        }
            
        //cout<<"3333 4444"<<"\n";
            
        return myArrayList;
        //return myGraph1; 
        
        
    }
 
    vector <Node> DFSIter( Node start,  Node end) {
        
        //Graph graph;
        
        stack <Node> S;
        
        
        vector <Node> myset=myGraph.getAllNodes();
        //vector <bool> visited=myGraph.getVisited();
        myArrayList.clear();
        visited.clear();
        
        int startIndex;
        int endIndex;
        if (myset.size()>0) {
            //cout<<"5555 1111 myset size, start.data: "<<myset.size()<<" "<<start.data<<"\n";
            for(int i=0; i<myset.size();i++) {
                if(myset[i].data==start.data) {
                    //int v=nodeList[i]->edgeList.size();
                    startIndex=i;
                       //nodeList[i]->edgeList.push_back(second);
                }
                if(myset[i].data==end.data) {
                    //int v=nodeList[i]->edgeList.size();
                    endIndex=i;
                       //nodeList[i]->edgeList.push_back(second);
                }
            }
            //let S be a stack
            for (int i = 0; i < myset.size(); i++) 
                visited.push_back(false);       
            //cout<<"5555 2222 startIndex endIndex: "<<startIndex<<" "<<endIndex<<"\n";
            /*
            let S be a stack
            for each vertex v in G:
                if v is not visited:
                    mark v as visited and add it to S
                    while S is not empty:
                        cur = S.pop()
                        “process cur”
                        for each vertex vi that has an edge from cur:
                         if vi is not visited:
                            mark vi as visited and add it to S 
            */
            for(int i=startIndex; i<=endIndex;i++) {
                if(!visited[i]) {
            //cout<<"5555 3333 i: "<<i<<"\n";
                    visited[i]=true;
                    S.push(myset[i]);
                    //myArrayList.push_back(myset[i]);
                    while (!S.empty()) {
                        Node cur=S.top();
                        S.pop(); 
                        myArrayList.push_back(cur);
                        for (int j=0; j<cur.edgeList.size();j++) {
                            //find the vertex from the edge nodes
                    //cout<<"5555 44444 111 j cur data and cur edgelist data: "<<j<<" "<<cur.data<<" "<<cur.edgeList[j].data <<"\n";
                            for  (int k = 0; k < myset.size(); k++) {
                    //cout<<"5555 44444 222 k: "<<k<<"\n";
                                if (myset[k].data==cur.edgeList[j].data) {
                    //cout<<"5555 44444 333 myset[k].data: "<<myset[k].data<<"\n";
                                    if(!visited[k]) {
                    //cout<<"5555 44444 4444 pushing: "<<myset[k].data<<"\n";
                                        visited[k]=true;
                                        S.push(myset[k]);
                                        //myArrayList.push_back(myset[k]);
                                        break;
                                    }
                                }
                                
                            }
                        }
                       
                    }
                }
                
            }
        }  
        //cout<<"5555 55555 myArrayList size: "<<myArrayList.size()<<"\n";
        //return myArrayList;
        //if(myArrayList.size()==0) {
           // return NULL;
        //}
        //else {
           return myArrayList; 
       // }
        
        
        

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
    	//cout << v << " ";
    
    	// do for every edge (v -> u)
    	for (int u; u<cur.edgeList.size();u++)
    	{

            for  (int k = 0; k < myset.size(); k++) {
                if (myset[k].data==cur.edgeList[u].data) {
                    if(!visited[k]) {
                        visited[k]=true;
                        q.push(myset[k]);
                        //myArrayList.push_back(myset[k]);
                        break;
                    }
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
        /*
        let Q be a queue
        for each vertex v in G:
            if v is not visited:
                mark v as visited and add it to Q
                while Q is not empty:
                    cur = Q.dequeue()
                    “process cur”
                    for each vertex vi that has an edge from cur:
                    if vi is not visited:
                        mark vi as visited and add it to Q
        */
        //Graph graph;
        
        //bool visited[myGraph.getAllNodes().size()-1];
        //stack<string> S;
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
                                    //myArrayList.push_back(myset[k]);
                                    break;
                                }
                            }
                            
                        }

                   }
                   
                }
            }
            
        }
        
        //return myArrayList;
        //if(myArrayList.size()==0) {
        //    return NULL;
        //}
        //else {
           return myArrayList; 
        //}                
            
    } 
};

class Main {
   public:
    vector <Node> h;
    Graph myGraph;    
    Main() {
        h=myGraph.getAllNodes();
    }
    Graph createRandomUnweightedGraphIter(int n) {
        //Graph myGraph1;
        //cout<<"1111 1111\n";
        //create n nodes with random values
        for (int i=0; i<n; i++) {
            int x=rand() % 10 + 1;
            vector <Node> nl = myGraph.getAllNodes();
            bool found=false;
            for (int j=0;j<nl.size();j++) {
                if (nl[j].data == to_string(x)) {
                    found=true;
                }
            }
            if (!found)
                myGraph.addNode(to_string(x));
            else
                i--;

        }
        //cout<<"1111 2222\n";
        int maxEdges=0;
        for (int i=n-1; i>=1; i--) {
            maxEdges=maxEdges+i;
        }
        //cout<<"1111 3333\n";
        //create random number of edges
        vector <Node> myNodesList;
        myNodesList = myGraph.getAllNodes();
        //cout<<"1111 4444 maxEdges,myNodesList: "<<maxEdges<<" "<<myNodesList.size()<<"\n";
        for (int i=0; i<maxEdges; i++) {
            int x=rand() % (n-1);
            int y=rand() % (n-1);
            //cout<<"1111 5555 x,y: "<<x<<" "<<y<<"\n";
            
            
            myGraph.addUndirectedEdge(myNodesList[x], myNodesList[y]);
        }
        //cout<<"1111 6666\n";

/*
        int edgesToBeCreated=rand() % maxEdges + 1;
        for (int i=0; i<edgesToBeCreated; i++) {
             myGraph.addUndirectedEdge((Node) (h.begin()+i)), (Node) (h.begin()+i+1));
        }
*/
        return myGraph; 
    }

    Graph createLinkedList(int n) {
        //Graph myGraph1;
        //create n nodes with random values
        for (int i=0; i<n; i++) {
            
            vector <Node> nl = myGraph.getAllNodes();
            bool found=false;
            for (int j=0;j<nl.size();j++) {
                if (nl[j].data == to_string(i)) {
                    found=true;
                }
            }
            if (!found)
                myGraph.addNode(to_string(i));
            else
                i--;
        }
        
        vector <Node> myNodesList;
        myNodesList = myGraph.getAllNodes();
        //create random number of edges
        for (int i=0; i<n-1; i++) {
             myGraph.addSingleEdge(myNodesList[i], myNodesList[i+1]);
        }
        return myGraph; 
    }

    vector <Node> BFTRecLinkedList( Graph graph) {
        GraphSearch myGraphSearch;
        vector <Node> myArrayList;
        
        //cout<<"START"<<"\n";
    
        //cout<<"CREATE LINKED LIST GRAPH"<<"\n";
        graph=createLinkedList(10000);

        //cout<<"EXECUTE BFT RECURSIVE"<<"\n";
        myArrayList = myGraphSearch.BFTRec(graph);
       
        //cout<<"PRINT BFT RECURSIVE"<<"\n";
        //printArray(myArrayList);
        //cout<<"END"<<"\n";

        return myArrayList;
    }

    vector <Node> BFTIterLinkedList( Graph graph) {
        GraphSearch myGraphSearch;
        vector <Node> myArrayList;
        
        //cout<<"START"<<"\n";
    
        //cout<<"CREATE LINKED LIST GRAPH"<<"\n";
        graph=createLinkedList(10000);

        //cout<<"EXECUTE BFT RECURSIVE"<<"\n";
        myArrayList = myGraphSearch.BFTIter(graph);
       
        //cout<<"PRINT BFT RECURSIVE"<<"\n";
        //printArray(myArrayList);
        //cout<<"END"<<"\n";

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
    
    //cout<<"CREATE LINKED LIST GRAPH"<<"\n";
    //myGraphSearch.myGraph=myGraphMain.createLinkedList(5);

    

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