#pragma once

#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>
#include <utility>

namespace s21 {

template <typename T, typename Alloc = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  // Стандартный конструктор
  vector(const Alloc &alloc = Alloc()) noexcept
      : m_size_(0), m_capacity_(0), arr_(nullptr) {
    alloc_ = alloc;
  }

  // Параметризированный конструктор:
  explicit vector(size_type n, const Alloc &alloc = Alloc())
      : m_size_(n), m_capacity_(n), arr_(nullptr) {
    alloc_ = alloc;
    if (n > 0) {
      try {
        take_data(nullptr, n, n);
      } catch (...) {
        m_size_ = 0;
        m_capacity_ = 0;
        throw;  //  передаем исключение выше
      }
    }
  }

  // Конструктор копированием:
  vector(const vector &v, const Alloc &alloc = Alloc())
      : m_size_(0), m_capacity_(0), arr_(nullptr) {
    alloc_ = alloc;
    take_data(v.arr_, v.m_size_, v.m_size_);
  };

  // Конструктор перемещением:
  vector(vector &&v, const Alloc &alloc = Alloc()) noexcept
      : m_size_(v.m_size_), m_capacity_(v.m_capacity_), arr_(nullptr) {
    alloc_ = alloc;
    std::swap(arr_, v.arr_);
    v.m_size_ = 0;
    v.m_capacity_ = 0;
  }

  // Инициализация списком:
  vector(std::initializer_list<value_type> const &items,
         const Alloc &alloc = Alloc())
      : m_size_(0), m_capacity_(0), arr_(nullptr) {
    alloc_ = alloc;
    size_type new_size = items.size();
    value_type *new_arr = alloc_.allocate(new_size);
    size_type i = 0;

    try {
      for (auto it = items.begin(); it != items.end(); i++, it++) {
        allocator_traits_.construct(alloc_, new_arr + i, value_type(*it));
      }
      arr_ = new_arr;
      m_size_ = new_size;
      m_capacity_ = new_size;
    } catch (...) {
      free_data_array(new_arr, i, new_size);
      throw;  //  передаем исключение дальше
    }
  };

  //  Деструктор:
  virtual ~vector() {
    free_data_array(arr_, m_size_, m_capacity_);
    m_capacity_ = 0;
    m_size_ = 0;
  }

  //  Оператор присваивания копированием:
  //  В случае исключения объект останется неизменным
  void operator=(vector &v) {
    vector<value_type> old_vector = std::move(*this);

    try {
      take_data(v.arr_, v.m_size_, v.m_capacity_);
    } catch (...) {
      *this = std::move(old_vector);
      throw;  // отправляем исключение дальше
    }
  }

  //  Оператор присваивания перемещением:
  void operator=(vector &&v) noexcept {
    //   if (arr_) {
    //    free_data_array(arr_, m_size_, m_capacity_);
    //  }
    std::swap(arr_, v.arr_);
    std::swap(m_capacity_, v.m_capacity_);
    std::swap(m_size_, v.m_size_);
    // m_capacity_ = v.m_capacity_;
    //  m_size_ = v.m_size_;
    //  v.m_capacity_ = 0;
    //  v.m_size_ = 0;
  }

