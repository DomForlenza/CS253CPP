//  EuclideanL2.cpp
//  Created by Dominick Forlenza on 3/21/16.


#include "EuclideanL2.h"
#include "pa.h"
#include "PoseDisplay.h"
#include "Point3D.h"
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

vector<vector<double>> EuclideanL2::EuclideanL2_Distance(vector<vector<Point3D>>& poses1, vector<vector<Point3D>>& poses2) {
    
    double aX = 0.0;
    double aY = 0.0;
    double aZ = 0.0;
    double bX = 0.0;
    double bY = 0.0;
    double bZ = 0.0;
    double distance = 0.0;
    double distanceTotal = 0.0;
    double sq_distance = 0.0;
    vector<Point3D> vectorA;
    vector<Point3D> vectorB;
    vector<double> distance_line;
    vector<vector<double>> distances;
    Point3D pointA;
    Point3D pointB;
    unsigned int dist_count = 0;
    
    /* GET POSES IN ACTION FILE */
    for (unsigned int i = 0; i < poses1.size(); i++) {
        
        vectorA = poses1[i];
        
        /* GET POSES IN TARGET FILE */
        for (unsigned int k = 0; k < poses2.size(); k++) {
            
            vectorB = poses2[k];
            
            for (unsigned int m = 0; m < vectorB.size(); m++) {
                
                pointA = vectorA[m];
                
                aX = pointA.X();
                aY = pointA.Y();
                aZ = pointA.Z();
                
                pointB = vectorB[m];
                
                bX = pointB.X();
                bY = pointB.Y();
                bZ = pointB.Z();
                
                dist_count++;
                
                double x_pow = pow((aX - bX), 2);
                double y_pow = pow((aY - bY), 2);
                double z_pow = pow((aZ - bZ), 2);
                
                // Euclidean distance between points A and B
                distance = x_pow + y_pow + z_pow;
                distance = sqrt(distance);
                
                sq_distance = pow(distance, 2); // Square for L2 Norm
                
                // Total distance
                distanceTotal += sq_distance;
                
                // End of pose - move to next
                if (dist_count == 25) {
                    
                    distanceTotal = sqrt(distanceTotal); // Sqrt for L2 Norm
                    
                    // Push total distance between poses onto vector
                    distance_line.push_back(distanceTotal);
                    
                    // Reset variables
                    distanceTotal = 0.0;
                    dist_count = 0;
                }
            }
        }
        
        // Push into 2D vector
        distances.push_back(distance_line);
        distance_line.clear();
    }
    
     // Vector debug
     //cout << "File size: " << poses2.size() << endl;
     //cout << "Vector size: " << distances.size() << endl;
    
     /* DEBUG
     for (unsigned int i = 0; i < distances.size(); i++) {
     for (unsigned int j = 0; j < distances[i].size(); j++) {
     cout << distances[i][j] << " ";
     }
     cout << endl;
     }
     */
    
    return distances;
}

double EuclideanL2::dynamic_time_warp(vector<vector<double>> d_vector) {
    
    vector<vector<double>> w_vector;
    vector<double> lastRow;
    vector<double> prevRow;
    vector<double> newRow;
    vector<double> w_row;
    vector<double> min_vector;
    double w_column = 0.0;
    double d_column = 0.0;
    double minimum_last_row = 0.0;
    double total = 0.0;
    double minimum = 0.0;
    
    w_vector.push_back(d_vector[0]);
    
    /* GET ROW AND COLUMN */
    for (unsigned int i = 0; i < d_vector.size() - 1; i++) {
        for (unsigned int j = 0; j < w_vector[i].size(); j++) {
            
            d_column = d_vector[i + 1][j]; // D[row][col]
            newRow.push_back(d_column);
            
            w_column = w_vector[i][j]; // W[row - 1][col]
            prevRow.push_back(w_column);
        }
        
        // Set new total and create row
        for (unsigned int k = 0; k < prevRow.size(); k++) {
            
            // Store into vector to compare values from 0 to current j
            min_vector.push_back(prevRow[k]);
            
            minimum = *min_element(min_vector.begin(), min_vector.end());
            
            // Add minimum of W[i -1][k] to next row j values
            total = (newRow[k] + minimum);
            w_row.push_back(total);
        }
        
        // Push row into W
        w_vector.push_back(w_row);
        newRow.clear();
        prevRow.clear();
        w_row.clear();
        min_vector.clear();
    }
    
    // Set last row vector and print minimum value of all
    lastRow = w_vector.back();
    minimum_last_row = *min_element(lastRow.begin(), lastRow.end());

    return minimum_last_row;
}
