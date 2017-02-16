#include<iostream>
#include<cstring>
#include<sstream>

#include "structure.h"

using namespace std;

Tree::Tree(int spines, int leaves){
    allLinks.resize(spines*leaves,0);
    for(int i=0; i<spines*leaves; i++){
        allLinks[i]=new Link;
        allLinks[i]->id="empty";
        allLinks[i]->weightF=0.0;
        allLinks[i]->weightB=0.0;
        allLinks[i]->spineNode=NULL;
        allLinks[i]->leafNode=NULL;
    }
}

void Tree::addLink(int spineIndex, int leafIndex, int* spineArray, int* leafArray, int leaves){
    
    string spineString,leafString;
    ostringstream convert;

    //int to string conversion    
    convert<<spineIndex;
    spineString=convert.str();
    convert<<leafIndex;                                          //add leafIndex to the string stream (concatenate)
    leafString=convert.str();
    
    //Set parameters
    allLinks[leaves*spineIndex+leafIndex]->id=leafString;        //Concatenate spineIndex and leafIndex to form Link ID (S-L)
    allLinks[leaves*spineIndex+leafIndex]->weightF=0.0;
    allLinks[leaves*spineIndex+leafIndex]->weightB=0.0;
    allLinks[leaves*spineIndex+leafIndex]->spineNode=&spineArray[spineIndex];
    allLinks[leaves*spineIndex+leafIndex]->leafNode=&leafArray[leafIndex];
}

void Tree::printLinks(int spines, int leaves){
    for(int i=0; i<spines*leaves; i++){                          //Spines are assumed from 0,1,...,spines //Leaves are assumed from 0,1,...,leaves
        cout<<allLinks[i]->id<<" ";                              //Concatenate spineIndex and leafIndex to form Link ID
        cout<<allLinks[i]->weightF<<" ";
        cout<<allLinks[i]->weightB<<" ";
        cout<<allLinks[i]->spineNode<<" ";
        cout<<allLinks[i]->leafNode<<endl;
    }
}

Track::Track(float numberOfFlows){
    allFlows.resize(numberOfFlows);
    for(int i=0; i<numberOfFlows; i++){
        allFlows[i]=new Flow;
        allFlows[i]->linkIds[0]="empty";
        allFlows[i]->linkIds[1]="empty";
        allFlows[i]->throughput=0.0;
    }
}

findPath(int sourceLeaf, int destLeaf){
    /*
    1. Find links from sourceLeaf to all spines (equal to no. of spines).
        a. Use sourceLeaf value to find index in leafArray.
        b. Use that pointer value as key.
        c. Use this key to find the links in allLinks.
        d. Return id of these sourceLinks links.
    2. Using id of the possible links, find the spines associated with each link.
    3. Find links from each spine to destLeaf
        a. Use spineNode value as key to find the links to destLeaf.
        b. Return id of these desinationLinks links.
    4. Form valid paths from obtained sourceLinks and desinationLinks.
    5. Choose randomly one path from all valid paths.
    */
}