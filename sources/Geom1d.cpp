/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Geom1d.h"

Geom1d::Geom1d() {
}

Geom1d::~Geom1d() {
}

Geom1d::Geom1d(const Geom1d &copy) {
    fNodeIndices = copy.fNodeIndices;
}

Geom1d& Geom1d::operator=(const Geom1d& copy) {
    fNodeIndices = copy.fNodeIndices;
    return *this;
}

void Geom1d::Shape(const VecDouble &xi, VecDouble &phi, MatrixDouble &dphi) {
    
    /*funcoes de forma
    xi é o qsi (valor do ponto)
    "fi" é a funcao chapeu - precisamos de expressões para essas equações
    fi(0)=(1-xi)/2 e fi(1)=(1+xi)/2
    */

   if (phi.size() != 2) DebugStop();

    //xi é o ksi variando de -1 a 1
    
    phi[0] = (1 - xi[0]) / 2.;
    phi[1] = (1 + xi[0]) / 2.;

    dphi(0,0) = -0.5;
    dphi(1,0) = 0.5;

}

void Geom1d::X(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x) {
    /*
    VecDouble phi(2);
    MatrixDouble dphi (2,1); (row, col)
    Shape(xi,phi,dphi);
    */

    VecDouble phi(2);
    MatrixDouble dphi (2,1);
    Shape(xi,phi,dphi);

    int nrow = NodeCo.rows();
    int ncol = NodeCo.cols();

    for (int i=1; i < nCorners; i++){
        for (int j=0; j < nrow; j++){
            x[j] += NodeCo(j,i) * phi[1];
        }
    }

    //coordenadas
}

void Geom1d::GradX(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x, MatrixDouble &gradx) {
    
    VecDouble phi(2);
    MatrixDouble dphi (2,1);
    Shape(xi,phi,dphi);

    // Novas definições:
    int npoints = NodeCo.cols(); // pontos
    int ndirections = NodeCo.rows(); // direções x, y e z

    gradx.resize(ndirections,1);
    gradx.fill(0.);

    for(int i=0; i<ndirections; i++){
        for(int j=0; j<npoints; j++){
            x[i] += NodeCo(i,j) * phi[j]; // coordenada dos nós * função em cada nó
            gradx(i,0) += NodeCo(i,j) * dphi(j,0); //phi relaciona-se com o nº de ptos = j
        }  
    }
    //std::cout << "GradX: \n" << gradx << std::endl;
    //std::cout << "NodeCo: \n" << NodeCo << std::endl;
}

void Geom1d::SetNodes(const VecInt &nodes) {
    if(nodes.rows() != 2) DebugStop();
    fNodeIndices = nodes;
}

void Geom1d::GetNodes(VecInt &nodes) const {
    nodes = fNodeIndices;
}

int Geom1d::NodeIndex(int node) const {
    if(node<0 || node > 2) DebugStop();
    return fNodeIndices[node];
}

int Geom1d::NumNodes(){
    return nCorners;    
}

GeoElementSide Geom1d::Neighbour(int side) const{
    if(side <0 || side>2) DebugStop();
    return fNeighbours[side];
}

void Geom1d::SetNeighbour(int side, const GeoElementSide &neighbour) {
    if(side < 0 || side > 2) DebugStop();
    fNeighbours[side]=neighbour;
}
