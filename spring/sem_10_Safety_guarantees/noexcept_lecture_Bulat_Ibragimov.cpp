// Bad implementation (neither effective nor safe)
template <class T>
void Stack<T>::Reallocate(size_t new_capacity) {
    if (new_capacity == capacity_) {
    	return;
    }
    
    auto new_buffer = new_capacity > 0 ? new T[new_capacity] : nullptr;
    auto new_size = std::min(size_, new_capacity);
    for (size_t i = 0; i < new_size; ++i) {  // проверка на внимательность, что не так
    	new_buffer[i] = buffer_[i];
    }

    delete[] buffer_;
    buffer_ = new_buffer;
    size_ = new_size;
    capacity_ = new_capacity;
}





// Bad implementation (safe but not effective)
template <class T>
void Stack<T>::Reallocate(size_t new_capacity) {
    if (new_capacity == capacity_) {
    	return;
    }
    
    auto new_buffer = new_capacity > 0 ? new T[new_capacity] : nullptr;
    auto new_size = std::min(size_, new_capacity);
    try {
        for (size_t i = 0; i < new_size; ++i) {
    	    new_buffer[i] = buffer_[i];  // копирование? зачем?
        }
    } catch (...) {
    	delete[] new_buffer;
    	throw;
    }

    delete[] buffer_;
    buffer_ = new_buffer;
    size_ = new_size;
    capacity_ = new_capacity;
}


// Effective and safe (?)
template <class T>
void Stack<T>::Reallocate(size_t new_capacity) {
    if (new_capacity == capacity_) {
    	return;
    }
    
    auto new_buffer = new_capacity > 0 ? new T[new_capacity] : nullptr;
    auto new_size = std::min(size_, new_capacity);
    try {
        for (size_t i = 0; i < new_size; ++i) {
    	    new_buffer[i] = std::move(buffer_[i]);
        }  // а если переместили часть и сломались
    } catch (...) {
    	delete[] new_buffer;
    	throw;
    }

    delete[] buffer_;
    buffer_ = new_buffer;
    size_ = new_size;
    capacity_ = new_capacity;
}



// Effective and safe (???)
template <class T>
void Stack<T>::Reallocate(size_t new_capacity) {
    if (new_capacity == capacity_) {
    	return;
    }
    
    auto new_buffer = new_capacity > 0 ? new T[new_capacity] : nullptr;
    auto new_size = std::min(size_, new_capacity);
    size_t moved_cnt = 0;
    try {
        for (; moved_cnt < new_size; ++moved_cnt) {
    	    new_buffer[moved_cnt] = std::move(buffer_[moved_cnt]);
        }
    } catch (...) {
    	for (size_t i = 0; i < moved_cnt; ++i) {
    		buffer_[i] = std::move(new_buffer[i]);  // а если снова исключение??) рекурсивно туда сюда мучаемся
    	}
    	delete[] new_buffer;
    	throw;
    }

    delete[] buffer_;
    buffer_ = new_buffer;
    size_ = new_size;
    capacity_ = new_capacity;
}



// Effective and safe (!)
template <class T>
void Stack<T>::Reallocate(size_t new_capacity) {
    if (new_capacity == capacity_) {
    	return;
    }
    
    auto new_buffer = new_capacity > 0 ? new T[new_capacity] : nullptr;
    auto new_size = std::min(size_, new_capacity);
    size_t i = 0;
    try {
        for (; i < new_size; ++i) {
    	    new_buffer[i] = std::move_if_noexcept(buffer_[i]);  // <-- !!!
        }  // если перемещение npexcept, to move, иначе просто ссылка и копирование
    } catch (...) {
    	delete[] new_buffer;
    	throw;
    }

    delete[] buffer_;
    buffer_ = new_buffer;
    size_ = new_size;
    capacity_ = new_capacity;
}
