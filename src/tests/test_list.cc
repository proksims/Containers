#include "all_test.h"

template <typename value_type>
bool eq_list(s21::list<value_type> my_list, std::list<value_type> orig_list) {
  if (my_list.empty() && orig_list.empty()) {
    return true;
  }
  if (my_list.size() == orig_list.size()) {
    typename s21::list<value_type>::const_iterator my_it = my_list.cbegin();
    typename std::list<value_type>::const_iterator orig_it = orig_list.cbegin();
    for (; orig_it != orig_list.cend(); ++my_it, ++orig_it) {
      if (*orig_it != *my_it) {
        return false;
      }
    }
    return true;
  }
  return false;
}

TEST(List, Constructor_default) {
  s21::list<int> my_list;
  std::list<int> orig_list;
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Constructor_size_type_int) {
  s21::list<int> my_list(3);
  std::list<int> orig_list(3);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Constructor_initializer_int) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Constructor_initializer_char) {
  s21::list<char> my_list = {'N', 'a', 't', 'a'};
  std::list<char> orig_list = {'N', 'a', 't', 'a'};
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Constructor_copy) {
  s21::list<char> my_list = {'N', 'a', 't', 'a'};
  s21::list<char> my_list_copy(my_list);
  std::list<char> orig_list = {'N', 'a', 't', 'a'};
  std::list<char> orig_list_copy(orig_list);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
  EXPECT_EQ(eq_list(my_list_copy, orig_list_copy), true);
}

TEST(List, Operator_copy) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  s21::list<int> my_list_copy = my_list;
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  std::list<int> orig_list_copy = orig_list;
  EXPECT_EQ(eq_list(my_list, orig_list), true);
  EXPECT_EQ(eq_list(my_list_copy, orig_list_copy), true);
}

TEST(List, Constructor_move) {
  s21::list<char> my_list = {'N', 'a', 't', 'a'};
  s21::list<char> my_list_copy(std::move(my_list));
  std::list<char> orig_list = {'N', 'a', 't', 'a'};
  std::list<char> orig_list_copy(std::move(orig_list));
  EXPECT_EQ(eq_list(my_list, orig_list), true);
  EXPECT_EQ(eq_list(my_list_copy, orig_list_copy), true);
}

TEST(List, Operator_move) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  s21::list<int> my_list_copy = std::move(my_list);
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  std::list<int> orig_list_copy = std::move(orig_list);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
  EXPECT_EQ(eq_list(my_list_copy, orig_list_copy), true);
}

TEST(List, Element_front) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  EXPECT_EQ(my_list.front(), orig_list.front());  // 1
}

TEST(List, Element_back) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  EXPECT_EQ(my_list.back(), orig_list.back());  // 5
}


TEST(List, Modifier_insert_begin) {
  s21::list<int> my_list = {1, 2, 4, 5};
  s21::list<int>::const_iterator my_it = my_list.cbegin();
  s21::list<int>::iterator res_my_it = my_list.insert(my_it, 0);
  std::list<int> orig_list = {1, 2, 4, 5};
  std::list<int>::const_iterator orig_it = orig_list.cbegin();
  std::list<int>::iterator res_orig_it = orig_list.insert(orig_it, 0);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
  EXPECT_EQ(*res_my_it, *res_orig_it);
}

TEST(List, Modifier_insert_end) {
  s21::list<int> my_list = {1, 2, 4, 5};
  s21::list<int>::const_iterator my_it = my_list.cend();
  s21::list<int>::iterator res_my_it = my_list.insert(my_it, 6);
  std::list<int> orig_list = {1, 2, 4, 5};
  std::list<int>::const_iterator orig_it = orig_list.cend();
  std::list<int>::iterator res_orig_it = orig_list.insert(orig_it, 6);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
  EXPECT_EQ(*res_my_it, *res_orig_it);
}

