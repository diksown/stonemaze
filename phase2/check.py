def check_file(num):
    print(f"Checking output{num}.txt")
    with open(f"output{num}.txt", "r") as f:
        lines = f.readlines()
    assert(len(lines) == 1)
    line = lines[0]
    line = line.strip()
    assert line[-1] in list("UDLR")
    print(len(line.split(" ")))

if __name__ == "__main__":
    for i in range(1, 5):
        check_file(i)