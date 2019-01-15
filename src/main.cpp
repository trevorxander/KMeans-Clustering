//
//  main.cpp
//  KMeans Clustering
//
//  Created by Trevor Xander on 11/8/18.
//  Copyright © 2018 Trevor Xander. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "KMeans.hpp"


using ImageArray = std::vector<std::vector <int>>;
int main(int argc, const char * argv[]) {
    
    try{

        int clusterCount;
        std:: cout << "Enter the number of cluster (K): ";
        std::cin >> clusterCount;
        
        std::string pointFileLoc = argv[1];
        auto clusteredPoints = KMeans::readPoints(pointFileLoc, clusterCount, std::cout);
        
        std::ofstream outFile (argv[2]);
        for (auto it = clusteredPoints.begin(); it != clusteredPoints.end(); ++it) {
            outFile << it->X << " " << it->Y <<" " << it->centroidLabel << "\n";
            
        }
        outFile.close();
        
    }
    catch (std::out_of_range e) {
        std::cerr << "Enter correct arguments\n";
    }
    catch (std::ifstream::failure e){
        std::cerr << "Could not open/read file\n";
    }
    catch (std::ofstream::failure e){
        std::cerr << "Could not open/wrote file\n";
    }
    
    return 0;
    
}
