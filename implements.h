#ifndef  IMPLEMENTS_H
#define  IMPLEMENTS_H

template <class TypeClass> bool checkElementInArray(const TypeClass element, const TypeClass* array, const int arraySize) {
	for (int i = 0; i < arraySize; i++)
		if (element == array[i])
			return true;
	return false;
}

#endif