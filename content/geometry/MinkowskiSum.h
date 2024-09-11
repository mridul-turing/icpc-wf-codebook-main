/**
 * Author: Tamajit
 * Description: computing the distance between two convex polygons (or simply checking whether they intersect) 
 * computing the distance between two convex polygons 
 * If we reflect Q through the point (0,0) obtaining polygon -Q, 
 * the problem boils down to finding the smallest distance between a point in (P+(-Q)) and (0,0).
 */
#pragma once
#include "Point.h"
void reorder_polygon(vector<Point<ll>> & P){
	size_t pos = 0;
	for(size_t i = 1; i < P.size(); i++)
		if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) pos = i;
	rotate(P.begin(), P.begin() + pos, P.end());
}
vector<Point<ll>> minkowski(vector<Point<ll>> P, vector<Point<ll>> Q){
	reorder_polygon(P); reorder_polygon(Q);
	P.push_back(P[0]); P.push_back(P[1]);
	Q.push_back(Q[0]); Q.push_back(Q[1]);
	vector<Point<ll>> result;
	size_t i = 0, j = 0;
	while (i < sz(P) - 2 || j < sz(Q) - 2){
		result.push_back(P[i] + Q[j]);
		int s = sgn((P[i + 1]-P[i]).cross(Q[j + 1]-Q[j]));
		if (s >= 0) ++i; if (s <= 0) ++j;}
	return result;
}
