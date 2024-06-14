
#include "all_test.h"

template <typename value_type>
bool eq_stack(s21::stack<value_type> my_stack,
              std::stack<value_type> orig_stack) {
  if (my_stack.empty() && orig_stack.empty()) {
    return true;
  }
  if (my_stack.size() == orig_stack.size()) {
    while (orig_stack.size() > 0) {
      if (my_stack.top() != orig_stack.top()) {
        return false;
      }
      my_stack.pop();
      orig_stack.pop();
    }
    return true;
  }
  return false;
}
TEST(Stack, Constructor_default) {
  s21::stack<int> my_stack;
  std::stack<int> orig_stack;
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
}

TEST(Stack, Constructor_initializer_int) {
  s21::stack<int> my_stack({1, 2, 3, 4, 5});
  std::stack<int> orig_stack({1, 2, 3, 4, 5});
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
}

TEST(Stack, Constructor_initializer_char) {
  s21::stack<char> my_stack({'N', 'a', 't', 'a'});
  std::stack<char> orig_stack({'N', 'a', 't', 'a'});
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
}

TEST(Stack, Constructor_copy) {
  s21::stack<char> my_stack({'N', 'a', 't', 'a'});
  s21::stack<char> my_stack_copy(my_stack);
  std::stack<char> orig_stack({'N', 'a', 't', 'a'});
  std::stack<char> orig_stack_copy(orig_stack);
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
  EXPECT_EQ(eq_stack(my_stack_copy, orig_stack_copy), true);
}

TEST(Stack, Operator_copy) {
  s21::stack<int> my_stack({1, 2, 3, 4, 5});
  s21::stack<int> my_stack_copy = my_stack;
  std::stack<int> orig_stack({1, 2, 3, 4, 5});
  std::stack<int> orig_stack_copy = orig_stack;
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
  EXPECT_EQ(eq_stack(my_stack_copy, orig_stack_copy), true);
}

TEST(Stack, Constructor_move) {
  s21::stack<char> my_stack({'N', 'a', 't', 'a'});
  s21::stack<char> my_stack_copy(std::move(my_stack));
  std::stack<char> orig_stack({'N', 'a', 't', 'a'});
  std::stack<char> orig_stack_copy(std::move(orig_stack));
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
  EXPECT_EQ(eq_stack(my_stack_copy, orig_stack_copy), true);
}

TEST(Stack, Operator_move) {
  s21::stack<int> my_stack({1, 2, 3, 4, 5});
  s21::stack<int> my_stack_copy = std::move(my_stack);
  std::stack<int> orig_stack({1, 2, 3, 4, 5});
  std::stack<int> orig_stack_copy = std::move(orig_stack);
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
  EXPECT_EQ(eq_stack(my_stack_copy, orig_stack_copy), true);
}

TEST(Stack, Element_top) {
  s21::stack<int> my_stack({1, 2, 3, 4, 5});
  std::stack<int> orig_stack({1, 2, 3, 4, 5});
  EXPECT_EQ(my_stack.top(), orig_stack.top());  // 1
}

TEST(Stack, Capacity_size) {
  s21::stack<int> my_stack({1, 2, 3, 4, 5});
  std::stack<int> orig_stack({1, 2, 3, 4, 5});
  EXPECT_EQ(my_stack.size(), orig_stack.size());
}

TEST(Stack, Capacity_empty) {
  s21::stack<int> my_stack;
  std::stack<int> orig_stack;
  EXPECT_EQ(my_stack.empty(), orig_stack.empty());
}

TEST(Stack, Capacity_no_empty) {
  s21::stack<int> my_stack({1, 2, 3, 4, 5});
  std::stack<int> orig_stack({1, 2, 3, 4, 5});
  EXPECT_EQ(my_stack.empty(), orig_stack.empty());
}

TEST(Stack, Modifier_push_empty) {
  s21::stack<int> my_stack;
  my_stack.push(6);
  my_stack.push(7);
  std::stack<int> orig_stack;
  orig_stack.push(6);
  orig_stack.push(7);
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
}

TEST(Stack, Modifier_push) {
  s21::stack<int> my_stack({1, 2, 3, 4, 5});
  my_stack.push(6);
  my_stack.push(7);
  std::stack<int> orig_stack({1, 2, 3, 4, 5});
  orig_stack.push(6);
  orig_stack.push(7);
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
}

TEST(Stack, Modifier_pop_to_empty) {
  s21::stack<int> my_stack({1});
  my_stack.pop();
  std::stack<int> orig_stack({1});
  orig_stack.pop();
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
}

TEST(Stack, Modifier_pop) {
  s21::stack<int> my_stack({1, 2, 3, 4, 5});
  my_stack.pop();
  my_stack.pop();
  std::stack<int> orig_stack({1, 2, 3, 4, 5});
  orig_stack.pop();
  orig_stack.pop();
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
}

TEST(Stack, Modifier_swap) {
  s21::stack<int> my_stack({1, 2, 3, 4, 5});
  s21::stack<int> my_stack_other({-1, -2, -3, -4, -5});
  my_stack.swap(my_stack_other);
  std::stack<int> orig_stack({1, 2, 3, 4, 5});
  std::stack<int> orig_stack_other({-1, -2, -3, -4, -5});
  orig_stack.swap(orig_stack_other);
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
}

TEST(Stack, Modifier_insert_many_front) {
  s21::stack<int> my_stack({1, 2, 4, 5});
  my_stack.insert_many_front(10, 20, 30);
  std::stack<int> orig_stack({1, 2, 4, 5, 10, 20, 30});
  EXPECT_EQ(eq_stack(my_stack, orig_stack), true);
}
