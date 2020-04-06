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

struct Coord {
    int xCoord;
    int yCoord;
};
struct GridNode {
    string data;
    vector <GridNode> edgeList;
    Coord myCoord;
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
            myCoord.xCoord=x;
            myCoord.yCoord=y;
            newNode.myCoord=myCoord;
            
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
            //cout<<"55555 n firstIndex secondIndex: "<<n<<" "<<firstIndex<<" "<<secondIndex<<"\n";

            //one of the first or second nodes have four edges/neighbours, in which case dont add new bi-directional edge
            if (nodeList[firstIndex].edgeList.size()>=4 || nodeList[secondIndex].edgeList.size()>=4)
                return;

            //cout<<"666666 1st edges 2nd edges : "<<nodeList[firstIndex].edgeList.size()<<" "<<nodeList[secondIndex].edgeList.size()<<"\n";

            //only create edge between neighbors
            //  i.e. either x coord or y coord should have a difference of 1 between first and second
            //  example: if first is 2,2 second can only be 3,2 or 2,3 or 1,2 or 2,1
            if (!(
                    (nodeList[secondIndex].myCoord.xCoord==nodeList[firstIndex].myCoord.xCoord+1 and nodeList[secondIndex].myCoord.yCoord==nodeList[firstIndex].myCoord.yCoord)
                    ||
                    (nodeList[secondIndex].myCoord.xCoord==nodeList[firstIndex].myCoord.xCoord and nodeList[secondIndex].myCoord.yCoord==nodeList[firstIndex].myCoord.yCoord+1)
                    ||
                    (nodeList[secondIndex].myCoord.xCoord==nodeList[firstIndex].myCoord.xCoord-1 and nodeList[secondIndex].myCoord.yCoord==nodeList[firstIndex].myCoord.yCoord)
                    ||
                    (nodeList[secondIndex].myCoord.xCoord==nodeList[firstIndex].myCoord.xCoord and nodeList[secondIndex].myCoord.yCoord==nodeList[firstIndex].myCoord.yCoord-1)
                ))
                return;
            //cout<<"7777"<<"\n";

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
                        //cout<<"88888 11111 created edge between: "<<firstIndex<<"->"<<secondIndex<<"\n";
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
                        //cout<<"88888 22222 created edge between: "<<secondIndex<<"->"<<firstIndex<<"\n";
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
                       //nodeList[i]->edgeList.push_back(second);
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
            /*set <GridNode> nodeset;
            int n=nodeList.size();
            for(int i=0; i<n;i++) {
                nodeset.insert(nodeList[i]);
            }
            */
            return nodeList;
        }
};
bool operator < (const Coord& left, const Coord& right)
{
    if (left.yCoord < right.yCoord)
    {
        return true;
    }
    else if (right.yCoord < left.yCoord)
    {
        return false;
    }
    else if (left.xCoord < right.xCoord)
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
        //cout<<"11111111\n";
        int nodesAdded=1;
        int xx = findNumberofDigits(n);
        int maxN = pow(10,xx);
        bool found;

        for (int y=0;y<n;y++) {
            for (int x=0;x<n;x++) {
                vector <GridNode> nl = myGridGraph.getAllNodes();
                while (1==1) {
                    //int x=rand() % maxN + 1;
                    int val=rand() % ((int)pow(n,3)) + 1;
                    
                    
                    found=false;
                    for (int j=0;j<nl.size();j++) {
                        if (nl[j].data == to_string(val)) {
                            //cout<<" true ";
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

        //cout<<"222222222\n";
        
        //create adjacent neighbours
        vector <GridNode> myNodesList;
        myNodesList = myGridGraph.getAllNodes();
        
        //cout<<"333333333 myNodesList size: "<<myNodesList.size()<<"\n";
            //for(int i=0; i<myNodesList.size();i++) {
        //cout<<"333333333 i coord data: "<<i<<" ("<<myNodesList[i].myCoord.xCoord<<","<<myNodesList[i].myCoord.yCoord<<") "<<myNodesList[i].data<<"\n";
          //  }

        //create edges across x-axis        
        int y=0;
        while (y<pow(n,2)) {
            for (int x=0;x<n;x++) {
        //cout<<"44444 1111111 x y x+y x+y+1 :"<<x<<" "<<y<<" "<<x+y<<" "<<x+y+1<<"\n";
                if ((x+y+1)<(n+y)) {
                    int createTheEdge = 1;//rand() % 1;
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
        //cout<<"44444 2222 x y x+y x+y+3 :"<<x<<" "<<y<<" "<<x+y<<" "<<x+y+3<<"\n";
                if ((x+y+3)<(pow(n,2))) { //< 7 8 9
                    int createTheEdge = 1;//rand() % 1;
                    if (createTheEdge==1) {
                        myGridGraph.addUndirectedEdge(myNodesList[x+y], myNodesList[x+y+3]);
                    }
                }
                y=y+n;
                
            }
            
        }
        //cout<<"5 5 5 5 5 5 5\n";

        return myGridGraph;
    }

    vector <GridNode> astar(GridNode sourceNode, GridNode destNode) {
        
        //myGridGraph = createRandomGridGraph(3);
        vector <GridNode> nodeList = myGridGraph.getAllNodes();
        
        //create a map of Coordinates to Nodes
        map<Coord, GridNode> mp;
        
        for (int i = 0; i < nodeList.size(); i++) {
            Coord myCoord;
            myCoord.xCoord=nodeList[i].myCoord.xCoord;
            myCoord.yCoord=nodeList[i].myCoord.yCoord;
            
            mp[myCoord] = nodeList[i];
            //cout<<"Map Index myCoord : "<<i<<" ("<<myCoord.xCoord<<","<<myCoord.yCoord<<")\n";
        }
        
        int n=sqrt(nodeList.size());

        bool goRight=false;
        if (destNode.myCoord.xCoord>sourceNode.myCoord.xCoord)
            goRight=true;
        bool goUp=false;
        if (destNode.myCoord.yCoord>sourceNode.myCoord.yCoord)
            goUp=true;
        
        vector <GridNode> myArrayList;
        
        if (goRight) {
            int y=sourceNode.myCoord.yCoord;
            for (int x=sourceNode.myCoord.xCoord;x<=destNode.myCoord.xCoord;x++) {
                //cout<<"aStar: 111111 x y: ("<<x<<","<<y<<")\n";
                Coord myCoord;
                myCoord.xCoord=x;
                myCoord.yCoord=y;
                auto itr = mp.find(myCoord);
                myArrayList.push_back((GridNode) itr->second);
                
                //cout<<"aStar: 22222 push: ("<<(((GridNode) itr->second).myCoord.xCoord)<<","<<(((GridNode) itr->second).myCoord.yCoord)<<")\n";

            }
        }
        else {// go left or stay there
            int y=sourceNode.myCoord.yCoord;
            for (int x=sourceNode.myCoord.xCoord;x>=destNode.myCoord.xCoord;x--) {
                //cout<<"aStar: 111111 x y: ("<<x<<","<<y<<")\n";
                Coord myCoord;
                myCoord.xCoord=x;
                myCoord.yCoord=y;
                auto itr = mp.find(myCoord);
                myArrayList.push_back((GridNode) itr->second);
                //cout<<"aStar: 22222 push: ("<<x<<","<<y<<")\n";
                
//                cout<<"aStar: 22222 push: ("<<(((GridNode) itr->second).myCoord.xCoord)<<","<<(((GridNode) itr->second).myCoord.yCoord)<<")\n";

            }
        }
        if (goUp) {
            int x=destNode.myCoord.xCoord;
            for (int y=sourceNode.myCoord.yCoord+1;y<=destNode.myCoord.yCoord;y++) {
                //cout<<"aStar: 111111 x y: ("<<x<<","<<y<<")\n";
                Coord myCoord;
                myCoord.xCoord=x;
                myCoord.yCoord=y;
                auto itr = mp.find(myCoord);
                myArrayList.push_back((GridNode) itr->second);
                
                //cout<<"aStar: 22222 push: ("<<(((GridNode) itr->second).myCoord.xCoord)<<","<<(((GridNode) itr->second).myCoord.yCoord)<<")\n";
            }
        }
        else {
            int x=destNode.myCoord.xCoord;
            for (int y=sourceNode.myCoord.yCoord-1;y>=destNode.myCoord.yCoord;y--) {
                //cout<<"aStar: 111111 x y: ("<<x<<","<<y<<")\n";
                Coord myCoord;
                myCoord.xCoord=x;
                myCoord.yCoord=y;
                auto itr = mp.find(myCoord);
                myArrayList.push_back((GridNode) itr->second);
                
                //cout<<"aStar: 22222 push: ("<<(((GridNode) itr->second).myCoord.xCoord)<<","<<(((GridNode) itr->second).myCoord.yCoord)<<")\n";
            }
        }
        
        return myArrayList;
    }
};
void printGraph (vector <GridNode> v) {
//        cout<<"55555555"<<"\n";
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
//           cout<<"6666666"<<"\n";

}
void printArray (vector <GridNode> v) {
    for (int i=0;i<v.size();i++) {
        cout<<"("<<v[i].myCoord.xCoord<<","<<v[i].myCoord.yCoord<<") ";
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
    //       cout<<"41414141"<<"\n";
    printGraph(h); 

    
    cout<<"PERFORM ASTAR SEARCH"<<"\n";
//    nodeList = myGraphMain.astar(h[h.size()-1],h[0]);
    nodeList = myGraphMain.astar(h[0],h[h.size()-1]);

    printArray(nodeList); 

    cout<<"END"<<"\n";

    return 0;
}

