#pragma once

const int MAX_OBJECTS = 1000;

#include "Object.h"

namespace df {
	class ObjectList {
	private:
		int m_count;					// Count of objcets in list
		Object* m_p_obj[MAX_OBJECTS];	// Array of pointers to objects

	public:
		ObjectList();	// Default constructor

		int insert(Object* p_o);	// Insert object pointer in list, returning 0 on a success and -1 otherwise
		int remove(Object* p_o);	// Remove object pointer from list, returning 0 if found and -1 otherwise

		void clear();	// Clears the list and resets m_count
		int getCount() const;	// m_count getter

		bool isEmpty() const;	// Returns true if list is empty, else false
		bool isFull() const;	// Returns true if list is full, else false

		Object* operator[](int index) const;	// Index operator
	};
}