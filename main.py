import copy
import random
from time import sleep

WHITE_CELL = 0
GREEN_CELL = 1
START = 3
FINISH = 4

class Maze:
    def __init__(self, board):
        # initialize maze, player position, finish position
        self.n_lines = len(board)
        self.n_cols = len(board[0])
        self.board = copy.deepcopy(board)

    def initpath(self):
        self.path = [["" for j in range(self.n_cols)] for i in range(self.n_lines)]

    def __repr__(self):
        transform = {
            WHITE_CELL: ' ',
            GREEN_CELL: '▓',
            START: 'O',
            FINISH: 'X',
        }

        board_copy = copy.deepcopy(self.board)
        to_show = [[transform[x] for x in y] for y in board_copy]

        to_draw_str = ""

        for line in to_show:
            to_draw_str += ''.join(line) + "\n"

        return to_draw_str

    def valid(self, line, col):
        return line >= 0 and line < self.n_lines and col >= 0 and col < self.n_cols

    def vertice_neighbours(self, line, col):
        neighs = []
        for dl in [-1, 0, +1]:
            for dc in [-1, 0, +1]:
                if dl == 0 and dc == 0:
                    continue
                new_l, new_c = line+dl, col+dc
                if not self.valid(new_l, new_c):
                    continue
                neighs.append([new_l, new_c])
        return neighs

    def edge_neighbours(self, line, col):
        neighs = []
        for dl, dc, direction in [[0, +1, 'R'], [0, -1, 'L'], [+1, 0, 'D'], [-1, 0, 'U']]:
            new_l, new_c = line+dl, col+dc
            if not self.valid(new_l, new_c):
                continue
            neighs.append([new_l, new_c, direction])
        return neighs

    def count(self, line, col):
        n_white = 0
        n_green = 0
        for neigh_l, neigh_c in self.vertice_neighbours(line, col):
            if self.board[neigh_l][neigh_c] == WHITE_CELL:
                n_white += 1
            if self.board[neigh_l][neigh_c] == GREEN_CELL:
                n_green += 1
        ans = {"n_white" : n_white, "n_green" : n_green}
        if line == 3 and col == 3:
            print(ans)
        return ans

    def next_color(self, line, col):
        cur_color = self.board[line][col]
        if cur_color == START:
            return START
        elif cur_color == FINISH:
            return FINISH
        elif cur_color == WHITE_CELL:
            n_green = self.count(line, col)["n_green"]
            if n_green > 1 and n_green < 5: # 4 for 1st challenge, 5 for the 2nd
                return GREEN_CELL
            else:
                return WHITE_CELL
        elif cur_color == GREEN_CELL:
            n_green = self.count(line, col)["n_green"]
            if n_green > 3 and n_green < 6: # 7 for 1st challenge, 6 for the 2nd
                return GREEN_CELL
            else:
                return WHITE_CELL

    def next(self):
        maze = copy.deepcopy(self)
        for i in range(self.n_lines):
            for j in range(self.n_cols):
                maze.board[i][j] = self.next_color(i, j)
        maze.initpath()
        return maze

def str_to_board(st):
    return list(map(lambda x: list(map(int, list(x))), st.split()))
        
board_example = [
    [3, 0, 0, 1, 1],
    [0, 0, 1, 1, 0],
    [0, 1, 0, 1, 0],
    [0, 0, 1, 0, 4],
]

board_stone_1 = str_to_board(
"""
30000000
00001000
00101100
01100110
00101100
00001000
00000004
""")

