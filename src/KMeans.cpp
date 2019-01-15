//
//  KMeans.cpp
//  KMeans Clustering
//
//  Created by Trevor Xander on 11/8/18.
//  Copyright © 2018 Trevor Xander. All rights reserved.
//

#include "KMeans.hpp"

int KMeans::K;
int KMeans::noOfRelabels;
std::vector<KMeans::Point> &KMeans::cluster (const std::vector<Point> &points, int clusterCount, int rows, int cols, std::ostream &out){
    static auto clusteredPoints = points;
    int iteration = 0;
    KMeans::K = clusterCount;
    KMeans::randomizeLabel (clusteredPoints);
    while (noOfRelabels != 0) {
        out << "Iteration no " << iteration <<"\n";
        KMeans::print(clusteredPoints, rows, cols, out);
        noOfRelabels = 0;
        auto centroids = KMeans::computeCentroids (clusteredPoints);
        for (auto it = clusteredPoints.begin(); it != clusteredPoints.end(); ++it){
            KMeans::relabelPoint ((*it), centroids);
        }
        ++iteration;
    }
    return clusteredPoints;
}

void KMeans::print (std::vector<Point> &points, int maxRows, int maxCols, std::ostream &out){
    for (int row = 0; row < maxRows; ++row){
        for (int col = 0; col < maxCols; ++col){
            for (auto it = points.begin(); it != points.end(); ++it){
                if (it->X == row && it->Y == col) out <<it->centroidLabel;
            }
            out <<" ";
        }
        out << "\n";
    }
}
std::vector<KMeans::Point> &KMeans::computeCentroids (std::vector<Point> &points){
    static std::vector<KMeans::Point> centroids;
    centroids.resize(K);
    double sumX, sumY, total;
    for (int centroid = 1; centroid <= K; ++centroid){
        sumX = 0;
        sumY = 0;
        total = 0;
        for (auto it = points.begin(); it != points.end(); ++it){
            if (it->centroidLabel == centroid){
                sumX += it->X;
                sumY += it->Y;
                ++total;
            }
        }
        if (total != 0){
            centroids[centroid - 1] ={sumX/total, //Xcoord
                sumY/total, //Ycoord
                centroid,   //Label
                0};        //Distance to centroid
        }
    }
    return centroids;
}

void KMeans::relabelPoint (Point &p, std::vector<KMeans::Point> &centroids){
    for (auto it = centroids.begin(); it != centroids.end(); ++it){
        double newDistance = p.distanceTo(*it);
        if (newDistance < p.distanceToCentroid){
            p.centroidLabel = it->centroidLabel;
            p.distanceToCentroid = p.distanceTo(*it);
            ++noOfRelabels;
        }
    }
}

void KMeans::randomizeLabel (std::vector <Point> &points){
    int label = 0;
    for (int front = 0, back = static_cast<int>(points.size() - 1); front - 1 < back; ++front, --back){
        points[front].centroidLabel = (label % K) + 1;
        ++noOfRelabels;
        points[back].centroidLabel = (++label % K) + 1;
        ++noOfRelabels;
        ++label;
    
    }

}
std::vector<KMeans::Point> & KMeans::readPoints(std::string pointFileLocation, int clusterCount, std::ostream &out){
    std::ifstream pointFile (pointFileLocation);
    static std::vector<KMeans::Point> points;
    int x, y;
    while (pointFile >> x >> y)
        points.push_back({static_cast<double>(x),static_cast<double>(y), INT_MAX, INT_MAX});
    
    return KMeans::cluster(points, clusterCount, 35, 40, out);
}


