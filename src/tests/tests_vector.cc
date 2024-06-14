
#include "all_test.h"

using namespace std;

class MyClass {
 public:
  void SetData(int number) {
    i_ = number;
    f_ = number;
    d_ = number;
  }

  void PrintData() {
    std::cout << "\n\n"
              << "NoConstructorClass data = " << i_ << " " << f_ << " " << d_
              << "\n\n";
  }

  int get_i() { return i_; }

  int get_f() { return f_; }

  int get_d() { return d_; }

  ~MyClass() {}

 private:
  int i_;
  float f_;
  double d_;
};

TEST(Vector, test_default_contructor) {
  s21::vector<string> v;
  vector<string> v_std;

  EXPECT_EQ(v_std.capacity(), v.capacity());
  EXPECT_EQ(v_std.size(), v.size());
  EXPECT_EQ(v_std.data(), v.data());
  EXPECT_EQ(v_std.empty(), v.empty());

  s21::vector<MyClass> v2;
  vector<MyClass> v2_std;

  EXPECT_EQ(v2_std.capacity(), v2.capacity());
  EXPECT_EQ(v2_std.size(), v2.size());
  EXPECT_EQ(v2_std.data(), v2.data());
  EXPECT_EQ(v2_std.empty(), v2.empty());

  const s21::vector<string> v_const;
  const vector<string> v_std_const;

  EXPECT_EQ(v_std_const.capacity(), v_const.capacity());
  EXPECT_EQ(v_std_const.size(), v_const.size());
  EXPECT_EQ(v_std_const.data(), v_const.data());
  EXPECT_EQ(v_std_const.empty(), v_const.empty());
}

TEST(Vector, test_parametr_contructor) {
  s21::vector<int> v(3);
  vector<int> v_std(3);

  EXPECT_EQ(v_std.capacity(), v.capacity());
  EXPECT_EQ(v_std.size(), v.size());
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v_std[0], v[0]);
  EXPECT_EQ(v_std[1], v[2]);
  EXPECT_EQ(v_std[1], v[2]);

  const s21::vector<int> v_const(3);
  const std::vector<int> v_std_const(3);

  EXPECT_EQ(v_std_const.capacity(), v_const.capacity());
  EXPECT_EQ(v_std_const.size(), v_const.size());
  EXPECT_FALSE(v_const.empty());
  EXPECT_EQ(v_std_const[0], v_const[0]);
  EXPECT_EQ(v_std_const[1], v_const[2]);
  EXPECT_EQ(v_std_const[1], v_const[2]);

  //  Пустой вектор:
  s21::vector<int> v0(0);
  vector<int> v0_std(0);

  EXPECT_EQ(v0_std.capacity(), v0.capacity());
  EXPECT_EQ(v0_std.size(), v0.size());
  EXPECT_TRUE(v0.empty());
  EXPECT_EQ(v0_std.empty(), v0.empty());
  EXPECT_EQ(v0_std.data(), v0.data());
  EXPECT_EQ(v0_std.data(), nullptr);

  //  Вектор строк:
  s21::vector<string> v2(3);
  vector<string> v2_std(3);

  EXPECT_EQ(v2_std.capacity(), v2.capacity());
  EXPECT_EQ(v2_std.size(), v2.size());
  EXPECT_FALSE(v2.empty());
  EXPECT_EQ(v2_std[0], v2[0]);
  EXPECT_EQ(v2_std[1], v2[2]);
  EXPECT_EQ(v2_std[1], v2[2]);

  //  Вектор классов:
  s21::vector<MyClass> v3(2);
  vector<MyClass> v3_std(2);

  EXPECT_EQ(v3_std.capacity(), v3.capacity());
  EXPECT_EQ(v3_std.size(), v3.size());
  EXPECT_FALSE(v3.empty());
  EXPECT_EQ(v3_std[0].get_i(), v3[0].get_i());
  EXPECT_EQ(v3_std[0].get_f(), v3[0].get_f());
  EXPECT_EQ(v3_std[0].get_d(), v3[0].get_d());
  EXPECT_EQ(v3_std[1].get_i(), v3[1].get_i());
  EXPECT_EQ(v3_std[1].get_f(), v3[1].get_f());
  EXPECT_EQ(v3_std[1].get_d(), v3[1].get_d());
}

