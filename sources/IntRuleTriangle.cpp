/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

///\cond
#include <iostream> 
///\endcond
#include "IntRuleTriangle.h"


IntRuleTriangle::IntRuleTriangle(){
  
  }
  
IntRuleTriangle::IntRuleTriangle(int order) : IntRule(order) {
  SetOrder(order);
  }

void IntRuleTriangle::SetOrder(int order) {
  /*  std::cout << __PRETTY_FUNCTION__ << " needs to be implemented\n";
    DebugStop(); */

    if (order < 0 || order > MaxOrder()) {
        DebugStop();
    }
    
    fOrder = order;
    int npoints=((2*(order))-1);
    
    if(order==0){
        npoints=1;
    }

    

    switch (order)
   {
    case 1:
        
        fPoints.resize(2,1);
        fWeights.resize(1);

        fPoints(0,0)=1/3;
        fPoints(1,0)=1/3;
        //fPoints(2,0)=1/3;
        
        fWeights[0]=1/2;

       break;
   
    case 2:

        fPoints.resize(2,3);
        fWeights.resize(3);

        fPoints(0,0)=2/3;
        fPoints(1,0)=1/6;
        //fPoints(2,0)=1/6;
        fWeights[0]=(1/3)/2;

        fPoints(0,1)=1/6;
        fPoints(1,1)=2/3;
        //fPoints(2,1)=1/6;
        fWeights[1]=(1/3)/2;

        fPoints(0,2)=1/6;
        fPoints(1,2)=1/6;
        //fPoints(2,2)=2/3;
        fWeights[2]=(1/3)/2;

       break;

case 3:
        fPoints.resize(2,6);
        fWeights.resize(6);

        fPoints(0,0)=0.108103;
        fPoints(1,0)=0.445948;
        //fPoints(2,0)=0.445948;
        fWeights[0]=0.223382/2;

        fPoints(0,1)=0.445948;
        fPoints(1,1)=0.108103;
        //fPoints(2,1)=0.445948;
        fWeights[1]=0.223382/2;

        fPoints(0,2)=0.445948;
        fPoints(1,2)=0.445948;
        //fPoints(2,2)=0.108103;
        fWeights[2]=0.223382/2;

        fPoints(0,3)=0.816848;
        fPoints(1,3)=0.0915762;
        //fPoints(2,3)=0.0915762;
        fWeights[3]=0.109952/2;

        fPoints(0,4)=0.0915762;
        fPoints(1,4)=0.816848;
        //fPoints(2,4)=0.0915762;
        fWeights[4]=0.109952/2;
        
        fPoints(0,5)=0.0915762;
        fPoints(1,5)=0.0915762;
        //fPoints(2,5)=0.816848;
        fWeights[5]=0.109952/2;
        
        /*
        fPoints.resize(6,2);
        fWeights.resize(6);

        fPoints(0,0)=0.108103; //(qsi, eta)
        fPoints(0,1)=0.445948;
        fWeights[0]=0.223382;

        fPoints(1,0)=0.445948; //(qsi, eta)
        fPoints(1,1)=0.108103;
        fWeights[0]=0.223382;

        fPoints(2,0)=0.108103; //(qsi, eta)
        fPoints(2,1)=0.108103;
        fWeights[0]=0.223382;

        fPoints(3,0)=0.445948; //(qsi, eta)
        fPoints(3,1)=0.445948;
        fWeights[0]=0.223382;
        */

        break;

    case 4:
        fPoints.resize(2,6);
        fWeights.resize(6);

        fPoints(0,0)=0.108103;
        fPoints(1,0)=0.445948;
        //fPoints(2,0)=0.445948;
        fWeights[0]=0.223382/2;

        fPoints(0,1)=0.445948;
        fPoints(1,1)=0.108103;
        //fPoints(2,1)=0.445948;
        fWeights[1]=0.223382/2;

        fPoints(0,2)=0.445948;
        fPoints(1,2)=0.445948;
        //fPoints(2,2)=0.108103;
        fWeights[2]=0.223382/2;

        fPoints(0,3)=0.816848;
        fPoints(1,3)=0.0915762;
        //fPoints(2,3)=0.0915762;
        fWeights[3]=0.109952/2;

        fPoints(0,4)=0.0915762;
        fPoints(1,4)=0.816848;
        //fPoints(2,4)=0.0915762;
        fWeights[4]=0.109952/2;
        
        fPoints(0,5)=0.0915762;
        fPoints(1,5)=0.0915762;
        //fPoints(2,5)=0.816848;
        fWeights[5]=0.109952/2;

        break;

    case 5:
        fPoints.resize(2,7);
        fWeights.resize(7);

        fPoints(0,0)=0.797427;
        fPoints(1,0)=0.101287;
        //fPoints(2,0)=0.101287;
        fWeights[0]=0.125939/2;

        fPoints(0,1)=0.101287;
        fPoints(1,1)=0.797427;
        //fPoints(2,1)=0.101287;
        fWeights[1]=0.125939/2;

        fPoints(0,2)=0.101287;
        fPoints(1,2)=0.101287;
        //fPoints(2,2)=0.797427;
        fWeights[2]=0.125939/2;

        fPoints(0,3)=0.0597159;
        fPoints(1,3)=0.470142;
        //fPoints(2,3)=0.470142;
        fWeights[3]=0.132394/2;

        fPoints(0,4)=0.470142;
        fPoints(1,4)=0.0597159;
        //fPoints(2,4)=0.470142;
        fWeights[4]=0.132394/2;
        
        fPoints(0,5)=0.470142;
        fPoints(1,5)=0.470142;
        //fPoints(2,5)=0.0597159;
        fWeights[5]=0.132394/2;

        fPoints(0,6)=1/3;
        fPoints(1,6)=1/3;
        //fPoints(2,6)=1/3;
        fWeights[6]=0.225/2;

        break;

   default:
    DebugStop();
       break;
   }

}