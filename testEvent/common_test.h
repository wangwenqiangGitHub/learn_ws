#ifndef MINDSPORE_LITE_TEST_COMMON_COMMON_TEST_H_
#define MINDSPORE_LITE_TEST_COMMON_COMMON_TEST_H_

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "gtest/gtest.h"
namespace mindspore {
class CommonTest : public testing::Test {
 public:
  // TestCase only enter once
  static void SetUpTestCase();
  static void TearDownTestCase();

  // every TEST_F macro will enter one
  virtual void SetUp();
  virtual void TearDown();

  template <typename T>
  void PrintData(std::string name, T *output_data, int size) {
    std::cout << "The " << name << " is as follows:" << std::endl;
    if (typeid(output_data[0]) == typeid(uint8_t) || typeid(output_data[0]) == typeid(int8_t)) {
      for (int i = 0; i < std::min(size, 100); i++) {
        std::cout << static_cast<int>(output_data[i]) << " ";
      }
    } else {
      for (int i = 0; i < std::min(size, 100); i++) {
        std::cout << output_data[i] << " ";
      }
    }
    std::cout << std::endl;
  }

  template <typename T>
  static void CompareOutputData(T *output_data, T *correct_data, int size, float err_bound) {
    for (size_t i = 0; i < size; i++) {
      T abs = fabs(output_data[i] - correct_data[i]);
      ASSERT_LE(abs, err_bound);
    }
  }

  void CompareOutputInt8(int8_t *output_data, int8_t *correct_data, int size, float err_percent) {
    int bias_count = 0;
    for (int i = 0; i < size; i++) {
      int8_t diff = abs(output_data[i] - correct_data[i]);
      ASSERT_LE(diff, 1);
      if (diff == 1) {
        bias_count++;
      }
    }
    float bias_percent = static_cast<float>(bias_count) / size;
    ASSERT_LE(bias_percent, err_percent);
  }

  void ReadFile(const char *file, size_t *size, char **buf) {
    ASSERT_NE(nullptr, file);
    ASSERT_NE(nullptr, size);
    ASSERT_NE(nullptr, buf);
    std::string path = std::string(file);
    std::ifstream ifs(path);
    ASSERT_EQ(true, ifs.good());
    ASSERT_EQ(true, ifs.is_open());

    ifs.seekg(0, std::ios::end);
    *size = ifs.tellg();
    *buf = new char[*size];

    ifs.seekg(0, std::ios::beg);
    ifs.read(*buf, *size);
    ifs.close();
  }
};
}  // namespace mindspore
#endif  // MINDSPORE_LITE_TEST_COMMON_COMMON_TEST_H_