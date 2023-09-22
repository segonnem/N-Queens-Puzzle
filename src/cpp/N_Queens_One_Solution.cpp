#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class NQueenSolver {
public:
    NQueenSolver(int n) : size(n), board(n, std::string(n, '.')), found(false) {
        solve(0, 0, 0, 0);
    }

    void printSolution() const {
        if (found) {
            for (const auto& row : board) {
                std::cout << row << "\n";
            }
        } else {
            std::cout << "No solution found." << std::endl;
        }
    }

private:
    int size;
    std::vector<std::string> board;
    bool found;

    void solve(int row, long long cols, long long diag1, long long diag2) {
        if (row == size) {
            found = true;
            return;
        }

        long long availablePositions = ~(cols | diag1 | diag2) & ((1LL << size) - 1);

        while (availablePositions && !found) {
            long long position = availablePositions & -availablePositions;
            availablePositions -= position;

            int column = static_cast<int>(log2(position));
            board[row][column] = 'Q';  // Place queen

            solve(row + 1, cols | position, (diag1 | position) << 1, (diag2 | position) >> 1);

            if (found) return; // Exit if a solution is found

            board[row][column] = '.';  // Remove queen
        }
    }
};

int main() {
    int n;
    std::cout << "Enter the size of the board (N): ";
    std::cin >> n;

    NQueenSolver solver(n);
    std::cout << "One solution for the " << n << "-Queens problem:\n";
    solver.printSolution();

    return 0;
}