TEST(Vector, test_initializer_list) {
  s21::vector<int> v1 = {1, 2, 3};

  EXPECT_EQ(v1.capacity(), size_t(3));
  EXPECT_EQ(v1.size(), size_t(3));
  EXPECT_FALSE(v1.empty());
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);

  s21::vector<int> v2 = {2};
  EXPECT_EQ(v2.capacity(), size_t(1));
  EXPECT_EQ(v2.size(), size_t(1));
  EXPECT_FALSE(v2.empty());
  EXPECT_EQ(v2[0], 2);

  const s21::vector<int> v_c = {2};
  EXPECT_EQ(v_c.capacity(), size_t(1));
  EXPECT_EQ(v_c.size(), size_t(1));
  EXPECT_FALSE(v_c.empty());
  EXPECT_EQ(v_c[0], 2);

  string a = "AAA";
  string b = "BBB";
  string c = "CCC";

  s21::vector<string> v3 = {a, b, c};
  EXPECT_EQ(v3.capacity(), size_t(3));
  EXPECT_EQ(v3.size(), size_t(3));
  EXPECT_FALSE(v3.empty());
  EXPECT_EQ(v3[0], a);
  EXPECT_EQ(v3[1], b);
  EXPECT_EQ(v3[2], c);

  s21::vector<string> v4 = {"AAA", "BBB", "CCC"};

  EXPECT_EQ(v3.capacity(), size_t(3));
  EXPECT_EQ(v3.size(), size_t(3));
  EXPECT_FALSE(v3.empty());
  EXPECT_EQ(v3[0], v4[0]);
  EXPECT_EQ(v3[1], v4[1]);
  EXPECT_EQ(v3[2], v4[2]);

  //  Стандартный вектор:
  vector<string> v4_std = {"AAA", "BBB", "CCC"};
  EXPECT_EQ(v4_std[0], v4[0]);
  EXPECT_EQ(v4_std[1], v4[1]);
  EXPECT_EQ(v4_std[2], v4[2]);

  s21::vector<int> v0 = {};
  EXPECT_EQ(v0.capacity(), size_t(0));
  EXPECT_EQ(v0.size(), size_t(0));
  EXPECT_TRUE(v0.empty());
}

TEST(Vector, test_copy_contructor) {
  //  Создаем вектор строк:
  string a = "AAA";
  string b = "BBB";
  string c = "CCC";

  s21::vector<string> v1;

  v1.push_back(a);
  v1.push_back(b);
  v1.push_back(c);

  //  Копируем во второй вектор:
  s21::vector<string> v2(v1);
  //  Память выделяется по кол-ву существующих элементов:
  EXPECT_EQ(v1.size(), v2.capacity());
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.empty(), v2.empty());

  EXPECT_EQ(v1.at(0), a);
  EXPECT_EQ(v1.at(1), b);
  EXPECT_EQ(v1.at(2), c);

  EXPECT_EQ(v2.at(0), a);
  EXPECT_EQ(v2.at(1), b);
  EXPECT_EQ(v2.at(2), c);

  //  С классом без конструктора:
  MyClass no_constr_value;

  no_constr_value.SetData(1);
  //  Создаём вектор с нашим классом:
  s21::vector<MyClass> v_noconstr;

  v_noconstr.push_back(no_constr_value);
  no_constr_value.SetData(2);
  v_noconstr.push_back(no_constr_value);

  EXPECT_EQ(v_noconstr[0].get_i(), 1);
  EXPECT_EQ(v_noconstr[0].get_f(), 1);
  EXPECT_EQ(v_noconstr[0].get_d(), 1);

  EXPECT_EQ(v_noconstr[1].get_i(), 2);
  EXPECT_EQ(v_noconstr[1].get_f(), 2);
  EXPECT_EQ(v_noconstr[1].get_d(), 2);

  //  Создаём копию вектора:
  s21::vector<MyClass> v_noconstr_copy(v_noconstr);

  EXPECT_EQ(v_noconstr_copy[0].get_i(), 1);
  EXPECT_EQ(v_noconstr_copy[0].get_f(), 1);
  EXPECT_EQ(v_noconstr_copy[0].get_d(), 1);

  EXPECT_EQ(v_noconstr_copy[1].get_i(), 2);
  EXPECT_EQ(v_noconstr_copy[1].get_f(), 2);
  EXPECT_EQ(v_noconstr_copy[1].get_d(), 2);

  EXPECT_EQ(v_noconstr.capacity(), v_noconstr_copy.capacity());
  EXPECT_EQ(v_noconstr.size(), v_noconstr_copy.size());

  //  Стандартный вектор:
  vector<MyClass> v_noconstr_std;

  no_constr_value.SetData(1);
  v_noconstr_std.push_back(no_constr_value);
  no_constr_value.SetData(2);
  v_noconstr_std.push_back(no_constr_value);

  EXPECT_EQ(v_noconstr_std[0].get_i(), 1);
  EXPECT_EQ(v_noconstr_std[0].get_f(), 1);
  EXPECT_EQ(v_noconstr_std[0].get_d(), 1);

  EXPECT_EQ(v_noconstr_std[1].get_i(), 2);
  EXPECT_EQ(v_noconstr_std[1].get_f(), 2);
  EXPECT_EQ(v_noconstr_std[1].get_d(), 2);

  vector<MyClass> v_noconstr_std_copy(v_noconstr_std);

  EXPECT_EQ(v_noconstr_std_copy[0].get_i(), 1);
  EXPECT_EQ(v_noconstr_std_copy[0].get_f(), 1);
  EXPECT_EQ(v_noconstr_std_copy[0].get_d(), 1);

  EXPECT_EQ(v_noconstr_std_copy[1].get_i(), 2);
  EXPECT_EQ(v_noconstr_std_copy[1].get_f(), 2);
  EXPECT_EQ(v_noconstr_std_copy[1].get_d(), 2);
  EXPECT_EQ(v_noconstr_std.capacity(), v_noconstr_std_copy.capacity());
  EXPECT_EQ(v_noconstr_std.size(), v_noconstr_std_copy.size());
}

