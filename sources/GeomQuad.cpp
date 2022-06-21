/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "GeomQuad.h"

GeomQuad::GeomQuad() {
}

GeomQuad::~GeomQuad() {
}

GeomQuad::GeomQuad(const GeomQuad &copy) {
    fNodeIndices = copy.fNodeIndices;
}

GeomQuad& GeomQuad::operator=(const GeomQuad& copy) {
    fNodeIndices = copy.fNodeIndices;
    return *this;
}

void GeomQuad::Shape(const VecDouble &xi, VecDouble &phi, MatrixDouble &dphi) {
    if(xi.size() != Dimension || phi.size() != nCorners || dphi.rows() != Dimension || dphi.cols() != nCorners) DebugStop();

    phi.resize(4);
    dphi.resize(2, 4);

    double qsi = xi[0];
    double eta = xi[1];
    
    //função chapéu    
    phi[0] = (1. - qsi) * (1. - eta) * (1./4.); //xi[0]=x e xi[1]=y
    phi[1] = (1. + qsi) * (1. - eta) * (1./4.);
    phi[2] = (1. + qsi) * (1. + eta) * (1./4.);
    phi[3] = (1. - qsi) * (1. + eta) * (1./4.);

    // std::cout << "qsi(x): \n" << qsi << std::endl;
    // std::cout << "eta(y): \n" << eta << std::endl;
    // std::cout << "phi: \n" << phi << std::endl;


    //(rows,columns)
    dphi(0,0) = (-1. + eta) * (1./4.); //dphi[0]/dx
    dphi(0,1) = (1. - eta) * (1./4.);  //dphi[1]/dx
    dphi(0,2) = (1. + eta) * (1./4.);  //dphi[2]/dx
    dphi(0,3) = (-1. - eta) * (1./4.); //dphi[3]/dx

    dphi(1,0) = (-1. + qsi) * (1./4.); //dphi[0]/dy
    dphi(1,1) = (-1. - qsi) * (1./4.); //dphi[1]/dy
    dphi(1,2) = (1. + qsi) * (1./4.);  //dphi[2]/dy
    dphi(1,3) = (1. - qsi) * (1./4.);  //dphi[3]/dy

    // std::cout << "dphi: \n" << dphi << std::endl;

    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    // DebugStop();
}

void GeomQuad::X(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x) {
    
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
        //    std::cout << "x: \n" << x << std::endl;
            }
    
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    // DebugStop();
    }
}

void GeomQuad::GradX(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x, MatrixDouble &gradx) {
         
    if(xi.size() != Dimension) DebugStop();
    if(x.size() < NodeCo.rows()) DebugStop();
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

    for (int i = 0; i < nCorners; i++) {
        for (int j = 0; j < Dimension; j++) {
            x[j] += NodeCo(j,i) * phi[i];
            gradx(j, 0) += NodeCo(j, i) * dphi(0, i);
            gradx(j, 1) += NodeCo(j, i) * dphi(1, i);
           
            // std::cout << "NodeCo: \n" << NodeCo << std::endl;
            // std::cout << "GradX: \n" << gradx << std::endl;
           
        }

     
    
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    // DebugStop();
}
}

void GeomQuad::SetNodes(const VecInt &nodes) {
    if(nodes.size() != nCorners) DebugStop();
    fNodeIndices = nodes;
}

void GeomQuad::GetNodes(VecInt &nodes) const{
    nodes = fNodeIndices;
}

int GeomQuad::NodeIndex(int node) const {
    return fNodeIndices[node];
}

int GeomQuad::NumNodes() {
    return nCorners;
}

GeoElementSide GeomQuad::Neighbour(int side) const {
    return fNeighbours[side];
}

void GeomQuad::SetNeighbour(int side, const GeoElementSide &neighbour) {
    fNeighbours[side] = neighbour;
}
