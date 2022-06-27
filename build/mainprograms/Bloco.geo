// Gmsh project created on Fri Jun 24 21:31:32 2022
SetFactory("OpenCASCADE");
//+
Point(1) = {0, 0, 0, 0};
//+
Point(2) = {39, 0, 0, 0};
//+
Point(3) = {39, 19, 0, 0};
//+
Point(4) = {0, 19, 0, 0};
//+
Point(5) = {2.5, 2.5, 0, 0};
//+
Point(6) = {18.25, 2.5, 0, 0};
//+
Point(7) = {20.75, 2.5, 0, 0};
//+
Point(8) = {36.5, 2.5, 0, 0};
//+
Point(9) = {36.5, 16.5, 0, 0};
//+
Point(10) = {20.75, 16.5, 0, 0};
//+
Point(11) = {18.25, 16.5, 0, 0};
//+
Point(12) = {2.5, 16.5, 0, 0};
//+
Point(13) = {2.5, 0, 0, 0};
//+
Point(14) = {2.5, 19, 0, 0};
//+
Point(15) = {36.5, 19, 0, 0};
//+
Point(16) = {36.5, 0, 0, 0};
//+
Point(17) = {20.75, 0, 0, 0};
//+
Point(18) = {18.25, 0, 0, 0};
//+
Point(19) = {18.25, 19, 0, 0};
//+
Point(20) = {20.75, 19, 0, 0};
//+
Point(21) = {0, 2.5, 0, 0};
//+
Point(22) = {0, 16.5, 0, 0};
//+
Point(23) = {39, 16.5, 0, 0};
//+
Point(24) = {39, 2.5, 0, 0};

//+
Line(1) = {1, 13};
//+
Line(2) = {13, 18};
//+
Line(3) = {18, 17};
//+
Line(4) = {17, 16};
//+
Line(5) = {16, 2};
//+
Line(6) = {2, 24};
//+
Line(7) = {24, 23};
//+
Line(8) = {23, 3};
//+
Line(9) = {3, 15};
//+
Line(10) = {15, 20};
//+
Line(11) = {20, 19};
//+
Line(12) = {19, 14};
//+
Line(13) = {14, 4};
//+
Line(14) = {4, 22};
//+
Line(15) = {22, 21};
//+
Line(16) = {21, 1};
//+
Line(17) = {5, 6};
//+
Line(18) = {6, 11};
//+
Line(19) = {11, 12};
//+
Line(20) = {12, 5};
//+
Line(21) = {7, 8};
//+
Line(22) = {8, 9};
//+
Line(23) = {9, 10};
//+
Line(24) = {10, 7};
//+
Curve Loop(1) = {12, 13, 14, 15, 16, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
//+
Curve Loop(2) = {19, 20, 17, 18};
//+
Curve Loop(3) = {23, 24, 21, 22};
//+
Plane Surface(1) = {1, 2, 3};
//+
Physical Surface("Concreto", 1) = {1};
//+
Physical Curve("HotSurface", 2) = {2, 1, 3, 4, 5};
//+
Physical Curve("ColdSurface", 3) = {10, 9, 11, 12, 13};
//+
Physical Curve("Adiabático", 4) = {14, 15, 16, 20, 18, 24, 22, 8, 7, 6};
//+
Transfinite Curve {13, 1, 9, 5} = 5 Using Progression 1;
//+
Transfinite Curve {14, 8, 16, 6} = 5 Using Progression 1;
//+
Transfinite Curve {11, 3} = 5 Using Progression 1;
//+
Transfinite Curve {15, 20, 18, 24, 22, 7} = 14 Using Progression 1;
//+
Transfinite Curve {19, 17, 23, 21} = 10 Using Progression 1;
//+
Recombine Surface {1};
//+
Physical Curve("Adiabático", 4) += {19, 17, 21, 23};
