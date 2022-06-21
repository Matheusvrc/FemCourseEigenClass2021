//
//  ShapeTriangle.h
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#include "ShapeTriangle.h"
#include "Shape1d.h"

/// computes the shape functions in function of the coordinate in parameter space and orders of the shape functions (size of orders is number of sides of the element topology)
void ShapeTriangle::Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, MatrixDouble &dphi){
    
    for (int i = 0; i < orders.size(); i++)
    {
        if (orders[i] < 0) {
            std::cout << "ShapeTriangle::Shape: Invalid dimension for arguments: order\n";
            DebugStop();
        }
    }
    if (orders[0] > 1 || orders[1] > 1 || orders[2] > 1) {
        std::cout << "ShapeTriangle::Shape: Invalid dimension for arguments: order\n";
        DebugStop();
    }

    auto nf = NShapeFunctions(orders);

    phi.resize(nf);
    dphi.resize(2,nf);// (x e y, )

    // Linear order
    phi[0] =  1.-xi[0]-xi[1]; //xi[0]=x e xi[1]=y
    phi[1] =  xi[0];
    phi[2] =  xi[1];
    
    //(linha,coluna)
    dphi(0,0) = -1.; //dphi[0]/dx
    dphi(1,0) = -1.; //dphi[0]/dy
    dphi(0,1) =  1.; //dphi[1]/dx
    dphi(1,1) =  0.; //dphi[1]/dy
    dphi(0,2) =  0.; //dphi[2]/dx
    dphi(1,2) =  1.; //dphi[2]/dy

    if (orders[nf-1] == 2) {
      
        phi[3] = 4.*phi[0]*phi[1];
        dphi(0,3) = 4.*dphi(0,0)*phi[1]+4.*dphi(0,1)*phi[0]; //dphi[3]/dx
        dphi(1,3) = 4.*dphi(1,0)*phi[1]+4.*dphi(1,1)*phi[0]; //dphi[3]/dy
        
        phi[4] = 4.*phi[1]*phi[2];
        dphi(0,4) = 4.*dphi(0,1)*phi[2]+4.*dphi(0,2)*phi[1]; //dphi[4]/dx
        dphi(1,4) = 4.*dphi(1,1)*phi[2]+4.*dphi(1,2)*phi[1]; //dphi[4]/dy
        
        phi[5] = 4.*phi[2]*phi[0];
        dphi(0,5) = 4.*dphi(0,2)*phi[0]+4.*dphi(0,0)*phi[2]; //dphi[4]/dx
        dphi(1,5) = 4.*dphi(1,2)*phi[0]+4.*dphi(1,0)*phi[2]; //dphi[4]/dy
      
       /* std::cout << "ShapeTriangle::Shape, only implemented until order = 2" << std::endl;
        DebugStop(); */
    }
    
    // std::cout << "phi = " << phi << std::endl;
    // std::cout << "dphi = " << dphi << std::endl;

    /*std::cout << "Please implement me\n";
    DebugStop();*/
    
    
}

/// returns the number of shape functions associated with a side
int ShapeTriangle::NShapeFunctions(int side, int order){
    switch(side) {
        case 0:
        case 1:
        case 2:
            return 1;
        case 3:
        case 4:
        case 5:
            return order-1;
        case 6:
            return 0;
    }
    
    DebugStop();
    std::cout << "ShapeTriangle::NShapeFunctions, bad parameter side " << std::endl;
    return 0;
}

/// returns the total number of shape functions
int ShapeTriangle::NShapeFunctions(VecInt &orders){
    
    int res=3;
    for(int in=3; in<orders.size(); in++) {
        res += NShapeFunctions(in, orders[in]);
    }
    
    return res;
    
}
