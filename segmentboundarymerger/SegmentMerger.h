//
// Created by luhy on 4/19/25.
//

#ifndef SEGMENTBOUNDARYMERGER_SEGMENTMERGER_H
#define SEGMENTBOUNDARYMERGER_SEGMENTMERGER_H

#include <vector>

struct Point {
    double x;

    Point(double x) : x(x) {}

    bool operator<(const Point &other) const { return x < other.x; }
};

using PointCollection = std::vector<Point>;
class SegmentMerger {
public:
    void addCollection(const PointCollection &points);

    PointCollection getMergedPoint() const;

private:
    PointCollection merged_points;
    std::vector<std::pair<double,double>> coverd_ranges;
    bool isPointCovered(const Point& point) const;
    bool isRangeCovered(const PointCollection& points) const;
    bool isRangeCoveringAllExisting(const PointCollection& points) const;
    void handlePartialOverlap(const PointCollection& points);
    void handleCoveringCollection(const PointCollection& points);
    void mergeCoveredRanges();
};


#endif //SEGMENTBOUNDARYMERGER_SEGMENTMERGER_H
