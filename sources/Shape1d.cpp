//
//  Shape1d.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//
///\cond
#include <cmath>
#include <math.h>
///\endcond
#include "Shape1d.h"

void Shape1d::Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, MatrixDouble &dphi){
    
    if (orders[0] < 0 || orders[1] < 0 || orders[2] < 0) {
        std::cout << "Shape1d::Shape: Invalid dimension for arguments: order\n";
        DebugStop();
        }
    if (orders[0] > 1 || orders[1] > 1) {
        std::cout << "Shape1d::Shape: Invalid dimension for arguments: order\n";
        DebugStop();
        }

        auto nshape = NShapeFunctions(orders);
        phi.resize(nshape);
        dphi.resize(1,nshape);
        
        phi[0] = (1 - xi[0]) / 2.; //xi[0] é a coordenada no eixo 'x' (0)?
        phi[1] = (1 + xi[0]) / 2.;
        dphi(0,0) = -0.5;
        dphi(0,1) = 0.5;

        std::cout << "phi: \n" << phi << std::endl;
        std::cout << "dphi: \n" << dphi << std::endl;
    
    if (orders[2] > 1) {
       /* VecDouble phiCheby(nshape);
        VecDouble dPhiCheby(nshape);
        phiCheby[0]=1.;
        phiCheby[1]=xi[0];
        dPhiCheby[0]=0.;
        dPhiCheby[1]=1.;

        for (int i = 2; i < nshape; i++)
        {
            phiCheby[i]=2.*xi[0]*phiCheby[i-1]-phiCheby[i-2];
            dPhiCheby[i]=2.*xi[0]*dPhiCheby[i-1]+2.*phiCheby[i-1] */
        if (nshape==3){
            phi[2]=4*phi[0]*phi[1];
            dphi(0,2)=4*dphi(0,0)*phi[1]+4*phi[0]*dphi(0,1);
            std::cout << "phi: \n" << phi << std::endl;
            std::cout << "dphi: \n" << dphi << std::endl;
        }
        
        }
        }
        
        
        /*std::cout << "Shape1d::Shape: Please implement it for order > 2\n";
        DebugStop();*/
    
    

/// returns the number of shape functions associated with a side
int Shape1d::NShapeFunctions(int side, int order){

    if(order < 1 || order >2) DebugStop();
    switch (side)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 1;
        break;
    case 2:
        return order-1;
        break;
    
    default:
        std::cout << "Shape1d::NShapeFunctions : Wrong side " << side << "\n";
        DebugStop();
        return -1;
        break;
    }
    return -1;
}

/// returns the total number of shape functions
int Shape1d::NShapeFunctions(VecInt &orders) {
    
    int nsf_tot = 0;
    for (int is=0; is<3; is++) {
        nsf_tot += NShapeFunctions(is, orders[is]);
    }
    
    return nsf_tot;
}
