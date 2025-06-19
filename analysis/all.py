import pandas as pd
import matplotlib.pyplot as plt
import os

def plot_comparisons(data, output_dir):
    """
    Gera os gráficos mais importantes para comparar o desempenho de múltiplas árvores.
    """
    os.makedirs(output_dir, exist_ok=True)
    
    metrics_to_plot = {
        "tempo_insercao_doc_ms": (
            "Comparativo: Tempo de Inserção",
            "Tempo (ms)",
            "comparativo_tempo_insercao.png"
        ),
        "tempo_busca_total_ms": (
            "Comparativo: Tempo de Busca",
            "Tempo (ms)",
            "comparativo_tempo_busca.png"
        ),
        "altura_arvore": (
            "Comparativo: Altura da Árvore",
            "Altura",
            "comparativo_altura.png"
        ),
        "comp_insercao_media": (
            "Comparativo: Comparações Médias na Inserção",
            "Nº de Comparações",
            "comparativo_comparacoes_insercao.png"
        ),
        "comp_busca_media": (
            "Comparativo: Comparações Médias na Busca",
            "Nº de Comparações",
            "comparativo_comparacoes_busca.png"
        )
    }
    
    x_axis = "num_docs_processados"
    
    for column, (title, ylabel, filename) in metrics_to_plot.items():
        plt.figure(figsize=(11, 7))
        
        # Plota a linha para cada árvore (BST, AVL, RBT)
        for name, df in data.items():
            plt.plot(df[x_axis], df[column], label=name.upper(), marker='.', markersize=4)
        
        plt.title(title, fontsize=16)
        plt.xlabel("Documentos Processados")
        plt.ylabel(ylabel)
        plt.legend()
        plt.grid(True, which='both', linestyle='--', linewidth=0.5)
        
        plt.savefig(f"{output_dir}/{filename}")
        plt.close()
    
    print(f"5 gráficos comparativos foram salvos com sucesso em '{output_dir}'.")

if __name__ == "__main__":
    data_paths = {
        "bst": "../benchmark/results/bst.csv",
        "avl": "../benchmark/results/avl.csv",
        "rbt": "../benchmark/results/rbt.csv",
    }
    
    all_data = {name: pd.read_csv(path) for name, path in data_paths.items()}
    
    plot_comparisons(all_data, "graphs")