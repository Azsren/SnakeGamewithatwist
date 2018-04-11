#include <utility>
#include "ll.h"
#include <vector>
#include<iostream>

template<typename ElementType>
LinkedList<ElementType>::LinkedList() : head_(nullptr) {

}

template<typename ElementType>
LinkedList<ElementType>::LinkedList(const std::vector<ElementType> &values) : head_(nullptr) {
	if (values.empty() || values.size() == 0) {
		return;
	}

	else {

		head_ = new LinkedListNode(values[0]);

		for (int i = 1; i < values.size(); i++) {
			push_back(values[i]);
		}

	}
}

// Copy constructor
template<typename ElementType>
LinkedList<ElementType>::LinkedList(const LinkedList<ElementType>& source) {
	*this = source; // I had a different 
}

// Move constructor
template<typename ElementType>
LinkedList<ElementType>::LinkedList(LinkedList<ElementType>&& source) noexcept {
	*this = std::move(source);
}

// Destructor
template<typename ElementType>
LinkedList<ElementType>::~LinkedList() {
	clear();
}

// Copy assignment operator
template<typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator= (const LinkedList<ElementType>& source) {
	if (!source.head_ && this != &source) {
		head_ = nullptr;

		LinkedListNode *initialSource = source.head_->next_;
		LinkedListNode *secondarySource = head_;
		head_ = new LinkedListNode(source.head_->data_);

		while (initialSource) {
			secondarySource->next_ = new LinkedListNode(initialSource->data_);
			initialSource = initialSource->next_;
			secondarySource = secondarySource->next_;

		}
	}
	return *this;
}

// Move assignment operator
template<typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator= (LinkedList<ElementType>&& source) noexcept {
	if (!source.head_ && this != &source) {
		head_ = nullptr;

		size_ = 0;
		return *this;
	}
	LinkedListNode *initialSource = source.head_->next_;
	LinkedListNode *secondarySource = head_;
	head_ = new LinkedListNode(source.head_->data_);

	while (initialSource) {
		secondarySource->next_ = initialSource;
		initialSource = initialSource->next_;
		secondarySource = secondarySource->next_;
	}
	return *this;
}

template<typename ElementType>
void LinkedList<ElementType>::push_front(ElementType value) {
	LinkedListNode *front = new LinkedListNode(value);
	front->next_ = head_;
	head_ = front;

}

template<typename ElementType>
void LinkedList<ElementType>::push_back(ElementType value) {   // LOOK FROM HSDUFIHSDUIF SDFUINSDIUFNDSUIFNS
	LinkedListNode *newTail = new LinkedListNode(value);
	if (!head_) {
		head_ = newTail;

	}
	else {
		LinkedListNode *tail = head_;

		while (tail->next_) {
			tail = tail->next_;
		}
		tail->next_ = newTail;


	}

}

template<typename ElementType>
ElementType LinkedList<ElementType>::front() const {
	if (head_) {
		return head_->data_;
	}
	else {
		return ElementType();
	}
}

template<typename ElementType>
ElementType LinkedList<ElementType>::back() const {
	if (!head_) {
		return ElementType();
	}
	else {
		LinkedListNode *tail = head_;

		while (tail->next_) {
			tail = tail->next_;
		}
		return tail->data_;

	}
}

template<typename ElementType>
void LinkedList<ElementType>::pop_front() {
	if (!head_) {
		return;
	}


	LinkedListNode *tmp = head_;
	head_ = tmp->next_;
	delete tmp;

}

template<typename ElementType>
void LinkedList<ElementType>::pop_back() {
	if (head_) {

		if (size() == 1) {

			delete head_;
			head_ = nullptr;

		}

		LinkedListNode *cur = head_;

		while (cur->next_->next_) {
			cur = cur->next_;
		}
		delete cur->next_;
		cur->next_ = nullptr;

	}
}

template<typename ElementType>
int LinkedList<ElementType>::size() const {
	int count = 0;  // Initialize count
	if (head_) {
		LinkedListNode *cur = head_;  // Initialize cur
		while (cur != nullptr) {
			count++;
			cur = cur->next_;
		}
	}
	return count;
}

template<typename ElementType>
std::vector<ElementType> LinkedList<ElementType>::GetVector() const {
	std::vector<ElementType> snakeVector;
	if (!head_) {
		return snakeVector;
	}
	LinkedListNode *cur = head_;
	while (cur) { // Loops through snake except for last element
		snakeVector.push_back(cur->data_);
		cur = cur->next_; // Becomes the last element
	}
	return snakeVector;
}


template<typename ElementType>
bool LinkedList<ElementType>::empty() const {
	return !head_;
}

template<typename ElementType>
void LinkedList<ElementType>::clear() {

	if (!head_) {
		return;
	}
	head_ = nullptr;
	LinkedListNode *cur = head_;

	while (cur) {
		LinkedListNode *temp = cur;
		cur = cur->next_;
		delete temp;

	}
}

template<typename ElementType>
std::ostream& operator<<(std::ostream& os, const LinkedList<ElementType>& list) {
	if (!list.head_) {
		return os << "List is empty";
	}
	LinkedList<ElementType>::LinkedListNode *cur = list.head_;
	while (cur->next_) {
		os << cur->data_ << " ";
		cur = cur->next_;
	}
	os << cur->data_;   //takes care of the last element
	return os;
}

template<typename ElementType>
void LinkedList<ElementType>::RemoveNth(int n) {
	LinkedListNode *cur = head_;
	if (!head_) {
		return;
	}
	if (n == 0) {
		pop_front();
		return;
	}
	if (n == size() - 1) {
		pop_back();
		return;
	}
	/// - In this case, jsut use an && to join these two
	if ((n >= size() - 1) || (n < 0)) {
		return;
	}

	for (int i = 0; i < n - 1 && cur->next_; i++) {
		cur = cur->next_;
	}
	LinkedListNode* tmp = cur->next_->next_;
	cur->next_->next_ = nullptr;
	delete cur->next_;

	cur->next_ = tmp;
}


template<typename ElementType>
bool LinkedList<ElementType>::operator==(const LinkedList<ElementType> &rhs) const {
	if (size() == rhs.size()) {
		if (size() == 0) {
			return true;
		}

		LinkedListNode *lhs = head_;
		LinkedListNode *rhs2 = rhs.head_;

		while (lhs->next_ && rhs2->next_) {
			if (lhs->data_ != rhs2->data_) {
				return false;
			}
			lhs = lhs->next_;
			rhs2 = rhs2->next_;
		}
		return true;
	}
	return false;
}

template<typename ElementType>
bool operator!=(const LinkedList<ElementType>& lhs, const LinkedList<ElementType> &rhs) {
	return (lhs != rhs);
}

template<typename ElementType>
typename LinkedList<ElementType>::Iterator& LinkedList<ElementType>::Iterator::operator++() {
	if (current_) {
		current_ = current_->next_;
	}
	return *this;
}

template<typename ElementType>
ElementType& LinkedList<ElementType>::Iterator::operator*() {
	return current__->data;
}

template<typename ElementType>
bool LinkedList<ElementType>::Iterator::operator!=(const LinkedList<ElementType>::Iterator& other) {
	return current_ != other.current_;  //NOT RIGHT
}

template<typename ElementType>
typename LinkedList<ElementType>::Iterator LinkedList<ElementType>::begin() {
	Iterator start;
	start.current_ = head_;
	return start;

}

template<typename ElementType>
typename LinkedList<ElementType>::Iterator LinkedList<ElementType>::end() {
	Iterator stop;
	stop.current_ = nullptr;
	return stop;
}