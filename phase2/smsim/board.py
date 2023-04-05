# Import standard library
from typing import Tuple

# Import modules
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.image import AxesImage
from loguru import logger

class Board:
    def __init__(self, size=(100, 100)):
        """Initialize the class
        Parameters
        ----------
        size : array_like of size 2
            Size of the board (default is `(100, 100)`)
        """
        self.size = size
        p = 1/3  # Probability of generating 1
        self.state = np.random.choice([0, 1], size=size, p=[1-p, p])

    def view(self, figsize=(5, 5)) -> Tuple[Figure, AxesImage]:
        """View the current state of the board
        Parameters
        ----------
        figsize : tuple
            Size of the output figure
        Returns
        -------
        (:obj:`matplotlib.figure.Figure`, :obj:`matplotlib.image.AxesImage`)
            Graphical view of the board
        """
        fig = plt.figure(figsize=figsize)
        ax = fig.add_axes([0, 0, 1, 1], xticks=[], yticks=[], frameon=False)
        im = ax.imshow(self.state, cmap=plt.cm.binary, interpolation="nearest")
        im.set_clim(-0.05, 1)
        return fig, im