//  EuclideanL2.h
//  Created by Dominick Forlenza on 3/21/16.

#ifndef ____EuclideanL2__
#define ____EuclideanL2__

#include "pa.h"
#include "PoseDisplay.h"
#include "Point3D.h"
#include <stdio.h>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

class EuclideanL2 {
    
public:
    
    // Get distance between poses - EUCLIDEAN(L2)
    vector<vector<double>> EuclideanL2_Distance(vector<vector<Point3D>>& poses1, vector<vector<Point3D>>& poses2);
    
    // Dynamic Time Warp
    double dynamic_time_warp(vector<vector<double>> d_vector);
};

#endif /* defined(____EuclideanL2__) */
