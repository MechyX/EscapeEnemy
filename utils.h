#include<bits/stdc++.h> 

#define COL 14
#define ROW 14

typedef unsigned int uint;
typedef std::pair<uint, uint> Pair;
typedef std::pair<double, std::pair<uint, uint>> pPair; 

bool aStarSearch(int grid[][COL], Pair src, Pair dest , std::stack<Pair>& path);

// A structure to hold the neccesary parameters 
struct cell{ 
	int parent_i, parent_j; 
	// f = g + h 
	double f, g, h; 
}; 



