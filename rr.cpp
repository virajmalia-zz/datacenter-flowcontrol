#include<iostream>
#include<vector>
//#include<time>

using namespace std;

struct Flow{
    int srcPath;
    int spine;
    int destPath;
    float throughput;
};

int main(){

    int spines, leaves;
    float flowFraction;
    vector<Flow*> allFlows;
    float globalSum, avg;

    cout<<"Enter number of Spines, Leaves: "<<endl;
    cin>>spines>>leaves;

    int linksF[spines][leaves];
    int linksB[spines][leaves];
    

    for(int i=0; i<spines; i++){
        for(int j=0; j<leaves; j++){
            linksF[i][j] = 0;
            linksB[i][j] = 0;
        }
    }
    //cout<<"Arrays initialized"<<endl;

    /////////////// Map and Store Flows ///////////////////
    int srcLeaf, destLeaf, selectedSpine;
    srand(time(NULL));
    flowFraction = 0.0625;
    for(int i=0; i<7; i++){
        flowFraction+=flowFraction;
        for(int j=0; j<10; j++){
            int numberOfFlows = flowFraction*spines*leaves;
            //cout<<"Number of flows: "<<numberOfFlows<<endl;
            allFlows.resize(numberOfFlows,0);
            selectedSpine = -1;
            for(int k=0; k<numberOfFlows; k++){
                srcLeaf = rand()%leaves;
                destLeaf = rand()%leaves;
                while(srcLeaf == destLeaf){
                    srcLeaf = rand()%leaves;
                    destLeaf = rand()%leaves;
                }

                selectedSpine++;
                //cout<<"Spine selected"<<endl;
                if(selectedSpine >= spines)
                    selectedSpine = 0;

                linksF[selectedSpine][srcLeaf] ++;
                linksB[selectedSpine][destLeaf] ++;
                //cout<<"Link incremented"<<endl;

                allFlows[k] = new Flow;
                allFlows[k]->srcPath = srcLeaf;
                allFlows[k]->spine = selectedSpine;
                allFlows[k]->destPath = destLeaf;
                allFlows[k]->throughput = 1.0;
                //cout<<"Flow stored"<<endl;
            }
      //  }
    //}
/*    cout<<"LinksF"<<endl;
    for(int i=0; i<spines; i++){
        for(int j=0; j<leaves; j++){
            cout<<linksF[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"LinksB"<<endl;
    for(int i=0; i<spines; i++){
        for(int j=0; j<leaves; j++){
            cout<<linksB[i][j]<<" ";
        }
        cout<<endl;
    }*/
    //////////////////// Find Bottlenecked link /////////////////////
    int maxF = linksF[0][0];
    int maxB = linksB[0][0];
    int maxFSpine, maxFLeaf, maxBSpine, maxBLeaf;

    for(int i=0; i<spines; i++){
        for(int j=0; j<leaves; j++){
            if(linksF[i][j] > maxF){
                maxF = linksF[i][j];
                maxFSpine = i;
                maxFLeaf = j;
            }
            if(linksB[i][j] > maxB){
                maxB = linksB[i][j];
                maxBSpine = i;
                maxBLeaf = j;
            }
        }
    }

while(maxF!=0 || maxB!=0){
//for(int p=0; p<2; p++){
    //////////////// Assign Static Throughput ///////////
    //cout<<"MaxF, maxFLeaf, maxFSpine: "<<maxF<<" "<<maxFLeaf<<" "<<maxFSpine<<endl;
    //cout<<"MaxB, maxBLeaf, maxBSpine: "<<maxB<<" "<<maxBLeaf<<" "<<maxBSpine<<endl;
    
    if(maxF>maxB){
        //max is in forward matrix
        for(int i=0; i<allFlows.size(); i++){
            if(allFlows[i]->srcPath == maxFLeaf && allFlows[i]->spine == maxFSpine){
                allFlows[i]->throughput = 1.0/maxF;
                linksF[maxFSpine][maxFLeaf] = -1;
            }
        }
    }
    else if(maxB>maxF){
        //max is in backward matrix
        for(int i=0; i<allFlows.size(); i++){
            if(allFlows[i]->destPath == maxBLeaf && allFlows[i]->spine == maxBSpine){
                allFlows[i]->throughput = 1.0/maxB;
                linksB[maxBSpine][maxBLeaf] = -1;
            }
        }
    }
    else{
        //max in both matrices
        for(int i=0; i<allFlows.size(); i++){
            if(allFlows[i]->srcPath == maxFLeaf && allFlows[i]->spine == maxFSpine){
                allFlows[i]->throughput = 1.0/maxF;
                linksF[maxFSpine][maxFLeaf] = -1;
            }
        }
        for(int i=0; i<allFlows.size(); i++){
            if(allFlows[i]->destPath == maxBLeaf && allFlows[i]->spine == maxBSpine){
                allFlows[i]->throughput = 1.0/maxB;
                linksB[maxBSpine][maxBLeaf] = -1;
            }
        }
    }

    maxF=0;
    maxB=0;

    for(int i=0; i<spines; i++){
        for(int j=0; j<leaves; j++){
            if(linksF[i][j] > maxF){
                maxF = linksF[i][j];
                maxFSpine = i;
                maxFLeaf = j;
            }
            if(linksB[i][j] > maxB){
                maxB = linksB[i][j];
                maxBSpine = i;
                maxBLeaf = j;
            }
        }
    }
}

/*    cout<<"LinksF"<<endl;
    for(int i=0; i<spines; i++){
        for(int j=0; j<leaves; j++){
            cout<<linksF[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"LinksB"<<endl;
    for(int i=0; i<spines; i++){
        for(int j=0; j<leaves; j++){
            cout<<linksB[i][j]<<" ";
        }
        cout<<endl;
    }*/
////////// Print Flows and Calculate Throughput /////////////
    float total = 0;
 //   cout<<"All Flows:"<<endl;
    for(int i=0; i<allFlows.size(); i++){
/*        cout.precision(4);
        cout<<allFlows[i]->srcPath<<" ";
        cout<<allFlows[i]->spine<<" ";
        cout<<allFlows[i]->destPath<<" ";
        cout<<allFlows[i]->throughput<<endl;*/
        total += allFlows[i]->throughput;
    }
    globalSum += total;
    //cout.precision(4);
    //cout<<"Total: "<<total<<endl;
        }
        avg = globalSum/10;
        cout<<"Avg Throughput for flowFraction = "<<flowFraction<<" : "<<avg<<endl;
    }
    return 0;
}