import sys

import matplotlib
import numpy as np

matplotlib.use("Agg")
import matplotlib.pyplot as plt

# Usage: python scripts/plot_cruise.py cruise.csv docs/cruise_step.png
data = np.genfromtxt(sys.argv[1], delimiter=",", names=True)
fig, axes = plt.subplots(3, 1, sharex=True, figsize=(8, 8))
axes[0].plot(data["t_s"], data["ref_mps"], "--", label="target")
axes[0].plot(data["t_s"], data["speed_mps"], label="speed")
axes[0].set_ylabel("speed (m/s)")
axes[0].legend()
axes[1].plot(data["t_s"], data["force_cmd_n"], label="asked")
axes[1].plot(data["t_s"], data["force_actual_n"], label="actual")
axes[1].set_ylabel("force (N)")
axes[1].legend()
axes[2].plot(data["t_s"], data["slope_rad"])
axes[2].set_ylabel("road slope (rad)")
axes[2].set_xlabel("time (s)")
fig.savefig(sys.argv[2], dpi=150)