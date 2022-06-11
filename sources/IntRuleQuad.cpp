/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

///\cond
#include <iostream>
#include <stdio.h>
///\endcond
#include "IntRule1d.h"
#include "IntRuleQuad.h"


IntRuleQuad::IntRuleQuad(){
}

IntRuleQuad::IntRuleQuad(int order) {
    SetOrder(order); //adicionei
    
    /*
    std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    DebugStop();
    */
}

static int ComputingSymmetricCubatureRule(int order, MatrixDouble &Points, VecDouble &Weights); //adicionei
/*
void IntRule1d::SetOrder(int order) {
    fOrder = order;
   if (order < 0 || order > MaxOrder()) {
        DebugStop();
    }
    */

void IntRuleQuad::SetOrder(int order) {
    
    int npoints=((2*(order))-1)*((2*(order))-1); //a ordem estava dando 'zero' e, portanto, gerando npoints negativo
    
    if(order==0){
        npoints=1;
    }

    fPoints.resize(npoints,2); //coordenadas dos pontos de integração
    fWeights.resize(npoints); //A0 e A1

    VecDouble coordAux(npoints);
    /*gaulegQuad(-1,1,coordAux,fWeights); //adicionei */
    
    //adicionei o comando switch
    switch (npoints){
        case 2:
            
            //fPoints[]{0.5773502692, -0.5773502692}; inicialização uniforme

            fPoints(0,0)=0.5773502692;
            fPoints(1,0)=-0.5773502692;

            fWeights[0]=1.;
            fWeights[1]=1.;
            break;
        
        case 3:
            fPoints(0,0)=0.7745966692;
            fPoints(1,0)=0.;
            fPoints(2,0)=-0.7745966692;

            fWeights[0]=0.5555555556;
            fWeights[1]=0.8888888889;
            fWeights[2]=0.5555555556;
            break;
            
        case 4:
            fPoints(0,0)=0.8611363116;
            fPoints(1,0)=0.3399810436;
            fPoints(2,0)=-0.3399810436;
            fPoints(3,0)=-0.8611363116;

            fWeights[0]=0.3478548451;
            fWeights[1]=0.6521451549;
            fWeights[2]=0.6521451549;
            fWeights[3]=0.3478548451;
            break;

        case 5:
            fPoints(0,0)=0.9061798459;
            fPoints(1,0)=0.5384693101;
            fPoints(2,0)=0.;
            fPoints(3,0)=-0.5384693101;
            fPoints(4,0)=-0.9061798459;

            fWeights[0]=0.2369268850;
            fWeights[1]=0.4786286705;
            fWeights[2]=0.5688888889;
            fWeights[3]=0.4786286705;
            fWeights[4]=0.2369268850;
            break;

        default:
        std::cout << "\nErro: Ordem superior ao limite programado\n";
    }

    /*
    std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    DebugStop();
    */
}

void IntRuleQuad::gaulegQuad(const double x1, const double x2, VecDouble &co, VecDouble &w) {
    IntRule1d x;
    IntRule1d y;
    
    int n = w.size();   

    VecDouble cox(n);
    VecDouble coy(n);
    VecDouble wx(n);
    VecDouble wy(n);


    x.gauleg(x1, x2, cox, wx);
    y.gauleg(x1, x2, coy, wy);
    
    co.resize(2*n*n);
    w.resize(n * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            co[j + i * n] = cox[j];
            co[j + i * n + n * n] = coy[i];
            w[n * i + j] = wx[i] * wy[j];
        }
    }
}
