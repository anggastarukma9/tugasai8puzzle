#include <bits/stdc++.h>

using namespace std;

/**
 * function to return default puzzles mentioned in
 * project description
 */
vector<vector<int>> DefaultPuzzle(int puzzle) {
  switch (puzzle) {
    case 0:
      return {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    case 2:
      return {{1, 2, 3}, {4, 5, 6}, {0, 7, 8}};
    case 4:
      return {{1, 2, 3}, {5, 0, 6}, {4, 7, 8}};
    case 8:
      return {{1, 3, 6}, {5, 0, 2}, {4, 7, 8}};
    case 12:
      return {{1, 3, 6}, {5, 0, 7}, {4, 8, 2}};
    case 16:
      return {{1, 6, 7}, {5, 0, 3}, {4, 8, 2}};
    case 20:
      return {{7, 1, 2}, {4, 8, 5}, {6, 3, 0}};
    case 24:
      return {{0, 7, 2}, {4, 6, 1}, {3, 5, 8}};
    default:
      break;
  }
  return {};
}

/**
 * class models Board
 */
class Board {
 public:
  Board(vector<vector<int>> vec) {
    m_board = vec;
    m_N = vec.size();
    for (int i = 0; i < m_N; i++) {
      for (int j = 0; j < m_N; j++) {
        if (m_board[i][j] == 0) {
          m_blankPosI = i;
          m_blankPosJ = j;
        }
      }
    }
  }

  // returns Xth row position of Blank
  int BlankX() { return m_blankPosI; }

  // returns Yth column position of Blank
  int BlankY() { return m_blankPosJ; }

  // Prints the current board in a form of 2-D grid
  void Print() {
    for (int i = 0; i < m_N; i++) {
      for (int j = 0; j < m_N; j++) {
        cout << m_board[i][j] << " ";
      }
      cout << endl;
    }
  }

  // checks if this board is the goal board
  bool IsGoalState() {
    for (int i = 0; i < m_N; i++) {
      for (int j = 0; j < m_N; j++) {
        if (m_goal[i][j] != m_board[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  // Operator function moves to swap up, down, left, right to the blank and returns updated board
  Board Swap(int xx, int yy) {
    auto board = m_board;
    swap(board[xx][yy], board[m_blankPosI][m_blankPosJ]);
    return Board(board);
  }


  // Returns string representation of board
  string ToString() {
    string str;
    for (int i = 0; i < m_N; i++) {
      for (int j = 0; j < m_N; j++) {
        str.append(to_string(m_board[i][j]));
      }
    }
    return str;
  }

  // Returns size of the grid, in our case: returns 3
  int Size() { return m_N; }

  // Set depth of the board
  void SetDepth(int depth) { m_depth = depth; }

  // Get depth of the board
  int GetDepth() { return m_depth; }

  int G() { return m_depth; }

  // Returns Manhattan distance of the board from the goal state
  int ManhattanDistance() {
    int dist = 0;
    for (int i = 0; i < m_N; i++) {
      for (int j = 0; j < m_N; j++) {
        int val = m_board[i][j];
        if (val != 0) {
          val--;
          int row = val / m_N;
          int col = val % m_N;

          dist += abs(row - i) + abs(col - j);
        }
      }
    }
    return dist;
  }

  // Returns Manhattan distance of the board from the goal state
  int H_ManhattanDistance () { return ManhattanDistance(); };

  // Returns number of misplaced tiles in the board from the goal state
  int MisplacedTiles() {
    int misplacedTiles = 0;
    for (int i = 0; i < m_N; i++) {
      for (int j = 0; j < m_N; j++) {
        if (m_board[i][j] != 0 and m_board[i][j] != m_goal[i][j]) {
          misplacedTiles++;
        }
      }
    }
    return misplacedTiles;
  }

  // Returns number of misplaced tiles in the board from the goal state
  int H_MisplacedTiles() { return MisplacedTiles(); }
 private:
  vector<vector<int>> m_board;
  vector<vector<int>> m_goal{{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
  int m_N;
  int m_blankPosI, m_blankPosJ;
  int m_depth{0};
};
