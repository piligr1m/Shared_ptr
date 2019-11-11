#ifndef shared_ptr_h
#define shared_ptr_h

#include <atomic>
#include <iostream>

using namespace std;

class Block
{
public:
    atomic_uint count;

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
    Shared_Ptr() // Конструктор по умолчанию создаёт shared_ptr, не управляющий никем
    {
        block = nullptr;
        value = nullptr;
    }
    Shared_Ptr(T data) // Берёт неуправляемый указатель ptr под автоматическое управление
    {
        value = new T(data);
        block = new Block();
        block->increase();
    }
    Shared_Ptr(const Shared_Ptr<T>& r) //Создает shared_ptr которая разделяет право собственности на объект, управляемый r.
    {
        value = r.value;
        block = r.block;
        block->increase();
    }
        Shared_Ptr(Shared_Ptr<T>&& r) //  Move-строит shared_ptr от r.
    {
        value = r.value;
        block = r.block;
        *this = r.value;
        r.block = nullptr;
        r.value  = nullptr;
        return *this;
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
     auto operator = (Shared_Ptr<T>& r) -> Shared_Ptr<T>& //Заменяет управляемый объект объектом управляемым r.
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

       // проверяет, указывает ли указатель на объект
       operator bool() const
    {
        if(value!=nullptr)
            return true;
        return false;
    }
       auto operator*() const -> T& //Разыменовывает указатель на управляемый объект.
    {
        if (value !=nullptr)
            return *value;
    }
    
       auto operator->() const -> T* //Разыменовывает указатель на управляемый объект.
    {
        return value;
    }
       
       auto get() -> T* //возвращает указатель на управляемый объект
    {
        if(value!=nullptr)
            return value;
        return 0;
    }
         auto reset() -> void //заменяет объект, которым владеет
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
           auto swap(Shared_Ptr& r) -> void //обмен содержимым
       {
           std::swap(block, r.block);
           std::swap(value, r.value);
       }

       // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
       auto use_count() const -> size_t
       {
           if (block != nullptr)
               return size_t(block->count);
           else return 0;
       };
};
#endif /* shared_ptr_h */
