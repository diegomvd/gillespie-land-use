import glob, os, sys
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.style as style
import seaborn as sns
import pandas as pd
from collections import OrderedDict
# from scipy.interpolate import splprep, splev
from scipy.signal import savgol_filter
from scipy import interpolate


def dfStringToList(string_):
    string_ = string_.replace(',','","')
    string_ = string_.replace('[','["')
    string_ = string_.replace(']','"]')
    return string_

# path for the data files
path = "/home/karpouzi/Research/Eukaryote-mountdir/experiment4-010521.csv"

sns.set_context("paper")


samplingData = pd.read_csv(path, sep=",", header=0)

# convert strings to lists in the needed columns
samplingData["N"] = samplingData["N"].apply(dfStringToList)
samplingData["N"] = samplingData["N"].apply(eval)
samplingData["P"] = samplingData["P"].apply(dfStringToList)
samplingData["P"] = samplingData["P"].apply(eval)
samplingData["nMax"] = samplingData["nMax"].apply(dfStringToList)
samplingData["nMax"] = samplingData["nMax"].apply(eval)
samplingData["nMin"] = samplingData["nMin"].apply(dfStringToList)
samplingData["nMin"] = samplingData["nMin"].apply(eval)
samplingData["pMax"] = samplingData["pMax"].apply(dfStringToList)
samplingData["pMax"] = samplingData["pMax"].apply(eval)
samplingData["pMin"] = samplingData["pMin"].apply(dfStringToList)
samplingData["pMin"] = samplingData["pMin"].apply(eval)
samplingData["maxSize"] = samplingData["maxSize"].apply(dfStringToList)
samplingData["maxSize"] = samplingData["maxSize"].apply(eval)
samplingData["nFrag"] = samplingData["nFrag"].apply(dfStringToList)
samplingData["nFrag"] = samplingData["nFrag"].apply(eval)
samplingData["meanSize"] = samplingData["meanSize"].apply(dfStringToList)
samplingData["meanSize"] = samplingData["meanSize"].apply(eval)
samplingData["stdSize"] = samplingData["stdSize"].apply(dfStringToList)
samplingData["stdSize"] = samplingData["stdSize"].apply(eval)

# explode list columns
samplingData=samplingData.apply(pd.Series.explode)

# change str to double
samplingData["N"] = samplingData["N"].astype('float')
samplingData["P"] = samplingData["P"].astype('float')

print(samplingData)
# select the points where irreversible collapses happened
df = samplingData.loc[(samplingData["P"]<10.0) & (samplingData["N"]<0.01)]

# for each couple (a,w) select the largest possible a0 value
aList=df['a'].unique()
wList=df['w'].unique()
a0Mat=np.zeros((len(aList)*len(wList),3))

ix=0
for a in aList:
    for w in wList:
        df1 = df.loc[(df['a']==a) & (df['w']==w)]
        a0 = df1['a0'].min()
        a0Mat[ix,0]=float(w)
        a0Mat[ix,1]=float(a)
        a0Mat[ix,2]=1-a0
        ix = ix+1

dfA0 = pd.DataFrame(data=a0Mat, index=None, columns=['w','a','a0'])
dfA0 = dfA0.pivot("a", "w", "a0")
fig, axs = plt.subplots(nrows=1, ncols=1, figsize=(6,5))
# sns.scatterplot(x=a0Mat[:,0],y=a0Mat[:,1],hue=a0Mat[:,2],ax=axs)
cmap1 = sns.color_palette("rocket", as_cmap=True)
cmap2 = sns.color_palette("Reds", as_cmap=True)
sns.heatmap(data=dfA0,cmap=cmap2,cbar_kws={'label': 'Minimum fraction of natural land \n to avoid irreversible collapse'},ax=axs)
# sns.heatmap(data=dfA0,center=0.05,cmap=cmap1,ax=axs)
axs.set_xlabel('Agricultural clustering')
axs.set_ylabel('Preference for intensification')
axs.invert_yaxis()
axs.axvline(4.5,linewidth=1,linestyle='-',color='k', alpha=0.8)
axs.axhline(5.0,linewidth=1,linestyle='-',color='k', alpha=0.8)
axs.annotate('   Land \n sparing',xy=(5.75,7.25),size=14)
axs.annotate('   Land \n sharing',xy=(1.0,2.5),size=14)

plt.tight_layout()
plt.savefig('Figure4-sharing-sparing.pdf', format='pdf', dpi = 600, bbox_inches='tight')

plt.show()
