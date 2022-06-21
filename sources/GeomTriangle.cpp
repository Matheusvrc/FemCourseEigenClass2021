/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GeomTriangle.h"

GeomTriangle::GeomTriangle() {
}

GeomTriangle::~GeomTriangle() {
}

GeomTriangle::GeomTriangle(const GeomTriangle &copy) {
    fNodeIndices = copy.fNodeIndices;

}

GeomTriangle& GeomTriangle::operator=(const GeomTriangle& copy) {
    fNodeIndices = copy.fNodeIndices;

    return *this;
}

void GeomTriangle::Shape(const VecDouble& xi, VecDouble& phi, MatrixDouble& dphi) {
    if(xi.size() != Dimension || phi.size() != nCorners || dphi.rows() != Dimension || dphi.cols() != nCorners) DebugStop();
    // Linear order

    phi.resize(3);
    dphi.resize(2, 3);
    
    double qsi = xi[0];
    double eta = xi[1];

    phi[0] =  1. - qsi - eta; //xi[0]=x e xi[1]=y
    phi[1] =  qsi;
    phi[2] =  eta;
    
    //(linha,coluna)
    dphi(0,0) = -1.; //dphi[0]/dx
    dphi(1,0) = -1.; //dphi[0]/dy
    dphi(0,1) =  1.; //dphi[1]/dx
    dphi(1,1) =  0.; //dphi[1]/dy
    dphi(0,2) =  0.; //dphi[2]/dx
    dphi(1,2) =  1.; //dphi[2]/dy

   
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    if(xi.size() != Dimension || phi.size() != nCorners || dphi.rows() != Dimension || dphi.cols() != nCorners) DebugStop();
}

void GeomTriangle::X(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x) {
    if(xi.size() != Dimension) DebugStop();
    if(x.size() < NodeCo.rows()) DebugStop();
    if(NodeCo.cols() != nCorners) DebugStop();
    
    VecDouble phi(nCorners);
    MatrixDouble dphi (Dimension,nCorners);
    Shape(xi,phi,dphi);
    x.setZero();

    int nrow = NodeCo.rows();
    int ncol = NodeCo.cols();

    for (int i=0; i < nrow; i++){
        for (int j=0; j < ncol; j++){
            x[i] += phi[j]*NodeCo(i,j);
            }
    
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    // DebugStop();
    }

    // int nrow = NodeCo.rows();
    // int ncol = NodeCo.cols();

    // for (int i=0; i < nrow; i++){
    //     for (int j=0; j < ncol; j++){
    //         x[i] += NodeCo(i,j) * phi[j];
    //     }
    // }
    
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
}

void GeomTriangle::GradX(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x, MatrixDouble &gradx) {
    if(xi.size() != Dimension) DebugStop();
    if(x.size() != NodeCo.rows()) DebugStop();
    if(NodeCo.cols() != nCorners) DebugStop();

    int nrow = NodeCo.rows();
    int ncol = NodeCo.cols();

    gradx.resize(nrow, 2);
    gradx.setZero();
    // x.resize(2);
    x.setZero();
    
    VecDouble phi(nCorners);
    MatrixDouble dphi(Dimension, nCorners);
    Shape(xi, phi, dphi);

    // int npoints = NodeCo.cols(); // pontos
    // int ndirections = NodeCo.rows(); // direções x, y e z

    for (int i = 0; i < nCorners; i++) {
        for (int j = 0; j < Dimension; j++) {
            x[j] += NodeCo(j,i) * phi[i];
            gradx(j, 0) += NodeCo(j, i) * dphi(0, i);
            gradx(j, 1) += NodeCo(j, i) * dphi(1, i);
           
            // std::cout << "NodeCo: \n" << NodeCo << std::endl;
            // std::cout << "GradX: \n" << gradx << std::endl;
            }
    
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    }
}

void GeomTriangle::SetNodes(const VecInt &nodes) {
    if(nodes.size() != nCorners) DebugStop();
    fNodeIndices = nodes;
}

void GeomTriangle::GetNodes(VecInt &nodes) const  {
    nodes = fNodeIndices;
}

int GeomTriangle::NodeIndex(int node) const {
    return fNodeIndices[node];
}

int GeomTriangle::NumNodes() {
    return nCorners;
}

GeoElementSide GeomTriangle::Neighbour(int side)  const {
    return fNeighbours[side];
}

void GeomTriangle::SetNeighbour(int side, const GeoElementSide &neighbour) {
    fNeighbours[side] = neighbour;
}
