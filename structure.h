#include<iostream>
#include<vector>

using namespace std;

class Tree{
private:
    struct Link{
        string id;
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

};

class Track{
private:
    struct Flow{
        string linkIds[2];
        float throughput;
    };

    vector<Flow*> allFlows;

public:
    Track(float);
    void addFlow();
    void printFlows();

};