TEST(Vector, test_move_contructor) {
  string a = "AAA";
  string b = "BBB";
  string c = "CCC";

  s21::vector<string> v1;
  v1.push_back(a);
  v1.push_back(b);
  v1.push_back(c);

  s21::vector<string> v1_copy(v1);
  EXPECT_EQ(v1.size(), v1_copy.capacity());
  EXPECT_EQ(v1.size(), v1_copy.size());
  EXPECT_EQ(v1.empty(), v1_copy.empty());

  s21::vector<std::string> v2(std::move(v1_copy));

  EXPECT_EQ(v1.size(), v2.capacity());
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.empty(), v2.empty());

  EXPECT_EQ(v1_copy.capacity(), size_t(0));
  EXPECT_EQ(v1_copy.size(), size_t(0));
  EXPECT_EQ(v1_copy.empty(), true);

  //  Стандартный вектор:
  std::vector<string> v1_std;

  v1_std.push_back(a);
  v1_std.push_back(b);
  v1_std.push_back(c);

  std::vector<string> v1_std_copy(v1_std);
  std::vector<std::string> v2_std(std::move(v1_std_copy));

  EXPECT_EQ(v2_std.capacity(), v2.capacity());
  EXPECT_EQ(v2_std.size(), v2.size());
  EXPECT_EQ(v2_std.empty(), v2.empty());

  EXPECT_EQ(v1_std_copy.capacity(), size_t(0));
  EXPECT_EQ(v1_std_copy.size(), size_t(0));
  EXPECT_EQ(v1_std_copy.empty(), true);
}

TEST(Vector, test_operator_do_equal) {
  s21::vector<string> v1 = {"AAA", "BBB", "CCC"};
  s21::vector<string> v1_copy(v1);
  EXPECT_EQ(v1.size(), v1_copy.capacity());
  EXPECT_EQ(v1.size(), v1_copy.size());
  EXPECT_EQ(v1.empty(), v1_copy.empty());

  s21::vector<std::string> v2 = std::move(v1_copy);

  EXPECT_EQ(v1.size(), v2.capacity());
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.empty(), v2.empty());

  EXPECT_EQ(v1_copy.capacity(), size_t(0));
  EXPECT_EQ(v1_copy.size(), size_t(0));
  EXPECT_EQ(v1_copy.empty(), true);

  s21::vector<string> v3 = {"three"};

  v2 = std::move(v3);

  EXPECT_EQ(v2.capacity(), size_t(1));
  EXPECT_EQ(v2.size(), size_t(1));
  EXPECT_EQ(v2.empty(), false);

  EXPECT_EQ(v3.capacity(), size_t(3));
  EXPECT_EQ(v3.size(), size_t(3));
  EXPECT_EQ(v3.empty(), false);
}

TEST(Vector, test_at) {
  s21::vector<int> v1 = {0, 1, 2};

  EXPECT_EQ(v1.size(), size_t(3));
  EXPECT_EQ(v1.at(0), 0);
  EXPECT_EQ(v1.at(1), 1);
  EXPECT_EQ(v1.at(2), 2);

  EXPECT_THROW(v1.at(-1), std::out_of_range);
  EXPECT_THROW(v1.at(10), std::out_of_range);

  const s21::vector<int> v2 = {0, 1, 2};

  EXPECT_EQ(v2.size(), size_t(3));
  EXPECT_EQ(v2.at(0), 0);
  EXPECT_EQ(v2.at(1), 1);
  EXPECT_EQ(v2.at(2), 2);

  EXPECT_THROW(v2.at(-1), std::out_of_range);
  EXPECT_THROW(v2.at(10), std::out_of_range);
}

TEST(Vector, test_operator_quad_brackets) {
  s21::vector<int> v1 = {0, 1, 2};

  EXPECT_EQ(v1.size(), size_t(3));
  EXPECT_EQ(v1[0], 0);
  EXPECT_EQ(v1[1], 1);
  EXPECT_EQ(v1[2], 2);

  const s21::vector<int> v2 = {0, 1, 2};

  EXPECT_EQ(v2.size(), size_t(3));
  EXPECT_EQ(v2[0], 0);
  EXPECT_EQ(v2[1], 1);
  EXPECT_EQ(v2[2], 2);
}

TEST(Vector, test_front) {
  s21::vector<int> v1 = {0, 1, 2};

  EXPECT_EQ(v1.size(), size_t(3));
  EXPECT_EQ(v1.front(), 0);

  const s21::vector<int> v2 = {0, 1, 2};

  EXPECT_EQ(v2.size(), size_t(3));
  EXPECT_EQ(v2.front(), 0);

  s21::vector<int> v_one(1);
  EXPECT_EQ(v_one.front(), 0);

  //  Стандартный вектор:
  vector<int> v1_std = {0, 1, 2};

  EXPECT_EQ(v1_std.size(), size_t(3));
  EXPECT_EQ(v1_std.front(), 0);

  vector<int> v_one_std = {5};
  EXPECT_EQ(v_one_std.front(), 5);
}

