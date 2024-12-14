import pandas as pd
import matplotlib.pyplot as plt

# Charger les données du fichier CSV
file = "tout_pc.csv"
data = pd.read_csv(file)
data.columns = data.columns.str.strip()

# Supprimer "src/" au début des noms de problème
data["problem"] = data["problem"].str.replace(r"^src/", "", regex=True)

# Extraire le nom principal du problème 
data["main_problem"] = data["problem"].apply(lambda x: x.split("_")[0])

fig, axes = plt.subplots(2, 1, figsize=(10, 12)) 

# Graphique pour TAS
test_and_set_data = data[data["problem"].str.contains("test-and-set")]
ax1 = axes[0]  # Subplot en haut
ax1.set_title("Performance de Test-and-Set")
ax1.set_xlabel("Nombre de threads")
ax1.set_ylabel("Temps moyen (s)")

# Tracer les courbes et boxplot
for keyword in ["test-and-set"]:
    test_data = test_and_set_data[test_and_set_data["problem"].str.contains(keyword)]
    
    if not test_data.empty:
        grouped = test_data.groupby("nb_of_threads")["time"].mean().reset_index()
        ax1.plot(grouped["nb_of_threads"], grouped["time"], marker="o", label=keyword)
        
        # Boxplot vertical
        data_for_boxplot = [test_data[test_data["nb_of_threads"] == threads]["time"].values
                            for threads in sorted(test_data["nb_of_threads"].unique())]
        bp = ax1.boxplot(data_for_boxplot, positions=sorted(test_data["nb_of_threads"].unique()), 
                         widths=0.6, patch_artist=True, boxprops=dict(facecolor="lightgray", alpha=0.5))
        
        # Légende
        handles = [
            bp["medians"][0],  # Médiane
            bp["whiskers"][0], # Moustaches
        ]
        labels = ["Médiane", "Moustaches", "Moyenne"]
        ax1.legend(handles=handles + [plt.Line2D([0], [0], marker='o', color='b', label='Moyenne')], 
                   labels=labels, loc="upper left")

# Graphique pour TTAS
test_and_test_and_set_data = data[data["problem"].str.contains("test-and-test-and-set")]
ax2 = axes[1]  # Subplot en bas
ax2.set_title("Performance de Test-and-Test-and-Set")
ax2.set_xlabel("Nombre de threads")
ax2.set_ylabel("Temps moyen (s)")

# Tracer les courbes et ajouter un boxplot
for keyword in ["test-and-test-and-set"]:
    test_data = test_and_test_and_set_data[test_and_test_and_set_data["problem"].str.contains(keyword)]
    
    if not test_data.empty:
        grouped = test_data.groupby("nb_of_threads")["time"].mean().reset_index()
        
        ax2.plot(grouped["nb_of_threads"], grouped["time"], marker="o", label=keyword)
        
        # Boxplot vertical
        data_for_boxplot = [test_data[test_data["nb_of_threads"] == threads]["time"].values
                            for threads in sorted(test_data["nb_of_threads"].unique())]
        bp = ax2.boxplot(data_for_boxplot, positions=sorted(test_data["nb_of_threads"].unique()), 
                         widths=0.6, patch_artist=True, boxprops=dict(facecolor="lightgray", alpha=0.5))
        
        # Légende
        handles = [
            bp["medians"][0],  # Médiane
            bp["whiskers"][0], # Moustaches
        ]
        labels = ["Médiane", "Moustaches", "Moyenne"]
        ax2.legend(handles=handles + [plt.Line2D([0], [0], marker='o', color='b', label='Moyenne')], 
                   labels=labels, loc="upper left")

for ax in axes:
    ax.grid(True)
plt.tight_layout()

# Save and show the graphs
plt.savefig("my_graphs/test_and_set_comparison_vertical_with_legend.pdf") # Path to change
plt.show()
