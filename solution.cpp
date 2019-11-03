#include<vector>
#include<utility> // for std::pair
#include<unordered_map>
#include<deque>
#include<string>
#include<sstream>


/// helper functions
namespace Helpers
{

  using Position = std::pair<size_t, size_t>;
  using Index2D = std::pair<int, int>;
  using Grid = std::vector<std::vector<int>>;

  const int WALL = 1; /// grid value for a wall
  const int FREE = 0; /// grid value for free space

  /// converts Postion to string
  ///
  /// used for hashing positions in unordered_map
  std::string position_to_string(Position pos)
  {
    std::stringstream ss;
    ss << "[" << pos.first << " " << pos.second << "]";
    return ss.str();
  }

  /// returns all neighbouring positions
  std::vector<Position> get_neighbours(Position& pos_in, Grid& grid)
  {
    std::vector<Position> output{};
    int m = grid.size();
    int n = grid[0].size();
    for (int i{ -1 }; i <= 1; ++i)
    {
      for (int j{ -1 }; j <= 1; ++j)
      {
        int y = pos_in.first + i;
        int x = pos_in.second + j;

        if (!((y < 0) || (y >= m) || (x < 0) || (x >= n) || (i == 0 && j == 0)))
        {
          if (grid[x][y] != WALL)
          {
            output.push_back(std::make_pair(y, x));
          }
        }
      }
    }
    return output;
  }

  /// returns the distance of the shortest path
  int breadth_first_search(Grid& grid)
  {
    int distance = -1;
    std::unordered_map<std::string, int> visited{};
    std::deque<Position> queue;

    Position start_pos = std::make_pair(0, 0);
    Position dest_pos = std::make_pair(grid.size() - 1, grid[0].size() - 1); // destination position

    // make sure start and destination are not blocked
    if (!(grid[start_pos.first][start_pos.second] == WALL || grid[dest_pos.first][dest_pos.second] == WALL))
    {
      // mark start as visited and add to queue
      visited[position_to_string(start_pos)] = 1; 
      queue.push_back(start_pos);

      bool path_exists{ false }; // flag set if path from start to destination exists
      while (!queue.empty())
      {
        Position cur_node_pos = queue.front();
        queue.pop_front();
        if (cur_node_pos == dest_pos)
        {
          path_exists = true;
          break;
        }
        // visit all unvisted neighbours
        for (auto neighbour_pos : Helpers::get_neighbours(cur_node_pos, grid))
        {
          if (visited.find(position_to_string(neighbour_pos)) == visited.end())
          {
            visited[position_to_string(neighbour_pos)] = visited[position_to_string(cur_node_pos)] + 1;
            queue.push_back(neighbour_pos);
          }
        }
      }
      if (path_exists)
      {
        distance = visited[position_to_string(dest_pos)];
      }
    }
    return distance;
  }

} // Namespace Helpers




class Solution {
public:
  int shortestPathBinaryMatrix(std::vector<std::vector<int>>& grid)
  {
    return Helpers::breadth_first_search(grid);
  }
};


//#include<iostream>
// Local Test Code
//int main()
//{
//  Solution sol;
//  std::vector<std::vector<int>> grid =
//  { {0, 0, 0},{1, 1, 0},{1, 1, 0} };
//  std::cout << sol.shortestPathBinaryMatrix(grid);
//}