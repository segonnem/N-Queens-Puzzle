import subprocess
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np

def run_cpp_executable(executable_path, n):
    result = subprocess.run([executable_path], text=True, input=str(n), capture_output=True)
    return result.stdout.strip().split('\n')

def draw_chessboard(n, queens_positions):
    fig, ax = plt.subplots(figsize=(9, 9))
    # Draw chessboard
    for i in range(n):
        for j in range(n):
            color = 'black' if (i + j) % 2 == 0 else 'white'
            ax.add_patch(plt.Rectangle((j, n-1-i), 1, 1, facecolor=color))

    
    queen_image = Image.open('../../assets/images/Queen.png')
    queen_image = queen_image.resize((int(fig.bbox.width / n), int(fig.bbox.height / n)), Image.Resampling.LANCZOS)
    queen_image = np.array(queen_image)
    queens_positions = queens_positions[-n:]

    # Add queens
    for i in range(n):
        for j in range(n):
            if queens_positions[i][j] == 'Q':
                ax.imshow(queen_image, extent=(j, j + 1, n - 1 - i, n - i), aspect='auto', zorder=2)

    ax.set_xlim(0, n)
    ax.set_ylim(0, n)
    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_aspect('equal')
    plt.show()

# N input
n = int(input("Enter the size of the board (N): "))

executable_path = '../cpp/NQueensOneSolu.exe'

queens = run_cpp_executable(executable_path, n)

draw_chessboard(n, queens)
