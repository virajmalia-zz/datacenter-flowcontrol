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
        allLinks[i]->spineId=-1;
        allLinks[i]->leafId=-1;
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
    allLinks[leaves*spineIndex+leafIndex]->spineId=spineIndex;
    allLinks[leaves*spineIndex+leafIndex]->leafId=leafIndex;
    allLinks[leaves*spineIndex+leafIndex]->weightF=0.0;
    allLinks[leaves*spineIndex+leafIndex]->weightB=0.0;
    allLinks[leaves*spineIndex+leafIndex]->spineNode=&spineArray[spineIndex];
    allLinks[leaves*spineIndex+leafIndex]->leafNode=&leafArray[leafIndex];
}

void Tree::printLinks(int spines, int leaves){
    for(int i=0; i<spines*leaves; i++){                          //Spines are assumed from 0,1,...,spines //Leaves are assumed from 0,1,...,leaves
        cout<<allLinks[i]->id<<" ";                              //Concatenate spineIndex and leafIndex to form Link ID
        cout<<allLinks[i]->spineId<<" ";
        cout<<allLinks[i]->leafId<<" ";
        cout<<allLinks[i]->weightF<<" ";
        cout<<allLinks[i]->weightB<<" ";
        cout<<allLinks[i]->spineNode<<" ";
        cout<<allLinks[i]->leafNode<<endl;
    }
}
/*
Track::Track(float numberOfFlows){
    allFlows.resize(numberOfFlows);
    for(int i=0; i<numberOfFlows; i++){
        allFlows[i]=new Flow;
        allFlows[i]->linkIds[0]="empty";
        allFlows[i]->linkIds[1]="empty";
        allFlows[i]->throughput=0.0;
    }
}
*/
void Track::findFlow(int srcLeaf, int dstLeaf, int leaves, int spines){
    /*
    1. Find links from sourceLeaf to all spines (equal to no. of spines).
        a. Use sourceLeaf value to find index in leafArray.
        b. Use that pointer value as key.
        c. Use this key to find the links in allLinks.
        d. Return id of these sourceLinks links.
    2. Using id of the possible links, find the spines associated with each link.
    3. Find links from each spine to destLeaf
        a. Use spineNode value as key to find the links to destLeaf.
        b. Return id of these desination links.                        In destId
    4. Form valid paths from obtained sourceLinks and desinationLinks.
    5. Choose randomly one path from all valid paths.
    6. Add this selected path to allFlows.
    */
}

void Track::storeValidFlow(int spines,vector<string> srcPath,vector<string> destPath){
    
    int selectedPathIndex = rand()%spines;
    cout<<"SelectedPathIndex: "<<selectedPathIndex<<endl;

    Track::Flow* selectedFlow = new Flow;

    selectedFlow->linkIds[0]=srcPath[selectedPathIndex];
    selectedFlow->linkIds[1]=destPath[selectedPathIndex];

    allFlows.push_back(selectedFlow);
    cout<<"All Flows:"<<endl;
    for(int i=0; i<allFlows.size(); i++){
        cout<<allFlows[i]->linkIds[0]<<" ";
        cout<<allFlows[i]->linkIds[1]<<" ";
        cout<<allFlows[i]->throughput<<endl;
    }
}

void Tree::findLinks(int sourceLeaf, int destLeaf, int leaves, int spines, int numberOfFlows){  // 1,2,3
    vector<string> srcPath(spines), destPath(spines);
    int i=0;
    while(allLinks[i]->leafId != sourceLeaf)                            //Find 1st occurrence of sourceLeaf in allLinks
        i++;

    srcPath[0]=allLinks[i]->id;

    for(int k=0; k<leaves; k++){
        if(allLinks[allLinks[i]->spineId*leaves+k]->leafId == destLeaf) //Find destination Leaf in allLinks
            destPath[0] = allLinks[allLinks[i]->spineId*leaves+k]->id;
    }

    for (int j=0; j<spines-1; j++){                                     //Find remaining occurences of sourceLeaf
        
        srcPath[j+1]=allLinks[i+leaves*(j+1)]->id;
        
        for(int k=0; k<leaves; k++){
            if(allLinks[
                allLinks[i+leaves]->spineId
                *leaves+k]
                ->leafId == destLeaf)                                  //Find destination Leaf in allLinks
                destPath[j+1] = allLinks[
                                allLinks[i+leaves*(j+1)]->spineId
                                *leaves+k]->id;
        }
    }
    cout<<"src and dest:"<<endl;
    for(int i=0; i<srcPath.size(); i++){
        cout<<srcPath[i]<<" "<<destPath[i]<<endl;
    }

    Track flowTracker;
    flowTracker.storeValidFlow(spines, srcPath, destPath);                          //4,5,6
}