// File:        gridlist.cpp
// Date:        2020-01-18 00:11
// Description: Contains partial implementation of GridList class
//              CPSC 221 2019W2 PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//

#include "gridlist.h"
#include "gridlist_given.cpp"

// Creates a PNG of appropriate pixel dimensions according to the GridList's structure
//   and colours each pixel according the each GridNode's Block data.
// The fully coloured PNG is returned.
PNG GridList::Render() const
{
  PNG image;
  GridNode * curr = northwest;
  int dim = curr->data.Dimension();
  int xsize = dimx * dim;
  int ysize = dimy * dim;

  image.resize(xsize, ysize);
  int i = 0;
  int j = 0;

  while (curr->next) {

    curr->data.Render(image, j, i);
    if (i < xsize - dim) {

      i += dim;

    } else {

      i = 0;
      j += dim;
    }

    curr = curr->next;
    
  }

  curr->data.Render(image, ysize - dim, xsize - dim);

  return image;
}

// Allocates a new GridNode containing bdata and
//   attaches it to end of this list.
// Be careful of the special case of inserting into an empty list.
void GridList::InsertBack(const Block& bdata)
{

	GridNode* inserted = new GridNode(bdata);

    if (IsEmpty()) {

		northwest = southeast = inserted;
		inserted = NULL;
		delete inserted;
	  	return;
	}

	inserted->prev = southeast;
	southeast->next = inserted;
	southeast = southeast->next;
	inserted = NULL;
	delete inserted;

}

// if this list has an odd number of column blocks, then the right side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two column blocks
//       inner list must have at least one column block
//       inner list must have the same vertical resolution, vertical block dimension, and block size
// POST: this list has nodes of the entire inner list in between the left and right halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_H(GridList& inner)
{

	if (dimx < 2 || inner.dimx < 1 || dimy != inner.dimy) {

		return;
	}
  
  	int mid = (dimx/2) - 1;
  	int i = 0;
  	int insertions = (inner.Length()/dimy) - 1;
  	int count = 0;

  	GridNode* otherNode = inner.northwest;
  	GridNode* curr = northwest;
  	GridNode* temp;
  	GridNode* otherTemp;

  	while (curr->next) {

  		if (i == mid && otherNode) {

  			temp = curr;
  			curr = curr->next;

  			otherTemp = otherNode;


  			while (count < insertions) {

  				otherTemp = otherNode; 
  				otherNode = otherNode->next;
  				otherTemp->next = otherNode;
  				otherNode->prev = otherTemp;
  				count++;
  			}

  			count = 0;

  			temp->next = otherTemp;
  			otherTemp->prev = temp;

  			otherTemp = otherNode;
  			otherNode = otherNode->next;

  			otherTemp->next = curr;
  			curr->prev = otherTemp;

  		} else {

  			curr = curr->next;
  		}

  		if (i < dimx - 1) {

  			i++;

  		} else {

  			i = 0;
  		}
  	}

  	dimx += inner.dimx;
  	inner.southeast = NULL;
  	inner.northwest = NULL;
  
}

// inner list must have the same horizontal resolution, horizontal block dimension, and block size
// if this list has an odd number of row blocks, then the bottom side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two row blocks
//       inner list must have at least one row block
//       inner list must have same horizontal resolution, horizontal block dimension, and block size
// POST: this list has nodes of the entire inner list in between the upper and lower halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_V(GridList& inner)
{
  if (dimy < 2 || inner.dimy < 1 || dimx != inner.dimx) {

  	return;
  }

  int mid = (dimy/2) - 1;

  int i = 0;
  int j = 0;

  GridNode* curr = northwest;
  GridNode* otherNode = inner.northwest;
  GridNode* temp;
  GridNode* otherTemp;

  while (curr->next) {

  	if (j == mid && i == dimx - 1) {

  		temp = curr;
  		curr = curr->next; 
  		temp->next = otherNode;
  		otherNode->prev = temp;

  		while (otherNode->next) {

  			otherTemp = otherNode;
  			otherNode = otherNode->next;
  			otherTemp->next = otherNode;
  			otherNode->prev = otherTemp;
  		}

  		otherNode->next = curr;
  		curr->prev = otherNode;
  
  	}

  	if (i < dimx - 1) {

  		i++;

  	} else {

  		i = 0;
  		j++;
  	}

  	curr = curr->next;
  }

  dimy += inner.dimy;
  inner.northwest = NULL;
  inner.southeast = NULL;
}


// PRE:  this list and otherlist have the same pixel dimensions, block dimensions, and block size
// POST: this list and otherlist are checkered with each other's nodes
//       each list's dimensions remain the same
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::CheckerSwap(GridList& otherlist)
{

	if (IsEmpty() || otherlist.IsEmpty()) {

		return;
	}

	GridNode* curr = northwest;
	GridNode* otherNode = otherlist.northwest;
	GridNode* temp;
	GridNode* otherTemp;

	int i = 0;
	int j = 0;

	while (curr->next) {

		if (dimx % 2 == 0 && i == dimx - 1) {

			curr = curr->next;
			otherNode = otherNode->next;
			i = 0;
			j++;
		}
		
		temp = curr->next;
		otherTemp = otherNode->next;

		curr->next = otherTemp;
		otherTemp->prev = curr;

		otherNode->next = temp;
		temp->prev = otherNode;

		if (i < dimx - 1) {

			i++;

		}

		curr = curr->next;
		otherNode = otherNode->next;
	}
}

// POST: this list has the negative effect applied selectively to GridNodes to form
//         a checkerboard pattern.
//       The northwest block is normal (does not have the negative effect applied).
// Ensure that the checkering looks correct for both odd and even horizontal block dimensions
void GridList::CheckerN()
{
 	if (!northwest || !northwest->next) {

 		return;
 	}

 	GridNode* curr = northwest->next;
 	int i = 1;
 	int j = 0;

 	while (curr->next) {

 		if ((j + i) % 2 == 1) {

 			curr->data.Negative();
 		}

 		if (i < dimx - 1) {

 			i++;

 		} else {

 			j++;
 			i = 0;
 		}

 		curr = curr->next;
 	}

 	if ((dimx + dimy)%2 == 1) {

 		curr->data.Negative();
 	}
}

// Deallocates any dynamic memory associated with this list
//   and re-initializes this list to an empty state
void GridList::Clear()
{
  if (IsEmpty()) {

  	return;
  }

  while (northwest->next) {

  	GridNode * temp = northwest->next;
  	delete northwest;
  	northwest = temp;
  }

  delete northwest;
  northwest = NULL;
}

// Allocates new nodes into this list as copies of all nodes from otherlist
void GridList::Copy(const GridList& otherlist)
{

	if (otherlist.IsEmpty()) {

		return;
	}
	  
	while (otherlist.northwest->next) {

		GridNode * currOther = otherlist.northwest;
		InsertBack(currOther->data);
		currOther = currOther->next;
	}
}

// IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE ADDED BELOW
//
//