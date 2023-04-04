for i in range(1, 6):
    maze = []
    n_zeros = 0
    n_ones = 0
    with open(f"input/input{i}.txt") as f:
        lines = f.readlines()
        maze = [line.split() for line in lines]
        for line in maze:
            n_zeros += line.count("0")
            n_ones += line.count("1")
    print(f"{i}: {len(maze)} x {len(maze[0])} (zeros = {n_zeros}, ones = {n_ones})")