TEST(Vector, test_back) {
  s21::vector<int> v1 = {0, 1, 2};

  EXPECT_EQ(v1.size(), size_t(3));
  EXPECT_EQ(v1.back(), 2);

  const s21::vector<int> v2 = {0, 1, 2};

  EXPECT_EQ(v2.size(), size_t(3));
  EXPECT_EQ(v2.back(), 2);

  s21::vector<int> v_one = {5};
  EXPECT_EQ(v_one.back(), 5);

  //  Стандартный вектор:
  vector<int> v1_std = {0, 1, 2};

  EXPECT_EQ(v1_std.size(), size_t(3));
  EXPECT_EQ(v1_std.back(), 2);

  vector<int> v_one_std = {5};
  EXPECT_EQ(v_one_std.back(), 5);
}

TEST(Vector, test_data) {
  s21::vector<int> v1;
  EXPECT_EQ(v1.data(), nullptr);

  const s21::vector<int> v2;
  EXPECT_EQ(v2.data(), nullptr);

  s21::vector<int> v3(0);
  EXPECT_EQ(v3.data(), nullptr);

  s21::vector<int> v4 = {5, 6};
  EXPECT_TRUE(v4.data());

  //  Стандартный вектор:
  vector<int> v_std(0);
  EXPECT_EQ(v_std.data(), nullptr);
}

TEST(Vector, test_empty) {
  s21::vector<int> v1(0);
  EXPECT_TRUE(v1.empty());

  v1.push_back(1);
  EXPECT_FALSE(v1.empty());
  v1.pop_back();
  EXPECT_TRUE(v1.empty());

  const s21::vector<int> v2(2);
  EXPECT_FALSE(v2.empty());
  EXPECT_EQ(v2.size(), size_t(2));

  //  Стандартный вектор:
  vector<int> v2_std(2);
  EXPECT_FALSE(v2_std.empty());
  EXPECT_EQ(v2_std.size(), size_t(2));
}

TEST(Vector, test_size) {
  s21::vector<int> v1(0);
  EXPECT_EQ(v1.size(), size_t(0));

  v1.push_back(1);
  EXPECT_EQ(v1.size(), size_t(1));
  v1.push_back(1);
  EXPECT_EQ(v1.size(), size_t(2));
  v1.pop_back();
  EXPECT_EQ(v1.size(), size_t(1));
  v1.pop_back();
  EXPECT_EQ(v1.size(), size_t(0));

  const s21::vector<int> v2 = {1, 2};
  EXPECT_EQ(v2.size(), size_t(2));

  s21::vector<int> v3(3);
  EXPECT_EQ(v3.size(), size_t(3));

  //  Стандартный вектор:
  vector<int> v3_std(3);
  EXPECT_EQ(v3_std.size(), size_t(3));
}

TEST(Vector, test_max_size) {
  s21::vector<int> v1(0);
  vector<int> v1_std(0);
  EXPECT_EQ(v1.max_size(), v1_std.max_size());

  s21::vector<string> v2(500);
  vector<string> v2_std(500);
  EXPECT_EQ(v2.max_size(), v2_std.max_size());

  string a = "AAA";
  string b = "BBB";
  string c = "CCC";

  v2.push_back(a);
  v2.push_back(b);
  v2.push_back(c);

  v2_std.push_back(a);
  v2_std.push_back(b);
  v2_std.push_back(c);

  EXPECT_EQ(v2.max_size(), v2_std.max_size());

  s21::vector<double> v3(0);
  vector<double> v3_std(0);
  EXPECT_EQ(v3.max_size(), v3_std.max_size());

  v3.push_back(9999.9999);
  v3.push_back(9999.9999);
  v3.push_back(9999.9999);

  v3_std.push_back(9999.9999);
  v3_std.push_back(9999.9999);
  v3_std.push_back(9999.9999);

  EXPECT_EQ(v3.max_size(), v3_std.max_size());

  const s21::vector<int> vc = {1, 2, 3};
  const vector<int> vc_std = {1, 2, 3};

  EXPECT_EQ(vc.max_size(), vc_std.max_size());
}

TEST(Vector, test_reserve) {
  s21::vector<string> v1;
  vector<string> v1_std;

  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());

  v1.reserve(5);
  v1_std.reserve(5);
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());

  v1.reserve(2);
  v1_std.reserve(2);
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());

  v1.reserve(0);
  v1_std.reserve(0);
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());

  v1.reserve(8);
  v1_std.reserve(8);
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());
}

