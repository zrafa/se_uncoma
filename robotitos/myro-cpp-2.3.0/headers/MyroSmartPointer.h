#pragma once

template <class T>
class MyroSmartPointer {
  private:
    T* ptr;        // pointer to the value
    long* count;   // shared number of owners

  public:
    // initialize pointer with existing pointer
    // - requires that the pointer p is a return value of new
    explicit MyroSmartPointer (T* p=0)
     : ptr(p), count(new long(1)) {
    }

    // copy pointer (one more owner)
    MyroSmartPointer (const MyroSmartPointer<T>& p) throw()
     : ptr(p.ptr), count(p.count) {
        ++*count;
    }

    // destructor (delete value if this was the last owner)
    ~MyroSmartPointer () throw() {
        dispose();
    }

    // assignment (unshare old and share new value)
    MyroSmartPointer<T>& operator= (const MyroSmartPointer<T>& p) throw() {
        if (this != &p) {
            dispose();
            ptr = p.ptr;
            count = p.count;
            ++*count;
        }
        return *this;
    }

    // access the value to which the pointer refers
    T& operator*() const throw() {
        return *ptr;
    }
    T* operator->() const throw() {
        return ptr;
    }

    T* get() const{
        return ptr;
    }

  private:
    void dispose() {
        if (--*count == 0) {
             delete count;
             delete ptr;
        }
    }
    
};
