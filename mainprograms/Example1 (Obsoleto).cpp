#include <iostream>
#include "GeoMesh.h"
#include "GeoElementTemplate.h"
#include "Geom1d.h"
#include "VTKGeoMesh.h"
#include "CompMesh.h"
#include "Poisson.h"
#include "Analysis.h"
#include "PostProcess.h"
#include "Geom0d.h"

using namespace std;

int main() {
       //Creating a Geometric Mesh
       int nElements = 4; //nElements = nNodes-1
       int nNodes = nElements + 1;
       

       GeoMesh *gmesh = new GeoMesh();
       gmesh->SetDimension(1); //1D
       gmesh->SetNumNodes(nNodes);
       gmesh->SetNumElements(nElements);

       VecDouble coord(3); //vetor de coordenadas com x, y e z
       coord[0] = 0.0; //(x)
       coord[1] = 0.0; //(y)
       coord[2] = 0.0; //(z)
       gmesh->Node(0).SetCo(coord);

        double deltaX = 1. / nElements; //comprimento do elemento (h no livro do Becker)
        double deltaY = 0.0;

        /* Delta x e Delta y são as coordenadas que compõe o elemento em 'x' e 'y'.
        O elemento pode ser curvo, inclinado ... */

        int matid = 1; //material

        for (int iEl = 0; iEl < nElements; iEl++) {

            coord[0] = deltaX*(iEl+1); //(multiplica o tamanho de cada elemento pela coordenada inicial)
            coord[1] = deltaY*(iEl+1); //(y)
            gmesh->Node(iEl+1).SetCo(coord); //gravando as coordenadas no vetor Node

            VecInt nodes(2); //criado um VecInt nome nodes com 2 espaços de memória
            nodes[0] = iEl;
            nodes[1] = iEl + 1;
            GeoElement *gel = new GeoElementTemplate<Geom1d>(nodes, matid, gmesh, iEl);
            gmesh->SetElement(iEl, gel);
           }

        //Inserindo os dois pontos de extremidade
        int matIdBC = 2;
        VecInt  nIndex(1);

        //Primeiro ponto
        nIndex[0] = 0;
        GeoElement *point1 = new GeoElementTemplate<Geom0d>(nIndex, matIdBC, gmesh, nElements);
        gmesh->SetElement(nElements, point1);

        //Ultimo ponto
        nIndex[0] = nNodes-1;
        GeoElement *point2 = new GeoElementTemplate<Geom0d>(nIndex, matIdBC, gmesh, nElements+1);
        gmesh->SetElement(nElements+1, point2);

        gmesh->BuildConnectivity();
        gmesh->Print(cout);

        VTKGeoMesh printer;
        printer.PrintGMeshVTK(gmesh,"geoMesh.vtk");

        //Cria uma malha computacional
        CompMesh cmesh(gmesh); 

        //Estabelece um tipo de material
        MatrixDouble perm(1,1); //matriz 2x2
        perm(0,0)=1.;
        Poisson *mat = new Poisson(matid,perm); //perm é a cte 'k' na fórmula (permeabilidade)
        
        //Inserir o material de condição de contorno
        auto force = [](const VecDouble &x, VecDouble &res)
        {
            res[0] = x[0];
        };
        mat->SetForceFunction(force);
        MatrixDouble proj(1,1), val1(1,1), val2(1,1);
        proj.setZero();
        val1.setZero();
        val2.setZero();
        int bcType = 0;
        L2Projection *bc_point = new L2Projection(bcType, matIdBC, proj, val1, val2);
        vector<MathStatement *>mathvec={0,mat,bc_po}

        //Insere o material na malha computacional e cria o espaço de aproximação
        cmesh.SetMathStatement(matid,mat); //(indice qualquer do material, obj com nome 'mat' e tipo 'poisson')
        cmesh.AutoBuild();

        //Análise
        Analysis an(&cmesh); //'an' é o nome do obj análise
        an.RunSimulation();

    return 0;
}