TEST(Vector, test_resize) {
  s21::vector<string> v1;
  vector<string> v1_std;

  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());

  v1.resize(5);
  v1_std.resize(5);
  EXPECT_EQ(v1.empty(), v1_std.empty());
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1[4], v1_std[4]);

  v1.resize(6);
  v1_std.resize(6);
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());

  v1.resize(2);
  v1_std.resize(2);
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());

  v1.resize(0);
  v1_std.resize(0);
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1.empty(), v1_std.empty());

  s21::vector<int> v2;
  vector<int> v2_std;

  v2.resize(2);
  v2_std.resize(2);
  EXPECT_EQ(v2.size(), v2_std.size());
  EXPECT_EQ(v2.capacity(), v2_std.capacity());

  v2.push_back(5);
  v2_std.push_back(5);

  EXPECT_EQ(v2.size(), v2_std.size());
  EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2[0], v2_std[0]);
  EXPECT_EQ(v2[1], v2_std[1]);
  EXPECT_EQ(v2[2], v2_std[2]);
  EXPECT_EQ(v2[2], 5);

  v2.resize(6);
  v2_std.resize(6);

  EXPECT_EQ(v2.size(), v2_std.size());
  EXPECT_EQ(v2[0], 0);
  EXPECT_EQ(v2[1], 0);
  EXPECT_EQ(v2[2], 5);
  EXPECT_EQ(v2[3], 0);
  EXPECT_EQ(v2[4], 0);

  EXPECT_EQ(v2[0], v2_std[0]);
  EXPECT_EQ(v2[1], v2_std[1]);
  EXPECT_EQ(v2[2], v2_std[2]);
  EXPECT_EQ(v2[3], v2_std[3]);
  EXPECT_EQ(v2[4], v2_std[4]);

  v2.resize(7);
  v2_std.resize(7);

  EXPECT_EQ(v2.size(), v2_std.size());
  // EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2[0], 0);
  EXPECT_EQ(v2[1], 0);
  EXPECT_EQ(v2[2], 5);
  EXPECT_EQ(v2[3], 0);
  EXPECT_EQ(v2[4], 0);

  EXPECT_EQ(v2[0], v2_std[0]);
  EXPECT_EQ(v2[1], v2_std[1]);
  EXPECT_EQ(v2[2], v2_std[2]);
  EXPECT_EQ(v2[3], v2_std[3]);
  EXPECT_EQ(v2[4], v2_std[4]);

  v2.resize(2);
  v2_std.resize(2);

  EXPECT_EQ(v2.size(), v2_std.size());
  // EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2[0], 0);
  EXPECT_EQ(v2[1], 0);

  EXPECT_EQ(v2[0], v2_std[0]);
  EXPECT_EQ(v2[1], v2_std[1]);

  v2.resize(5);
  v2_std.resize(5);

  EXPECT_EQ(v2.size(), v2_std.size());
  EXPECT_EQ(v2[0], 0);
  EXPECT_EQ(v2[1], 0);

  EXPECT_EQ(v2[0], v2_std[0]);
  EXPECT_EQ(v2[1], v2_std[1]);
  EXPECT_EQ(v2[2], v2_std[2]);
  EXPECT_EQ(v2[2], 0);  //  была 5
}

TEST(Vector, test_capacity) {
  s21::vector<string> v1;
  vector<string> v1_std;
  EXPECT_EQ(v1.capacity(), size_t(0));
  EXPECT_EQ(v1.capacity(), v1_std.capacity());

  v1.reserve(5);
  v1_std.reserve(5);
  EXPECT_EQ(v1.capacity(), size_t(5));
  EXPECT_EQ(v1.capacity(), v1_std.capacity());

  const s21::vector<int> v2 = {1, 2, 3};
  const vector<int> v2_std = {1, 2, 3};
  EXPECT_EQ(v2.capacity(), size_t(3));
  EXPECT_EQ(v2.capacity(), v2_std.capacity());
}

TEST(Vector, test_shrink_to_fit) {
  s21::vector<string> v1;
  vector<string> v1_std;
  EXPECT_EQ(v1.capacity(), size_t(0));
  EXPECT_EQ(v1.capacity(), v1_std.capacity());

  string a = "AAA";
  string b = "BBB";
  string c = "CCC";

  v1.push_back(a);
  v1.push_back(b);
  v1.push_back(c);

  v1_std.push_back(a);
  v1_std.push_back(b);
  v1_std.push_back(c);

  EXPECT_EQ(v1.capacity(), size_t(4));
  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1.size(), size_t(3));
  EXPECT_EQ(v1.size(), v1_std.size());

  v1.shrink_to_fit();
  v1_std.shrink_to_fit();
  EXPECT_EQ(v1.capacity(), v1.size());
  EXPECT_EQ(v1_std.capacity(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1.size(), v1_std.size());
}

TEST(Vector, test_clear) {
  s21::vector<int> v1 = {1, 2, 3};
  vector<int> v1_std = {1, 2, 3};

  v1.clear();
  v1_std.clear();

  EXPECT_EQ(v1.capacity(), size_t(3));
  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1.size(), size_t(0));
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.empty(), 1);
}

