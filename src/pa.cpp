//  pa.cpp
//  Created by Dominick Forlenza

#include "pa.h"
#include "PoseDisplay.h"
#include "Point3D.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;


bool pa::readFile(ifstream& inFile) {
    
        string lineString;
        double xAvg = xAverage();
        double yAvg = yAverage();
        double zAvg = zAverage();
        int lineNumber = 0;
        point_vector.reserve(25);
        double scale = totalScale();
    
        while (getline(inFile, lineString)) {
            
            lineNumber++;

            // Parse line
            istringstream stream(lineString);

             while (stream >> x >> y >> z || !stream.eof()) {
                 
                    // Check for non doubles or ints
                    if (!stream) {
                        cerr << "Error on line " << lineNumber << ": Data not recognized (not double or int)." << endl;
                        return false;
                    }

                    // Catch divide by zero case
                    if (scale == -1) {
                        cerr << "Error on line " << lineNumber << ": Attempting to divide by zero." << endl;
                        return false;
                    }
                 
                    // Handle blank line in file
                    if (lineString.empty() && !stream.eof()) {
                        cerr << "Error on line " << lineNumber << ": Blank line found in file." << endl;
                        return false;
                    }

                    // Shift figure to the middle
                    x = (x - xAvg);
                    y = (y - yAvg);
                    z = (z - zAvg);
                 
                    // Create Point3D object
                    // Second normalization step
                    Point3D point = Point3D((x * scale), (y * scale), (z * scale));
                
                    // Add Point3D object to vector
                    point_vector.push_back(point);
                 
                    // Print for debug
                    // cout << "Vector size: " << point_vector.size() << endl;
                    // cout << "End of vector: " << point_vector.back() << endl;
			
                    // Wrong number of data points on line
                    if (point_vector.size() != 25 && stream.tellg() == -1) {
                        cerr << "Error on line " << lineNumber << ": Incorrect number of data points on line." << endl;
                        return false;
                    }

                    // Pass vector of 25 points at a time
                    // Store into vector of Point3D vectors
                    if (point_vector.size() == 25) {
                        vectors.push_back(point_vector);
                        point_vector.clear();
                        continue;
                    }
              }
        }
        return true;
}

bool pa::readFirstThree(std::ifstream& inFile) {
    
    string line;
    int lineNumber = 0;
    
        // Get line and read first three points
        while (getline(inFile, line)) {
            
            lineNumber++;
            
            istringstream threeStream(line);
            
            // Handle blank line in file
            if (line.empty() && !threeStream.eof()) {
                cerr << "Error on line " << lineNumber << ": Blank line found in file." << endl;
                return false;
            }
            
            // x
            if (!(threeStream >> x)) {
                cerr << "Error on line " << lineNumber << ": Data not recognized as valid input." << endl;
                return false;
            }
            
            // Debug x
           // cout << "X: " << x << endl;
            
            xVector.push_back(x);
            
            // Debug x vector
           // cout << "X Vector: " << xVector.back() << endl;
            
            // y
            if (!(threeStream >> y)) {
                cerr << "Error on line " << lineNumber << ": Data not recognized as valid input." << endl;
                return false;
            }
            
            // Debug y
           // cout << "Y: " << y << endl;
            
            yVector.push_back(y);
            
            // Debug y vector
           // cout << "Y Vector: " << yVector.back() << endl;
            
            // z
            if (!(threeStream >> z)) {
                cerr << "Error on line " << lineNumber << ": Data not recognized as valid input." << endl;
                return false;
            }
            
            // Debug z
           // cout << "Z: " << z << endl;
            
            zVector.push_back(z);
            
            // Debug z vector
           // cout << "Z Vector: " << zVector.back() << endl;
        }

    return true;
}

bool pa::getAbsValues(ifstream& inFile) {
    
        string lineString;
        double xAvg = xAverage();
        double yAvg = yAverage();
        double zAvg = zAverage();
        int lineNumber = 0;
        int dataCount;
    
        while (getline(inFile, lineString)) {
            
            // Reset data counter
            dataCount = 0;
            
            lineNumber++;

            // Parse line
            istringstream stream(lineString);
            
            // Handle blank line in file
            if (lineString.empty() && !stream.eof()) {
                cerr << "Error on line " << lineNumber << ": Blank line found in file." << endl;
                return false;
            }
	   
            // Check for non doubles or ints
            if (!(stream >> x)) {
               cerr << "Error on line " << lineNumber << ": Data not recognized (not double or int)." << endl;
               return false;
            }

            x = (x - xAvg);
            dataCount++;
	        xAbsVector.push_back(fabs(x));

            // Check for non doubles or ints
            if (!(stream >> y)) {
               cerr << "Error on line " << lineNumber << ": Data not recognized (not double or int)." << endl;
               return false;
            }

            y = (y - yAvg);
            dataCount++;
	        yAbsVector.push_back(fabs(y));

            // Check for non doubles or ints
            if (!(stream >> z)) {
               cerr << "Error on line " << lineNumber << ": Data not recognized (not double or int)." << endl;
               return false;
            }

            z = (z - zAvg);
            dataCount++;
	        zAbsVector.push_back(fabs(z));

             while (stream >> x >> y >> z || !stream.eof()) {

                // Check for non doubles or ints
                if (!stream) {
                   cerr << "Error on line " << lineNumber << ": Data not recognized (not double or int)." << endl;
                   return false;
                }

                 // Get x absolute value
                 x = (x - xAvg);
                 dataCount++;
                 xAbsVector.push_back(fabs(x));
                 
                 // x vector debug
                 //cout << "x abs: " << xAbsVector.back() << endl;
                 
                 // Get y absolute value
                 y = (y - yAvg);
                 dataCount++;
                 yAbsVector.push_back(fabs(y));
                 
                 // y vector debug
                 //cout << "y abs: " << yAbsVector.back() << endl;

                 // Get z absolute value
                 z = (z - zAvg);
                 dataCount++;
                 zAbsVector.push_back(fabs(z));
                 
                 // z vector debug
                 //cout << "z abs: " << zAbsVector.back() << endl;
              }
            
              // Handle <75 or >75 data points on line
              if (dataCount != 75) {
                  cerr << "Error on line " << lineNumber << ": Expected 75 data points on line." << endl;
                  return false;
              }
        }
        return true;
}

