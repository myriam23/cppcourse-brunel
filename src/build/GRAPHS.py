
# coding: utf-8

# In[19]:


import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('FigureA.txt')

select= np.array([d for d in data if d[1] < 50])
data1= select.transpose()
pl.xlim([100,300])
pl.scatter(data1[0],data1[1],s = 3, color='red',alpha=0.75, edgecolors='none');
pl.xlabel('Time in ms')
pl.ylabel('Neuron index')
pl.title('Network simulation with v_ext/v_th = 2 & g = 3')
pl.show();

n, bins, patches = pl.hist(np.array(100*list(data1[0])), 200, normed=0, rwidth =0.3, color = 'r', alpha=0.75)
pl.xlim([100,300])
pl.xlabel('Time in ms')
pl.ylabel('Number of spikes per time step')
pl.title('Network simulation with v_ext/v_th = 2 & g = 3')
pl.show();


# In[10]:


import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('FigureB.txt')

select= np.array([d for d in data if d[1] < 50 if d[0] < 800])
data1= select.transpose()
pl.xlim([100,300])
pl.scatter(data1[0],data1[1],s = 10, color='b',alpha=0.75, edgecolors='none');
pl.xlabel('Time in ms')
pl.ylabel('Neuron index')
pl.title('Network simulation with v_ext/v_th = 4 & g = 6')
pl.show();

n, bins, patches = pl.hist(np.array(10*list(data1[0])), 150, normed=0, rwidth =0.3, color='b', alpha=0.75)
pl.xlim([100,300])
pl.xlabel('Time in ms')
pl.ylabel('Number of spikes per time step')
pl.title('Network simulation with v_ext/v_th = 4 & g = 6')
pl.show();


# In[20]:


import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('FigureC.txt')

select= np.array([d for d in data if d[1] < 50])
data1= select.transpose()
pl.xlim([100,300])
pl.scatter(data1[0],data1[1],s = 3, color='green',alpha=1, edgecolors='none');
pl.xlabel('Time in ms')
pl.ylabel('Neuron index')
pl.title('Network simulation with v_ext/v_th = 2 & g = 5')
pl.show();

n, bins, patches = pl.hist(np.array(10*list(data1[0])), 200, normed=0, rwidth =0.3, color = 'green', alpha=0.75)
pl.xlim([100,300])
pl.xlabel('Time in ms')
pl.ylabel('Number of spikes per time step')
pl.title('Network simulation with v_ext/v_th = 2 & g = 5')
pl.show();


# In[18]:


import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('FigureD.txt')

select= np.array([d for d in data if d[1] < 50])
data1= select.transpose()
pl.xlim([100,300])
pl.scatter(data1[0],data1[1],s = 3, color='purple',alpha=0.75, edgecolors='none');
pl.xlabel('Time in ms')
pl.ylabel('Neuron index')
pl.title('Network simulation with v_ext/v_th = 0.9 & g = 4.5')
pl.show();

n, bins, patches = pl.hist(np.array(10*list(data1[0])), 200, normed=0, rwidth =0.3, color='purple', alpha=0.75)
pl.xlim([100,300])
pl.ylim([0,250])
pl.xlabel('Time in ms')
pl.ylabel('Number of spikes per time step')
pl.title('Network simulation with v_ext/v_th = 0.9 & g = 4.5')
pl.show();

