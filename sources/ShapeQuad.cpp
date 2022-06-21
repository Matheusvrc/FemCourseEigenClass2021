//
//  ShapeQuad.cpp
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#include "Shape1d.h"
#include "ShapeQuad.h"

/// computes the shape functions in function of the coordinate in parameter space and orders of the shape functions (size of orders is number of sides of the element topology)
void ShapeQuad::Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, MatrixDouble &dphi){
    
    for (int i = 0; i < orders.size(); i++)
    {
        if (orders[i] < 0) {
            std::cout << "ShapeQuad::Shape: Invalid dimension for arguments: order\n";
            DebugStop();
        }
    }
    if (orders[0] > 1 || orders[1] > 1 || orders[2] > 1 || orders[3] > 1) {
        std::cout << "ShapeQuad::Shape: Invalid dimension for arguments: order\n";
        DebugStop();
    }

    auto nf = NShapeFunctions(orders);
    
    phi.resize(nf);
    dphi.resize(2,nf); //x e y

    //função chapéu    
    phi[0] = (1. - xi[0]) * (1. - xi[1]) * (1./4.); //xi[0]=x e xi[1]=y
    phi[1] = (1. + xi[0]) * (1. - xi[1]) * (1./4.);
    phi[2] = (1. + xi[0]) * (1. + xi[1]) * (1./4.);
    phi[3] = (1. - xi[0]) * (1. + xi[1]) * (1./4.);

    // std::cout << "phi: \n" << phi << std::endl;


    //(rows,columns)
    dphi(0,0) = (-1. + xi[1]) * (1./4.); //dphi[0]/dx
    dphi(0,1) = (1. - xi[1]) * (1./4.);  //dphi[1]/dx
    dphi(0,2) = (1. + xi[1]) * (1./4.);  //dphi[2]/dx
    dphi(0,3) = (-1. - xi[1]) * (1./4.); //dphi[3]/dx

    dphi(1,0) = (-1. + xi[0]) * (1./4.); //dphi[0]/dy
    dphi(1,1) = (-1. - xi[0]) * (1./4.); //dphi[1]/dy
    dphi(1,2) = (1. + xi[0]) * (1./4.);  //dphi[2]/dy
    dphi(1,3) = (1. - xi[0]) * (1./4.);  //dphi[3]/dy

    // std::cout << "dphi: \n" << dphi << std::endl;

    if (orders[nf-1] == 2) {
        if (nf==9){
            // phi[4] = 4. * phi[0] * phi[1];
            phi[4] = 4.* ((1. - xi[0]) * (1. - xi[1]) * (1./4.)) * ((1. + xi[0]) * (1. - xi[1]) * (1./4.));
            // dphi(0,4) = 4. * dphi(0,0) * phi[1] + 4. * phi[0] * dphi(0,1); //dphi[4]/dx
            dphi(0,4) = 4 * ((-1. + xi[1]) * (1./4.)) * ((1. + xi[0]) * (1. - xi[1]) * (1./4.)) + 4. * ((1. - xi[0]) * (1. - xi[1]) * (1./4.)) * ((1. - xi[1]) * (1./4.));
            // dphi(1,4) = 4. * dphi(1,0) * phi[1] + 4. * dphi(1,1) * phi[0]; //dphi[4]/dy
            dphi(1,4) = 4 * ((-1. + xi[0]) * (1./4.)) * ((1. + xi[0]) * (1. - xi[1]) * (1./4.)) + 4. * ((-1. - xi[0]) * (1./4.)) * ((1. - xi[0]) * (1. - xi[1]) * (1./4.));

            // phi[5] = 4. * phi[1] * phi[2];
            phi[5] = 4.* ((1. + xi[0]) * (1. - xi[1]) * (1./4.)) * (1. + xi[0]) * (1. + xi[1]) * (1./4.);
            // dphi(0,5) = 4. * dphi(0,1) * phi[2] + 4. * phi[1] * dphi(0,2); //dphi[5]/dx
            dphi(0,5) = 4. * ((1. - xi[1]) * (1./4.)) * ((1. + xi[0]) * (1. + xi[1]) * (1./4.)) + 4. * ((1. + xi[0]) * (1. - xi[1]) * (1./4.)) * ((1. + xi[1]) * (1./4.));
            // dphi(1,5) = 4. * dphi(1,1) * phi[2] + 4. * dphi(1,2) * phi[1]; //dphi[5]/dy
            dphi(1,5) = 4. * ((-1. - xi[0]) * (1./4.)) * ((1. + xi[0]) * (1. + xi[1]) * (1./4.)) + 4. * ((1. + xi[0]) * (1./4.)) * ((1. + xi[0]) * (1. - xi[1]) * (1./4.));

            // phi[6] = 4. * phi[2] * phi[3];
            phi[6] = 4. * ((1. + xi[0]) * (1. + xi[1]) * (1./4.)) * ((1. - xi[0]) * (1. + xi[1]) * (1./4.));
            // dphi(0,6) = 4. * dphi(0,2) * phi[3] + 4. * phi[2] * dphi(0,3); //dphi[6]/dx
            dphi(0,6) = 4. * ((1. + xi[1]) * (1./4.)) * ((1. - xi[0]) * (1. + xi[1]) * (1./4.)) + 4. * ((1. + xi[0]) * (1. + xi[1]) * (1./4.)) * ((-1. - xi[1]) * (1./4.));
            // dphi(1,6) = 4. * dphi(1,2) * phi[3] + 4. * dphi(1,3) * phi[2]; //dphi[6]/dy
            dphi(1,6) = 4. * ((1. + xi[0]) * (1./4.)) * ((1. - xi[0]) * (1. + xi[1]) * (1./4.)) + 4. * ((1. - xi[0]) * (1./4.)) * ((1. + xi[0]) * (1. + xi[1]) * (1./4.));

            // phi[7] = 4. * phi[3] * phi[0];
            phi[7] = 4. * ((1. - xi[0]) * (1. + xi[1]) * (1./4.)) * ((1. - xi[0]) * (1. - xi[1]) * (1./4.));
            // dphi(0,7) = 4. * dphi(0,3) * phi[0] + 4. * phi[3] * dphi(0,0); //dphi[7]/dx
            dphi(0,7) = 4. * ((-1. - xi[1]) * (1./4.)) * ((1. - xi[0]) * (1. - xi[1]) * (1./4.)) + 4. * ((1. - xi[0]) * (1. + xi[1]) * (1./4.)) * ((-1. + xi[1]) * (1./4.));
            // dphi(1,7) = 4. * dphi(1,3) * phi[0] + 4. * dphi(1,0) * phi[3]; //dphi[7]/dy
            dphi(1,7) = 4. * ((1. - xi[0]) * (1./4.)) * ((1. - xi[0]) * (1. - xi[1]) * (1./4.)) + 4. * ((-1. + xi[0]) * (1./4.)) * ((1. - xi[0]) * (1. + xi[1]) * (1./4.));

            // phi[8] = 16. * phi[0] * phi[2];
            phi[8] = 16. * ((1. - xi[0]) * (1. - xi[1]) * (1./4.)) * ((1. + xi[0]) * (1. + xi[1]) * (1./4.));
            // dphi(0,8) = 16. * dphi(0,0) * phi[2] + 16. * phi[0] * dphi(0,2); //dphi[8]/dx
            dphi(0,8) = 16. * ((-1. + xi[1]) * (1./4.)) * ((1. + xi[0]) * (1. + xi[1]) * (1./4.)) + 16. * ((1. - xi[0]) * (1. - xi[1]) * (1./4.)) * ((1. + xi[1]) * (1./4.));
            // dphi(1,8) = 16. * dphi(1,0) * phi[2] + 16. * dphi(1,2) * phi[0]; //dphi[8]/dy
            dphi(1,8) =16. * ((-1. + xi[0]) * (1./4.)) * ((1. + xi[0]) * (1. + xi[1]) * (1./4.)) + 16. * ((1. + xi[0]) * (1./4.)) * ((1. - xi[0]) * (1. - xi[1]) * (1./4.));

            // std::cout << "phi: \n" << phi << std::endl;
            // std::cout << "dphi: \n" << dphi << std::endl;

            
        /*std::cout << "ShapeQuad::Shape, only implemented until order = 2" << std::endl;
        DebugStop();*/
    }



   /* std::cout << "Please implement me\n";
    DebugStop();*/
    }
}

/// returns the number of shape functions associated with a side
int ShapeQuad::NShapeFunctions(int side, int order){
    if(order < 1 || order >2) DebugStop();
    if(side<4)
        return 1;//0 a 4
    else if(side<8)
        return (order-1);//6 a 14
    else if(side==8)
        return ((order-1)*(order-1));
    
    std::cout << "ShapeQuad::NShapeFunctions, bad parameter side " << side << std::endl;
    DebugStop();
    
    return 0;
}

/// returns the total number of shape functions
int ShapeQuad::NShapeFunctions(VecInt &orders){
    
    int res=4;
    for(int in=4; in<orders.size(); in++) {
        res += NShapeFunctions(in, orders[in]);
    }
    
    return res;
}
