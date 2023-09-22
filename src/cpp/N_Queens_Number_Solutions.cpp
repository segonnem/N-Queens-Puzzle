#include <iostream>
#include <vector>

class NQueenSolver {
public:
    NQueenSolver(int n) : size(n), solutions(0) {
        solve(0, 0, 0, 0);
    }

    int getSolutionCount() const {
        return solutions;
    }

private:
    int size;
    int solutions;

    void solve(int row, int cols, int diag1, int diag2) {
        if (row == size) {
            solutions++;
            return;
        }

        // Available positions for this row
        // ~(cols | diag1 | diag2) gives all the free positions (1's)
        // ((1 << size) - 1) ensures the row is within the N size (bit mask)
        int availablePositions = ~(cols | diag1 | diag2) & ((1 << size) - 1);

        while (availablePositions) {
            int position = availablePositions & -availablePositions;
            availablePositions -= position;

            solve(row + 1, 
                  cols | position, 
                  (diag1 | position) << 1, 
                  (diag2 | position) >> 1);
        }
    }
};

int main() {
    int n;
    std::cout << "Enter the size of the board (N): ";
    std::cin >> n;

    NQueenSolver solver(n);
    std::cout << "Number of solutions for " << n << "-Queens problem: " << solver.getSolutionCount() << std::endl;

    return 0;
}