TEST(Vector, test_insert) {
  s21::vector<int> v1;
  vector<int> v1_std;

  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(3);

  v1_std.push_back(1);
  v1_std.push_back(2);
  v1_std.push_back(3);

  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1.size(), v1_std.size());

  //  Проверяем итератор:
  s21::vector<int>::iterator v1_iterator = v1.insert(v1.begin(), 5);
  v1_std.insert(v1_std.begin(), 5);

  EXPECT_EQ(v1_iterator, v1.begin());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1.size(), v1_std.size());

  EXPECT_EQ(v1_std[0], 5);
  EXPECT_EQ(v1_std[1], 1);
  EXPECT_EQ(v1_std[2], 2);
  EXPECT_EQ(v1_std[3], 3);
  EXPECT_EQ(v1[0], v1_std[0]);
  EXPECT_EQ(v1[1], v1_std[1]);
  EXPECT_EQ(v1[2], v1_std[2]);
  EXPECT_EQ(v1[3], v1_std[3]);
  EXPECT_EQ(v1[0], 5);
  EXPECT_EQ(v1[1], 1);
  EXPECT_EQ(v1[2], 2);
  EXPECT_EQ(v1[3], 3);

  v1.insert(v1.end(), 8);
  v1_std.insert(v1_std.end(), 8);

  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1_std[0], 5);
  EXPECT_EQ(v1_std[1], 1);
  EXPECT_EQ(v1_std[2], 2);
  EXPECT_EQ(v1_std[3], 3);
  EXPECT_EQ(v1_std[4], 8);
  EXPECT_EQ(v1[0], v1_std[0]);
  EXPECT_EQ(v1[1], v1_std[1]);
  EXPECT_EQ(v1[2], v1_std[2]);
  EXPECT_EQ(v1[3], v1_std[3]);
  EXPECT_EQ(v1[4], v1_std[4]);
  EXPECT_EQ(v1[0], 5);
  EXPECT_EQ(v1[1], 1);
  EXPECT_EQ(v1[2], 2);
  EXPECT_EQ(v1[3], 3);
  EXPECT_EQ(v1[4], 8);

  s21::vector<int>::iterator iter = v1.begin();
  iter += 2;

  vector<int>::iterator iter_std = v1_std.begin();
  iter_std += 2;

  v1.insert(iter, 4);
  v1_std.insert(iter_std, 4);

  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1_std[0], 5);
  EXPECT_EQ(v1_std[1], 1);
  EXPECT_EQ(v1_std[2], 4);
  EXPECT_EQ(v1_std[3], 2);
  EXPECT_EQ(v1_std[4], 3);
  EXPECT_EQ(v1_std[5], 8);
  EXPECT_EQ(v1[0], v1_std[0]);
  EXPECT_EQ(v1[1], v1_std[1]);
  EXPECT_EQ(v1[2], v1_std[2]);
  EXPECT_EQ(v1[3], v1_std[3]);
  EXPECT_EQ(v1[4], v1_std[4]);
  EXPECT_EQ(v1[5], v1_std[5]);
  EXPECT_EQ(v1[0], 5);
  EXPECT_EQ(v1[1], 1);
  EXPECT_EQ(v1[2], 4);
  EXPECT_EQ(v1[3], 2);
  EXPECT_EQ(v1[4], 3);
  EXPECT_EQ(v1[5], 8);

  //  Вектор из строк:
  s21::vector<string> v2;
  vector<string> v2_std;

  string a = "AAA";
  string b = "BBB";
  string c = "CCC";

  v2.push_back(a);
  v2.push_back(b);
  v2.push_back(c);
  v2_std.push_back(a);
  v2_std.push_back(b);
  v2_std.push_back(c);

  s21::vector<string>::iterator iter2 = v2.begin();
  iter2 += 1;

  vector<string>::iterator iter2_std = v2_std.begin();
  iter2_std += 1;

  v2.insert(iter2, c);
  v2_std.insert(iter2_std, c);

  EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2.size(), v2_std.size());
  EXPECT_EQ(v2_std[0], a);
  EXPECT_EQ(v2_std[1], c);
  EXPECT_EQ(v2_std[2], b);
  EXPECT_EQ(v2_std[3], c);
  EXPECT_EQ(v2[0], v2_std[0]);
  EXPECT_EQ(v2[1], v2_std[1]);
  EXPECT_EQ(v2[2], v2_std[2]);
  EXPECT_EQ(v2[3], v2_std[3]);
  EXPECT_EQ(v2[0], a);
  EXPECT_EQ(v2[1], c);
  EXPECT_EQ(v2[2], b);
  EXPECT_EQ(v2[3], c);
}

