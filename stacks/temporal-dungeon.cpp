#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Position {
    int x, y;
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
};

struct GameState {
    Position playerPos;
    int health;
    vector<string> inventory;
    vector<vector<char>> dungeon; // 5x5
    vector<Position> pathUpToThisPoint;
};

class TemporalDungeonExplorer {
private:
public:
};

int main() {
    return 0;
}