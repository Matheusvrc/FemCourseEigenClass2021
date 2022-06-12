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

   
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    if(xi.size() != Dimension || phi.size() != nCorners || dphi.rows() != Dimension || dphi.cols() != nCorners) DebugStop();
    DebugStop();
}

void GeomTriangle::X(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x) {
    
    VecDouble phi(3);
    MatrixDouble dphi (2,3);
    Shape(xi,phi,dphi);

    int nrow = NodeCo.rows();
    int ncol = NodeCo.cols();

    for (int i=0; i < nrow; i++){
        for (int j=0; j < ncol; j++){
            x[i] += NodeCo(i,j) * phi[j];
            }
    }
    
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    if(xi.size() != Dimension) DebugStop();
    if(x.size() != NodeCo.rows()) DebugStop();
    if(NodeCo.cols() != nCorners) DebugStop();
    DebugStop();
}

void GeomTriangle::GradX(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x, MatrixDouble &gradx) {
    
    VecDouble phi(3);
    MatrixDouble dphi (2,3);
    Shape(xi,phi,dphi);

    int npoints = NodeCo.cols(); // pontos
    int ndirections = NodeCo.rows(); // direções x, y e z

    gradx.resize(ndirections,1);
    gradx.fill(0.);

    for(int i=0; i<ndirections; i++){
        for(int j=0; j<npoints; j++){
            x[i] += NodeCo(i,j) * phi[j]; // coordenada dos nós * função em cada nó
            gradx(i,j) += NodeCo(i,j) * dphi(i,j); //phi relaciona-se com o nº de ptos = j
        }  
    
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    if(xi.size() != Dimension) DebugStop();
    if(x.size() != NodeCo.rows()) DebugStop();
    if(NodeCo.cols() != nCorners) DebugStop();
    DebugStop();
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
