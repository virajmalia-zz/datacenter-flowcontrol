#include<iostream>
#include<ctime>

#include "structure.cpp"

using namespace std;

int main(){

    ////////////////////////////////////// Phase 1 - Configure Static Network Model //////////////////////////////////////////////
    int leaves, spines; 
    float flowFraction, capacityFraction;                                   //Initial inputs

    cout<<"Enter Leaves, Spines, flowFraction, capacityFraction"<<endl;
    cin>>leaves>>spines>>flowFraction>>capacityFraction;

    int spineArray[spines], leafArray[leaves];                              //Spine and leaf Arrays

    for(int i=0; i<spines; i++)
        spineArray[i]=i;
    for (int i=0; i<leaves; i++)
        leafArray[i]=i;
    
    cout<<"Arrays initialized"<<endl;

    Tree separateTree(spines, leaves);                                      //Tree object

    //Form Data Structure
    for(int i=0; i<spines; i++){                                            //Spines are assumed from 0,1,...,spines
        for(int j=0; j<leaves; j++){                                        //Leaves are assumed from 0,1,...,leaves
            separateTree.addLink(i,j,spineArray,leafArray,leaves);          //add link to allLinks Hashtable for each spine-leaf
        }
    }

    cout<<"All Links:"<<endl;
    separateTree.printLinks(spines,leaves);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////// Phase 2 - Assign Random Flows ///////////////////////////////////////////////////
    int numberOfFlows=flowFraction*leaves*spines;
    int sourceLeaf, destinationLeaf;

    srand(time(NULL));                                                      //Random seed generator
    cout<<"Seed planted"<<endl;
    for(int i=0; i<numberOfFlows; i++){                                     //For each flow
        sourceLeaf = rand()%leaves;                                         //Select random sourceLeaf
        destinationLeaf = rand()%leaves;                                    //Select random destinationLeaf
        separateTree.findLinks(sourceLeaf,destinationLeaf,leaves,spines,numberOfFlows); //Find flow from sourceLeaf to                                                                                            //destinationLeaf via a spine randomly
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////// Phase 3 - Calculate Throughput ////////////////////////////////////////////////////




    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////// Phase 4 - Modify Flows based on available Throughput //////////////////////////////




    /////////////////////////////////////////////////////////////////////////////////////////////////////////////


    return 0;
}