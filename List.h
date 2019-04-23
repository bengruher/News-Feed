/**
 * @file adt/List.h - the List ADT
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */
#pragma once
#include <iostream>

/**
 * @class List<T> -- abstract base class for the List ADT
 *
 * The List Abstract Data Type is an indexable list of same-datatype elements.
 * The list can be enlarged by appending an element of type T to it. (Note that
 * T must have an accessible default constructor.) It can be shrunk by the remove
 * methods (the no-arg version removes from the end). Elements can be accessed by
 * index number with the get method. The index numbers are like an array, starting
 * at 0 up to n-1, where n is the current size of the list.
 *
 * @param T  Data type of the elements. Each T element is copied into the list with
 *           the append, insert, and set methods (a const reference to the copy is
 *           returned by the get method). T therefore must have an accessible
 *           copy-constructor and assignment operator. Most implementations also
 *           require a default constructor. The ADT does not require that T support
 *           any comparison operators, though many implementations may
 *           add == and < requirements on T.
 */
template <typename T>
class List {
public:
    /**
     * Get the current number of elements in the list.
     *
     * Efficiency: guaranteed O(1)
     * @return the number of elements
     * @post   size() >= 0
     */
    virtual int size() const = 0;

    /**
     * Get a reference to the element stored at index i.
     *
     * Efficiency: depends on implementation
     * @param i  index number of sought element
     * @return   a const reference to the ith element in this list
     * @throws   out_of_range if i not in range 0...size()-1
     * @pre      0 <= i < size()
     */
    virtual const T& get(int i) const = 0;

    /**
     * Change the element stored at index i to be a copy of the given datum.
     *
     * Efficiency: depends on implementation
     * @param i      index number of element to be changed
     * @param datum  value to be copied into list[i]
     * @throws       out_of_range if i not in range 0...size()-1
     * @pre          0 <= i < size()
     * @post         get(i) == datum
     */
    virtual void set(int i, const T& datum) = 0;

    /**
     * Append a new element to the end of this list.
     *
     * Efficiency: O(1)
     * @param datum  value to be copied onto the end of the list
     * @return       index number of the newly appended datum
     * @post         size() is one greater than before and get(return) == datum
     */
    virtual int append(const T& datum) = 0;

    /**
     * Insert a new element at the given index.
     *
     * All subsequent elements are moved forward.
     * Efficiency: depends on implementation.
     * @param i      desired index number of inserted element
     * @param datum  value to be copied into location i
     * @throws       out_of_range if i not in range 0...size()
     * @pre          0 <= i <= size(), Note: if i == size(), then append
     * @post         size() is one greater than before
     *               and get(i) == datum
     *               and for all valid j>i, get(j) == what get(j-1) was before
     */
    virtual void insert(int i, const T& datum) = 0;

    /**
     * Remove the final element from the end of this list.
     *
     * Efficiency: depends on implementation
     * @throws  out_of_range if size() == 0
     * @pre     size() > 0
     * @post    size() is one less than before
     */
    virtual void remove() = 0;

    /**
     * Remove the element at the given index and shrink the list.
     *
     * Efficiency: depends on implementation
     * @param i  index number of element to be removed
     * @throws   out_of_range if i not in range 0...size()-1
     * @pre      0 <= i < size()
     * @post     size() is one less than before
     *           and for all valid j>=i, get(j) == what get(j+1) was before
     */
    virtual void remove(int i) = 0;

    /**
     * Remove all elements from this list.
     *
     * @post  size() == 0
     */
    virtual void clear() = 0;

    /**
     * Print the contents to the given stream.
     *
     * Requires that T has << operator into std::ostream.
     * @param out  stream to print to
     * @return     modified output stream
     * @pre        out is writable
     * @post       out has a textual representation of list inserted (with <<)
     */
    virtual std::ostream& print(std::ostream& out) const = 0;

    virtual ~List() {} // make the destructors virtual
};

/**
 * Template operator<< overload for printing.
 *
 * This just redirects to the print method.
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& list) {
    return list.print(out);
}