TEST(Vector, test_erase) {
  s21::vector<string> v1;
  vector<string> v1_std;

  string a = "AAA";
  string b = "BBB";
  string c = "CCC";
  string d = "DDD";
  string e = "EEE";

  v1.push_back(a);
  v1.push_back(b);
  v1.push_back(c);
  v1.push_back(d);
  v1.push_back(e);
  v1_std.push_back(a);
  v1_std.push_back(b);
  v1_std.push_back(c);
  v1_std.push_back(d);
  v1_std.push_back(e);

  s21::vector<string>::iterator iter = v1.begin();
  vector<string>::iterator iter_std = v1_std.begin();

  v1.erase(iter);
  v1_std.erase(iter_std);

  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.size(), size_t(4));
  EXPECT_EQ(v1.capacity(), size_t(8));
  EXPECT_EQ(v1[0], v1_std[0]);
  EXPECT_EQ(v1[1], v1_std[1]);
  EXPECT_EQ(v1[0], b);
  EXPECT_EQ(v1[1], c);

  s21::vector<MyClass> v2;
  vector<MyClass> v2_std;

  EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2.size(), v2_std.size());

  MyClass value;
  value.SetData(1);

  v2.push_back(value);
  v2.push_back(value);
  v2.push_back(value);
  v2_std.push_back(value);
  v2_std.push_back(value);
  v2_std.push_back(value);

  EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2.size(), v2_std.size());
  EXPECT_EQ(v2.capacity(), size_t(4));
  EXPECT_EQ(v2.size(), size_t(3));

  v2.erase(v2.end() - 1);
  v2_std.erase(v2_std.end() - 1);
  EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2.size(), v2_std.size());
  EXPECT_EQ(v2.capacity(), size_t(4));
  EXPECT_EQ(v2.size(), size_t(2));

  s21::vector<int> v3 = {1, 2, 3};
  vector<int> v3_std = {1, 2, 3};

  s21::vector<int>::iterator iter_int = v3.begin();
  iter_int += 1;

  vector<int>::iterator iter_int_std = v3_std.begin();
  iter_int_std += 1;

  v3.erase(iter_int);
  v3_std.erase(iter_int_std);

  EXPECT_EQ(v3.capacity(), v3_std.capacity());
  EXPECT_EQ(v3.size(), v3_std.size());
  EXPECT_EQ(v3.capacity(), size_t(3));
  EXPECT_EQ(v3.size(), size_t(2));
  EXPECT_EQ(v3[0], v3_std[0]);
  EXPECT_EQ(v3[1], v3_std[1]);
  EXPECT_EQ(v3[0], 1);
  EXPECT_EQ(v3[1], 3);

  iter_int = v3.end() - 1;
  iter_int_std = v3_std.end() - 1;

  v3.erase(iter_int);
  v3_std.erase(iter_int_std);

  EXPECT_EQ(v3.capacity(), v3_std.capacity());
  EXPECT_EQ(v3.size(), v3_std.size());
  EXPECT_EQ(v3.capacity(), size_t(3));
  EXPECT_EQ(v3.size(), size_t(1));
  EXPECT_EQ(v3[0], v3_std[0]);
  EXPECT_EQ(v3[0], 1);

  iter_int = v3.begin();
  iter_int_std = v3_std.begin();

  v3.erase(iter_int);
  v3_std.erase(iter_int_std);

  EXPECT_EQ(v3.capacity(), v3_std.capacity());
  EXPECT_EQ(v3.size(), v3_std.size());
  EXPECT_EQ(v3.capacity(), size_t(3));
  EXPECT_EQ(v3.empty(), v3_std.empty());

  iter_int += 100;

  EXPECT_THROW(v3.erase(iter_int), std::out_of_range);
  EXPECT_EQ(v3.capacity(), v3_std.capacity());
  EXPECT_EQ(v3.size(), v3_std.size());
  EXPECT_EQ(v3.capacity(), size_t(3));
  EXPECT_EQ(v3.empty(), v3_std.empty());
}

TEST(Vector, test_push_back) {
  s21::vector<int> v1;
  vector<int> v1_std;

  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(3);
  v1_std.push_back(1);
  v1_std.push_back(2);
  v1_std.push_back(3);

  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1_std[0], 1);
  EXPECT_EQ(v1_std[1], 2);
  EXPECT_EQ(v1_std[2], 3);
  EXPECT_EQ(v1[0], v1_std[0]);
  EXPECT_EQ(v1[1], v1_std[1]);
  EXPECT_EQ(v1[2], v1_std[2]);
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);

  s21::vector<string> v2;
  vector<string> v2_std;

  string a = "AAA";
  string b = "BBB";
  string c = "CCC";

  v2.push_back(a);
  v2.push_back(b);
  v2.push_back(c);

  v2_std.push_back(a);
  v2_std.push_back(b);
  v2_std.push_back(c);

  EXPECT_EQ(v2_std[0], a);
  EXPECT_EQ(v2_std[1], b);
  EXPECT_EQ(v2_std[2], c);
  EXPECT_EQ(v2[0], v2_std[0]);
  EXPECT_EQ(v2[1], v2_std[1]);
  EXPECT_EQ(v2[2], v2_std[2]);
  EXPECT_EQ(v2[0], a);
  EXPECT_EQ(v2[1], b);
  EXPECT_EQ(v2[2], c);

  v2.pop_back();
  v2_std.pop_back();

  v2.push_back("DDD");

  v2_std.push_back("DDD");
  EXPECT_EQ(v2[2], v2_std[2]);
  EXPECT_EQ(v2[2], "DDD");

  EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2.size(), v2_std.size());
}

