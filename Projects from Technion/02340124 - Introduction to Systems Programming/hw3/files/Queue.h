#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include "iostream"
#include <string>


template<class T>

class Queue
{
private:

    class Node
    {
    public:
        T m_data;
        Node* m_next;
        Node()
        {
            m_next = nullptr;
        }
        explicit Node(T data): m_data(data), m_next(nullptr)
        {

        }

        T& operator*()
        {
            return m_data;
        }

    };

    Node* m_tail;
    Node* m_head;
    void deleteList()
    {
        while(m_head)
        {
            Node *toDelete = m_head;
            m_head = m_head->m_next;
            toDelete->m_next = nullptr;
            delete toDelete;
        }
        m_tail = nullptr;
        m_head = nullptr;
    }


public:

    class Iterator {
    public:
        Node* m_element;
        ~Iterator()
        {
            m_element = nullptr;
        }
        explicit Iterator(Node *node)
        {
            m_element = node;
        }
        friend class Queue<T>;
        Queue<T>::Iterator operator++()
        {
            if(!m_element)
            {
                throw InvalidOperation{};
            }

            m_element = m_element->m_next;

            return *this;
        }
        bool operator!=(Iterator i )
        {
            return (m_element != i.m_element);
        }

        T& operator*()
        {
            if(!m_element)
            {
                throw InvalidOperation{};
            }
            return m_element->m_data;
        }
        class Exception : public std::exception {};
        class InvalidOperation : public Exception{};
    };

    class ConstIterator
    {
    public:
        Node *m_element;
        ~ConstIterator()
        {
            m_element = nullptr;
        }
        explicit ConstIterator(Queue<T>::Node *node)
        {
            m_element = node;
        }
        friend class Queue<T>;
        bool operator!=(const ConstIterator i ) const
        {
            return (m_element != i.m_element);
        }

        const T& operator*() const
        {
            if(!m_element)
            {
                throw InvalidOperation{};
            }
            return m_element->m_data;
        }

        Queue<T>::ConstIterator operator++()
        {
            if(!m_element)
            {
                throw InvalidOperation{};
            }
            m_element = m_element->m_next;
            return *this;
        }

        class Exception : public std::exception {};
        class InvalidOperation : public Exception{};

    };


    class Exception : public std::exception {};
    class EmptyQueue : public Exception{};
    class InvalidOperation : public Exception{};

    Queue<T>()
    {
        m_head = nullptr;
        m_tail = nullptr;
    }

    ~Queue<T>()
    {
        this->deleteList();
    }
    Queue<T>(const Queue<T>& queue)
    {
        m_tail = nullptr;
        m_head = nullptr;
        for(typename Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it)
        {
            try
            {
                this->pushBack((*it));
            }
            catch (std::bad_alloc)
            {
                this->deleteList();
                m_tail = nullptr;
                m_head = nullptr;
                throw std::bad_alloc();
            }
        }
    }

    Queue<T>& operator = (const Queue<T>& queue1)
    {
        if(this==&queue1)
        {
            return *this;
        }
        Queue<T> backUp = *this; // to preserve the initial queque in case assignment fails
        this->deleteList();
        m_tail = nullptr;
        m_head = nullptr;
        for(typename Queue<T>::ConstIterator it = queue1.begin(); it != queue1.end(); ++it)
        {
            try
            {
                this->pushBack(*(it));
            }

            catch (std::bad_alloc)
            {
                this->deleteList();
                m_tail = nullptr;
                m_head = nullptr;
                *this = backUp;
                throw std::bad_alloc();
            }
        }
        return *this;
    }


    void pushBack(const T& data)
    {
        Node *tempNode = new Node(data);
        if(m_head== nullptr)
        {
            m_head = tempNode;
            m_tail = tempNode;
            return;
        }
        m_tail->m_next=tempNode;
        m_tail = tempNode;
    }

    T& front() const
    {
        if(this->size()<=0)
        {
            throw EmptyQueue{};
        }
        return m_head->m_data;
    }

    void popFront()
    {
        int size = Queue<T>::size();
        if(size<=0)
        {
            throw EmptyQueue{};
        }
        if(size==1)
        {
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
            return;
        }

        Node* temp = m_head;
        m_head = m_head->m_next;
        temp->m_next = nullptr;
        delete temp;
        temp = nullptr;
    }

    int size() const
    {
        int count =0;
        for(Queue<T>::ConstIterator it = this->begin(); it != this->end(); ++it )
        {
            count++;

        }
        return count;
    }

    Queue<T>::Iterator begin()
    {
        return Iterator(m_head);
    }
    Queue<T>::ConstIterator begin() const
    {
        return ConstIterator(m_head);
    }

    Queue<T>::Iterator end()
    {
        if(m_tail== nullptr)
        {
            return Iterator(m_tail);
        }
        return Iterator(m_tail->m_next);
    }

    Queue<T>::ConstIterator end() const
    {
        if(m_tail== nullptr)
        {
            return ConstIterator(m_tail);
        }
        return ConstIterator(m_tail->m_next);
    }
};


template<class T, typename Condition>

Queue<T> filter(Queue<T> queue1,Condition condition)
{
    Queue<T> resultQueue = Queue<T>();
    for(typename Queue<T>::Iterator it = queue1.begin(); it != queue1.end(); ++it )
    {
        if(condition(it.m_element->m_data))
        {
            resultQueue.pushBack(*it);
        }
    }

    return resultQueue;
}

template <class T, typename Transformation>
Queue<T> transform(Queue<T> &queue1,Transformation transformation)
{
    for(typename Queue<T>::Iterator it = queue1.begin(); it != queue1.end(); ++it )
    {
        transformation(it.m_element->m_data);
    }
    return queue1;
}

#endif //EX3_QUEUE_H
