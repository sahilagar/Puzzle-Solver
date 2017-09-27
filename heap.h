#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T, typename Comparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int mary, Comparator c = Comparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

  void print();

 private:
  /// Add whatever helper functions and data members you need below
 	void heapify(int idx);
 	void trickleUp(int idx);
 	void swap(int parent, int child);
 	std::vector<T> values;
 	Comparator c;
 	int m;



};

template<typename T, typename Comparator>
Heap<T,Comparator>::Heap(int mary, Comparator c): m(mary)
{
}


template<typename T, typename Comparator>
Heap<T,Comparator>::~Heap() 
{
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return values[0];

}

template<typename T, typename Comparator>
void Heap<T,Comparator>::push(const T &item) {

	values.push_back(item);
	trickleUp((int) values.size() - 1);
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  	values[0] = values.back();
  	//std::cout << values[0] << std::endl;
	values.pop_back();
	heapify(0);
}


template <typename T, typename Comparator>
bool Heap<T,Comparator>::empty() const {
	return values.size() == 0;
}

//removing the top item, swap with the bottom element
//and trickle down the root with the compator child
template<typename T, typename Comparator>
void Heap<T,Comparator>::heapify(int idx) {

	//take the value and compare with all the children
	//swap with the minimum child, otherwise return
	if (idx > (int)values.size()/m) //scales correctly
	{
		return;
	}
	T compare_value = values[idx]; //temp parent value
	int cindex = idx; //minchild index
	int childrenStartIndex = idx * m + 1;

	//run as long as vector can support a full search of children
	
	for (int i=childrenStartIndex; i < childrenStartIndex + m; i++){	
		if (i < values.size()){
			if (c(values[i], compare_value)){
				compare_value = values[i];
				cindex = i;
			}
		}
					
	}	


	//succesfully found a child to swap with
	if (cindex != idx){
		swap(idx, cindex);
		heapify(cindex);
	}

}

template <typename T, typename Comparator>
void Heap<T,Comparator>::swap(int parent, int child) {

	T temp = values[parent];
	values[parent] = values[child];
	values[child] = temp;
}

//adding an item to the end, recursively promote to the top
//or until
template <typename T, typename Comparator>
void Heap<T,Comparator>::trickleUp(int idx) {

	if (idx == 0) {
		return;
	}

	int parent = (idx -1)/ m;

	if (c(values[idx],values[parent])) {
		swap(parent, idx);
		trickleUp(parent);
	}
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::print()
{
	for (unsigned int i = 0; i < values.size(); i++)
		std::cout << values[i] << " ";
	std::cout << std::endl;
}


#endif

