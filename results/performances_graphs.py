import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

#################
# configuration #
#################

data = pd.DataFrame(pd.read_csv("output.csv"))

data_ph = data.drop(["uTime", "sTime"], axis=1)[data["Program"] == "ph"]
data_pc = data.drop(["uTime", "sTime"], axis=1)[data["Program"] == "pc"]
data_le = data.drop(["uTime", "sTime"], axis=1)[data["Program"] == "le"]


plt.figure(figsize = (9,7))
plt.gcf().subplots_adjust(hspace = 0.5)


###################
# plot philosophe #
###################

plt.subplot(3,1,1)
plt.title('méthode des Philosophes')

x = data_ph['Threads'].unique()
y = []
y_mean = []
for i in range (len(x)):
    data = data_ph[data_ph['Threads']==x[i]]['eTime']
    y.append(data) 
    y_mean.append(data.mean())


plt.plot(x, y_mean)
plt.boxplot(y, positions=x)


plt.xlabel('Nombre de threads')
plt.ylabel('Temps en seconde')
plt.xticks(x)


#################################
# plot Producteur - Consomateur #
#################################

plt.subplot(3,1,2)
plt.title('méthode Producteur - Consomateur')

x = data_pc['Threads'].unique()
y = []
y_mean = []
for i in range (len(x)):
    data = data_pc[data_pc['Threads']==x[i]]['eTime']
    y.append(data) 
    y_mean.append(data.mean())


plt.plot(x, y_mean)
plt.boxplot(y, positions=x)


plt.xlabel('Nombre de threads')
plt.ylabel('Temps en seconde')
plt.xticks(x)


###########################
# plot Lecteur - Ecrivain #
###########################

plt.subplot(3,1,3)
plt.title('méthode Lecteur - Ecrivain')

x = data_pc['Threads'].unique()
y = []
y_mean = []
for i in range (len(x)):
    data = data_pc[data_pc['Threads']==x[i]]['eTime']
    y.append(data) 
    y_mean.append(data.mean())


plt.plot(x, y_mean)
plt.boxplot(y, positions=x)


plt.xlabel('Nombre de threads')
plt.ylabel('Temps en seconde')
plt.xticks(x)



plt.show()
plt.close()

