/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
template <class T> void Queue<T>::enqueue(T const &newItem)
{
    /**
     * @todo Your code here!
     */
     stack_1.push(newItem);
     // while (!stack_1.isEmpty()) {
     //        stack_2.push(stack_1.peek());
     //        stack_1.pop();
     //    }
     //
     //    // Push item into s1
     //    stack_1.push(newItem);
     //
     //    // Push everything back to s1
     //    while (!stack_2.isEmpty()) {
     //        stack_1.push(stack_2.peek());
     //        stack_2.pop();
     //
     //    }
}

/**
 * Removes the object at the front of the Queue, and returns it to the
 * caller.
 *
 * @return The item that used to be at the front of the Queue.
 */
template <class T> T Queue<T>::dequeue()
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */
     if (stack_2.isEmpty()) {
       // if (stack_1.isEmpty()) {
       //   return NULL;
       // }
       while (!stack_1.isEmpty()) {
         stack_2.push(stack_1.pop());
       }
     }
     return stack_2.pop();

    // T ret = stack_1.peek();
    // stack_1.pop();
    // return ret;
  }





/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T> void Queue<T>::add(const T &theItem)
{
    /**
     * @todo Your code here! Hint: this function should call a Queue
     *  function to add the element to the Queue.
     */
     enqueue(theItem);
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T> T Queue<T>::remove()
{
    /**
     * @todo Your code here! Hint: this function should call a Queue
     *  function to remove an element from the Queue and return it. You will
     *  need to replace the following line.
     */
     return dequeue();
}

/**
 * Finds the object at the front of the Queue, and returns it to the
 * caller. Unlike pop(), this operation does not alter the queue.
 *
 * @return The item at the front of the queue.
 */
template <class T> T Queue<T>::peek()
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */
     if (stack_2.isEmpty()) {
       // if (stack_1.isEmpty()) {
       //   return NULL;
       // }
       while (!stack_1.isEmpty()) {
         stack_2.push(stack_1.pop());
       }
     }
     return stack_2.peek();
     // T ret = stack_1.peek();
     // return ret;
}

/**
 * Determines if the Queue is empty.
 *
 * @return bool which is true if the Queue is empty, false otherwise.
 */
template <class T> bool Queue<T>::isEmpty() const
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */
     return stack_1.isEmpty() && stack_2.isEmpty();
    // return stack_1.isEmpty();
}
