import sys

import matplotlib
import numpy as np

matplotlib.use("Agg")
import matplotlib.pyplot as plt

# Usage: python scripts/plot_windup.py with.csv without.csv docs/windup_comparison.png
with_aw = np.genfromtxt(sys.argv[1], delimiter=",", names=True)
without_aw = np.genfromtxt(sys.argv[2], delimiter=",", names=True)
plt.figure(figsize=(8, 4))
plt.plot(with_aw["t_s"], with_aw["ref_mps"], "--", label="target")
plt.plot(with_aw["t_s"], with_aw["speed_mps"], label="anti-windup on")
plt.plot(without_aw["t_s"], without_aw["speed_mps"], label="anti-windup off")
plt.xlabel("time (s)")
plt.ylabel("speed (m/s)")
plt.legend()
plt.savefig(sys.argv[3], dpi=150)