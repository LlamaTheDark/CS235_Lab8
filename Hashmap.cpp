#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <queue>
#include "Hashmap.h"

/* #### CONSTRUCTORS #### */

Hashmap::Hashmap()  {
    for(auto & n : buckets){
        n = NULL;
    }
    mapSize = 0;
}

Hashmap::~Hashmap() {
    for(int i = 0; i < length; i++){
        delete buckets[i];
    }
}

/* ### /CONSTRUCTORS #### */

/* #### ACCESSORS #### */

int Hashmap::get(std::string key) const { // can't use (*this)[key] because it isn't const
    Node * ptr = buckets[hash(key)];
    while(ptr != NULL){
        if(key == ptr->first){
            // found value
            return ptr->second;
        }else{
            // nope, check next pointer
            ptr = ptr->next;
        }
    }
    throw std::invalid_argument("Given key does not exist in map.");
}
std::string Hashmap::toString() const {
    std::stringstream ss;
    
    for(int i = 0; i < BUCKETS; i++){
        ss << "[" << i << "]" << std::flush;
        Node * ptr = buckets[i];
        while(ptr != NULL){
            if(ptr != buckets[i]){
                ss << ",";
            }
            ss << " " << ptr->first << " => " << ptr->second << std::flush;
            ptr = ptr->next;
        }
        ss << std::endl;
    }
    
    return ss.str();
}
std::string Hashmap::toSortedString() const {
    std::stringstream ss;
    std::priority_queue<Node*, std::vector<Node*>, NodeCompare> nodeHeap;
    for(int i = 0; i < length; i++){
        // Iterate through each bucket. Use nodeHeap.push to push all Node* onto heap.
        Node * ptr = buckets[i];
        while(ptr != NULL){
            nodeHeap.push(ptr);
            ptr = ptr->next;
        }
    }
    while(!nodeHeap.empty()){
        Node* top = nodeHeap.top(); // Get top node (next node in sorted order)
        ss << top->first << " => " << top->second << endl; // Add node data to stringstream
        nodeHeap.pop(); // Pop it off
    }
    return ss.str();
}

/* ### /ACCESSORS #### */

/* #### MUTATORS #### */

void Hashmap::insert(std::string key, int value) {
    (*this)[key] = value;
}

void Hashmap::clear() {
    for(int i = 0; i < length; i++){
        delete buckets[i];
    }
    for(auto & n : buckets){
        n = NULL;
    }
    mapSize = 0;
}

bool Hashmap::remove(std::string key){
    // std::cout << "trying to remove " << key << " from the following tree:" << std::endl << this->toString() << std::endl;
    int hashVal = hash(key);
    Node * ptr = buckets[hashVal];
    while(ptr != NULL){
        if(key == ptr->first){
            // remove ptr
            if(ptr == buckets[hashVal]){
                buckets[hashVal] = ptr->next;
            }else{
                ptr->prev->next = ptr->next;
                if(ptr->next != NULL){
                    ptr->next->prev = ptr->prev;
                }
            }

            ptr->cut();
            delete ptr;
            mapSize--;
            return true;
        }else {
            ptr = ptr->next;
        }
    }
    // didn't find key in Hashmap
    return false;
}

/* ### /MUTATORS #### */

/* #### CHECKS #### */

bool Hashmap::contains(std::string key) const {
    Node * ptr = buckets[hash(key)];
    // std::cout << "hash: " << hash(key) << std::endl;
    while(ptr != NULL){
        // std::cout << "ptr @ " << "(" << ptr->first << " => " << ptr->second << ")" << std::endl;
        if(key == ptr->first){
            return true;
        }else{
            ptr = ptr->next;
        }
    }
    return false;
}

bool Hashmap::isEmpty() const {
    return mapSize == 0;
}

/* ### /CHECKS #### */

/* #### MISC #### */

int& Hashmap::operator [](std::string key) {
    int hashVal = hash(key);
    Node * ptr = buckets[hashVal];
    while(ptr != NULL){
        if(key == ptr->first){
            // found value
            return ptr->second;
        }else{
            // nope, check next pointer
            ptr = ptr->next;
        }
    }
    
    // if it makes it to this point, the pointer is equal to NULL
    // and so we need to add the node to the list and return a new int
    ptr = new Node(key);
    ptr->next = buckets[hashVal];
    buckets[hashVal] = ptr;
    if(ptr->next != NULL)
        ptr->next->prev = ptr;
    mapSize++;
    return ptr->second;
}
int Hashmap::hash(std::string & str) const {
    unsigned int result = 7;
    for(auto& c : str){
        if(result > 4294967295){
            result >>=10;
        }
        result = result*13 + c;
    }
    
    // std::cout << "\t\treturn value: " << result%length << std::endl;
    return result%length;
}

int Hashmap::size() const {
    std::cout << "testing" << std::endl;
    return mapSize;
}

/* ### /MISC #### */