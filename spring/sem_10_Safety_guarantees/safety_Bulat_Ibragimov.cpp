template <class T>
class Stack {
	T* buffer_;
	size_t size_;
	size_t capacity_;
	...
};


// 0. No safety guarantee
template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
    	size_ = other.size_;
    	capacity_ = other.size_;
    	delete[] buffer_;
    	buffer_ = new T[capacity_];  // <-- std::bad_alloc  // невалидное состояние
    	for (size_t i = 0; i < size_; ++i) {
    		buffer_[i] = other.buffer_[i];  // <-- исключение при присваивании
    	}
    }
    return *this;
}


// 1. Nothrow guarantee
template <class T>
void Swap(Stack<T>& other) noexcept {
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
	std::swap(buffer_, other.buffer_);	
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept {
	Swap(other);
	return *this;
}


// 2. Basic safety guarantee
template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
    	size_ = 0;
    	capacity_ = 0;
    	delete[] buffer_;
    	buffer_ = nullptr;

    	buffer_ = new T[other.size_];  // <-- std::bad_alloc
    	capacity_ = other.size_;
    	for (; size_ < other.size_; ++size_) {
    		buffer_[size_] = other.buffer_[size_];  // <-- исключение при присваивании  // валидное состояние
    	}
    }
    return *this;
}


// 3. Strong safety guarantee
template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
    	auto new_buffer = new T[other.size_];  // <-- std::bad_alloc
    	try {
    	    for (size_t i = 0; i < other.size_; ++i) {
    		    new_buffer[i] = other.buffer_[i];  // <-- исключение при присваивании
     	    }
     	} catch (...) {
     		delete[] new_buffer;
     		throw;
     	}
// -------------
     	delete[] buffer_;
     	buffer_ = new_buffer;
     	size_ = other.size_;
     	capacity_ = other.size_;
    }
    return *this;
}


// 3*. Strong safety guarantee
template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    auto tmp_stack = other;  // Предполагаем, что написан безопасный конструктор копирования
    Swap(tmp_stack);
    return *this;
}
