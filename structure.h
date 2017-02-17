#include<iostream>
#include<vector>

using namespace std;

class Track{
private:
    struct Flow{
        string linkIds[2];
        float throughput;
    };

    vector<Flow*> allFlows;

public:
    //Track(float);
    void addFlow();
    void printFlows();
    void storeValidFlow(int,vector<string>,vector<string>);
    void findFlow(int,int,int,int);

};

class Tree{
private:
    struct Link{
        string id;
        int spineId;
        int leafId;
        float weightF;
        float weightB;        
        int* spineNode;
        int* leafNode;
    };

    vector<Link*> allLinks;

public:
    Tree(int, int);
    void addLink(int, int, int*, int*, int);
    void printLinks(int, int);
    void findLinks(int, int, int, int, int);
    friend void Track::findFlow(int,int,int,int);

};
