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
   
    phi[0] = ((1 - xi[0]) * (1 - xi[1])) / 4.; //xi[0]=x e xi[1]=y
    phi[1] = ((1 + xi[0]) * (1 - xi[1])) / 4.;
    phi[2] = ((1 + xi[0]) * (1 + xi[1])) / 4.;
    phi[3] = ((1 - xi[0]) * (1 + xi[1])) / 4.;


    //(rows,columns)
    dphi(0,0) = -0.25; //dphi[0]/dx
    dphi(0,1) = 0.25;  //dphi[1]/dx
    dphi(0,2) = 0.25;  //dphi[2]/dx
    dphi(0,3) = -0.25; //dphi[3]/dx

    dphi(1,0) = -0.25; //dphi[0]/dy
    dphi(1,1) = -0.25; //dphi[1]/dy
    dphi(1,2) = 0.25;  //dphi[2]/dy
    dphi(1,3) = 0.25;  //dphi[3]/dy

    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
   
    if(xi.size() != Dimension || phi.size() != nCorners || dphi.rows() != Dimension || dphi.cols() != nCorners) DebugStop();
    DebugStop();
}

void GeomQuad::X(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x) {
    
    VecDouble phi(4);
    MatrixDouble dphi (2,4);
    Shape(xi,phi,dphi);

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

    VecDouble phi(4);
    MatrixDouble dphi (2,4);
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