  //  Увеличение размера вектора:
  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::invalid_argument("In reserve() size greater than max_size!\n");
    }

    if (size > m_capacity_) {
      take_data(arr_, m_size_, size);
    }
  }

  //  Освободить неиспользуемую память:
  void shrink_to_fit() {
    if (m_size_ < m_capacity_) {
      take_data(arr_, m_size_, m_size_);
    }
  }

  //  Изменение размера вектора с инициализаций элементов по умолчанию:
  void resize(size_type size) {
    if (size > max_size()) {
      throw std::invalid_argument("In resize() size greater than max_size!\n");
    }
    if (size < m_size_) {
      while (m_size_ > size) {
        pop_back();  //  обрезаем вектор
      }
    } else if (size > m_size_) {  //  увеличиваем вектор:
      size_type i = m_size_;
      size_type new_capacity = m_capacity_;
      vector<value_type> old_vector = std::move(*this);
      try {
        if (old_vector.m_capacity_ < size) {
          if (old_vector.m_size_ < old_vector.m_capacity_) {
            new_capacity = old_vector.m_size_;
          }
          if (new_capacity == 0) {
            new_capacity = size;
          } else if (new_capacity < size) {
            while (new_capacity < size) {
              new_capacity *= 2;
            }
          }  //  выделяем новую память:
          take_data(old_vector.arr_, old_vector.m_size_, new_capacity);
        } else {  //  используем ту же память:
          *this = std::move(old_vector);
        }
        for (; i < size; ++i) {  //  добавляем знчения по-умолчанию
          allocator_traits_.construct(alloc_, arr_ + i, value_type());
        }
        m_capacity_ = new_capacity;
        m_size_ = size;
      } catch (...) {
        if (old_vector.arr_ != nullptr) {
          free_data_array(arr_, i, m_capacity_);
          *this = std::move(old_vector);
        } else {  //  если память та же:
          for (; i >= m_size_; --i) {
            allocator_traits_.destroy(alloc_, arr_ + i);
          }
        }
        throw;  //  передаем исключение дальше
      }
    }
  }

  //  Очистка содержимого:
  void clear() {
    for (size_type i = 0; i < m_size_; ++i) {
      allocator_traits_.destroy(alloc_, arr_ + i);  //  вызываем деструкторы
    }
    m_size_ = 0;
  }

  //  Добавить элемент в конец вектора:
  void push_back(const_reference add_value) {
    if (m_size_ < m_capacity_) {
      allocator_traits_.construct(alloc_, arr_ + m_size_,
                                  value_type(add_value));
      ++m_size_;
    } else {
      vector<value_type> old_vector(std::move(*this));
      bool was_relocate = false;
      size_type i = 0;

      try {
        if (old_vector.m_capacity_ == 0) {
          reserve(1);
          was_relocate = true;
        } else if (old_vector.m_size_ == old_vector.m_capacity_) {
          reserve(old_vector.m_size_ * 2);
          was_relocate = true;
        } else {  //  остаемся в той же памяти:
          *this = std::move(old_vector);
        }

        if (was_relocate) {  //  было перевыделение памяти
          for (; i < old_vector.m_size_; ++i) {
            allocator_traits_.construct(alloc_, arr_ + i,
                                        value_type(old_vector[i]));
          }
          m_size_ = old_vector.m_size_;
        }
        //  добавляем новый элемент:
        allocator_traits_.construct(alloc_, arr_ + m_size_,
                                    value_type(add_value));
        ++m_size_;
      } catch (...) {
        if (m_size_ == 0) {  //  при перевыделении:
          *this = std::move(old_vector);
        } else if (was_relocate) {  //  при копировании:
          free_data_array(arr_, i, m_capacity_);
          *this = std::move(old_vector);
        }
        throw;  //  кидаем исключение выше
      }
    }
  }

  //  Удалить послдний элемент:
  //  Стандартный вектор не проверяет на пустоту и вызывает неопределенное
  //  поведение, на практике каждый раз проверять на пустоту нецелесообразно
  void pop_back() {
    allocator_traits_.destroy(alloc_, arr_ + m_size_ - 1);
    --m_size_;
  }

  //  Удалить эелемнт по позиции:
  void erase(iterator pos) {
    size_type i = pos - begin();

    if (i > m_size_ || pos < begin()) {
      throw std::out_of_range("In erase() index out ot range!\n");
    }
    allocator_traits_.destroy(alloc_, arr_ + i);  //  уничтожаем наш объект
    for (++i; i < m_size_; ++i) {  //  "смещаем" элементы
      allocator_traits_.construct(alloc_, arr_ + i - 1, arr_[i]);
    }
    --m_size_;
  }

  //  Добавить элемент в указанную позицию:
  iterator insert(iterator pos, const_reference value) {
    size_type insert_i = pos - begin();

    if (insert_i > m_size_ || pos < begin()) {
      throw std::out_of_range("In insert() index out ot range!\n");
    }
    vector<value_type> old_vector = std::move(*this);

    try {
      shift_in_data(old_vector, insert_i, 1);
      //  заполняем пропуск значением:
      allocator_traits_.construct(alloc_, arr_ + insert_i, value_type(value));

    } catch (...) {
      free_data_array(arr_, m_size_, m_capacity_);
      *this = std::move(old_vector);
      throw;  //  передаём исключение выше
    }

    return (arr_ + insert_i);
  }

  //  Вставка нескольких элементов на указанную позицию:
  template <typename... Args>
  const_iterator insert_many(const_iterator pos, Args &&...args) {
    size_type insert_i = pos - begin();

    if (insert_i > m_size_ || pos < begin()) {
      throw std::out_of_range("In insert() index out ot range!\n");
    }
    size_type skip_amount = sizeof...(args);
    vector<value_type> old_vector = std::move(*this);

    try {
      shift_in_data(old_vector, insert_i, skip_amount);

      for (auto element : {std::forward<Args>(args)...}) {
        allocator_traits_.construct(alloc_, arr_ + insert_i,
                                    value_type(element));
        ++insert_i;
      }

    } catch (...) {
      free_data_array(arr_, m_size_, m_capacity_);
      *this = std::move(old_vector);
      throw;  //  отправляем исключение дальше
    }

    return pos;
  }

  //  Вставка нескольких элементов в конец вектора:
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end(), std::forward<Args>(args)...);
  }

  //  Обращение к i-му элементу вектора:
  reference at(size_type i) {
    if (i > m_size_) {
      throw std::out_of_range("In method vector::at() out of range!\n");
    }
    return arr_[i];
  }

  const_reference at(size_type i) const {
    if (i > m_size_) {
      throw std::out_of_range("In method vector::at() out of range!\n");
    }
    return arr_[i];
  }

  //  Индексация по номеру элемента:
  //  Отличие от at() - нет проверки на границы
  reference operator[](size_type pos) { return arr_[pos]; }

  const_reference operator[](size_type pos) const { return arr_[pos]; }

  //  Пустой ли вектор:
  bool empty() const noexcept { return m_size_ == 0; }

  //  Размер вектора:

  size_type size() const noexcept { return m_size_; }

  //  Максимальный размер вектора:

  size_type max_size() const noexcept {
    return allocator_traits_.max_size(alloc_);
  }

  //  Максимальное кол-во элементов без перевыделения памяти:
  size_type capacity() const noexcept { return m_capacity_; }

  //  Итератор на начало вектора:
  iterator begin() noexcept { return iterator(arr_); }

  const_iterator begin() const noexcept { return const_iterator(arr_); }

  //  Итератор на конец вектора (после последнего элемента):
  iterator end() noexcept { return iterator(arr_ + m_size_); }

  const_iterator end() const noexcept { return const_iterator(arr_ + m_size_); }

  //  Обращение к массиву данных:
  value_type *data() noexcept { return arr_; }

  const value_type *data() const noexcept { return arr_; }

  //  Обращение к первому элементу вектора:
  reference front() { return arr_[0]; }

  const_reference front() const { return arr_[0]; }

  //  Обращение к последнему элементу вектора:
  reference back() { return arr_[m_size_ - 1]; }

  const_reference back() const { return arr_[m_size_ - 1]; }

  //  Обмен содержимым:
  void swap(vector &other) noexcept {
    std::swap(other.m_size_, m_size_);
    std::swap(other.m_capacity_, m_capacity_);
    std::swap(other.arr_, arr_);
  }

  //  Поля класса:
 private:
  size_t m_size_;
  size_t m_capacity_;
  Alloc alloc_;
  std::allocator_traits<Alloc> allocator_traits_;

  T *arr_;

  //  Приватные методы:
 private:
  //  Освобождение памяти дата-массива:
  void free_data_array(value_type *&data_arr, size_type size,
                       size_type capacity) {
    if (m_capacity_ && data_arr) {
      for (size_type i = 0; i < size; ++i) {
        allocator_traits_.destroy(alloc_, data_arr + i);
      }
      alloc_.deallocate(data_arr, capacity);
      data_arr = nullptr;
    }
  }

  //  Копирует данные из массива src_data
  void take_data(value_type *src_data, size_type size, size_type new_capacity) {
    value_type *new_arr = alloc_.allocate(new_capacity);
    size_type i = 0;

    try {
      if (src_data != nullptr) {  //  обычное копирование:
        for (; i < size && i < new_capacity; ++i) {
          allocator_traits_.construct(alloc_, new_arr + i,
                                      value_type(src_data[i]));
        }
        free_data_array(arr_, m_size_, m_capacity_);
      } else {  //  инициавлизация по умолчанию:
        for (; i < size; ++i) {
          allocator_traits_.construct(alloc_, new_arr + i, value_type());
        }
      }
      arr_ = new_arr;
      m_size_ = size;
      m_capacity_ = new_capacity;

    } catch (...) {
      free_data_array(new_arr, i, new_capacity);
      throw;  //  передаем ислючение выше
    }
  }

  //  Смещение в векторе, данные которого хранятся в old_vector:
  void shift_in_data(const vector &old_vector, size_type insert_pos,
                     size_type skip_amount) {
    size_type new_capacity = old_vector.m_capacity_;
    size_type new_size = old_vector.m_size_ + skip_amount;

    if (new_capacity == 0) {  //  сколько нужно выделить памяти
      new_capacity = skip_amount;
    } else if (new_size > old_vector.m_capacity_) {
      while (new_capacity <= new_size) {
        new_capacity *= 2;
      }
    }

    value_type *new_arr = alloc_.allocate(new_capacity);
    size_type i = 0;
    try {
      for (; i < new_size; ++i) {
        if (i < insert_pos) {
          //  копируем элементы до смещения
          allocator_traits_.construct(alloc_, new_arr + i,
                                      value_type(old_vector.arr_[i]));
        } else if (skip_amount && i == insert_pos) {
          //  производим смещение
          i += skip_amount - 1;  //  -1 так как цикл сделает ++
        } else if (i > insert_pos) {
          //  копируем элементы после смещения
          allocator_traits_.construct(
              alloc_, new_arr + i,
              value_type(old_vector.arr_[i - skip_amount]));
        }
      }
      arr_ = new_arr;
      m_size_ = new_size;
      m_capacity_ = new_capacity;
    } catch (...) {
      free_shift_exception(new_arr, new_capacity, insert_pos, skip_amount, i);
      throw;  //  передаём исключение выше
    }
  }

  //  Освобождение памяти при исключении в ф-ии shift_in_data() :
  void free_shift_exception(value_type *&bad_arr, size_type size,
                            size_type insert_pos, size_type skip_amount,
                            size_type i) {
    //  Вызываем деструкторы:
    for (size_t j = 0; j < i; ++j) {
      if (i < insert_pos) {
        allocator_traits_.destroy(alloc_, bad_arr + j);
      } else if (skip_amount && i == insert_pos) {
        //  -1 так как цикл сделает ++
        j += skip_amount - 1;
      } else if (i > insert_pos) {
        allocator_traits_.destroy(alloc_, bad_arr + j + skip_amount);
      }
    }
    //  Очищаем сам массив:
    alloc_.deallocate(bad_arr, size);
    bad_arr = nullptr;
  }

};  //  class vector

}  // namespace s21
