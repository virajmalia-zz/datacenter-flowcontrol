#include<iostream>
#include<vector>

using namespace std;

class Track{
public:
    struct Flow{
        string linkId[2];
        float throughput;
    };

    vector<Flow*> allFlows;

    Track(){};
    void printFlows();
    void storeValidFlow(int,vector<string>,vector<string>);
    void checkLinkThroughput(Track::Flow*);
};

class Tree{
public:
    struct Link{
        string id;
        int spineId;
        int leafId;
        float weightUp;
        float weightDown;
    };

    

    Tree(int, int);
    void addLink(int, int, int*, int*, int);
    void printLinks(int, int);
    void findLinks(int, int, int, int, int);
    friend void checkLinkThroughput(Track::Flow*);
};
vector<Tree::Link*> allLinks;