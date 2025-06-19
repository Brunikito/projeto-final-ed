import pandas as pd
import matplotlib.pyplot as plt
import os

def plot_all_metrics_separately(df, tree_name, output_dir):
    """Gera 6 gráficos de desempenho, um para cada métrica principal, e um grafico agrupado, salvando-os em arquivos separados."""
    
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
    
    # Total de Nós na Árvore
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
    
    # Geração do grafico agrupado
    
    fig, axes = plt.subplots(2, 2, figsize=(16, 12))
    fig.suptitle(f'Análise de Desempenho - {tree_name.upper()}', fontsize=16)
    
    # 1: Tempo de Execução
    axes[0, 0].plot(df[x_axis], df["tempo_insercao_doc_ms"], label="Inserção")
    axes[0, 0].plot(df[x_axis], df["tempo_busca_total_ms"], label="Busca")
    axes[0, 0].set_title("Tempo de Execução")
    axes[0, 0].set_ylabel("Tempo (ms)")
    axes[0, 0].legend()
    axes[0, 0].grid(True)

    # 2: Altura da Árvore
    axes[0, 1].plot(df[x_axis], df["altura_arvore"], color='green')
    axes[0, 1].set_title("Altura da Árvore")
    axes[0, 1].set_ylabel("Altura")
    axes[0, 1].grid(True)

    # 3: Comparações Médias
    axes[1, 0].plot(df[x_axis], df["comp_insercao_media"], label="Inserção")
    axes[1, 0].plot(df[x_axis], df["comp_busca_media"], label="Busca")
    axes[1, 0].set_title("Comparações Médias")
    axes[1, 0].set_ylabel("Nº de Comparações")
    axes[1, 0].legend()
    axes[1, 0].grid(True)

    # 4: Profundidade Média
    axes[1, 1].plot(df[x_axis], df["prof_insercao_media"], label="Inserção")
    axes[1, 1].plot(df[x_axis], df["prof_busca_media"], label="Busca")
    axes[1, 1].set_title("Profundidade Média")
    axes[1, 1].set_ylabel("Profundidade")
    axes[1, 1].legend()
    axes[1, 1].grid(True)
    
    for ax in axes.flat:
        ax.set_xlabel("Documentos Processados")

    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.savefig(f"{output_dir}/{tree_name}_analise_completa.png")
    plt.close()


    print(f"Gráficos individuais e agrupado para {tree_name.upper()} salvos.")

if __name__ == "__main__":
    plot_all_metrics_separately(
        df=pd.read_csv("../benchmark/results/bst.csv"),
        tree_name="bst",
        output_dir="graphs"
    )