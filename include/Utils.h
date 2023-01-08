/**
 * File with helper functions globally used.
 */

#ifndef FEUP_AED2_UTILS_H
#define FEUP_AED2_UTILS_H

#include "Airport.h"

#include <cmath>
#include <iostream>

namespace utils {
    /**
     * Calculates the shortest distance between two points on a sphere using their latitude and longitude.
     * The result is not exact because the Earth is not a perfect sphere so the radius at the poles is different than the equator.
     *
     * @details Time Complexity: O(log(n))
     *
     * @param lat1 Latitude of the first point
     * @param lat2 Latitude of the second point
     * @param long1 Longitude of the first point
     * @param long2 Longitude of the second point
     * @return Distance between the two points in Kilometers.
     */
    double haversine(double lat1, double lat2, double long1, double long2);
    /**
     * Overloading of haversine.
     *
     * @details Uses airports information to get their GPS coordinates.
     * @details Time Complexity: O(log(n))
     *
     * @param source Source Airport's code.
     * @param target Target Airport´s code.
     * @return Distance between the airports in Kilometers.
     */
    double haversine(Airport &source, Airport &target);

    void clearScreen();
    
    // used in priority queue used in dijkstra algorithm
    struct CompareDistance {
        bool operator()(std::pair<std::string, double> const &n1, std::pair<std::string, double> const &n2) {
            return n1.second>n2.second;
        }
    };
}

#endif //FEUP_AED2_UTILS_H
