//
// Created by luhy on 4/19/25.
//

#include <iostream>
#include "SegmentMerger.h"
#include <algorithm>

void SegmentMerger::addCollection(const PointCollection &points) {
    if(points.empty())
    {
        return;
    }

    if(isRangeCovered(points))
    {
        std::cout<<"Range is Covered by existing range"<<std::endl;
        return;
    }

    if(isRangeCoveringAllExisting(points))
    {
        std::cout<<"Existing Range is all Covered by new range"<<std::endl;
        handleCoveringCollection(points);
        return;
    }

    handlePartialOverlap(points);
}

void SegmentMerger::handlePartialOverlap(const PointCollection &points)
{
    PointCollection new_points;
    for (const auto p:points) {
        if (!isPointCovered(p))
        {
            std::cout<<p.x<<"->keep ";
            new_points.emplace_back(p);
        }
        else
        {
            std::cout<<p.x<<"->discard";
        }
    }
    std::cout<<std::endl;

    if(!new_points.empty())
    {
        std::cout<<"New point to add: ";
        for(const auto&p :new_points) std::cout<<p.x<<" ";
        std::cout<<std::endl;

        for (const auto &new_point: new_points) {
            merged_points.insert(
                    std::upper_bound(merged_points.begin(), merged_points.end(), new_points.front()),
                    new_point);
        }
    }

    coverd_ranges.emplace_back(points.front().x,points.back().x);
    mergeCoveredRanges();

}

void SegmentMerger::handleCoveringCollection(const PointCollection& points)
{
    PointCollection new_points;

    for (const auto&p:points)
    {
        if(p.x <coverd_ranges.front().first)
        {
            new_points.push_back(p);
        }
    }
    new_points.insert(new_points.end(),merged_points.begin(),merged_points.end());

    for (const auto&p:points)
    {
        if((p.x>=coverd_ranges.front().first)&&(p.x<=coverd_ranges.back().second)&& !isPointCovered(p))
        {
            new_points.insert(std::upper_bound(new_points.begin(),new_points.end(),p),p);
        }
    }

    for (const auto&p:points)
    {
        if(p.x>coverd_ranges.back().second)
        {
            new_points.emplace_back(p);
        }
    }
    merged_points = std::move(new_points);
    coverd_ranges.emplace_back(points.front().x,points.back().x);
    mergeCoveredRanges();
}

bool SegmentMerger::isPointCovered(const Point& point) const
{
    return std::any_of(coverd_ranges.begin(), coverd_ranges.end(),
                       [point](const auto &range) { return point.x >= range.first && point.x <= range.second; });
}

bool SegmentMerger::isRangeCovered(const PointCollection& points) const
{
    return std::any_of(coverd_ranges.begin(),coverd_ranges.end(),[points](const auto& range) {
        return points.front().x>=range.first&&points.back().x<=range.second;});

}

bool SegmentMerger::isRangeCoveringAllExisting(const PointCollection &points) const {
    if(coverd_ranges.empty())
    {
        return false;
    }
    return ((points.front().x < coverd_ranges.front().first) && (points.back().x > coverd_ranges.back().second));
}


void SegmentMerger::mergeCoveredRanges()
{
    if(coverd_ranges.empty())
    {
        return;
    }

    std::sort(coverd_ranges.begin(),coverd_ranges.end());

    std::vector<std::pair<double,double>> merged;
    merged.emplace_back(coverd_ranges[0]);

    for(auto i{1};i<coverd_ranges.size();++i)
    {
        if(coverd_ranges[i].first<=merged.back().second)//has overlap
        {
            merged.back().second = std::max(coverd_ranges[i].second,merged.back().second);
        }
        else
        {
            merged.emplace_back(coverd_ranges[i]);
        }
    }
    coverd_ranges = std::move(merged);

}


PointCollection SegmentMerger::getMergedPoint() const {
    for(auto &p:merged_points)
    {
        std::cout<<p.x<<" ";
    }
    std::cout<<std::endl;
    return merged_points;
}

