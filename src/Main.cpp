//  Main.cpp
//  Created by Dominick Forlenza on 1/27/16.
//  Main driver program for pa.cpp and all distance measure programs.

#include "pa.h"
#include "PoseDisplay.h"
#include "Point3D.h"
#include "EuclideanL2.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;


int main (int argc, char* argv[]) {
    
    // Create pa class objects to read file
    pa read;
    
    // Variable declarations
    vector<double> L2_dist;
    
    if (argc > 2) {
        cerr << "Error: Too many command line arguments. Expected only one input file." << endl;
        return -1;
    }
    else if (argc < 2) {
        cerr << "Error: Too few command line arguments. Expected one input file." << endl;
        return -1;
    }
    
    /* NORMALIZE FILE */
    
    // Give file stream to readFirstThree
    ifstream inStream(argv[1]);
    
    // Can not open input file
    if (inStream.fail()) {
        cerr << "Error: Unable to read file." << endl;
        return -1;
    }
    
    // Read first three points or throw error
    if (!(read.readFirstThree(inStream))) {
        cerr << "Error: File not valid." << endl;
        return -1;
    }
    
    // Give file stream to getAbsValues
    ifstream inStream2(argv[1]);

    // Can not open input file
    if (inStream2.fail()) {
       cerr << "Error: Unable to read file." << endl;
       return -1;
    }

    // Get absolute value of data points infile
    if (!(read.getAbsValues(inStream2))) {
        cerr << "Error: Unable to read first point." << endl;
        return -1;
    }

    // Give file stream to readFile
    ifstream inStream3(argv[1]);
    
    // Can not open input file
    if (inStream3.fail()) {
       cerr << "Error: Unable to read file." << endl;
       return -1;
    }

    // Call readFile or throw error
    if (!(read.readFile(inStream3))) {
        cerr << "Error: Unable to complete read file function." << endl;
        return -1;
    }
    
    // Error - no data in vector to analyze in first file
    if (read.vectors.empty()) {
        cerr << "Error: No data to analyze distance in the first file." << endl;
        return -1;
    }
    
    
    /* COMPARE FILE TO ITSELF */
    unsigned int N = read.vectors.size();
    unsigned int start_count = 30;
    unsigned int mid = ((N /2) + 1);
    unsigned int stop_count = 30;
    
    EuclideanL2 *e = new EuclideanL2();
    vector<vector<Point3D>> action_vec;
    vector<vector<Point3D>> target_vec;
    vector<vector<double>> distances;
    vector<double> distance_vec;
    
    while (start_count <= mid) {
        
        // Get short action frames
        for (unsigned int i = 0; i < start_count; i++) {
            action_vec.push_back(read.vectors[i]);
        }
        
        // Get longer target frames
        for (unsigned int j = start_count; j < N; j++) {
            target_vec.push_back(read.vectors[j]);
        }
        
        distances = e->EuclideanL2_Distance(action_vec, target_vec);
        
        double dist = e->dynamic_time_warp(distances);
        
        double val = (dist / stop_count); // Divide value by number of frames
        
        distance_vec.push_back(val);
        
        // Clean up
        action_vec.clear();
        target_vec.clear();
        distances.clear();
        start_count++;
        stop_count++;
    }

    delete e; // Clean up EuclideanL2 object
    
    /* PRINT LENGTH OF FRAMES FOR SHORTEST DISTANCE */
    unsigned int stop_after_loop = 30;
    double minimum = *min_element(distance_vec.begin(), distance_vec.end());
    
    for (unsigned int i = 0; i < distance_vec.size(); i++) {
        if (distance_vec[i] == minimum) {
            cout << (stop_after_loop + i) << endl;
        }
    }
    
    return 0;
}
