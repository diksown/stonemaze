def is_valid(board):
    # Check for 2x2 squares of same value
    for i in range(len(board)-1):
        for j in range(len(board[0])-1):
            if board[i][j] == -1:
                continue
            if board[i][j] == board[i+1][j] == board[i][j+1] == board[i+1][j+1]:
                return False
    
    # Check if all 1's and 0's are connected
    visited = [[False] * len(board[0]) for _ in range(len(board))]
    queue = []
    for i in range(len(board)):
        for j in range(len(board[0])):
            if not visited[i][j]:
                if board[i][j] == 1:
                    queue.append((i, j))
                while queue:
                    x, y = queue.pop(0)
                    if not visited[x][y]:
                        visited[x][y] = True
                        if x > 0 and board[x-1][y] == board[i][j]:
                            queue.append((x-1, y))
                        if y > 0 and board[x][y-1] == board[i][j]:
                            queue.append((x, y-1))
                        if x < len(board)-1 and board[x+1][y] == board[i][j]:
                            queue.append((x+1, y))
                        if y < len(board[0])-1 and board[x][y+1] == board[i][j]:
                            queue.append((x, y+1))
    for row in visited:
        if False in row:
            return False
    
    return True

def solve(board, row=0, col=0):
    if row == len(board):
        return board
    
    next_row = row
    next_col = col + 1
    if next_col == len(board[0]):
        next_row += 1
        next_col = 0
    
    if board[row][col] == -1:
        for val in [0, 1]:
            board[row][col] = val
            if is_valid(board):
                result = solve(board, next_row, next_col)
                if result is not None:
                    return result
            board[row][col] = -1
    else:
        if is_valid(board):
            result = solve(board, next_row, next_col)
            if result is not None:
                return result
    
    return None

board_string = """
xxxxxx1xxx
x0xxx01xx1
xxx1xxxx0x
x11xx1x1xx
1xxxx0xx1x
xxx1xxx10x
x1xxxx11xx
1xxxxxxx1x
xx1xx1x11x
x1xx1xxxxx""".strip()
# Example usage
board = [[-1 if c == 'x' else int(c) for c in row] for row in board_string.split('\n')]
print(board)

result = solve(board)
if result is not None:
    for row in result:
        print(' '.join(str(val) for val in row))
else:
    print('No solution found.')