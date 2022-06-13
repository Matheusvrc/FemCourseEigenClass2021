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
        
       

    switch (order)
   {
    case 0:
    
    case 1:
        
        fPoints.resize(1,2); //(ponto, dimensão)
        fWeights.resize(1);

        fPoints(0,0)=1./3.;
        fPoints(0,1)=1./3.;
        //fPoints(2,0)=1/3;
        
        fWeights[0]=1./2.;

       break;
   
    case 2:

        fPoints.resize(3,2);
        fWeights.resize(3);

        fPoints(0,0)=2./3.;
        fPoints(0,1)=1./6.;
        //fPoints(2,0)=1/6;
        fWeights[0]=(1./3.)/2.;

        fPoints(1,0)=1./6.;
        fPoints(1,1)=2./3.;
        //fPoints(2,1)=1/6;
        fWeights[1]=(1./3.)/2.;

        fPoints(2,0)=1./6.;
        fPoints(2,1)=1./6.;
        //fPoints(2,2)=2/3;
        fWeights[2]=(1./3.)/2.;

       break;

case 3:
        fPoints.resize(6,2);
        fWeights.resize(6);

        fPoints(0,0)=(-1./9.)*std::sqrt(38.-44.*std::sqrt(2./5.))+(1./9.)*(1.+std::sqrt(10.));
        fPoints(0,1)=(1./18.)*(8.-std::sqrt(10.)+std::sqrt(38.-44.*std::sqrt(2./5.)));
        //fPoints(2,0)=0.445948;
        fWeights[0]=((620.+std::sqrt(155.*(1375.-344.*std::sqrt(10.))))/3720.)/2.;

        fPoints(1,0)=(1./18.)*(8.-std::sqrt(10.)+std::sqrt(38.-44.*std::sqrt(2./5.)));
        fPoints(1,1)=(-1./9.)*std::sqrt(38.-44.*std::sqrt(2./5.))+(1./9.)*(1+std::sqrt(10.));
        //fPoints(2,1)=0.445948;
        fWeights[1]=((620.+std::sqrt(155.*(1375.-344.*std::sqrt(10.))))/3720.)/2.;

        fPoints(2,0)=(1./18.)*(8.-std::sqrt(10.)+std::sqrt(38.-44.*std::sqrt(2./5.)));
        fPoints(2,1)=(1./18.)*(8.-std::sqrt(10.)+std::sqrt(38.-44.*std::sqrt(2./5.)));
        //fPoints(2,2)=0.108103;
        fWeights[2]=((620.+std::sqrt(155.*(1375.-344.*std::sqrt(10.))))/3720.)/2.;

        fPoints(3,0)=1. + (1./9.)*(-8. + std::sqrt(10.) + std::sqrt(38. - 44.*std::sqrt(2./5.)));
        fPoints(3,1)=(1./18.) * (8. - std::sqrt(10.) - std::sqrt(38. - 44.*std::sqrt(2./5.)));
        //fPoints(2,3)=0.0915762;
        fWeights[3]=((1./6.) - (1./24.)*std::sqrt((1./155.)*(1375. - 344.*std::sqrt(10.))))/2.;

        fPoints(4,0)=(1./18.) * (8. - std::sqrt(10.) - std::sqrt(38. - 44.*std::sqrt(2./5.)));
        fPoints(4,1)=1. + (1./9.)*(-8. + std::sqrt(10.) + std::sqrt(38. - 44.*std::sqrt(2./5.)));
        //fPoints(2,4)=0.0915762;
        fWeights[4]=((1./6.) - (1./24.)*std::sqrt((1./155.)*(1375. - 344.*std::sqrt(10.))))/2.;
        
        fPoints(5,0)=(1./18.) * (8. - std::sqrt(10.) - std::sqrt(38. - 44.*std::sqrt(2./5.)));
        fPoints(5,1)=(1./18.) * (8. - std::sqrt(10.) - std::sqrt(38. - 44.*std::sqrt(2./5.)));
        //fPoints(2,5)=0.816848;
        fWeights[5]=((1./6.) - (1./24.)*std::sqrt((1./155.)*(1375. - 344.*std::sqrt(10.))))/2.;
        
        
        break;

    case 4:
        fPoints.resize(6,2);
        fWeights.resize(6);

        fPoints(0,0)=(-1./9.)*std::sqrt(38.-44.*std::sqrt(2./5.))+(1./9.)*(1.+std::sqrt(10.));
        fPoints(0,1)=(1./18.)*(8.-std::sqrt(10.)+std::sqrt(38.-44.*std::sqrt(2./5.)));
        //fPoints(2,0)=0.445948;
        fWeights[0]=((620.+std::sqrt(155.*(1375.-344.*std::sqrt(10.))))/3720.)/2.;

        fPoints(1,0)=(1./18.)*(8.-std::sqrt(10.)+std::sqrt(38.-44.*std::sqrt(2./5.)));
        fPoints(1,1)=(-1./9.)*std::sqrt(38.-44.*std::sqrt(2./5.))+(1./9.)*(1.+std::sqrt(10.));
        //fPoints(2,1)=0.445948;
        fWeights[1]=((620.+std::sqrt(155.*(1375.-344.*std::sqrt(10.))))/3720.)/2.;

        fPoints(2,0)=(1./18.)*(8-std::sqrt(10.)+std::sqrt(38.-44.*std::sqrt(2./5.)));
        fPoints(2,1)=(1./18.)*(8-std::sqrt(10.)+std::sqrt(38.-44.*std::sqrt(2./5.)));
        //fPoints(2,2)=0.108103;
        fWeights[2]=((620.+std::sqrt(155.*(1375.-344.*std::sqrt(10.))))/3720.)/2.;

        fPoints(3,0)=1. + (1./9.)*(-8. + std::sqrt(10.) + std::sqrt(38. - 44.*std::sqrt(2./5.)));
        fPoints(3,1)=(1./18.) * (8. - std::sqrt(10.) - std::sqrt(38. - 44.*std::sqrt(2./5.)));
        //fPoints(2,3)=0.0915762;
        fWeights[3]=((1./6.) - (1./24.)*std::sqrt((1./155.)*(1375. - 344.*std::sqrt(10.))))/2.;

        fPoints(4,0)=(1./18.) * (8. - std::sqrt(10.) - std::sqrt(38. - 44.*std::sqrt(2./5.)));
        fPoints(4,1)=1. + (1./9.)*(-8. + std::sqrt(10.) + std::sqrt(38. - 44.*std::sqrt(2./5.)));
        //fPoints(2,4)=0.0915762;
        fWeights[4]=((1./6.) - (1./24.)*std::sqrt((1./155.)*(1375. - 344.*std::sqrt(10.))))/2.;
        
        fPoints(5,0)=(1./18.) * (8. - std::sqrt(10.) - std::sqrt(38. - 44.*std::sqrt(2./5.)));
        fPoints(5,1)=(1./18.) * (8. - std::sqrt(10.) - std::sqrt(38. - 44.*std::sqrt(2./5.)));
        //fPoints(2,5)=0.816848;
        fWeights[5]=((1./6.) - (1./24.)*std::sqrt((1./155.)*(1375. - 344.*std::sqrt(10.))))/2.;

        break;

    case 5:
        fPoints.resize(7,2);
        fWeights.resize(7);

        fPoints(0,0)=(1./21.)*(9.+2.*(std::sqrt(15.)));
        fPoints(0,1)=(1./21.)*(6.-std::sqrt(15.));
        //fPoints(2,0)=0.101287;
        fWeights[0]=(((155.-std::sqrt(15.))/1200.))/2.;

        fPoints(1,0)=(1./21.)*(6.-std::sqrt(15.));
        fPoints(1,1)=(1./21.)*(9.+2.*(std::sqrt(15.)));
        //fPoints(2,1)=0.101287;
        fWeights[1]=(((155.-std::sqrt(15.))/1200.))/2.;

        fPoints(2,0)=(1./21.)*(6.-std::sqrt(15.));
        fPoints(2,1)=(1./21.)*(6.-std::sqrt(15.));
        //fPoints(2,2)=0.797427;
        fWeights[2]=(((155.-std::sqrt(15.))/1200.))/2.;

        fPoints(3,0)=(1./21.)*(9.-2.*std::sqrt(15.));
        fPoints(3,1)=(1./21.)*(6.+std::sqrt(15.));
        //fPoints(2,3)=0.470142;
        fWeights[3]=(((155.+std::sqrt(15.))/1200.))/2.;

        fPoints(4,0)=(1./21.)*(6.+std::sqrt(15.));
        fPoints(4,1)=(1./21.)*(9.-2.*std::sqrt(15.));
        //fPoints(2,4)=0.470142;
        fWeights[4]=(((155.+std::sqrt(15.))/1200.))/2.;
        
        fPoints(5,0)=(1./21.)*(6.+std::sqrt(15.));
        fPoints(5,1)=(1./21.)*(6.+std::sqrt(15.));
        //fPoints(2,5)=0.0597159;
        fWeights[5]=(((155.+std::sqrt(15.))/1200.))/2.;

        fPoints(6,0)=1./3.;
        fPoints(6,1)=1./3.;
        //fPoints(2,6)=1/3;
        fWeights[6]=(9./40.)/2.;

        break;

   default:
    DebugStop();
       break;
   }

}