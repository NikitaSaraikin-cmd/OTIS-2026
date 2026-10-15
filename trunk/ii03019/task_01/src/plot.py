# -*- coding: utf-8 -*-
import os
import csv
import matplotlib.pyplot as plt

CSV_FILENAME = "results.csv"

csv_file = CSV_FILENAME
if not os.path.exists(csv_file):
    csv_file = os.path.join("..", CSV_FILENAME)
if not os.path.exists(csv_file):
    csv_file = os.path.join("build", "src", CSV_FILENAME)

doc_dir = os.path.join(os.path.dirname(__file__), "..", "doc")
if not os.path.exists(doc_dir):
    os.makedirs(doc_dir)

# Считывание данных
rows = []
with open(csv_file, 'r') as f:
    reader = csv.DictReader(f)
    for r in reader:
        rows.append({
            'step': int(r['step']),
            'signal': r['signal'],
            'model1': float(r['model1']),
            'model2': float(r['model2']),
            'model3': float(r['model3'])
        })

signals = ["Step", "Impulse", "Harmonic"]
models_info = [
    ("model1", "Model 1.1 (Standard First-Order Inertial System)", "plot.png"),
    ("model2", "Model 2.5 (Signum Friction and Exponential Growth)", "plot2.png"),
    ("model3", "Model 3.9 (Bounded Saturation Rate)", "plot3.png")
]

created_files = []

for key, title_name, out_filename in models_info:
    plt.figure(figsize=(9, 5))
    for sig in signals:
        steps_sig = [r['step'] for r in rows if r['signal'] == sig]
        vals_sig = [r[key] for r in rows if r['signal'] == sig]
        lbl = "Output y (Input: " + str(sig) + ")"
        plt.plot(steps_sig, vals_sig, marker='o', markersize=3, label=lbl)

    plt.title(title_name, fontsize=12)
    plt.xlabel("Step (tau)", fontsize=10)
    plt.ylabel("Output y", fontsize=10)
    plt.grid(True, linestyle=':', alpha=0.6)
    plt.legend()
    plt.tight_layout()

    save_path = os.path.join(doc_dir, out_filename)
    plt.savefig(save_path, dpi=300)
    plt.close()
    created_files.append(os.path.abspath(save_path))

for img_path in created_files:
    if hasattr(os, "startfile"):
        os.startfile(img_path)