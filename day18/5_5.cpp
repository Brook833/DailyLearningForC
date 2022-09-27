#include <iostream>
#include <vector>

int main() {
  system("chcp 65001");

  const std::vector<std::string> scores = {"F", "D", "C", "B", "A", "A++"};
  std::string s;
  int grade;

  /*while (std::cin >> grade) {
    if (grade < 60) {
      s = scores[0];
    } else if (grade < 70) {
      s = scores[1];
    } else if (grade < 80) {
      s = scores[2];
    } else if (grade < 90) {
      s = scores[3];
    } else if (grade < 100) {
      s = scores[4];
    } else {
      s = scores[5];
    }
  }*/
  std::cin >> grade;
  if (grade < 60) {
    s = scores[0];
  } else {
    if (grade == 100) {
      s = scores[5];
    } else {
      s = scores[(grade - 50) / 10];
      if ((grade % 10) > 7) {
        s += "+";
      } else if ((grade % 10) < 3) {
        s += "-";
      }
    }
  }

  std::cout << s << std::endl;
  system("pause");
  return 0;
}