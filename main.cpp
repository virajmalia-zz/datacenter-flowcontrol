#include<iostream>
#include<ctime>

#include "structure.cpp"

using namespace std;

int main(){

    ////////////////////////////////////// Phase 1 /////////////////////////////////////////////////////////
    int leaves, spines; 
    float flowFraction, capacityFraction;                     //Initial inputs

    cout<<"Enter Leaves, Spines, capacityFraction, flowFraction"<<endl;
    cin>>leaves>>spines>>capacityFraction>>flowFraction;

    int spineArray[spines], leafArray[leaves];                              //Spine and leaf Arrays

    for(int i=0; i<spines; i++)
        spineArray[i]=i;
    for (int i=0; i<leaves; i++)
        leafArray[i]=i;
    
    cout<<"Arrays initialized"<<endl;

    Tree separateTree(spines, leaves);                                      //Tree object

    //Form Data Structure
    for(int i=0; i<spines; i++){                    //Spines are assumed from 0,1,...,spines
        for(int j=0; j<leaves; j++){                //Leaves are assumed from 0,1,...,leaves
            //Create link
            separateTree.addLink(i,j,spineArray,leafArray,leaves);          //add link to allLinks table for each spine-leaf combo
        }
    }
    cout<<"All Links:"<<endl;
    separateTree.Tree::printLinks(spines,leaves);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////Phase 2/////////////////////////////////////////////////////////
    int numberOfFlows=flowFraction*leaves*spines;

    Track flowTracker(numberOfFlows);                                       //Flow Tracker object

    srand(time(NULL));

    int sourceLeaf = rand()%leaves;                 //Select random sourceLeaf
    int destinationLeaf = rand()%leaves;            //Select random destinationLeaf

    findPath(sourceLeaf,destinationLeaf);                                     //Find path from sourceLeaf to destinationLeaf via a spine randomly





    return 0;
}