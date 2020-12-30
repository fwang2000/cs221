
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"
#include "math.h"

// Node constructor, given.
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

// twoDtree destructor, given.
twoDtree::~twoDtree(){
	clear();
}

// twoDtree copy constructor, given.
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}


// twoDtree assignment operator, given.
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG & imIn){ 

// YOUR CODE HERE'
	width = imIn.width();
	height = imIn.height();
	stats s(imIn);
	pair<int, int> ul = pair<int, int>(0, 0);
	pair<int, int> lr = pair<int, int>(width - 1, height - 1);

	root = buildTree(s, ul, lr, true);


}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr, bool vert) {

// YOUR CODE HERE!!
	Node * node = new Node(ul, lr, s.getAvg(ul, lr));

	if (ul == lr) {

		return node;
	}

	if (ul.first == lr.first) {

		vert = false;

	} else if (ul.second == lr.second) {

		vert = true;
	}

	long minScore = LONG_MAX;
	pair<int, int> minUL;
	pair<int, int> minLR;

	if (vert) {

		for (int x = ul.first; x < lr.first; x++) {

	        pair<int, int> tempLR = make_pair(x, lr.second);
	        pair<int, int> tempUL = make_pair(x + 1, ul.second);

	        long score = s.getScore(ul, tempLR) + s.getScore(tempUL, lr);

	        if (score <= minScore) {
	            minScore = score;
	            minLR = tempLR;
	            minUL = tempUL;
	        }
	    }

		node->left = buildTree(s, ul, minLR, false);
		node->right = buildTree(s, minUL, lr, false);

	} else {

		for (int y = ul.second; y < lr.second; y++) {

	        pair<int, int> tempLR = make_pair(lr.first, y);
	        pair<int, int> tempUL = make_pair(ul.first, y + 1);

	        long score = s.getScore(ul, tempLR) + s.getScore(tempUL, lr);

	        if (score <= minScore) {
	            minScore = score;
	            minLR = tempLR;
	            minUL = tempUL;
	        }
	    }

		node->left = buildTree(s, ul, minLR, true);
		node->right = buildTree(s, minUL, lr, true);
		
	}

	return node;
}

PNG twoDtree::render(){

	PNG rpng = PNG(width, height);

	renderHelper(root, rpng);

	return rpng;
}

void twoDtree::renderHelper(const Node * node, PNG & img) {

	if (!node) {

		return;
	}

	if (node->left == NULL && node->right == NULL){

		for (int x = node->upLeft.first; x <= node->lowRight.first; x++){

			for (int y = node->upLeft.second; y <= node->lowRight.second; y++){

				*(img.getPixel(x, y)) = node->avg;
			}
		}
		return;
	}

	renderHelper(node->left, img);
	renderHelper(node->right, img);
	
}

int twoDtree::idealPrune(int leaves){

	int min = 0; 
	int max = 3 * 255 * 255;

	while (min <= max) {

		int tol = (min + max)/2;
		int result = pruneSize(tol);

		if (result > leaves) {

			min = tol + 1;

		} else if (result < leaves) {

			max = tol - 1;

		} else {

			max = tol;

			while (min <= max) {

				tol = (min + max)/2;
				result = pruneSize(tol);

				if (result == leaves) {

					max = tol - 1;

				} else {

					min = tol + 1;
				}

			}

			return tol + 1;
		}
	}

	return -1;
}

int twoDtree::pruneSize(int tol){
    
	return pruneSizeHelper(root, tol);

}

int twoDtree::pruneSizeHelper(twoDtree::Node * node, int tol) {

	if (!node) {

		return 0;
	}

	if (shouldPrune(node, tol, node->avg)) {

		return 1;
	}

	return pruneSizeHelper(node->left, tol) + pruneSizeHelper(node->right, tol);

}

int twoDtree::countNodes(twoDtree::Node * node) {

	if (!node) {

		return 0;
	}

	return 1 + countNodes(node->left) + countNodes(node->right);
}

void twoDtree::prune(int tol){

	pruneHelper(root, tol);

}

void twoDtree::pruneHelper(twoDtree::Node * node, int tol) {

	if (!node) {

		return;
	}

	if (shouldPrune(node, tol, node->avg)) {

		clearHelper(node->left);
		clearHelper(node->right);
		node->left = NULL;
		node->right = NULL;
		return;

	} else {

		pruneHelper(node->left, tol);
		pruneHelper(node->right, tol);
	}
}

bool twoDtree::shouldPrune(twoDtree::Node * node, int tol, RGBAPixel a) {

	if (!node) {

		return true;
	}

	if (node->left == NULL && node->right == NULL) {

		long rdist = (node->avg.r - a.r) * (node->avg.r - a.r);
		long gdist = (node->avg.g - a.g) * (node->avg.g - a.g);
		long bdist = (node->avg.b - a.b) * (node->avg.b - a.b);

		long sum = rdist + bdist + gdist;
		return sum <= tol;
	}	

	return shouldPrune(node->left, tol, a) && shouldPrune(node->right, tol, a);
}

void twoDtree::clear() {

	clearHelper(root);
	root = NULL;
	height = 0;
	width = 0;

}

void twoDtree::clearHelper(twoDtree::Node * node) {

	if (!node) {

		return;
	}

	clearHelper(node->left);
	clearHelper(node->right);
	delete node;
}

void twoDtree::copy(const twoDtree & orig){

	height = orig.height;
	width = orig.width;
	root = copyHelper(orig.root);
}

twoDtree::Node * twoDtree::copyHelper(twoDtree::Node *other) {

	if (!other) {

		return NULL;
	}

	Node * node = new Node(other->upLeft, other->lowRight, other->avg);
	node->left = copyHelper(other->left);
	node->right = copyHelper(other->right);
	return node; 
}





