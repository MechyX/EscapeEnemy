#include "utils.h"
using namespace std; 


bool isValid(int row, int col){ 
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL); 
} 

bool isUnBlocked(int grid[][COL], int row, int col) { 
	// Returns true if the cell is not blocked else false 
	if (grid[row][col] == 1) 
		return (true); 
	else
		return (false); 
} 

bool isDestination(int row, int col, Pair dest) { 
	if (row == dest.first && col == dest.second) 
		return (true); 
	else
		return (false); 
} 

double calculateHValue(int row, int col, Pair dest) { 
	return ((double)sqrt ((row-dest.first)*(row-dest.first) 
						+ (col-dest.second)*(col-dest.second))); 
} 

void tracePath(cell cellDetails[][COL], Pair dest ,stack<Pair>& Path){ 
	int row = dest.first; 
	int col = dest.second;  

	while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col )){ 
		Path.push (make_pair (row, col)); 
		int temp_row = cellDetails[row][col].parent_i; 
		int temp_col = cellDetails[row][col].parent_j; 
		row = temp_row; 
		col = temp_col; 
	} 

	Path.push (make_pair (row, col)); 
} 

bool aStarSearch(int grid[][COL], Pair src, Pair dest , stack<Pair>& path){ 
	// If the source is out of range 
	if (isValid (src.first, src.second) == false){ 
		cout <<"Source is invalid"<< endl; 
		return false; 
	} 

	// If the destination is out of range 
	if (isValid (dest.first, dest.second) == false){ 
		cout << "Destination is invalid"<< endl; 
		return false; 
	} 

	// Either the source or the destination is blocked 
	if (!isUnBlocked(grid, src.first, src.second) || !isUnBlocked(grid, dest.first, dest.second)) { 
		cout << "Source or the destination is blocked" << endl; 
		return false; 
	} 

	// If the destination cell is the same as source cell 
	if (isDestination(src.first, src.second, dest) == true) { 
		cout << "We are already at the destination" << endl;
		return true; 
	} 

	bool closedList[ROW][COL]; 
	memset(closedList, false, sizeof (closedList)); 

	// Declare a 2D array of structure to hold the details of that cell 
	cell cellDetails[ROW][COL]; 

	int i, j; 

	for (i=0; i<ROW; i++){ 
		for (j=0; j<COL; j++){ 
			cellDetails[i][j].f = FLT_MAX; 
			cellDetails[i][j].g = FLT_MAX; 
			cellDetails[i][j].h = FLT_MAX; 
			cellDetails[i][j].parent_i = -1; 
			cellDetails[i][j].parent_j = -1; 
		} 
	} 

	// Initialising the parameters of the starting node 
	i = src.first;
    j = src.second; 
	cellDetails[i][j].f = 0.0; 
	cellDetails[i][j].g = 0.0; 
	cellDetails[i][j].h = 0.0; 
	cellDetails[i][j].parent_i = i; 
	cellDetails[i][j].parent_j = j; 


	set<pPair> openList; 


	openList.insert(make_pair (0.0, make_pair (i, j))); 

	bool foundDest = false; 

	while (!openList.empty()){ 
		pPair p = *openList.begin(); 

		// Remove this vertex from the open list 
		openList.erase(openList.begin()); 

		// Add this vertex to the closed list 
		i = p.second.first; 
		j = p.second.second; 
		closedList[i][j] = true; 

    /* 
		Generating all the 4 successor of this cell 

			N 
			\   
			\  
	  W----Cell----E 
			\ 
			\ 
		    S 

		Cell-->Popped Cell (i, j) 
		N --> North	 (i-1, j) 
		S --> South	 (i+1, j) 
		E --> East	 (i, j+1) 
		W --> West   (i, j-1) 

    */

		// To store the 'g', 'h' and 'f' of the 8 successors 
		double gNew, hNew, fNew; 

		//----------- 1st Successor (North) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid(i-1, j) == true) { 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i-1, j, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i-1][j].parent_i = i; 
				cellDetails[i-1][j].parent_j = j;  
				tracePath (cellDetails, dest , path); 
				foundDest = true; 
				return true; 
			} 

			else if (closedList[i-1][j] == false && isUnBlocked(grid, i-1, j) == true) { 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue (i-1, j, dest); 
				fNew = gNew + hNew; 

			if (cellDetails[i-1][j].f == FLT_MAX || cellDetails[i-1][j].f > fNew) { 
					openList.insert( make_pair(fNew, make_pair(i-1, j))); 

					// Update the details of this cell 
					cellDetails[i-1][j].f = fNew; 
					cellDetails[i-1][j].g = gNew; 
					cellDetails[i-1][j].h = hNew; 
					cellDetails[i-1][j].parent_i = i; 
					cellDetails[i-1][j].parent_j = j; 
				} 
			} 
		} 

		//----------- 2nd Successor (South) ------------ 

		if (isValid(i+1, j) == true){ 
			if (isDestination(i+1, j, dest) == true){ 

				cellDetails[i+1][j].parent_i = i; 
				cellDetails[i+1][j].parent_j = j; 
				tracePath(cellDetails, dest, path); 
				foundDest = true; 
				return true; 
			} 

			else if (closedList[i+1][j] == false && isUnBlocked(grid, i+1, j) == true) { 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue(i+1, j, dest); 
				fNew = gNew + hNew; 

				if (cellDetails[i+1][j].f == FLT_MAX || cellDetails[i+1][j].f > fNew) { 
					openList.insert( make_pair (fNew, make_pair (i+1, j))); 
					// Update the details of this cell 
					cellDetails[i+1][j].f = fNew; 
					cellDetails[i+1][j].g = gNew; 
					cellDetails[i+1][j].h = hNew; 
					cellDetails[i+1][j].parent_i = i; 
					cellDetails[i+1][j].parent_j = j; 
				} 
			} 
		} 

		//----------- 3rd Successor (East) ------------ 

		if (isValid (i, j+1) == true){ 
			if (isDestination(i, j+1, dest) == true) { 
				cellDetails[i][j+1].parent_i = i; 
				cellDetails[i][j+1].parent_j = j; 
				tracePath(cellDetails, dest, path); 
				foundDest = true; 
				return true; 
			} 

			else if (closedList[i][j+1] == false && isUnBlocked (grid, i, j+1) == true) { 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue (i, j+1, dest); 
				fNew = gNew + hNew; 

				if (cellDetails[i][j+1].f == FLT_MAX || cellDetails[i][j+1].f > fNew) { 
					openList.insert( make_pair(fNew, make_pair (i, j+1))); 

					cellDetails[i][j+1].f = fNew; 
					cellDetails[i][j+1].g = gNew; 
					cellDetails[i][j+1].h = hNew; 
					cellDetails[i][j+1].parent_i = i; 
					cellDetails[i][j+1].parent_j = j; 
				} 
			} 
		} 

		//----------- 4th Successor (West) ------------ 
		if (isValid(i, j-1) == true){
			if (isDestination(i, j-1, dest) == true) { 

				cellDetails[i][j-1].parent_i = i; 
				cellDetails[i][j-1].parent_j = j; 
				tracePath(cellDetails, dest, path); 
				foundDest = true; 
				return true; 
			} 

			else if (closedList[i][j-1] == false && isUnBlocked(grid, i, j-1) == true) { 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue(i, j-1, dest); 
				fNew = gNew + hNew; 

				if (cellDetails[i][j-1].f == FLT_MAX || cellDetails[i][j-1].f > fNew) { 
					openList.insert( make_pair (fNew, 
										make_pair (i, j-1))); 

					cellDetails[i][j-1].f = fNew; 
					cellDetails[i][j-1].g = gNew; 
					cellDetails[i][j-1].h = hNew; 
					cellDetails[i][j-1].parent_i = i; 
					cellDetails[i][j-1].parent_j = j; 
				} 
			} 
		} 
	}
	//This may happen when the there is no way to destination cell (due to blockages)
	return foundDest; 
}

