#pragma once

#include <initializer_list>

namespace s21 {

template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  //  Стандартный конструктор:
  array() = default;

  // Инициализация списком:
  array(std::initializer_list<value_type> const &items) {
    auto iter = items.begin();
    for (size_type i = 0; i < N && iter != items.end(); ++iter, ++i) {
      arr_[i] = *iter;
    }
  }

  //  Конструктор копированием:
  array(const array &other) {
    for (size_type i = 0; i < N; ++i) {
      arr_[i] = other.arr_[i];
    }
  }

  //  Конструктор перемещением:
  array(array &&other) noexcept {
    std::swap_ranges(begin(), end(), other.begin());
  }

  //    Деструктор:
  ~array() = default;

  //    Приравнивание копированием:
  array &operator=(array &other) {
    for (auto i = 0; i < N; ++i) {
      arr_[i] = other.arr_[i];
    }

    return *this;
  }

  //    Приранивание перемещением:
  array &operator=(array &&other) {
    std::swap_ranges(begin(), end(), other.begin());
    return *this;
  }

  //    Доступ к массиву:
  value_type *data() noexcept { return arr_; }

  const value_type *data() const noexcept { return arr_; }

  //  Доступ к элементу:
  reference operator[](size_type pos) noexcept { return arr_[pos]; }

  const_reference operator[](size_type pos) const noexcept { return arr_[pos]; }

  //  Доступ к элементу с проверкой на границы:
  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("In method array::at() out of range!\n");
    }
    return arr_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= N) {
      throw std::out_of_range("In method array::at() out of range!\n");
    }
    return arr_[pos];
  }

  //  Доступ к первому элементу:
  reference front() noexcept { return arr_[0]; }

  const_reference front() const noexcept { return arr_[0]; }

  //  Доступ к последнему элементу:
  reference back() noexcept {
    size_type index = N - 1;
    if (index == (size_type)-1) {
      return arr_[0];
    } else {
      return arr_[index];
    }
  }

  const_reference back() const noexcept {
    size_type index = N - 1;
    if (index == (size_type)-1) {
      return arr_[0];
    } else {
      return arr_[index];
    }
  }

  //  Размер массива:
  size_type size() const noexcept { return N; }

  //  Максимальное число элементов в мссиве:
  size_type max_size() const noexcept { return N; }

  //  Проверка на пустоту:
  bool empty() const noexcept { return N == 0; }

  //  Итератор на начало:
  iterator begin() noexcept { return iterator(data()); }

  const_iterator begin() const noexcept { return const_iterator(data()); }

  //  Итератор на конец:
  iterator end() noexcept { return iterator(data() + N); }

  const_iterator end() const noexcept { return const_iterator(data() + N); }

  //  Перемещение массивов:
  void swap(array &other) noexcept {
    std::swap_ranges(begin(), end(), other.begin());
  }

  //  Заполнение массива значением:
  void fill(const_reference value) {
    for (size_type i = 0; i < N; ++i) {
      arr_[i] = value;
    }
  }

  //  Поля класса:
 private:
  value_type arr_[N]{};

};  //  class array

}  // namespace s21
