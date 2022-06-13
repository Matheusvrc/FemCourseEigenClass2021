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

    phi[0] = ((1 - xi[0]) * (1 - xi[1])) / 4.; //xi[0]=x e xi[1]=y
    phi[1] = ((1 + xi[0]) * (1 - xi[1])) / 4.;
    phi[2] = ((1 + xi[0]) * (1 + xi[1])) / 4.;
    phi[3] = ((1 - xi[0]) * (1 + xi[1])) / 4.;


    //(rows,columns)
    dphi(0,0) = (xi[1]-1.)/4.; //dphi[0]/dx
    dphi(0,1) = (1.-xi[1])/4.;  //dphi[1]/dx
    dphi(0,2) = (1.+xi[1])/4.;  //dphi[2]/dx
    dphi(0,3) = (-1.-xi[1])/4.; //dphi[3]/dx

    dphi(1,0) = (xi[0]-1.)/4.; //dphi[0]/dy
    dphi(1,1) = (-1.-xi[0])/4.; //dphi[1]/dy
    dphi(1,2) = (1.+xi[0])/4.;  //dphi[2]/dy
    dphi(1,3) = (1.-xi[0])/4.;  //dphi[3]/dy

    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
   
    if(xi.size() != Dimension || phi.size() != nCorners || dphi.rows() != Dimension || dphi.cols() != nCorners) DebugStop();
    DebugStop();
}

void GeomQuad::X(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x) {
    
    if(xi.size() != Dimension) DebugStop();
    if(x.size() != NodeCo.rows()) DebugStop();
    if(NodeCo.cols() != nCorners) DebugStop();

    VecDouble phi(nCorners);
    MatrixDouble dphi (Dimension,nCorners);
    Shape(xi,phi,dphi);
    x.setZero();

    int nrow = NodeCo.rows();
    int ncol = NodeCo.cols();

    for (int i=0; i < nrow; i++){
        for (int j=0; j < ncol; j++){
            x[i] += NodeCo(i,j) * phi[j];
            }
    
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    
    if(xi.size() != Dimension) DebugStop();
    if(x.size() < NodeCo.rows()) DebugStop();
    if(NodeCo.cols() != nCorners) DebugStop();
    DebugStop();
    }
}

void GeomQuad::GradX(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x, MatrixDouble &gradx) {
    
    //Como colocar uma variavel puxando a ordem de interpolação para phi?      

    VecDouble phi(nCorners);
    MatrixDouble dphi (Dimension,nCorners);
    Shape(xi,phi,dphi);
    x.setZero();

    int npoints = NodeCo.cols(); // pontos
    int ndirections = NodeCo.rows(); // direções x, y e z

    gradx.resize(ndirections,npoints);
    gradx.fill(0.);

    for(int i=0; i<ndirections; i++){
        for(int j=0; j<npoints; j++){
            x[i] += NodeCo(i,j) * phi[j]; // coordenada dos nós * função em cada nó
            gradx(i,0) += NodeCo(i,j) * dphi(0,i); //phi relaciona-se com o nº de ptos = j
            gradx(i,1) += NodeCo(i,j) * dphi(1,i);
        }  
    
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
   
    if(xi.size() != Dimension) DebugStop();
    if(x.size() != NodeCo.rows()) DebugStop();
    if(NodeCo.cols() != nCorners) DebugStop();
    DebugStop();
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