TEST(List, Modifier_insert_centre) {
  s21::list<int> my_list = {1, 2, 4, 5};
  s21::list<int>::const_iterator my_it = my_list.cbegin();
  ++my_it;
  s21::list<int>::iterator res_my_it = my_list.insert(my_it, 10);
  std::list<int> orig_list = {1, 2, 4, 5};
  std::list<int>::const_iterator orig_it = orig_list.cbegin();
  ++orig_it;
  std::list<int>::iterator res_orig_it = orig_list.insert(orig_it, 10);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
  EXPECT_EQ(*res_my_it, *res_orig_it);
}

TEST(List, Modifier_insert_empty) {
  s21::list<int> my_list;
  s21::list<int>::const_iterator my_it = my_list.cbegin();
  s21::list<int>::iterator res_my_it = my_list.insert(my_it, 10);
  std::list<int> orig_list;
  std::list<int>::const_iterator orig_it = orig_list.cbegin();
  std::list<int>::iterator res_orig_it = orig_list.insert(orig_it, 10);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
  EXPECT_EQ(*res_my_it, *res_orig_it);
}

TEST(List, Modifier_erase_begin) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator my_it = my_list.begin();
  my_list.erase(my_it);
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  std::list<int>::iterator orig_it = orig_list.begin();
  orig_list.erase(orig_it);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_erase_end) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator my_it = my_list.end();
  --my_it;
  my_list.erase(my_it);
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  std::list<int>::iterator orig_it = orig_list.end();
  --orig_it;
  orig_list.erase(orig_it);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_erase_centre) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator my_it = my_list.begin();
  ++my_it;
  my_list.erase(my_it);
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  std::list<int>::iterator orig_it = orig_list.begin();
  ++orig_it;
  orig_list.erase(orig_it);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_erase_to_empty) {
  s21::list<int> my_list = {1};
  s21::list<int>::iterator my_it = my_list.begin();
  my_list.erase(my_it);
  std::list<int> orig_list = {1};
  std::list<int>::iterator orig_it = orig_list.begin();
  orig_list.erase(orig_it);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_push_empty) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  my_list.clear();
  my_list.push_front(0);
  my_list.push_front(-1);
  my_list.push_back(6);
  my_list.push_back(7);
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  orig_list.clear();
  orig_list.push_front(0);
  orig_list.push_front(-1);
  orig_list.push_back(6);
  orig_list.push_back(7);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_push) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  my_list.push_front(0);
  my_list.push_front(-1);
  my_list.push_back(6);
  my_list.push_back(7);
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  orig_list.push_front(0);
  orig_list.push_front(-1);
  orig_list.push_back(6);
  orig_list.push_back(7);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_pop_to_empty) {
  s21::list<int> my_list = {1};
  my_list.pop_back();
  std::list<int> orig_list = {1};
  orig_list.pop_back();
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_pop) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  my_list.pop_front();
  my_list.pop_front();
  my_list.pop_back();
  my_list.pop_back();
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  orig_list.pop_front();
  orig_list.pop_front();
  orig_list.pop_back();
  orig_list.pop_back();
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_swap) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  s21::list<int> my_list_other = {-1, -2, -3, -4, -5};
  my_list.swap(my_list_other);
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  std::list<int> orig_list_other = {-1, -2, -3, -4, -5};
  orig_list.swap(orig_list_other);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_merge_to_epmty) {
  s21::list<int> my_list;
  s21::list<int> my_list_other = {0, 3, 2, 1};
  my_list.merge(my_list_other);
  std::list<int> orig_list;
  std::list<int> orig_list_other = {0, 3, 2, 1};
  orig_list.merge(orig_list_other);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_merge_from_empty) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  s21::list<int> my_list_other;
  my_list.merge(my_list_other);
  std::list<int> orig_list = {1, 2, 3, 4, 5};
  std::list<int> orig_list_other;
  orig_list.merge(orig_list_other);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_merge) {
  s21::list<int> my_list = {2, 2, 3, 4, 5};
  s21::list<int> my_list_other = {0, 1, 3, 2, 1};
  my_list.merge(my_list_other);
  std::list<int> orig_list = {2, 2, 3, 4, 5};
  std::list<int> orig_list_other = {0, 1, 3, 2, 1};
  orig_list.merge(orig_list_other);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_splice) {
  s21::list<int> my_list = {2, 2, 3, 4, 5};
  s21::list<int> my_list_other = {0, 1, 3, 2, 1};
  s21::list<int>::const_iterator my_it = my_list.cbegin();
  my_list.splice(my_it, my_list_other);
  std::list<int> orig_list = {2, 2, 3, 4, 5};
  std::list<int> orig_list_other = {0, 1, 3, 2, 1};
  std::list<int>::const_iterator orig_it = orig_list.cbegin();
  orig_list.splice(orig_it, orig_list_other);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_to_empty) {
  s21::list<int> my_list;
  s21::list<int> my_list_other = {0, 1, 3, 2, 1};
  s21::list<int>::const_iterator my_it = my_list.cbegin();
  my_list.splice(my_it, my_list_other);
  std::list<int> orig_list;
  std::list<int> orig_list_other = {0, 1, 3, 2, 1};
  std::list<int>::const_iterator orig_it = orig_list.cbegin();
  orig_list.splice(orig_it, orig_list_other);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}
