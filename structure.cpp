#include<iostream>
#include<cstring>
#include<sstream>
#include<algorithm>

#include "structure.h"

using namespace std;

int nextSpine=-1;

Tree::Tree(int spines, int leaves){
    allLinks.resize(spines*leaves,0);
    for(int i=0; i<spines*leaves; i++){
        allLinks[i]=new Link;
        allLinks[i]->id="empty";
        allLinks[i]->spineId=-1;
        allLinks[i]->leafId=-1;
        allLinks[i]->weightUp=1.0;
        allLinks[i]->weightDown=0.0;
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
    allLinks[leaves*spineIndex+leafIndex]->weightUp=1.0;
    allLinks[leaves*spineIndex+leafIndex]->weightDown=1.0;
    allLinks[leaves*spineIndex+leafIndex]->availableUp=1.0;
    allLinks[leaves*spineIndex+leafIndex]->availableDown=1.0;
}

void Tree::printLinks(int spines, int leaves){
    for(int i=0; i<spines*leaves; i++){                          //Spines are assumed from 0,1,...,spines //Leaves are assumed                                                                  //from 0,1,...,leaves
        cout.precision(5);
        cout<<allLinks[i]->id<<" ";                              //Concatenate spineIndex and leafIndex to form Link ID
        cout<<allLinks[i]->spineId<<" ";
        cout<<allLinks[i]->leafId<<" ";
        cout<<fixed<<allLinks[i]->weightUp<<" ";
        cout<<fixed<<allLinks[i]->weightDown<<" ";
        cout<<fixed<<allLinks[i]->availableUp<<" ";
        cout<<fixed<<allLinks[i]->availableDown<<endl;
    }
}

void printFlows(){
    float total=0;
    cout<<"All Flows: "<<allFlows.size()<<endl;
    for(int i=0; i<allFlows.size(); i++){
        cout.precision(5);
        cout<<allFlows[i]->linkId[0]<<" ";
        cout<<allFlows[i]->linkId[1]<<" ";
        cout<<fixed<<allFlows[i]->throughput<<endl;
        total+=allFlows[i]->throughput;
    }
    cout<<endl;
    cout<<"Total throughput: "<<total<<endl;
}

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

void Track::storeValidFlow(int spines,vector<string> srcPath,vector<string> destPath){
    nextSpine++;
    if(nextSpine == spines)
        nextSpine = 0;    
    int selectedPathIndex = nextSpine;
    cout<<"SelectedPathIndex: "<<selectedPathIndex<<endl;

    Track::Flow* selectedFlow = new Flow;

    selectedFlow->linkId[0]=srcPath[selectedPathIndex];
    selectedFlow->linkId[1]=destPath[selectedPathIndex];
    selectedFlow->throughput=1.0;

    allFlows.push_back(selectedFlow);                   //Add flow to list

    checkLinkThroughput(selectedFlow);                  //Static throughput check
    printFlows();
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
    static Track flowTracker;
    flowTracker.storeValidFlow(spines, srcPath, destPath);                          //4,5,6
}

void Track::checkLinkThroughput(Track::Flow* selectedFlow){
    cout<<"Checking Throughput"<<endl;
    int srcForwardCount=0,destForwardCount=0;
  
        for(int i=0; i<allFlows.size(); i++){
            if (strcmp(selectedFlow->linkId[0].c_str(),allFlows[i]->linkId[0].c_str())==0){
                //if srcPath id is same, change srclink weight.
                srcForwardCount+=1;
                //cout<<"Source Equal, New throughput"<<endl;
                //cout<<srcForwardCount<<endl;
                for(int j=0; j<allLinks.size(); j++){
                    if(strcmp(allLinks[j]->id.c_str(),selectedFlow->linkId[0].c_str())==0){
                        allLinks[j]->weightUp = (float)1.0/(float)srcForwardCount;
                        allLinks[j]->availableUp=1.0-allLinks[j]->weightUp;
                    }
                }
            }
            if(strcmp(selectedFlow->linkId[1].c_str(),allFlows[i]->linkId[1].c_str())==0){
                //if destPath id is same, change destlink weight.
                destForwardCount+=1;
                //cout<<"Dest Equal"<<endl;
                //cout<<destForwardCount<<endl;
                for(int k=0; k<allLinks.size(); k++){
                    if(strcmp(allLinks[k]->id.c_str(),selectedFlow->linkId[1].c_str())==0){
                        allLinks[k]->weightDown = (float)1.0/(float)destForwardCount;
                        allLinks[k]->availableDown=1.0-allLinks[k]->weightDown;
                    }
                }
            }
        }
    srcForwardCount=1;
    destForwardCount=1;
}

void findSmallest(){
    string upMinId, downMinId;
    float upMin = allLinks[0]->weightUp;                //1st element's weight as min
    float downMin = allLinks[0]->weightDown;
    
    cout<<"Finding Smallest"<<endl;

    //Find minimum

    for(int p=0; p<allLinks.size(); p++){    
    upMin = allLinks[0]->weightUp;                //1st element's weight as min
    downMin = allLinks[0]->weightDown;

    for(int i=0; i<allLinks.size(); i++){
        if(allLinks[i]->weightUp < upMin){
            upMin = allLinks[i]->weightUp;
            upMinId = allLinks[i]->id;
        }
        if(allLinks[i]->weightDown < downMin){
            downMin = allLinks[i]->weightDown;
            downMinId = allLinks[i]->id;
        }
    }

    //if same elements have minimum values in src and dest, assign min of both values to flow
    if(strcmp(upMinId.c_str(),downMinId.c_str())==0){
            upMin = min(upMin, downMin);
            downMin = upMin;
    }

    cout<<"upMinId: "<<upMinId<<endl;
    cout<<"downMinId: "<<downMinId<<endl;

    //Modify allFlows with minimum throughput possible due to bottleneck
    for(int j=0; j<allFlows.size(); j++){

        if(strcmp(allFlows[j]->linkId[0].c_str(),upMinId.c_str())==0){
            cout<<"upMinId match"<<endl;
            allFlows[j]->throughput = min(upMin,allFlows[j]->throughput);

            for(int m=0; m<allFlows.size(); m++){
                if(strcmp(allFlows[j]->linkId[1].c_str(),allFlows[m]->linkId[1].c_str())==0 && j != m){
                    allFlows[m]->throughput = allFlows[j]->throughput;
                }
            }
        }
        if(strcmp(allFlows[j]->linkId[1].c_str(),downMinId.c_str())==0){
            cout<<"downMinId match"<<endl;
            allFlows[j]->throughput = min(downMin,allFlows[j]->throughput);
      
            for(int m=0; m<allFlows.size(); m++){
                if(strcmp(allFlows[j]->linkId[1].c_str(),allFlows[m]->linkId[1].c_str())==0 && m != j){
                    allFlows[m]->throughput = allFlows[j]->throughput;
                }
            }
        }
    }

    //Change used min values from allLinks to 2.0 to avoid re-detection as min value
    for(int k=0; k<allLinks.size(); k++){
        //cout<<"Modifying used values"<<endl;
        if(strcmp(upMinId.c_str(),allLinks[k]->id.c_str())==0){
            allLinks[k]->weightUp=2.0;
            cout<<"weightUp is 2.0"<<endl;
        }
        if(strcmp(downMinId.c_str(),allLinks[k]->id.c_str())==0){
            allLinks[k]->weightDown=2.0;
            cout<<"weightDown is 2.0"<<endl;
        }
    }
    }
    printFlows();

}