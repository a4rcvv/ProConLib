#include <algorithm>
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

template <typename T, const int row, const int column>
class Matrix {
  T entry_[row][column] = {};

public:
  Matrix(void) {
    // Nothing
  }

  Matrix<T, row, column>& operator+=(const Matrix<T, row, column>& matrix);
  Matrix<T, row, column>& operator-=(const Matrix<T, row, column>& matrix);
  Matrix<T, row, column>& operator*=(const T scholar);

  T Entry(const int output_row, const int output_column) const {
    return entry_[output_row][output_column];
  }

  void AssignEntry(const int assign_row, const int assign_column,
                   const T entry) {
    entry_[assign_row][assign_column] = entry;
    return;
  }

  bool IsSquareMatrix(void) const {
    return row == column;
  }

  int Row(void) const {
    return row;
  }
  int Column(void) const {
    return column;
  }

  void Output(void) {
    for (int ri = 0; ri < Row(); ri++) {
      for (int ci = 0; ci < Column(); ci++) {
        cout << entry_[ri][ci] << "\t";
      }
      cout << endl;
    }
  }
};

// FIXME: 参照にしてるせいでバグってるかもしれないので直す->finished
//行列和
template <typename T, int row, int column>
Matrix<T, row, column> operator+(Matrix<T, row, column> left,
                                 const Matrix<T, row, column>& right) {
  left += right;
  return left;
}
//行列差
template <typename T, int row, int column>
Matrix<T, row, column> operator-(Matrix<T, row, column> left,
                                 const Matrix<T, row, column>& right) {
  left -= right;
  return left;
}
//スカラー倍
template <typename T, int row, int column>
Matrix<T, row, column> operator*(Matrix<T, row, column> matrix,
                                 const T scholar) {
  matrix *= scholar;
  return matrix;
}
// TODO: 行列積の実装(グローバル関数になるかも)->finished
//行列積
template <typename T, int row, int column, int column_2>
Matrix<T, row, column_2> operator*(const Matrix<T, row, column>& left,
                                   const Matrix<T, column, column_2>& right) {
  Matrix<T, row, column_2> result;
  for (int ri = 0; ri < row; ri++) {
    for (int ci = 0; ci < column_2; ci++) {
      T assign_value = 0;
      for (int pos = 0; pos < column; pos++) {
        assign_value += left.Entry(ri, pos) * right.Entry(pos, ci);
      }
      result.AssignEntry(ri, ci, assign_value);
    }
  }
  return result;
}

template <typename T, const int row, const int column>
Matrix<T, row, column>& Matrix<T, row, column>::operator+=(
    const Matrix<T, row, column>& matrix) {
  for (int ri = 0; ri < row; ri++) {
    for (int ci = 0; ci < column; ci++) {
      this->entry_[ri][ci] += matrix.entry_[ri][ci];
    }
  }
  return *this;
}

template <typename T, const int row, const int column>
Matrix<T, row, column>& Matrix<T, row, column>::operator-=(
    const Matrix<T, row, column>& matrix) {
  for (int ri = 0; ri < row; ri++) {
    for (int ci = 0; ci < column; ci++) {
      this->entry_[ri][ci] -= matrix.entry_[ri][ci];
    }
  }
  return *this;
}

template <typename T, const int row, const int column>
Matrix<T, row, column>& Matrix<T, row, column>::operator*=(const T scholar) {
  for (int ri = 0; ri < row; ri++) {
    for (int ci = 0; ci < column; ci++) {
      this->entry_[ri][ci] *= scholar;
    }
  }
  return *this;
}

// for verifying
int main(void) {
  cout << std::fixed << std::setprecision(10);
  cin.tie(0);
  std::ios::sync_with_stdio(false);
  Matrix<int, 2, 2> a, b;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a.AssignEntry(i, j, i + j);
      b.AssignEntry(i, j, (i + 1) * (j + 1));
    }
  }
  a.Output();
  cout << endl;
  b.Output();
  cout << endl;

  Matrix<int, 2, 2> c = a * b;
  c.Output();

  return 0;
}