TEST(List, Modifier_from_empty) {
  s21::list<int> my_list = {0, 1, 3, 2, 1};
  ;
  s21::list<int> my_list_other;
  s21::list<int>::const_iterator my_it = my_list.cbegin();
  my_list.splice(my_it, my_list_other);
  std::list<int> orig_list = {0, 1, 3, 2, 1};
  ;
  std::list<int> orig_list_other;
  std::list<int>::const_iterator orig_it = orig_list.cbegin();
  orig_list.splice(orig_it, orig_list_other);
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_reverse) {
  s21::list<int> my_list = {2, 2, 3, 4, 5};
  my_list.reverse();
  std::list<int> orig_list = {2, 2, 3, 4, 5};
  orig_list.reverse();
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}
TEST(List, Modifier_reverse_one) {
  s21::list<int> my_list = {2};
  my_list.reverse();
  std::list<int> orig_list = {2};
  orig_list.reverse();
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}
TEST(List, Modifier_reverse_empty) {
  s21::list<int> my_list;
  my_list.reverse();
  std::list<int> orig_list;
  orig_list.reverse();
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_unique) {
  s21::list<int> my_list = {2, 2, 3, 4, 5, 2, 6, 6, 6, 8};
  my_list.unique();
  std::list<int> orig_list = {2, 2, 3, 4, 5, 2, 6, 6, 6, 8};
  orig_list.unique();
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}
TEST(List, Modifier_unique_one) {
  s21::list<int> my_list = {2};
  my_list.unique();
  std::list<int> orig_list = {2};
  orig_list.unique();
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}
TEST(List, Modifier_unique_empty) {
  s21::list<int> my_list;
  my_list.unique();
  std::list<int> orig_list;
  orig_list.unique();
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_sort) {
  s21::list<int> my_list = {2, 2, 3, 4, 5, 1, 6, 6, 2, 8};
  my_list.sort();
  std::list<int> orig_list = {2, 2, 3, 4, 5, 1, 6, 6, 2, 8};
  orig_list.sort();
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}
TEST(List, Modifier_not_sort) {
  s21::list<int> my_list = {1, 2, 3, 4, 5, 6, 7};
  my_list.sort();
  std::list<int> orig_list = {1, 2, 3, 4, 5, 6, 7};
  orig_list.sort();
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_insert_many_front) {
  s21::list<int> my_list = {1, 2, 4, 5};
  my_list.insert_many_front(10, 20, 30);
  std::list<int> orig_list = {10, 20, 30, 1, 2, 4, 5};
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}
TEST(List, Modifier_insert_many_back) {
  s21::list<int> my_list = {1, 2, 4, 5};
  my_list.insert_many_back(10, 20, 30);
  std::list<int> orig_list = {1, 2, 4, 5, 10, 20, 30};
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}

TEST(List, Modifier_insert_many) {
  s21::list<int> my_list = {1, 2, 4, 5};
  s21::list<int>::const_iterator my_it = my_list.cbegin();
  ++my_it;
  my_list.insert_many(my_it, 10, 20, 30);
  std::list<int> orig_list = {1, 10, 20, 30, 2, 4, 5};
  EXPECT_EQ(eq_list(my_list, orig_list), true);
}
