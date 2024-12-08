import matplotlib.pyplot as plt
import pandas as pd
import numpy as np



data = pd.DataFrame(pd.read_csv("results/output.csv"))


probl = data["problem"].unique()
nom_probl = probl
n = len(probl)

for i in range(n):

   data_probl = data[data["problem"] == probl[i]]
   plt.figure(i)
   #plt.subplot(n,1,i+1)s
   plt.title(nom_probl[i])

   x = data_probl['nb_of_threads'].unique()
   y = []
   y_mean = []
   for i in range (len(x)):
       data_temp = data_probl[data_probl['nb_of_threads']==x[i]]['time']
       y.append(data_temp) 
       y_mean.append(data_temp.mean())


   plt.plot(x, y_mean)
   plt.boxplot(y, positions=x)

   plt.xlabel('Nombre de threads')
   plt.ylabel('Temps [s]')
   plt.ylim(0,data_probl['time'].max()*(1.05))
   plt.xticks(x)


plt.show()
plt.close()