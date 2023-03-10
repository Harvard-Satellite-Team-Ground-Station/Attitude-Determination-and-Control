import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import math 

def  readfile(filename):
    with open(filename) as f:
        lines = f.readlines()

    arr = []
    for line in lines:
        
        temp = line.split(" ")
        if temp[2].startswith("%"):
            temp_list = []
        elif temp[2].startswith("Full"):
            if not(bool(temp_list)):
                arr.append(temp_list)
        else:
            temp_list.append(float(temp[2]))
        
    return arr

def  readfiles(filenames):
    arr = []
    for filename in filenames:
        
        with open(filename) as f:
            lines = f.readlines()

        
        for line in lines:
            
            temp = line.split(" ")
            if temp[2].startswith("%"):
                temp_list = []
            elif temp[2].startswith("Full"):
                if not(bool(temp_list)):
                    arr.append(temp_list)
            else:
                temp_list.append(float(temp[2]))
        
    return arr


x_axis = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
cali_1 = readfile('Sun_Sensor_Test_Data//cali_1.txt')
cali_2 = readfile('Sun_Sensor_Test_Data//cali_2.txt')
cali_3 = readfile('Sun_Sensor_Test_Data//cali_3.txt')
cali_4 = readfile('Sun_Sensor_Test_Data//cali_4.txt')
cali_5 = readfile('Sun_Sensor_Test_Data//cali_5.txt')
cali_6 = readfile('Sun_Sensor_Test_Data//cali_6.txt')
all = readfiles(['Sun_Sensor_Test_Data//cali_1.txt','Sun_Sensor_Test_Data//cali_2.txt','Sun_Sensor_Test_Data//cali_3.txt','Sun_Sensor_Test_Data//cali_4.txt','Sun_Sensor_Test_Data//cali_5.txt','Sun_Sensor_Test_Data//cali_6.txt'])

df1 = pd.DataFrame(cali_1).T 
df1['mean'] = df1.mean(axis=1)
df2 = pd.DataFrame(cali_2).T 
df2['mean'] = df2.mean(axis=1)
df3 = pd.DataFrame(cali_3).T 
df3['mean'] = df3.mean(axis=1)
df4 = pd.DataFrame(cali_4).T 
df4['mean'] = df4.mean(axis=1)
df5 = pd.DataFrame(cali_5).T 
df5['mean'] = df5.mean(axis=1)
df6 = pd.DataFrame(cali_6).T 
df6['mean'] = df6.mean(axis=1)


df7 = pd.DataFrame(all).T 

x = np.array(df7.max(axis=1)) 
        

for cali in cali_1:
    plt.plot(x_axis, cali, color = "blue", alpha = 0.5, linewidth = 0.3 )
    
for cali in cali_2:
    plt.plot(x_axis, cali, color = "g", alpha = 0.5, linewidth = 0.3 )

for cali in cali_3:
    plt.plot(x_axis, cali, color = "r", alpha = 0.5, linewidth = 0.3 )
    
for cali in cali_4:
    plt.plot(x_axis, cali, color = "c", alpha = 0.5, linewidth = 0.3 )

for cali in cali_5:
    plt.plot(x_axis, cali, color = "m", alpha = 0.5, linewidth = 0.3 )
    
for cali in cali_6:
    plt.plot(x_axis, cali, color = "k", alpha = 0.5, linewidth = 0.3 )
plt.title('Calibration of Photodiodes - No Case')
plt.xlabel('Photodiode Number')
plt.ylabel('Intensity of Photodiode')
plt.bar(x_axis,x, alpha = 0.3)
plt.xticks(x_axis)
plt.show()


plt.plot(x_axis,df1["mean"],label = "Light on leftmost side")
plt.plot(x_axis,df2["mean"],label = "Light on left side")
plt.plot(x_axis,df3["mean"],label = "Light on center left side")
plt.plot(x_axis,df4["mean"],label = "Light on center right side")
plt.plot(x_axis,df5["mean"],label = "Light on right side")
plt.plot(x_axis,df6["mean"],label = "Light on rightmost side")
plt.title('Calibration of Photodiodes - No Case')
plt.xlabel('Photodiode Number')
plt.ylabel('Intensity of Photodiode')
plt.xticks(x_axis)
plt.legend()
plt.show()

#x = x - 750
print(x)
plt.bar(x_axis,x, alpha = 0.5)
low = min(x)
high = max(x)
plt.ylim([math.ceil(low-0.5*(high-low)), math.ceil(high+0.5*(high-low))])
plt.title('Calibration of Photodiodes - No Case')
plt.xlabel('Photodiode Number')
plt.ylabel('Intensity of Photodiode (Zoomed in)')
#plt.ylabel('Intensity of Photodiode (minus 750, normalize)')
plt.show()

