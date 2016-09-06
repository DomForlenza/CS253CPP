// pa.h
// Created by Dominick Forlenza
// Header file for CS253 programming assignment pa class

#ifndef ____pa__
#define ____pa__

#include "PoseDisplay.h"
#include "Point3D.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>


class pa {

public:

    bool readFile(std::ifstream& inFile);
    bool readFirstThree(std::ifstream& inFile);
    bool getAbsValues(std::ifstream& inFile);
    inline double xAverage();
    inline double yAverage();
    inline double zAverage();
    inline double xAbsMax();
    inline double yAbsMax();
    inline double zAbsMax();
    inline double pointMax();
    inline double totalScale();
    
    std::vector<Point3D> point_vector;
    std::vector<vector<Point3D>> vectors;
    std::vector<double> xVector;
    std::vector<double> yVector;
    std::vector<double> zVector;
    std::vector<double> xAbsVector;
    std::vector<double> yAbsVector;
    std::vector<double> zAbsVector;
    
    double x;
    double y;
    double z;
    
};


#endif /* defined(____pa__) */
