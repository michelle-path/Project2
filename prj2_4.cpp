#include <iostream>
#include<stdio.h> 
#include<stdlib.h> 
#include <vector>
#include <stack> 
#include <queue>
#include <string>
#include <bits/stdc++.h>
using namespace std;

#define MIN_PER_RANK 1 /* Nodes/Rank: How 'fat' the DAG should be.  */
#define MAX_PER_RANK 5
#define MIN_RANKS 3    /* Ranks: How 'tall' the DAG should be.  */
#define MAX_RANKS 5
#define PERCENT 30     /* Chance of having an Edge.  */

struct Node {
    string data;
    //Node *right, *left;
    vector <Node> edgeList;
    int noOfIncomingEdges;

}; 

void printGraph (vector <Node> v) {
    for (int i=0;i<v.size();i++) {
        cout<<v[i].data<<" ("<<v[i].noOfIncomingEdges<<") : ";
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

//similar to Graph class in Part 3
class DirectedGraph {
    private: 
        vector <Node> nodeList;
        vector <bool> visitedList;
    public:
        void addNode( string nodeVal) {
            Node newNode;
            newNode.data=nodeVal;
            newNode.noOfIncomingEdges=0;
            nodeList.push_back(newNode);
            visitedList.push_back(false);
            
        }

        void addDirectedEdge( Node first, Node second) {
            //****************** Differs from previous Graph ***********
            // create DAG Graph..acyclic edges....an edge does not point to itself
            if (first.data != second.data) {
                int n=nodeList.size();
                bool found=false;
                int v;
                for(int i=0; i<n;i++) {
                    //find the first node and then add the node between first and second
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
                            
                            //****************** Differs from previous Graph ***********
                            // find the second node and identify this node has incoming edges
                            for(int l=0; l<n;l++) {
                                if(nodeList[l].data==second.data) {
                                    nodeList[l].noOfIncomingEdges++;
                                }
                            }
                        }
                        break;
                    }
                    
                }
            }
        }

        void removeDirectedEdge(Node first, Node second) {
            int n=nodeList.size();
            //cout<<"r 11111111\n";
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==first.data) {
                    int v=nodeList[i].edgeList.size();
                    for(int j=0; j<v; j++) {
                        if(nodeList[i].edgeList[j].data==second.data) {
                            //cout<<"r 2222222"<<"\n";
                            nodeList[i].edgeList.erase(nodeList[i].edgeList.begin()+j);
                            //cout<<"r 33333333\n";
                            //find out if all incoming edges to second have been removed. 
                            // if so identify that this node has NO incoming edges
                            for(int l=0; l<n;l++) {
                                if(nodeList[l].data==second.data) {
                                    nodeList[l].noOfIncomingEdges--;
                           //cout<<"r 11111111 node noOfIncomingEdges : "<<nodeList[l].data<<" "<<nodeList[l].noOfIncomingEdges<<"\n";
                                         }
                            }
                            
                            break;
                        }
                    }
                    break;
                       //nodeList[i]->edgeList.push_back(second);
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


class Main {
    public:
    vector <Node> h;
    DirectedGraph myDirectedGraph;    

    int findNumberofDigits(int n) {
        string s = to_string(n);
        return s.length();
        
    }
    DirectedGraph createRandomDAGIter(int n) {
        
        int nodesAdded=1;
        int xx = findNumberofDigits(n);
        int maxN = pow(10,xx);
        bool found;
        while (1==1) {
            
            int x=rand() % maxN + 1;
            
            vector <Node> nl = myDirectedGraph.getAllNodes();
            
            found=false;
            for (int j=0;j<nl.size();j++) {
                if (nl[j].data == to_string(x)) {
                    //cout<<" true ";
                    found=true;
                    break;
                }
            }
            if (!found) {
                myDirectedGraph.addNode(to_string(x));
                nodesAdded++;
                if (nodesAdded>n)
                    break;
            }

        }
        //cout<<"1111 2222\n";
        int maxEdges=0;
        for (int i=n-1; i>=1; i--) {
            maxEdges=maxEdges+i;
        }
        //cout<<"1111 3333\n";
        //create random number of edges
        vector <Node> myNodesList;
        myNodesList = myDirectedGraph.getAllNodes();

                      
        for (int j = 0; j < myNodesList.size(); j++) {
            for (int k = j+1; k < (myNodesList.size()/4); k++)
                //if ( (rand () % 100) < PERCENT)
                    //printf ("  %d -> %d;\n", j, k + nodes); 
                    myDirectedGraph.addDirectedEdge(myNodesList[j], myNodesList[k]);
        }  


        return myDirectedGraph; 
    }


};

class TopSort {
    public:
        int V;
        vector <Node> myArrayList;
        vector <bool> visited;

    vector <Node> Kahns( DirectedGraph pGraph) {
        vector <Node> L;
        DirectedGraph myGraph = pGraph;
        vector <Node> nodeList = myGraph.getAllNodes();
        vector <Node> nodeListWithNoIncomingEdge;
/*
L ← Empty list that will contain the sorted elements
S ← Set of all nodes with no incoming edge

while S is non-empty do
    remove a node n from S
    add n to tail of L
    for each node m with an edge e from n to m do
        remove edge e from the graph
        if m has no other incoming edges then
            insert m into S

if graph has edges then
    return error   (graph has at least one cycle)
else 
    return L   (a topologically sorted order)

*/
    
        //create a "no incoming edges" list for processing
        for(int i=0; i<nodeList.size();i++) {
            if(nodeList[i].noOfIncomingEdges==0) {
                nodeListWithNoIncomingEdge.push_back(nodeList[i]);
            }
        }
       //cout<<"222222222"<<"\n"; 
        //for each node in "no incoming edges" list 
        while  (nodeListWithNoIncomingEdge.size()>0) {
            
            Node tNode = nodeListWithNoIncomingEdge[0];
            //cout<<"333333333 tNode: "<<tNode.data<<"\n";
            //add node to sorted array
            L.push_back(tNode);
            //cout<<"4444444444"<<"\n";
            // remove node from "no incoming edges" list
            nodeListWithNoIncomingEdge.erase(nodeListWithNoIncomingEdge.begin());
            //cout<<"555555"<<"\n";
            //for each edge node from the edge list of this node
            int v=tNode.edgeList.size();
            for(int j=0; j<v; j++) {
                //cout<<"6666666666"<<"\n";
                //remove edge
                Node edgeNode = tNode.edgeList[j];
                //cout<<"77777 tNode edgeNode: "<<tNode.data<<" "<<edgeNode.data<<"\n";
                myGraph.removeDirectedEdge (tNode, edgeNode);

                //refresh the nodeList and edgeNode variables after removing an edge
                nodeList = myGraph.getAllNodes();
                for(int k=0; k<nodeList.size(); k++) {
                        if(nodeList[k].data==edgeNode.data) {
                            edgeNode=nodeList[k];
                        }
                }
              
                //cout<<"77777"<<"\n";
                //if this edge node does not have any incoming edges then add it to the no incoming edgles list for reprocessing
                if (edgeNode.noOfIncomingEdges==0)
                    nodeListWithNoIncomingEdge.push_back(edgeNode);
                 
            }
        }     
        
    //cout<<"8888888888"<<"\n";
    //printGraph(nodeList);    
        
        //does graph still have edges then return error
        bool edgesLeft=false;
        for(int i=0; i<nodeList.size();i++) {
            if(nodeList[i].noOfIncomingEdges>0) {
                edgesLeft=true;
            }
        }
        if (!edgesLeft)
            return L;
        else {
            vector <Node> x;
            return x;
        }

    }


    vector <Node> mDFS( DirectedGraph myGraph) {
        vector <Node> L;
        stack <Node> tempStack;
        vector <Node> nodeList = myGraph.getAllNodes();
        vector <bool> visitedList;
        
        stack <Node> S;
/*
procedure DFS-iterative(G, v) is
    let S be a stack
    S.push(v)
    while S is not empty do
        v = S.pop()
        if v is not labeled as discovered then
            label v as discovered
            for all edges from v to w in G.adjacentEdges(v) do 
                S.push(w)
*/
        for (int i = 0; i < nodeList.size(); i++) 
            visited.push_back(false);      
    
        for(int i=0; i<nodeList.size();i++) {
            if(!visited[i]) {
                S.push(nodeList[i]);
            }   

            

            while (!S.empty()) {
                Node cur=S.top();
                S.pop(); 
                //visited[i]=true;
                //cout<<"11111111111111 cur : "<<cur.data<<"\n";
                if (stoi(cur.data) < 0) {
                    Node cur1 = cur;
                    cur1.data = to_string(stoi(cur1.data) * -1);
                    tempStack.push(cur1);
                }
                else 
                {
                    Node cur1 = cur;
                    cur1.data = to_string(stoi(cur1.data) * -1);
                    S.push(cur1);

                    //traverse all edges of node on the top of the stack - first edge node goes to the bottom of stack
                    for (int j=0; j<cur.edgeList.size();j++) {
                        for  (int k = 0; k < nodeList.size(); k++) {
                            if (nodeList[k].data==cur.edgeList[j].data) {
                                if(!visited[k]) {
                                    visited[k]=true;
                                    S.push(nodeList[k]);
                                    break;
                                }
                            }
                            
                        }
                    }
                }
            }
            
            
        }
        
        while (!tempStack.empty()){
            Node cur=tempStack.top();
            tempStack.pop();             
            
            L.push_back (cur);
        }
        
        return L;
        
    }

    vector <Node> KahnsRandomDAGIter() {
        Main myMain;
        DirectedGraph myDirectedGraph;
        
        myDirectedGraph=myMain.createRandomDAGIter(1000);
    //cout<<"222222222"<<"\n";
        //printGraph(myDirectedGraph.getAllNodes());   
           
        return Kahns(myDirectedGraph);   
         
    }


    vector <Node> myDFSRandomDAGIter() {
        Main myMain;
        DirectedGraph myDirectedGraph;
        
        myDirectedGraph=myMain.createRandomDAGIter(1000);
    //cout<<"1111111111"<<"\n";
        //printGraph(myDirectedGraph.getAllNodes());    

        return mDFS(myDirectedGraph);       
    }


};




int main() {
    DirectedGraph myDirectedGraph;
    TopSort myTopSort;
    Main myGraphMain;
    vector <Node> myArrayList;

    cout<<"START"<<"\n";

    cout<<"CREATE KAHN RANDOM DIRECTED UNWEIGHTED GRAPH"<<"\n";
    myArrayList = myTopSort.KahnsRandomDAGIter();

    cout<<"PRINT KAHNS"<<"\n";
    printArray(myArrayList);

    cout<<"CREATE DFS RANDOM DIRECTED UNWEIGHTED GRAPH"<<"\n";
    myArrayList = myTopSort.myDFSRandomDAGIter();
   
    cout<<"PRINT DFS"<<"\n";
    printArray(myArrayList);
       
    cout<<"END"<<"\n";


    return 0;
}