#include <iostream>
#include "GeoMesh.h"
#include "GeoElementTemplate.h"
#include "Geom1d.h"
using namespace std;

int main() {
       //Creating a Geometric Mesh
       int nNodes = 2;
       int nElements = 1; //nElements = nNodes-1

       GeoMesh *gmesh = new GeoMesh();
       gmesh->SetDimension(1);
       gmesh->SetNumNodes(nNodes);
       gmesh->SetNumElements(nElements);

       VecDouble coord(2);
       coord[0] = 0.0; //(x)
       coord[1] = 0.0; //(y)
       gmesh->Node(0).SetCo(coord);

       coord[0] = 1.0; //(x)
       coord[1] = 0.0; //(y)
       gmesh->Node(1).SetCo(coord);

       int matid = 1;
       int elindex = 0;
       int element_id = 0;
       VecInt nodes(2);
       nodes[0] = 0;
       nodes[1] = 1;
       GeoElement *gel = new GeoElementTemplate<Geom1d>(nodes, matid, gmesh, elindex);
       gmesh->SetElement(element_id, gel);

       gmesh->BuildConnectivity();
       gmesh->Print(cout);

    return 0;
}