/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "IntRule1d.h"
///\cond
#include <iostream> 
#include <vector>
#include <math.h>
#include <cmath>
///\endcond
using namespace std;

#define PI 3.141592654

IntRule1d::IntRule1d(){

}

IntRule1d::IntRule1d(int order) : IntRule(order) {
    SetOrder(order);
}
static int ComputingSymmetricCubatureRule(int order, MatrixDouble &Points, VecDouble &Weights);
void IntRule1d::SetOrder(int order) {
    fOrder = order+1; //a ordem estava dando 'zero' e, portanto, gernado npoints negativo
   if (order < 0 || order > MaxOrder()) {
        DebugStop();
    }

    /*A0*f(x0)+A1*f(x1)
    fWeights são as constantes A0 e A1
    fPoints são os pontos médios de aproximação - {[3^(1/2)/3];-[3^(1/2)/3]} == {0.57735026919;-0.57735026919}
    */
    int npoints=(2*(order))-1; //a ordem estava dando 'zero' e, portanto, gerando npoints negativo
    
    if(order==0){
        npoints=1;
    }

    fPoints.resize(npoints,1); //coordenadas dos pontos de integração
    fWeights.resize(npoints); //A0 e A1

    VecDouble coordAux(npoints); //vecdouble é um vetor de números reais (linha,coluna)
    gauleg(-1,1,coordAux,fWeights);

    for (int i=0; i<npoints;i++){
        fPoints(i,0)=coordAux[i];
    }
}

//co = coordenada ; w = peso (A0, A1 ...) ; x1 e x2 são os qsi's -1 e 1;
void IntRule1d::gauleg(const double x1, const double x2, VecDouble &co, VecDouble &w){
    int n = w.size();

    double EPS = 1.0e-14;
    int m, j, i;
    double z1, z, xm, xl, pp, p3, p2, p1;    
    
    m = (n + 1) / 2;
    xm = 0.5 * (x2 + x1);
    xl = 0.5 * (x2 - x1);
    for (i = 0; i < m; i++) {
        z = cos(PI * (i + 0.75) / (n + 0.5));
        do {
            p1 = 1.0;
            p2 = 0.0;
            for (j = 0; j < n; j++) {
                p3 = p2;
                p2 = p1;
                p1 = ((2.0 * j + 1.0) * z * p2 - j * p3) / (j + 1);
            }
            pp = n * (z * p1 - p2) / (z * z - 1.0);
            z1 = z;
            z = z1 - p1 / pp;
        } while (fabs(z - z1) > EPS);
        co[i] = xm - xl*z;
        co[n - 1 - i] = xm + xl*z;
        w[i] = 2.0 * xl / ((1.0 - z * z) * pp * pp);
        w[n - 1 - i] = w[i];
    }
    
}

