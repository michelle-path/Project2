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
        //add a node
        void addNode( string nodeVal) {
            Node newNode;
            newNode.data=nodeVal;
            newNode.noOfIncomingEdges=0;
            nodeList.push_back(newNode);
            visitedList.push_back(false);
            
        }

        //add an edge, edges cannot be between the same nodes
        void addDirectedEdge( Node first, Node second) {

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
                            
                            // find the second node and identify this node has incoming edges
                            for(int l=0; l<n;l++) {
                                if(nodeList[l].data==second.data) {
                                    nodeList[l].noOfIncomingEdges++;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    
                }
            }
        }

        //remove an edge
        void removeDirectedEdge(Node first, Node second) {
            int n=nodeList.size();
            for(int i=0; i<n;i++) {
                if(nodeList[i].data==first.data) {
                    int v=nodeList[i].edgeList.size();
                    for(int j=0; j<v; j++) {
                        if(nodeList[i].edgeList[j].data==second.data) {
                            nodeList[i].edgeList.erase(nodeList[i].edgeList.begin()+j);
                            //find out if all incoming edges to second have been removed. 
                            // if so identify that this node has NO incoming edges
                            for(int l=0; l<n;l++) {
                                if(nodeList[l].data==second.data) {
                                    nodeList[l].noOfIncomingEdges--;
                                    break;
                                }
                            }
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


class Main {
    public:
    
    DirectedGraph myDirectedGraph;    

    int findNumberofDigits(int n) {
        string s = to_string(n);
        return s.length();
        
    }
    DirectedGraph createRandomDAGIter(int n) {
        
        //created a Random DAG graph
        
        //first create nodes with random values
        int nodesAdded=1;
        int xx = findNumberofDigits(n);
        int maxN = pow(10,xx);
        bool found;
        while (true) {
            
            int x=rand() % maxN + 1;
            
            vector <Node> nl = myDirectedGraph.getAllNodes();
            
            found=false;
            for (int j=0;j<nl.size();j++) {
                if (nl[j].data == to_string(x)) {
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
        
        //create random number of edges
        vector <Node> myNodesList;
        myNodesList = myDirectedGraph.getAllNodes();

        for (int j = 0; j < myNodesList.size(); j++) {
            //random edge node from a node
            int x = rand()%((myNodesList.size() - (j+1)) + 1) + (j+1);
            for (int k = j+1; k < x; k++)
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
        vector <Node> sortedList;
        DirectedGraph myGraph = pGraph;
        vector <Node> nodeListWithNoIncomingEdge;
        
        
        //create a "no incoming edges" list for processing
        for(int i=0; i<myGraph.getAllNodes().size();i++) {
            if((myGraph.getAllNodes())[i].noOfIncomingEdges==0) {
                nodeListWithNoIncomingEdge.push_back((myGraph.getAllNodes())[i]);
            }
        }

        //for each node in "no incoming edges" list 
        while  (nodeListWithNoIncomingEdge.size()>0) {
            
            Node tNode = nodeListWithNoIncomingEdge[0];

            //add node to sorted array
            sortedList.push_back(tNode);

            // remove node from "no incoming edges" list
            nodeListWithNoIncomingEdge.erase(nodeListWithNoIncomingEdge.begin());

            //for each edge node from the edge list of this node
            int v=tNode.edgeList.size();
            for(int j=0; j<v; j++) {

                //remove edge
                Node edgeNode = tNode.edgeList[j];

                myGraph.removeDirectedEdge (tNode, edgeNode);

                //refresh the nodeList and edgeNode variables after removing an edge
                for(int k=0; k<myGraph.getAllNodes().size(); k++) {
                        if((myGraph.getAllNodes())[k].data==edgeNode.data) {
                            edgeNode=(myGraph.getAllNodes())[k];
                            break;
                        }
                }
                //if this edge node does not have any incoming edges then add it to the no incoming edgles list for reprocessing
                if (edgeNode.noOfIncomingEdges==0)
                    nodeListWithNoIncomingEdge.push_back(edgeNode);
                 
            }
        }     
        
        //does graph still have edges then return null
        bool edgesLeft=false;
        for(int i=0; i<myGraph.getAllNodes().size();i++) {
            if((myGraph.getAllNodes())[i].noOfIncomingEdges>0) {
                edgesLeft=true;
                break;
            }
        }
        if (!edgesLeft)
            return sortedList;
        else {
            vector <Node> x;
            return x;
        }
    }


    vector <Node> mDFS( DirectedGraph myGraph) {
        vector <Node> sortedList;
        stack <Node> tempStack;
        vector <bool> visitedList;
        
        stack <Node> S;

        for (int i = 0; i < myGraph.getAllNodes().size(); i++) 
            visited.push_back(false);      
    
        for(int i=0; i<myGraph.getAllNodes().size();i++) {
            if(!visited[i]) {
                S.push((myGraph.getAllNodes())[i]);
            }   

            while (!S.empty()) {
                Node cur=S.top();
                S.pop(); 
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
                        for  (int k = 0; k < myGraph.getAllNodes().size(); k++) {
                            if ((myGraph.getAllNodes())[k].data==cur.edgeList[j].data) {
                                if(!visited[k]) {
                                    visited[k]=true;
                                    S.push((myGraph.getAllNodes())[k]);
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
            
            sortedList.push_back (cur);
        }
        
        return sortedList;
        
    }

};

int main() {
    DirectedGraph myDirectedGraph;
    TopSort myTopSort;
    Main myGraphMain;
    vector <Node> myArrayList;

    cout<<"START"<<"\n";

    cout<<"CREATE RANDOM DIRECTED UNWEIGHTED GRAPH"<<"\n";
    myDirectedGraph=myGraphMain.createRandomDAGIter(10);
    printGraph (myDirectedGraph.getAllNodes());

    cout<<"PRINT KAHNS"<<"\n";
    myArrayList = myTopSort.Kahns(myDirectedGraph); 
    printArray(myArrayList);

    cout<<"PRINT DFS"<<"\n";
    myArrayList = myTopSort.mDFS(myDirectedGraph); 

    printArray(myArrayList);
       
    cout<<"END"<<"\n";


    return 0;
}