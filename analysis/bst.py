import pandas as pd
import matplotlib.pyplot as plt
import os

def plot_all_metrics_separately(df, tree_name, output_dir):
    """Gera 6 gráficos de desempenho, um para cada métrica principal, em arquivos separados."""
    os.makedirs(output_dir, exist_ok=True)
    x_axis = "num_docs_processados"

    # Tempo de Inserção
    plt.figure(figsize=(10, 6))
    plt.plot(df[x_axis], df["tempo_insercao_doc_ms"], marker='.')
    plt.title(f'Tempo de Inserção - {tree_name.upper()}')
    plt.xlabel("Documentos Processados")
    plt.ylabel("Tempo (ms)")
    plt.grid(True)
    plt.savefig(f"{output_dir}/{tree_name}_tempo_insercao.png")
    plt.close()

    # Tempo de Busca
    plt.figure(figsize=(10, 6))
    plt.plot(df[x_axis], df["tempo_busca_total_ms"], marker='.', color='orange')
    plt.title(f'Tempo de Busca - {tree_name.upper()}')
    plt.xlabel("Documentos Processados")
    plt.ylabel("Tempo (ms)")
    plt.grid(True)
    plt.savefig(f"{output_dir}/{tree_name}_tempo_busca.png")
    plt.close()

    # Altura da Árvore
    plt.figure(figsize=(10, 6))
    plt.plot(df[x_axis], df["altura_arvore"], color='green', marker='.')
    plt.title(f'Altura da Árvore - {tree_name.upper()}')
    plt.xlabel("Documentos Processados")
    plt.ylabel("Altura")
    plt.grid(True)
    plt.savefig(f"{output_dir}/{tree_name}_altura.png")
    plt.close()
    
    # Total de Nós na Árvore (O que faltava)
    plt.figure(figsize=(10, 6))
    plt.plot(df[x_axis], df["total_nos_arvore"], color='purple', marker='.')
    plt.title(f'Total de Nós na Árvore - {tree_name.upper()}')
    plt.xlabel("Documentos Processados")
    plt.ylabel("Total de Nós")
    plt.grid(True)
    plt.savefig(f"{output_dir}/{tree_name}_total_nos.png")
    plt.close()

    # Comparações Médias (Inserção vs Busca)
    plt.figure(figsize=(10, 6))
    plt.plot(df[x_axis], df["comp_insercao_media"], label="Inserção", marker='.')
    plt.plot(df[x_axis], df["comp_busca_media"], label="Busca", marker='.')
    plt.title(f'Comparações Médias (Inserção vs. Busca) - {tree_name.upper()}')
    plt.xlabel("Documentos Processados")
    plt.ylabel("Nº de Comparações")
    plt.legend()
    plt.grid(True)
    plt.savefig(f"{output_dir}/{tree_name}_comparacoes_media.png")
    plt.close()

    # Profundidade Média (Inserção vs Busca)
    plt.figure(figsize=(10, 6))
    plt.plot(df[x_axis], df["prof_insercao_media"], label="Inserção", marker='.')
    plt.plot(df[x_axis], df["prof_busca_media"], label="Busca", marker='.')
    plt.title(f'Profundidade Média (Inserção vs. Busca) - {tree_name.upper()}')
    plt.xlabel("Documentos Processados")
    plt.ylabel("Profundidade")
    plt.legend()
    plt.grid(True)
    plt.savefig(f"{output_dir}/{tree_name}_profundidade_media.png")
    plt.close()

    print(f"6 gráficos de análise para {tree_name.upper()} salvos em '{output_dir}'.")

if __name__ == "__main__":
    plot_all_metrics_separately(
        df=pd.read_csv("../benchmark/results/bst.csv"),
        tree_name="bst",
        output_dir="graphs"
    )