/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    
    return 2 * currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    
    return 2 * currentIdx + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
    
    return (currentIdx - 1) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
    
    return 2 * currentIdx + 1 >= _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    
    if (higherPriority(_elems[2 * currentIdx + 1], _elems[2 * currentIdx + 2])) {

    	return 2 * currentIdx + 1;

    } else {

    	return 2 * currentIdx + 2;
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.

	if (!hasAChild(currentIdx)) {

		return;
	}

	size_t leftIdx = leftChild(currentIdx);
	size_t rightIdx = rightChild(currentIdx);
	size_t min = currentIdx;

	if (higherPriority(_elems[leftIdx], _elems[min])) {

		min = leftIdx;
	}

	if (higherPriority(_elems[rightIdx], _elems[min])) {

		min = rightIdx;
	}

	if (min != currentIdx) {

		std::swap(_elems[currentIdx], _elems[min]);
		heapifyDown(min);
	}
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    /// Your algorithm should use heapifyDown() so that it constructs
    /// the same heap as our test case.

    for (size_t i = 0; i < elems.size(); i++) {

    	_elems.push_back(elems[i]);
    	heapifyUp(i);
    }
   
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
	if (empty()) {

		return T();
	}

    T popped = peek();
    std::swap(_elems[0], _elems[_elems.size() - 1]);
    _elems.pop_back();
    heapifyDown(0);
    return popped;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    if (empty()) {

    	return T();
    }

    return _elems[0];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap

	_elems.push_back(elem);
	heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    
    return _elems.size() <= 0;
}
