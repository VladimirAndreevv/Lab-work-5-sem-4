#pragma once
#ifndef HHeader
#define HHeader
#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class Iterator;

const size_t SizeMax = 100;

template <typename T>

class Container
{
public:
    Container(){}
    virtual ~Container() {}
    virtual Iterator<T>* GetIterator() = 0;
};

template<typename T>
class ArrayIterator;


template <typename T>
class ArrayClass : public Container<T>
{
private:

    T Items[SizeMax];
    size_t ArraySize;

public:

    void Add(T Object) { Items[ArraySize++] = Object; }
    size_t Size() const { return ArraySize; }

    T operator[](size_t index) const { return Items[index]; }
    T GetElement(size_t index) const { return Items[index]; }
   Iterator<T>* GetIterator() override
    {
        return  new ArrayIterator<T>(Items, ArraySize);
    }
    ArrayClass() : ArraySize(0) {}
};

template<typename T>
class VectorIterator;


template <typename T>
class VectorClass : public Container<T>
{
private:
    vector <T> Items;
    size_t VectorSize;
public:
    T GetItems(size_t i) const { return Items[i]; }
    void PishBack(T Object)
    {
        Items.push_back(Object);
        VectorSize = VectorSize + 1;
    }
    size_t Size() const { return VectorSize; }

    Iterator<T>* GetIterator() override
    {
        return new VectorIterator<T>(Items, VectorSize);
    }
    VectorClass() : VectorSize(0) {}
};

template<typename T>
class Iterator
{
protected:
    Iterator() {}

public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual T GetCurrent() const = 0;
};


template<typename T>
class ArrayIterator : public Iterator<T>
{
private:
    const T* ArrayContainer;
    size_t Position;
    size_t Size;
public:
    ArrayIterator(T* container, size_t size) : ArrayContainer(container), Position(0), Size(size) {}
    void First() override { Position = 0; }
    void Next() override { Position++; }
    bool IsDone() const override { return (Position >= Size); }
    T GetCurrent() const override { return ArrayContainer[Position]; }
};


template<typename T>
class VectorIterator : public Iterator<T>
{
private:
    const vector<T>* VectorContainer;
    size_t position;
    size_t Size;

public:
    VectorIterator(const vector<T>& container, size_t size) : VectorContainer(&container), position(0), Size(size) {}
    void First() override { position = 0; }
    void Next() override { position++; }
    bool IsDone() const override { return (position >= Size); }
    T GetCurrent() const override { return (*VectorContainer)[position]; }
};

template<typename T>
class IteratorDecor : public Iterator<T>
{
protected:
    Iterator<T>* It;

public:
    IteratorDecor(Iterator<T>* it) : It(it) {}
    virtual ~IteratorDecor() { delete It; }
    virtual void First() { It->First(); }
    virtual void Next() { It->Next(); }
    virtual bool IsDone() const { return It->IsDone(); }
    virtual T GetCurrent() const { return It->GetCurrent(); }
};

template<typename ContType, typename TypeItem>
class IteratorAdapter : public Iterator<TypeItem>
{
protected:
    ContType* Cont;
    typename ContType::const_iterator It;

public:
    IteratorAdapter(ContType* cont)
        : Cont(cont)
    {
        It = Cont->begin();
    }

    virtual ~IteratorAdapter() {}
    virtual void First() { It = Cont->begin(); }
    virtual void Next() { It++; }
    virtual bool IsDone() const { return (It == Cont->end()); }
    virtual TypeItem GetCurrent() const { return *It; }
};

#endif