// Compute average of x
double pa::xAverage() {
    
    double average = 0.0;
    double xSum = 0.0;
    int xCount = 0;
    
    vector<double>::iterator iter = xVector.begin();
    vector<double>::iterator end = xVector.end();
    
    for (; iter < end; iter++) {
        if (xVector.size() == 0) {
            cerr << "Error: No X data points." << endl;
            break;
        }
        xSum += *iter;
        xCount++;
    }
    
    // Debug sum of x
    //cout << "X Sum: " << xSum << endl;

    // Debug count variable
    //cout << "Number of x: " << xCount << endl;
    
    // Compute average
    average = (xSum / xCount);
    
    // Debug average
    //cout << "Average of x: " << average << endl;
    
    return average;
}

// Compute average of y
double pa::yAverage() {
    
    double average = 0.0;
    double ySum = 0.0;
    int yCount = 0;
    
    vector<double>::iterator iter = yVector.begin();
    vector<double>::iterator end = yVector.end();
    
    for (; iter < end; iter++) {
        if (yVector.size() == 0) {
            cerr << "Error: No X data points." << endl;
            break;
        }
        ySum += *iter;
        yCount++;
    }
    
    // Debug sum of y
    //cout << "Y Sum: " << ySum << endl;
    
    // Debug count variable
    //cout << "Number of y: " << yCount << endl;
    
    // Compute average
    average = (ySum / yCount);
    
    // Debug average
    //cout << "Average of y: " << average << endl;
    
    return average;
}

// Compute average of z
double pa::zAverage() {
    
    double average = 0.0;
    double zSum = 0.0;
    int zCount = 0;
    
    vector<double>::iterator iter = zVector.begin();
    vector<double>::iterator end = zVector.end();
    
    for (; iter < end; iter++) {
        if (zVector.size() == 0) {
            cerr << "Error: No X data points." << endl;
            break;
        }
        zSum += *iter;
        zCount++;
    }
    
    // Debug sum of z
    //cout << "Z Sum: " << zSum << endl;
    
    // Debug count variable
    //cout << "Number of z: " << zCount << endl;
    
    // Compute average
    average = (zSum / zCount);
    
    // Debug average
    //cout << "Average of z: " << average << endl;
    
    return average;
}

// X absolute value
double pa::xAbsMax() {
    
    double absValue = 0.0;
    
    xAverage();
    
    if (xAbsVector.size() == 0) {
        cerr << "Error: No x data to analyze maximum." << endl;
        return -1;
    }
    
    absValue = *max_element(xAbsVector.begin(), xAbsVector.end());
    
    // X absolute value debug
    //cout << "X Max: " << absValue << endl;
    
    return absValue;
    
}

// Y absolute value
double pa::yAbsMax() {
    
    double absValue = 0.0;
    
    yAverage();
    
    if (yAbsVector.size() == 0) {
        cerr << "Error: No y data to analyze maximum." << endl;
        return -1;
    }
    
    absValue = *max_element(yAbsVector.begin(), yAbsVector.end());
    
    // Y absolute value debug
    //cout << "Y Max: " << absValue << endl;
    
    return absValue;
}

// Z absolute value
double pa::zAbsMax() {
    
    double absValue = 0.0;
    
    zAverage();
    
    if (zAbsVector.size() == 0) {
        cerr << "Error: No z data to analyze maximum." << endl;
        return -1;
    }
    
    absValue = *max_element(zAbsVector.begin(), zAbsVector.end());
    
    // Z absolute value debug
    //cout << "Z Max: " << absValue << endl;
    
    return absValue;
}

// Get max of x, y, and z max
double pa::pointMax() {
    
    double total_max = 0.0;
    double first_total = 0.0;
    double xMax = xAbsMax();
    double yMax = yAbsMax();
    double zMax = zAbsMax();
    
    if (xMax > yMax) {
        first_total = xMax;
    }
    
    else if (yMax > xMax) {
        first_total = yMax;
    }
    
    if (first_total > zMax) {
        total_max = first_total;
    }
    else if (zMax > first_total) {
        total_max = zMax;
    }
    
    // Debug point max
    //cout << "Largest Abs Max: " << total_max << endl;
    
    return total_max;
}

// Scale for total max
double pa::totalScale() {
    
    double scale = 0.0;
    double max = pointMax();
    
    // Handle divide by zero
    if (max == 0) {
        return -1;
    }
    
    scale = (1.0 / max);
    
    // Debug scale
    //cout << "Scale: " << scale << endl;
    
    return scale;
}
