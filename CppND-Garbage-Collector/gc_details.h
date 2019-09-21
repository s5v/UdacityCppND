// This class defines an element that is stored
// in the garbage collection information list.
//
template <class T>
class PtrDetails
{
  public:
    unsigned refcount{0}; // current reference count
    T *memPtr{NULL};         // pointer to allocated memory
    /* isArray is true if memPtr points
to an allocated array. It is false
otherwise. */
    bool isArray{false}; // true if pointing to array
    /* If memPtr is pointing to an allocated
array, then arraySize contains its size */
    unsigned arraySize{0}; // size of array
    // Here, mPtr points to the allocated memory.
    // If this is an array, then size specifies
    // the size of the array.

    PtrDetails(void)
    {
        // TODO: Implement PtrDetails
        //Do Nothing All Elements Init by Def.
    }
    
    //Have One More Constructor For Initializing from List 
    PtrDetails(T* t_, bool isArr_=false , unsigned arrayS_ = 0)
    {
        memPtr = t_;
        isArray = isArr_;
        arraySize = arrayS_;
        refcount = 1;
    }
    
};
// Overloading operator== allows two class objects to be compared.
// This is needed by the STL list class.
template <class T>
bool operator==(const PtrDetails<T> &ob1,
                const PtrDetails<T> &ob2)
{
    return (ob1.memPtr == ob2.memPtr);
}
