maze = []
with open("../input/input4.txt") as f:
    lines = f.readlines()
    maze = [line.split() for line in lines]

print(len(maze))
print(len(maze[0]))

hidden = [line[2300:2310] for line in maze[2300:2310]]

to_print = '\n'.join([''.join(line) for line in hidden])

print(to_print)