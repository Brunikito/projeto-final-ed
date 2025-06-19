#!/usr/bin/env python3
"""
all.py — comparação global BST × AVL × RBT

Lê os três CSVs de benchmark e gera gráficos comparativos em um único
arquivo para cada métrica.

Estrutura de diretórios esperada:

benchmark/results/bst.csv
benchmark/results/avl.csv
benchmark/results/rbt.csv
analysis/graphs/

Uso:
    python analysis/all.py                              # caminhos padrão
    python analysis/all.py --dir benchmark/results      # diretório de CSVs
    python analysis/all.py --outdir figs/               # salva em figs/
"""

import argparse
from pathlib import Path

import pandas as pd
import matplotlib.pyplot as plt


DEFAULT_METRICS = [
    ("tempo_insercao_doc_ms", "Tempo de inserção (ms/doc)", "all_insert_time.png"),
    ("tempo_busca_total_ms", "Tempo total de busca (ms)", "all_search_time.png"),
    ("altura_arvore", "Altura da árvore", "all_height.png"),
    ("comp_insercao_media", "Comparações médias de inserção", "all_comp_insert.png"),
    ("comp_busca_media", "Comparações médias de busca", "all_comp_search.png"),
]


def load_csvs(csv_dir: Path):
    """Carrega bst.csv, avl.csv e rbt.csv para um dict de DataFrames."""
    files = {
        "BST": csv_dir / "bst.csv",
        "AVL": csv_dir / "avl.csv",
        "RBT": csv_dir / "rbt.csv",
    }
    data = {}
    for name, path in files.items():
        if not path.exists():
            raise FileNotFoundError(f"CSV não encontrado: {path}")
        data[name] = pd.read_csv(path)
    return data


def plot_metric(data, metric, ylabel, out_path):
    """Plota a métrica escolhida para as três estruturas."""
    plt.figure()
    for name, df in data.items():
        plt.plot(
            df["num_docs_processados"],
            df[metric],
            marker="o",
            linewidth=2,
            label=name,
        )
    plt.xlabel("Número de documentos processados")
    plt.ylabel(ylabel)
    plt.title(f"{ylabel} vs. Nº de documentos")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(out_path, dpi=300)
    plt.close()


def main():
    parser = argparse.ArgumentParser(description="Gera gráficos comparativos BST/AVL/RBT")
    parser.add_argument(
        "--dir",
        default=str(Path(__file__).resolve().parents[1] / "benchmark" / "results"),
        help="Diretório contendo bst.csv, avl.csv e rbt.csv (padrão: benchmark/results)",
    )
    parser.add_argument(
        "--outdir",
        default=str(Path(__file__).resolve().parents[0] / "graphs"),
        help="Diretório onde os PNGs serão salvos (padrão: analysis/graphs)",
    )
    args = parser.parse_args()

    csv_dir = Path(args.dir)
    outdir = Path(args.outdir)
    outdir.mkdir(parents=True, exist_ok=True)

    data = load_csvs(csv_dir)

    for col, ylabel, filename in DEFAULT_METRICS:
        out_path = outdir / filename
        plot_metric(data, col, ylabel, out_path)
        print(f"Gerado: {out_path}")


if __name__ == "__main__":
    main()
