#include "simulation.h"

#include <algorithm>
#include <tuple>

#include "board.h"
#include "lidi.h"
#include "utils.h"

SimulationResult Simulation::run(int lives, bool log, double sleepTimeSeconds,
                                 int iterations) {
    // Check if simulation was already run.
    if (lidiBoards.size() != 0) {
        warn("Simulation was already run.");
        return result;
    }

    Board curBoard = initialBoard;
    LidiBoard curLidiBoard =
        LidiBoard::getLidiBoardWithOneParticle(curBoard.n, curBoard.m, lives);

    lidiBoards.push_back(curLidiBoard);
    if (log) display(curBoard, curLidiBoard);

    int curIteration = 0;
    while (iterations == -1 || curIteration < iterations) {
        if (sleepTimeSeconds != 0) {
            nap(sleepTimeSeconds);
        }
        curBoard.next();
        curLidiBoard = curLidiBoard.getNextLidiBoard(curBoard);
        lidiBoards.push_back(curLidiBoard);
        if (log) display(curBoard, curLidiBoard);
        curIteration++;

        // Stop if one of the particles reached the bottom.
        if (curLidiBoard.reachedEnd()) break;
        if (curLidiBoard.isDead()) {
            warn("All particles are dead.");
            result = getResultClosest();
            return result;
        }
    }

    result = getResult();
    return result;
}

SimulationResult Simulation::backtrackFrom(int line, int col, int ind) {
    SimulationResult ans;

    std::vector<char> path;

    int lenPath = ind;

    // To keep track of the path.
    int curLine = line, curCol = col;

    LidiBoard curLidiBoard = lidiBoards[lenPath];

    for (int i = lenPath; i >= 0; i--) {
        curLidiBoard = lidiBoards[i];
        lidi particle = curLidiBoard.board[curLine][curCol];
        int life, parentDir;
        std::tie(life, parentDir) = unpackLidi(particle);

        if (parentDir == 0) {
            // Particle was created by the board.
            // We don't need to add it to the path.
            break;
        }

        // U, R, D, L
        int dl[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};
        char reverseDir[] = {'D', 'L', 'U', 'R'};

        curLine = curLine + dl[parentDir - 1];
        curCol = curCol + dc[parentDir - 1];

        path.push_back(reverseDir[parentDir - 1]);
    }
    std::reverse(path.begin(), path.end());
    ans.path = path;
    ans.pathLen = lenPath;
    return ans;
}

SimulationResult Simulation::getResultClosest() {
    int indLidiBoardBest = -1;
    int currentBest = 1e9;

    // These will be updated by the getClosest() method.

    for (int i = 0; i < (int)lidiBoards.size(); i++) {
        LidiBoard curLidiBoard = lidiBoards[i];
        int minDistLidi, lBestLidi, rBestLidi = -1;
        std::tie(minDistLidi, lBestLidi, rBestLidi) = curLidiBoard.getClosest();
        if (minDistLidi < currentBest) {
            currentBest = minDistLidi;

            // update the indices
            lBest = lBestLidi;
            rBest = rBestLidi;
            minDistance = currentBest;

            indLidiBoardBest = i;
        }
    }

    int lenPath = indLidiBoardBest;
    return backtrackFrom(lBest, rBest, lenPath);
}

SimulationResult Simulation::getResult() {
    SimulationResult ans;

    std::vector<char> path;

    int lenPath = (int)lidiBoards.size() - 1;

    // To keep track of the path.
    int curLine = initialBoard.n - 1, curCol = initialBoard.m - 1;

    minDistance = 0;
    lBest = curLine;
    rBest = curCol;

    return backtrackFrom(curLine, curCol, lenPath);

    // LidiBoard curLidiBoard = lidiBoards[lenPath];

    // for (int i = lenPath; i >= 0; i--) {
    //     curLidiBoard = lidiBoards[i];
    //     lidi particle = curLidiBoard.board[curLine][curCol];
    //     int life, parentDir;
    //     std::tie(life, parentDir) = unpackLidi(particle);

    //     if (parentDir == 0) {
    //         // Particle was created by the board.
    //         // We don't need to add it to the path.
    //         break;
    //     }

    //     // U, R, D, L
    //     int dl[] = {-1, 0, 1, 0};
    //     int dc[] = {0, 1, 0, -1};
    //     char reverseDir[] = {'D', 'L', 'U', 'R'};

    //     curLine = curLine + dl[parentDir - 1];
    //     curCol = curCol + dc[parentDir - 1];

    //     path.push_back(reverseDir[parentDir - 1]);
    // }
    // std::reverse(path.begin(), path.end());
    // ans.path = path;
    // ans.pathLen = lenPath;
    // return ans;
}

std::string getLightLine(int boardWidth) {
    std::string lightLine = "";
    for (int i = 0; i < 2 * boardWidth + 4; i++) {
        lightLine += "░";
    }
    lightLine += "\n";
    return lightLine;
}

void Simulation::display(Board bd, LidiBoard lidiBd) {
    std::vector<std::string> boardRepr = bd.repr(), lidiRepr = lidiBd.repr();
    assert(boardRepr.size() == lidiRepr.size());

    std::string lightLine = getLightLine(bd.m);

    std::cout << lightLine;
    for (int i = 0; i < (int)boardRepr.size(); i++) {
        std::cout << boardRepr[i] << " | " << lidiRepr[i] << '\n';
    }

    std::cout << lightLine;
    std::cout << std::endl;
}

std::string SimulationResult::pathString() {
    if (path.size() == 0) return "No path found.";
    std::string pathString = "";
    for (char c : path) {
        pathString += c;
        pathString += " ";
    }
    pathString.pop_back();
    return pathString;
}

std::ostream& operator<<(std::ostream& o, SimulationResult& result) {
    o << "Path:   " << result.pathString() << std::endl;
    o << "Path Len: " << result.pathLen << std::endl;
    return o;
}

std::ostream& operator<<(std::ostream& o, Simulation& sim) {
    o << "min distance: " << sim.minDistance << std::endl;
    o << "l: " << sim.lBest << std::endl;
    o << "r: " << sim.rBest << std::endl;
    return o;
}
//
//
//
//
//
//
//
//
//
//
// D U D U D U D U D R D