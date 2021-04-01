#ifndef HASHMAP_H
#define HASHMAP_H

#define BUCKETS 10


#include <string>
#include <iostream>
#include "HashmapInterface.h"

class Hashmap : public HashmapInterface {
private:
    struct Node { // i guess we're not using templates for this then?
        std::string first; // key
        int second;        // value

        Node * next = NULL;
        Node * prev = NULL;

        Node() {};
        Node(std::string first): first(first) {}; 
        Node(std::string first, int second): first(first), second(second) {};

        ~Node() {
            delete next;
        }
        void cut() {
            next = NULL;
            prev = NULL;
        }
    };

    /*
	 * Compare struct to be used for sorting nodes
	 * Nodes with different values should sort by greater values first
	 * Nodes with the same values should sort alphabetically (a-z) by key
	 */
	struct NodeCompare
	{
		bool operator()(Node* a, Node* b)
		{
			if(a->second != b->second)
				return a->second < b->second;
			else
				return a->first > b->first;
		}
	};

    Node * buckets[BUCKETS];
    int mapSize; // number of elements in the array
    int length = BUCKETS; // total length of allocated array space;

    int hash(std::string &) const;
    bool isEmpty() const;

public:
	Hashmap();
	virtual ~Hashmap();

	/*
	 * Insert a key/value pair into the map
	 *  If key is not in the map yet, add new key/value pair to map
	 *  If key is already in the map, replace old value with new value
	 */
	virtual void insert(std::string key, int value);

	/*
	 * Test if the key exists in the map
	 *  Return true if one of the nodes in the map has the given key, false otherwise
	 */
	virtual bool contains(std::string key) const;

	/*
	 * Return the value associated with the given key in the map
	 *  Throw invalid_argument exception if key is not in map
	 */
	virtual int get(std::string key) const;

	/*
	 * Return a reference to a value associated with the given key in the map
	 *  This will allow you use syntax such as map['pig'] to get the value
	 *   for the given key
	 *  This will also allow you use sytnax such as map['pig']=10 to set/update
	 *   the value for the given key
	 *  If the node with the given key is found in the map, return that node's value
	 *  If the ndoe with the given key is not found in the map, insert a new node with
	 *   the given key and a value of 0 into the map, then return newNode->value
	 */
	virtual int& operator [](std::string key);

	/*
	 * Remove the node with given key from the map
	 *  Return true if node is found and removed
	 *  Return false if the key does not exist in the map
	 */
	virtual bool remove(std::string key);

	/*
	 * Reset map to empty
	 *  Deallocate all memory
	 */
	virtual void clear();

	/*
	 * Return string representation of map
	 *  Each row of the string representation should represent a list of key/values
	 *  in a single bucket.
	 *
	 *  An empty bucket should look like this:
	 *  [0]
	 *
	 *  A bucket with a single key/value pair should look like this:
	 *  [0] pig => 10
	 *
	 *  And a bucket with multiple key/value pairs should look like this:
	 *  [0] pig => 10, moose => 3
	 *
	 *  Each bucket should be on one line. Buckets should be in numerical order
	 *  starting at 0 and going up to BUCKETS-1. For example, if BUCKETS is 5
	 *  the string might look like this:
	 *  [0]
	 *  [1] rock => 4, bacon => 17
	 *  [2] hippie => 8
	 *  [3]
	 *  [4] dagger => 2, wrench => 1, pipe => 4
	 *
	 *  There should be no trailing spaces or commas. Lines should end with single
	 *  newline character \n
	 */
	virtual std::string toString() const;
    std::string toSortedString() const;



	/*
	 * Return number of keys in map
	 */
	virtual int size() const;

};

#endif /* HASHMAP_H */