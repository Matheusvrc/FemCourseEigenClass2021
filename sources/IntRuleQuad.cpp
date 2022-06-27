/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

///\cond
#include <iostream> 
///\endcond
#include "IntRule1d.h"
#include "IntRuleQuad.h"

IntRuleQuad::IntRuleQuad(){
}

IntRuleQuad::IntRuleQuad(int order) {
    SetOrder(order);
}

void IntRuleQuad::SetOrder(int order) {
    fOrder = order;

    if (order < 0 || order > MaxOrder()) {
        DebugStop();
    }

    int nPoints = 2*order-1;
    if (order == 0) {
        nPoints = 1;
    }
    fPoints.resize(nPoints*nPoints,2);
    fWeights.resize(nPoints);//is resized in GaulegQuad
    
    VecDouble coordAux(nPoints);
    gaulegQuad(-1,1,coordAux,fWeights);

    for (int i = 0; i < nPoints; i++)
    {
        for (int j = 0; j < nPoints; j++)
        {
            fPoints(i*nPoints+j,0) = coordAux[i];
            fPoints(j+i*nPoints,1) = coordAux[j+nPoints];
        }
    }
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
