//
//  KMeans.hpp
//  KMeans Clustering
//
//  Created by Trevor Xander on 11/8/18.
//  Copyright © 2018 Trevor Xander. All rights reserved.
//

#ifndef KMeans_hpp
#define KMeans_hpp

#include <fstream>
#include <set>
#include <ostream>
#include <vector>
#include <math.h>
#include <random>

class KMeans {
public:
    struct Point;
private:
    static int K;
    static int noOfRelabels;
    static std::vector<Point> &computeCentroids (std::vector<Point> &points);
    static void relabelPoint (Point &p, std::vector<Point> &centroids);
    static void randomizeLabel (std::vector <Point> &points);
    static void print (std::vector<Point> &points, int maxRows, int maxCols, std::ostream &out);

public:
    struct Point{
        double X;
        double Y;
        int centroidLabel;
        double distanceToCentroid;
       
        double distanceTo (Point p2){
            double distX, distY;
            distX = pow(X - p2.X, 2);
            distY =  pow(Y - p2.Y, 2);
        
            return (distX + distY);
        }
    };
    static std::vector<Point> &cluster (const std::vector<Point> &points, int rows, int cols, int K, std::ostream &out);
    

};

#endif /* KMeans_hpp */
