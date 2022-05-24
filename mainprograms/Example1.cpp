#include <iostream>
#include "GeoMesh.h"
#include "GeoElementTemplate.h"
#include "Geom1d.h"
#include "VTKGeoMesh.h"
#include "CompMesh.h"
#include "Poisson.h"
#include "Analysis.h"
#include "PostProcess.h"

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
        int a=1;

        //Insere o material na malha computacional e cria o espaço de aproximação
        cmesh.SetMathStatement(matid,mat); //(índice qualquer do material, obj com nome 'mat' e tipo 'poisson')
        cmesh.AutoBuild();

        //Análise
        Analysis an(&cmesh); //'an' é o nome do obj análise
        an.RunSimulation();

    return 0;
}