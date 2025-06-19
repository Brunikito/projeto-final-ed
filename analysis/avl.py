#!/usr/bin/env python3
"""
avl.py — análise de benchmarks da AVL

Gera e salva gráficos a partir do CSV de resultados produzido por `bench_avl.cpp`.

Estrutura de diretórios esperada (raiz do projeto):

benchmark/results/avl.csv
analysis/graphs/           (onde os PNGs serão salvos)

Uso:
    python analysis/avl.py                # caminhos padrão
    python analysis/avl.py --csv outra.csv --outdir figs/
"""

import argparse
from pathlib import Path

import pandas as pd
import matplotlib.pyplot as plt


def plot_metric(df, x_col, y_col, ylabel, title, out_path):
    """Gera um gráfico simples linha-por-pontos e salva em *out_path*"""
    plt.figure()
    plt.plot(df[x_col], df[y_col], marker="o", linewidth=2)
    plt.xlabel("Número de documentos processados")
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(out_path, dpi=300)
    plt.close()


def main():
    parser = argparse.ArgumentParser(description="Gera gráficos de benchmark da AVL")
    parser.add_argument(
        "--csv",
        default=str(
            Path(__file__).resolve().parents[1]
            / "benchmark"
            / "results"
            / "avl.csv"
        ),
        help="Caminho para o CSV de resultados (padrão: benchmark/results/avl.csv)",
    )
    parser.add_argument(
        "--outdir",
        default=str(Path(__file__).resolve().parents[0] / "graphs"),
        help="Diretório onde os PNGs serão salvos (padrão: analysis/graphs)",
    )

    args = parser.parse_args()
    csv_path = Path(args.csv)
    outdir = Path(args.outdir)
    outdir.mkdir(parents=True, exist_ok=True)

    if not csv_path.exists():
        raise FileNotFoundError(f"CSV não encontrado: {csv_path}")

    df = pd.read_csv(csv_path)

    metrics = [
        ("tempo_insercao_doc_ms", "Tempo de inserção (ms/doc)", "avl_insert_time.png"),
        ("tempo_busca_total_ms", "Tempo total de busca (ms)", "avl_search_time.png"),
        ("altura_arvore", "Altura da árvore", "avl_height.png"),
        ("comp_insercao_media", "Comparações médias de inserção", "avl_comp_insert.png"),
        ("comp_busca_media", "Comparações médias de busca", "avl_comp_search.png"),
    ]

    for col, ylabel, filename in metrics:
        out_path = outdir / filename
        title = f"{ylabel} vs. Nº de documentos"
        plot_metric(df, "num_docs_processados", col, ylabel, title, out_path)
        print(f"Gerado: {out_path}")


if __name__ == "__main__":
    main()
