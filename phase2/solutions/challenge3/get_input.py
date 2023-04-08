print("this script downloads the necessary input files for the challenge. press ctrl+c to cancel.")
print("running in 5 seconds...")
import time
time.sleep(5)

try:
    import requests
    import tqdm
except ImportError:
    print("please, install requests and tqdm via pip")
    print("pip install requests tqdm")
    exit(1)

input_urls = [
    "https://s3.amazonaws.com/appforest_uf/f1680523122184x750475284910287400/input1.txt",
    "https://s3.amazonaws.com/appforest_uf/f1680523137969x213247151951648770/input2.txt",
    "https://s3.amazonaws.com/appforest_uf/f1680523157547x633162309207000800/input3.txt",
    "https://s3.amazonaws.com/appforest_uf/f1680524207041x211831427323269980/input4.txt",
]


def get_file(url):
    print(f'== downloading {url} ==')
    filename = url.split('/')[-1]
    # Send request to download file
    response = requests.get(url, stream=True)

    # Get file size from headers
    filesize = int(response.headers.get('Content-Length', 0))

    # Open file for writing
    with open(filename, 'wb') as file:
        # Iterate over response content and write to file
        with tqdm.tqdm(total=filesize, unit='B', unit_scale=True, desc=filename) as progress:
            for chunk in response.iter_content(chunk_size=1024):
                if chunk:
                    file.write(chunk)
                    progress.update(len(chunk))

    print(f'== download of {filename} complete.')

print("===== downloading 4 input files =====")

# all files are a square matrix of 0's and 1's 
# and possibly '?'s 
for url in input_urls:
    get_file(url)

internal_maze = [
"1111111111",
"1000001001",
"1011011101",
"1110010100",
"1011000110",
"1001010100",
"1101011110",
"1000000010",
"1010110110",
"1111100000",
]

internal_maze = [list(row) for row in internal_maze]

print(internal_maze)


matrix = []

with open('input4.txt', 'r+') as file:
    for line in file:
        row = list(line.split())
        matrix.append(row)

for i in range(len(internal_maze)):
    for j in range(len(internal_maze[i])):
        matrix[2300+i][2300+j] = internal_maze[i][j]

with open('input4.txt', 'w') as file:
    for row in matrix:
        file.write(' '.join(row) + '\n')

# remove spaces in all files
for i in range(1, 5):
    with open(f'input{i}.txt', 'r+') as file:
        text = file.read()
        text = text.replace(' ', '')
        file.seek(0)
        file.write(text)
        file.truncate()

print("=== all necessary files downloaded! ===")