#include "all_test.h"

template <typename value_type>
bool eq_queue(s21::queue<value_type> my_queue,
              std::queue<value_type> orig_queue) {
  if (my_queue.empty() && orig_queue.empty()) {
    return true;
  }
  if (my_queue.size() == orig_queue.size()) {
    while (orig_queue.size() > 0) {
      if (my_queue.front() != orig_queue.front()) {
        return false;
      }
      my_queue.pop();
      orig_queue.pop();
    }
    return true;
  }
  return false;
}
TEST(Queue, Constructor_default) {
  s21::queue<int> my_queue;
  std::queue<int> orig_queue;
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
}

TEST(Queue, Constructor_initializer_int) {
  s21::queue<int> my_queue({1, 2, 3, 4, 5});
  std::queue<int> orig_queue({1, 2, 3, 4, 5});
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
}

TEST(Queue, Constructor_initializer_char) {
  s21::queue<char> my_queue({'N', 'a', 't', 'a'});
  std::queue<char> orig_queue({'N', 'a', 't', 'a'});
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
}

TEST(Queue, Constructor_copy) {
  s21::queue<char> my_queue({'N', 'a', 't', 'a'});
  s21::queue<char> my_queue_copy(my_queue);
  std::queue<char> orig_queue({'N', 'a', 't', 'a'});
  std::queue<char> orig_queue_copy(orig_queue);
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
  EXPECT_EQ(eq_queue(my_queue_copy, orig_queue_copy), true);
}

TEST(Queue, Operator_copy) {
  s21::queue<int> my_queue({1, 2, 3, 4, 5});
  s21::queue<int> my_queue_copy = my_queue;
  std::queue<int> orig_queue({1, 2, 3, 4, 5});
  std::queue<int> orig_queue_copy = orig_queue;
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
  EXPECT_EQ(eq_queue(my_queue_copy, orig_queue_copy), true);
}

TEST(Queue, Constructor_move) {
  s21::queue<char> my_queue({'N', 'a', 't', 'a'});
  s21::queue<char> my_queue_copy(std::move(my_queue));
  std::queue<char> orig_queue({'N', 'a', 't', 'a'});
  std::queue<char> orig_queue_copy(std::move(orig_queue));
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
  EXPECT_EQ(eq_queue(my_queue_copy, orig_queue_copy), true);
}

TEST(Queue, Operator_move) {
  s21::queue<int> my_queue({1, 2, 3, 4, 5});
  s21::queue<int> my_queue_copy = std::move(my_queue);
  std::queue<int> orig_queue({1, 2, 3, 4, 5});
  std::queue<int> orig_queue_copy = std::move(orig_queue);
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
  EXPECT_EQ(eq_queue(my_queue_copy, orig_queue_copy), true);
}

TEST(Queue, Element_front) {
  s21::queue<int> my_queue({1, 2, 3, 4, 5});
  std::queue<int> orig_queue({1, 2, 3, 4, 5});
  EXPECT_EQ(my_queue.front(), orig_queue.front());
}

TEST(Queue, Element_back) {
  s21::queue<int> my_queue({1, 2, 3, 4, 5});
  std::queue<int> orig_queue({1, 2, 3, 4, 5});
  EXPECT_EQ(my_queue.back(), orig_queue.back());
}

TEST(Queue, Capacity_size) {
  s21::queue<int> my_queue({1, 2, 3, 4, 5});
  std::queue<int> orig_queue({1, 2, 3, 4, 5});
  EXPECT_EQ(my_queue.size(), orig_queue.size());
}

TEST(Queue, Capacity_empty) {
  s21::queue<int> my_queue;
  std::queue<int> orig_queue;
  EXPECT_EQ(my_queue.empty(), orig_queue.empty());
}

TEST(Queue, Capacity_no_empty) {
  s21::queue<int> my_queue({1, 2, 3, 4, 5});
  std::queue<int> orig_queue({1, 2, 3, 4, 5});
  EXPECT_EQ(my_queue.empty(), orig_queue.empty());
}

TEST(Queue, Modifier_push_empty) {
  s21::queue<int> my_queue;
  my_queue.push(6);
  my_queue.push(7);
  std::queue<int> orig_queue;
  orig_queue.push(6);
  orig_queue.push(7);
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
}

TEST(Queue, Modifier_push) {
  s21::queue<int> my_queue({1, 2, 3, 4, 5});
  my_queue.push(6);
  my_queue.push(7);
  std::queue<int> orig_queue({1, 2, 3, 4, 5});
  orig_queue.push(6);
  orig_queue.push(7);
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
}

TEST(Queue, Modifier_pop_to_empty) {
  s21::queue<int> my_queue({1});
  my_queue.pop();
  std::queue<int> orig_queue({1});
  orig_queue.pop();
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
}

TEST(Queue, Modifier_pop) {
  s21::queue<int> my_queue({1, 2, 3, 4, 5});
  my_queue.pop();
  my_queue.pop();
  std::queue<int> orig_queue({1, 2, 3, 4, 5});
  orig_queue.pop();
  orig_queue.pop();
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
}

TEST(Queue, Modifier_swap) {
  s21::queue<int> my_queue({1, 2, 3, 4, 5});
  s21::queue<int> my_queue_other({-1, -2, -3, -4, -5});
  my_queue.swap(my_queue_other);
  std::queue<int> orig_queue({1, 2, 3, 4, 5});
  std::queue<int> orig_queue_other({-1, -2, -3, -4, -5});
  orig_queue.swap(orig_queue_other);
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
}

TEST(Queue, Modifier_insert_many_back) {
  s21::queue<int> my_queue({1, 2, 4, 5});
  my_queue.insert_many_back(10, 20, 30);
  std::queue<int> orig_queue({1, 2, 4, 5, 10, 20, 30});
  EXPECT_EQ(eq_queue(my_queue, orig_queue), true);
}
