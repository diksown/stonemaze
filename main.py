import copy
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

    def count(self, line, col):
        n_white = 0
        n_green = 0
        for dl in [-1, 0, +1]:
            for dc in [-1, 0, +1]:
                    if dl == 0 and dc == 0:
                        continue
                    new_l, new_c = line+dl, col+dc
                    if not self.valid(new_l, new_c):
                        continue
                    if self.board[new_l][new_c] == WHITE_CELL:
                        n_white += 1
                    if self.board[new_l][new_c] == GREEN_CELL:
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
            if n_green > 1 and n_green < 4: # 4 for 1st challenge, 5 for the 2nd
                return GREEN_CELL
            else:
                return WHITE_CELL
        elif cur_color == GREEN_CELL:
            n_green = self.count(line, col)["n_green"]
            if n_green > 3 and n_green < 7: # 7 for 1st challenge, 6 for the 2nd
                return GREEN_CELL
            else:
                return WHITE_CELL

    def next(self):
        maze = copy.deepcopy(self)
        for i in range(self.n_lines):
            for j in range(self.n_cols):
                maze.board[i][j] = self.next_color(i, j)
        return maze

def str_to_board(st):
    return list(map(lambda x: list(map(int, list(x))), st.split()))
        
board_example = [
    [3, 0, 0, 1, 1],
    [0, 0, 1, 1, 0],
    [0, 1, 0, 1, 0],
    [0, 0, 1, 0, 4],
]

board_stone = str_to_board(
"""
30000000
00001000
00101100
01100110
00101100
00001000
00000004
"""
)

    
def find_path(maze: Maze) -> str:
    next_maze = maze.copy()
    next_maze.next()

if __name__ == "__main__":
    maze = Maze(board=board_stone)
    for i in range(10000):
        print("\n" * 100)
        print(maze)
        print(i)
        maze = maze.next()
        # sleep(2)
        input()