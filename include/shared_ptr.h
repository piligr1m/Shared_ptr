//
//  shared_ptr.h
//  LW3
//
//  Created by Stanislav Martynov on 26/10/2019.
//  Copyright © 2019 Stanislav Martynov. All rights reserved.
//

#ifndef shared_ptr_h
#define shared_ptr_h

#include <atomic>
#include <iostream>

using namespace std;

class Block
{
public:
    atomic_uint count;

public:
    Block()
    {
        count = 0;
    }
    auto decrease() -> void
    {
        count--;
    }
    auto increase() -> void
    {
        count++;
    }
};

template <typename T>
class Shared_Ptr
{
private:
    T* value; //объект
    Block* block; //блок управления
public:
    Shared_Ptr() // Constructs a shared_ptr with no managed object,
    {
        block = nullptr;
        value = nullptr;
    }
    Shared_Ptr(T* ptr) // Constructs a shared_ptr with ptr as the pointer to the managed object.
    {
        value = ptr;
        block = new Block();
        block->increase();
    }
    Shared_Ptr(const Shared_Ptr<T>& r) // Constructs a shared_ptr which shares ownership of the object managed by r
    {
        value = r.value;
        block = r.block;
        block->increase();
    }
    Shared_Ptr(Shared_Ptr<T>&& r) // Move-constructs a shared_ptr from r
    {
        value = r.value;
        block = r.block;
        r.block = nullptr;
        r.value  = nullptr;
    }
     ~Shared_Ptr() //деструктор
        {
            if(block != nullptr)
            {
                if(block->count == 0)
                {
                    delete value;
                    delete block;
                }
            }
            value = nullptr;
            block = nullptr;
        }
    auto operator = (Shared_Ptr<T>& r) -> Shared_Ptr<T>& //Replaces the managed object with the one managed by r.
    {
        if (value != nullptr)
        {
            block->decrease();
            if (block != nullptr)
            {
                delete value;
                value = nullptr;
                delete block;
                block = nullptr;
            }
        }
        value = r.value;
        block = &r.block;
        block->increase();
        return *this;
    }


       operator bool() const // checks if the stored pointer is not null
    {
        if(value!=nullptr)
            return true;
        return false;
    }
       auto operator*() const -> T& //dereferences the stored pointer
    {
        if (value !=nullptr)
            return *value;
    }
    
       auto operator->() const -> T* //dereferences the stored pointer
    {
        return value;
    }
       
       auto get() -> T* //returns the stored pointer
    {
        if(value!=nullptr)
            return value;
        return 0;
    }
         auto reset() -> void //replaces the managed object
         {
             if(block != nullptr)
             {
                 block -> decrease();
                 if(block -> count == 0)
                 {
                     delete value;
                     delete block;
                 }
                 value = nullptr;
                 block = nullptr;
             }
         }
       auto reset(T* ptr) -> void
       {
           if(block!= nullptr)
           {
               block->decrease();
               if(block -> count == 0)
               {
                   delete value;
                   delete block;
               }
           }
           value = ptr;
           block = new Block();
           block->increase();
       }
           auto swap(Shared_Ptr& r) -> void //swaps the managed objects
       {
           std::swap(block, r.block);
           std::swap(value, r.value);
       }

       // returns the number of shared_ptr objects referring to the same managed object
       auto use_count() const -> size_t
       {
           if (block != nullptr)
               return size_t(block->count);
           else return 0;
       };
};
#endif /* shared_ptr_h */
