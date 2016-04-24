#ifndef CONTAINER_H
#define CONTAINER_H

template <class TypeClass> class Container {
public:

	Container() : topElementPointer(nullptr), freezed(false), containerSize(0) {}
	
	void
		freeze(bool sort = true),
		insertSort(),
		push(const TypeClass &element);

	unsigned int
		getIndexOf(const TypeClass element);

	unsigned int
		getSize() const;

	TypeClass
		pop();
	TypeClass&
		operator[](const unsigned int i) const;

private:

	struct stackElement {

		stackElement(const TypeClass &newElement, stackElement* newElement_ptr) : element(newElement), previousElementPointer(newElement_ptr) {}

		TypeClass element;
		stackElement* previousElementPointer;

	};

	bool freezed;
	unsigned int containerSize; // used both for stack and array sizes

	TypeClass* array;
	stackElement* topElementPointer;

	// The container provides only stack or fixed array
	// Some functions are used only with stack, while another only with array, some are both compatible

};

template<class TypeClass> inline void Container<TypeClass>::freeze(bool sort)
{
	// Creates new dynamic array and allocates stack there
	// Simultaneously provides pair-type sort while filling array if received value is true (set as a default)
	// Else no sort is provided
	// Array is filled from the end

	if (!freezed)
	{
		int size = containerSize;
		array = new TypeClass[size];
		for (int i = size - 1; i >= 0; i -= 2)
		{
			TypeClass first, second;
			if (topElementPointer) first = pop();
			if (i >= 1)
			{
				second = pop();
				array[i - 1] = !sort || first > second ? second : first;
				array[i] = !sort || first > second ? first : second;
			}
			else
				array[i] = first;
		}
		freezed = true;
		containerSize = size;
	}
}

template<class TypeClass> inline void Container<TypeClass>::insertSort() {
	if (freezed) {
		TypeClass* cell = new TypeClass;
		int j;
		for (unsigned int i = 1; i < containerSize; i++)
		{
			*cell = array[i];
			for (j = i - 1; j >= 0 && array[j] > *cell; j--)
				array[j + 1] = array[j];
			array[j + 1] = *cell;
		}
		delete cell;
	}
}

template<class TypeClass> inline void Container<TypeClass>::push(const TypeClass &element) {
	if (!freezed)
	{
		containerSize++;
		topElementPointer = new stackElement(element, topElementPointer);
	}
}

template<class TypeClass> inline unsigned int Container<TypeClass>::getIndexOf(const TypeClass element)
{
	if (freezed)
	{
		for (unsigned int i = 0; i < containerSize; i++)
			if (array[i] == element) return i + 1;
	}
	else
	{
		int i = 1;
		stackElement* currentElement = topElementPointer;
		while (currentElement)
		{
			if (currentElement->element == element) return i;
			currentElement = currentElement->previousElementPointer;
			i++;
		}
	}
	return 0;
}

template<class TypeClass> inline unsigned int Container<TypeClass>::getSize() const {
	return containerSize;
}

template <class TypeClass> inline TypeClass Container<TypeClass>::pop() {
	if (!freezed && topElementPointer)
	{
		containerSize--;
		stackElement* topElement = topElementPointer;
		topElementPointer = topElementPointer->previousElementPointer;
		TypeClass element = topElement->element;
		delete topElement;
		return element;
	}
}

template<class TypeClass> inline TypeClass& Container<TypeClass>::operator[](const unsigned int i) const {
	if (freezed)
		return array[i];
	else
	{
		unsigned int j = i - 1; // For compatibility with getIndexOf() that returns i + 1 or 0 if element wasn't founded
		stackElement* currentElement = topElementPointer;
		while (j)
		{
			currentElement = currentElement->previousElementPointer;
			j--;
		}
		return currentElement->element;
	}
}

#endif