using comp = std::function<bool(Board&, Board&)>;

/**
 * Brief: Comparator for Uniform cost search: compares depth of two element
 * to find their relative position in prority queue
 *
 *  returns true if first element is to be placed after second element
 */
bool UniformCostSearch(Board& lhs, Board& rhs) {
  return (lhs.GetDepth() > rhs.GetDepth());
}

/**
 * Brief: Comparator for Uniform cost search: compares depth and number
 * misplaced tiles of two element to find their relative position
 * in prority queue
 *
 * returns true if first element is to be placed after second element
 */
bool AStarMisplaced(Board& lhs, Board& rhs) {
  return (lhs.GetDepth() + lhs.MisplacedTiles()) >
         (rhs.GetDepth() + rhs.MisplacedTiles());
}

/**
 * Brief: Comparator for Uniform cost search: compares depth and manhattan
 * distance of two element to find their relative position
 * in prority queue
 *
 * returns true if first element is to be placed after second element
 */
bool AStarManhattan(Board& lhs, Board& rhs) {
  return (lhs.GetDepth() + lhs.ManhattanDistance()) >
         (rhs.GetDepth() + rhs.ManhattanDistance());
}

/**
 * Factory method for creating priority_queue based on algorithm selected
 *
 * returns queuing structure based on algorithm selected
 */
priority_queue<Board, vector<Board>, comp> MakeQueue(int algo) {
  if (algo == 1) {
    cout << "Using Uniform Cost Search \n";
    priority_queue<Board, vector<Board>, comp> q(UniformCostSearch);
    return q;
  } else if (algo == 2) {
    cout << "Using ASTAR with Misplaced \n";
    priority_queue<Board, vector<Board>, comp> q(AStarMisplaced);
    return q;
  }
  cout << "Using AStar with Manhattan \n";
  priority_queue<Board, vector<Board>, comp> q(AStarManhattan);
  return q;
}

/**
 * Function that implements General search algorithm
 */
void Solve(Board board, int algorithm) {
  uint32_t maxQueueSize = 1;  //!< tracks the max size of queue
  uint32_t nodesExpanded = 0; //!< tracks number of nodes expanded

  int found = -1;
  board.SetDepth(0);
  set<string> seen;
  seen.insert(board.ToString());

  // This is equivalent to MAKE-QUEUE
  auto q = MakeQueue(algorithm); //!< call factory method to get the queueing function
  q.push(board);                 //!< push initial board

  // These are four operators for moving blank
  // in directions: Down, Up, Right, Left
  vector<int> dx = {1, -1, 0, 0};
  vector<int> dy = {0, 0, 1, -1};

  auto start = std::chrono::high_resolution_clock::now();
  while (!q.empty()) {
    Board oldBoard = q.top(); // This is equivalent to REMOVE-FRONT
    q.pop();
    int currDepth = oldBoard.GetDepth();

    if (oldBoard.IsGoalState()) { // problem.GOAL - TEST(node.STATE)
      found = currDepth;
      break;
    }
    nodesExpanded++;

    // This is equivalent to  QUEUEING - FUNCTION(nodes, EXPAND(node, problem.OPERATORS))
    for (int i = 0; i < 4; i++) {
      int xx = dx[i] + oldBoard.BlankX();
      int yy = dy[i] + oldBoard.BlankY();

      if (xx < 0 || xx >= board.Size() || yy < 0 || yy >= board.Size()) {
        continue;
      }

      Board newBoard = oldBoard.Swap(xx, yy);
      // Checking if state is already processed
      if (seen.find(newBoard.ToString()) != seen.end()) {
        continue;
      }
      // set depth of the newly explored board
      newBoard.SetDepth(currDepth + 1);
      q.push(newBoard);
      maxQueueSize = max<uint32_t>(maxQueueSize, q.size());
      seen.insert(newBoard.ToString());
    }
  }
  auto finish = std::chrono::high_resolution_clock::now();

  // Print different statistics such as if solution found, total compution time
  // Numner of nodes expanded, max size of queue
  std::chrono::duration<double, std::milli> elapsed = finish - start;
  std::cout << "Elapsed Time: " << elapsed.count() << " milliseconds"
            << std::endl;
  if (found == -1) {
    cout << "No solution " << std::endl;
  } else {
    cout << "Found at " << found << endl;
  }
  cout << "Max Queue Size: " << maxQueueSize << endl;
  cout << "Nodes expanded: " << nodesExpanded << endl;
}
