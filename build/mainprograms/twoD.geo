// Gmsh project created on Wed Jun 15 18:35:40 2022
SetFactory("OpenCASCADE");
//+
Point(1) = {0, 0, 0, 1.0};
//+
Extrude {1, 0, 0} {
  Point{1}; Layers{1}; Recombine;
}
//+
Extrude {0, 1, 0} {
  Curve{1}; Layers{1}; Recombine;
}
//+
Physical Surface("Concreto", 1) = {1};
//+
Physical Curve("Contorno", 2) = {4, 2, 1, 3};