TEST(Vector, test_pop_back) {
  s21::vector<string> v2;
  vector<string> v2_std;

  string a = "AAA";
  string b = "BBB";
  string c = "CCC";

  v2.push_back(a);
  v2.push_back(b);
  v2.push_back(c);

  v2_std.push_back(a);
  v2_std.push_back(b);
  v2_std.push_back(c);

  v2.pop_back();
  v2_std.pop_back();

  EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2.size(), v2_std.size());
  EXPECT_EQ(v2[0], v2_std[0]);
  EXPECT_EQ(v2[1], v2_std[1]);
  EXPECT_EQ(v2[0], a);
  EXPECT_EQ(v2[1], b);

  v2.pop_back();
  v2_std.pop_back();

  EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2.size(), v2_std.size());
  EXPECT_EQ(v2[0], v2_std[0]);
  EXPECT_EQ(v2[0], a);

  v2.pop_back();
  v2_std.pop_back();

  EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2.size(), v2_std.size());
  EXPECT_EQ(v2.empty(), v2_std.empty());
}

TEST(Vector, test_swap) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};
  vector<int> v1_std = {1, 2, 3};
  vector<int> v2_std = {4, 5, 6};

  v2.push_back(7);
  v2_std.push_back(7);

  v1.swap(v2);
  v1_std.swap(v2_std);

  EXPECT_EQ(v1.size(), size_t(4));
  EXPECT_EQ(v1.capacity(), size_t(6));
  EXPECT_EQ(v1.size(), v1_std.size());
  EXPECT_EQ(v1.capacity(), v1_std.capacity());
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[1], 5);
  EXPECT_EQ(v1[2], 6);
  EXPECT_EQ(v1[3], 7);
  EXPECT_EQ(v2.size(), size_t(3));
  EXPECT_EQ(v2.capacity(), size_t(3));
  EXPECT_EQ(v2.size(), v2_std.size());
  EXPECT_EQ(v2.capacity(), v2_std.capacity());
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
}

TEST(Vector, test_insert_many) {
  s21::vector<int> v1 = {1, 2, 3};
  int four = 4, five = 5, six = 6;

  v1.insert_many(v1.end(), four, five, six);
  EXPECT_EQ(v1.size(), size_t(6));
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);
  EXPECT_EQ(v1[3], 4);
  EXPECT_EQ(v1[4], 5);
  EXPECT_EQ(v1[5], 6);

  int nine = 9;
  v1.insert_many(v1.begin(), nine, nine);
  EXPECT_EQ(v1.size(), size_t(8));
  EXPECT_EQ(v1[0], 9);
  EXPECT_EQ(v1[1], 9);
  EXPECT_EQ(v1[2], 1);
  EXPECT_EQ(v1[3], 2);
  EXPECT_EQ(v1[4], 3);
  EXPECT_EQ(v1[5], 4);
  EXPECT_EQ(v1[6], 5);
  EXPECT_EQ(v1[7], 6);

  v1.insert_many(v1.begin() + 2, five);
  EXPECT_EQ(v1.size(), size_t(9));
  EXPECT_EQ(v1[0], 9);
  EXPECT_EQ(v1[1], 9);
  EXPECT_EQ(v1[2], 5);
  EXPECT_EQ(v1[3], 1);
  EXPECT_EQ(v1[4], 2);
  EXPECT_EQ(v1[5], 3);
  EXPECT_EQ(v1[6], 4);
  EXPECT_EQ(v1[7], 5);
  EXPECT_EQ(v1[8], 6);

  v1.push_back(five);
  v1.pop_back();
  EXPECT_EQ(v1.size(), size_t(9));
}

TEST(Vector, test_insert_many_back) {
  s21::vector<string> v1;
  string a = "AAA";
  string b = "BBB";
  string c = "CCC";

  v1.insert_many_back(a, b, c);
  EXPECT_EQ(v1.size(), size_t(3));
  EXPECT_EQ(v1[0], a);
  EXPECT_EQ(v1[1], b);
  EXPECT_EQ(v1[2], c);

  v1.insert_many_back(a, a);
  EXPECT_EQ(v1.size(), size_t(5));
  EXPECT_EQ(v1[0], a);
  EXPECT_EQ(v1[1], b);
  EXPECT_EQ(v1[2], c);
  EXPECT_EQ(v1[3], a);
  EXPECT_EQ(v1[4], a);

  v1.insert_many_back(c);
  EXPECT_EQ(v1.size(), size_t(6));
  EXPECT_EQ(v1[0], a);
  EXPECT_EQ(v1[1], b);
  EXPECT_EQ(v1[2], c);
  EXPECT_EQ(v1[3], a);
  EXPECT_EQ(v1[4], a);
  EXPECT_EQ(v1[5], c);
}