board_stone_2 = str_to_board(
"""
3000000000000000000000000000000000000000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000111110000000000000000000000000000000000000
0000000000000000000000000000000000000000000111111111000000000000000000000000000000000
0000000000000000000000000000000000000000000111111111110000000000000000000000000000000
0000000000000000000000000000000000000000000111111111111100000000000000000000000000000
0000000000000000000000000000000000000000000111111111111111000000000000000000000000000
0000000000000000000000000000000000000000000111111111111111110000000000000000000000000
0000000000000000000000000000000000000000000111111111111111111000000000000000000000000
0000000000000000000000000000000000000000000111111111111111111110000000000000000000000
0000000000000000000000000000000000000000000111111111111111111111000000000000000000000
0000000000000000000000000000000000000000000111111111111111111111100000000000000000000
0000000000000000000000000000000000000000000111111111111111111111110000000000000000000
0000000000000000000000000000000000000000000111111111111111111111110000000000000000000
0000000000000000000000000000000000000000000111111111111111111111111000000000000000000
0000000000000000000000000000000000000000000111111111111111111111111100000000000000000
0000000000000000000000000000000000000000000111111111111111111111111110000000000000000
0000000000000000000000000100000000000000000001111111111111111111111110000000000000000
0000000000000000000000001110000000000000000000001111111111111111111111000000000000000
0000000000000000000000011110000000000000000000000011111111111111111111000000000000000
0000000000000000000000111110000000000000000000000000111111111111111111100000000000000
0000000000000000000001111110000000000000000000000000011111111111111111100000000000000
0000000000000000000011111110000000000000000000000000001111111111111111100000000000000
0000000000000000000111111110000000000000000000000000000111111111111111110000000000000
0000000000000000001111111110000000000000000000000000000111111111111111110000000000000
0000000000000000011111111110000000000000000000000000000011111111111111110000000000000
0000000000000000111111111110000000000000000000000000000011111111111111110000000000000
0000000000000001111111111110000000000000000000000000000001111111111111111000000000000
0000000000000011111111111110000000000000000000000000000001111111111111111000000000000
0000000000000111111111111110000000000000000000000000000001111111111111111000000000000
0000000000001111111111111110000000000000000000000000000000111111111111111000000000000
0000000000001111111111111110000000000000000000000000000000111111111111111000000000000
0000000000001111111111111110000000000000000000000000000000111111111111111000000000000
0000000000001111111111111110000000000000000000000000000000111111111111111000000000000
0000000000001111111111111110000000000000000000000000000000111111111111111000000000000
0000000000000111111111111110000000000000000000000000000001111111111111111000000000000
0000000000000011111111111110000000000000000000000000000001111111111111111000000000000
0000000000000001111111111110000000000000000000000000000001111111111111111000000000000
0000000000000000111111111110000000000000000000000000000011111111111111110000000000000
0000000000000000011111111110000000000000000000000000000011111111111111110000000000000
0000000000000000001111111110000000000000000000000000000111111111111111110000000000000
0000000000000000000111111110000000000000000000000000000111111111111111110000000000000
0000000000000000000011111110000000000000000000000000001111111111111111100000000000000
0000000000000000000001111110000000000000000000000000011111111111111111100000000000000
0000000000000000000000111110000000000000000000000000111111111111111111100000000000000
0000000000000000000000011110000000000000000000000011111111111111111111000000000000000
0000000000000000000000001110000000000000000000001111111111111111111111000000000000000
0000000000000000000000000100000000000000000001111111111111111111111110000000000000000
0000000000000000000000000000000000000000000111111111111111111111111110000000000000000
0000000000000000000000000000000000000000000111111111111111111111111100000000000000000
0000000000000000000000000000000000000000000111111111111111111111111000000000000000000
0000000000000000000000000000000000000000000111111111111111111111110000000000000000000
0000000000000000000000000000000000000000000111111111111111111111110000000000000000000
0000000000000000000000000000000000000000000111111111111111111111100000000000000000000
0000000000000000000000000000000000000000000111111111111111111111000000000000000000000
0000000000000000000000000000000000000000000111111111111111111110000000000000000000000
0000000000000000000000000000000000000000000111111111111111111000000000000000000000000
0000000000000000000000000000000000000000000111111111111111110000000000000000000000000
0000000000000000000000000000000000000000000111111111111111000000000000000000000000000
0000000000000000000000000000000000000000000111111111111100000000000000000000000000000
0000000000000000000000000000000000000000000111111111110000000000000000000000000000000
0000000000000000000000000000000000000000000111111111000000000000000000000000000000000
0000000000000000000000000000000000000000000111110000000000000000000000000000000000000
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000000000000000000000000000000000000000000004""")

def evaluate_path_mazes(next_maze, maze):
    # compara todas as celulas do next_maze com as vizinhas do maze
    # se a do maze tiver uma string nao vazia, entao o vizinho do next_maze
    # pode ser chegado. dai a gente concatena com a direcao
    next_maze.path = [["" for j in range(maze.n_cols)] for i in range(maze.n_lines)]
    poss_neighs = [[[] for j in range(maze.n_cols)] for i in range(maze.n_lines)]
    for i in range(maze.n_lines):
        for j in range(maze.n_cols):
            if maze.path[i][j] == '':
                continue
            for line, col, direction in maze.edge_neighbours(i, j):
                poss_neighs[line][col].append([i, j, direction])
    for i in range(maze.n_lines):
        for j in range(maze.n_cols):
            if len(poss_neighs[i][j]) == 0:
                continue
            if next_maze.board[i][j] == GREEN_CELL:
                continue
            # could be also be poss_neighs[i][j][0] for determinism
            line, col, direction = random.choice(poss_neighs[i][j])
            next_maze.path[i][j] = maze.path[line][col] + " " + direction

    
def find_path(maze: Maze) -> str:
    assert maze.board[0][0] == 3 # assume the start is at the top left corner
    assert maze.board[-1][-1] == 4 # assume the finish is at the bottom right corner
    maze.initpath()
    maze.path[0][0] = 'X' # just to have a non-null path at 3
    while maze.path[-1][-1] == '':
        print(maze)
        print(maze.path)
        sleep(0.5)
        next_maze = maze.next()
        evaluate_path_mazes(next_maze, maze)
        maze = next_maze
    print(maze)
    print(maze.path)
    return maze.path[-1][-1]


if __name__ == "__main__":
    maze = Maze(board=board_stone_1)
    find_path(maze)