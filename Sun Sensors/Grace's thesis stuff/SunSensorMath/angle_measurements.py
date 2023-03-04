import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import math 

def  readfile(filename):
    with open(filename) as f:
        lines = f.readlines()
    column_names =[]
    column_names.append(0)
    arr = []
    temp_list = []
    for line in lines:
        temp = line.strip().split(" ")
        if temp[2].startswith("%"):
            if (column_names[-1] == float(temp[3])):
                print("same")
            else:
                column_names.append(float(temp[3]))
                arr.append(temp_list)
                temp_list = []
        elif temp[2].startswith("Angle"):
            temp_list.append(float(temp[3]))

    arr.append(temp_list)
    return arr, column_names


x_axis = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
angles_10mm, column_names = readfile('Sun_Sensor_Test_Data//angle_measurements_tests//angle_10mm.txt')

print((angles_10mm))
df1 = pd.DataFrame(np.array(angles_10mm).T.tolist(), columns=column_names)
df1 = df1[[ -30.0, -20.0 , -10.0, 0.0,  5.0,  10.0, 15.0,  20.0, 25.0, 30.0,  35.0, 40.0,  45.0,  50.0, 51.0, 52.0, 53.0, 54.0, 55.0,  55.0,  56.0, 57.0, 58.0,  59.0, 60.0,  61.0, 62.0 ]]

df1.to_csv('Sun_Sensor_Test_Data//angle_measurements_tests//out.csv')  

df1_Transpose = df1.T
df1_Transpose['mean'] = df1_Transpose.mean(axis=1)
df1_Transpose['std']  = df1_Transpose.std(axis = 1)

print(df1_Transpose)

# df7 = pd.DataFrame(all).T 

# x = np.array(df7.max(axis=1)) 
    
plt.title('Calibration of Photodiodes - No Case')
plt.xlabel('Photodiode Number')
plt.ylabel('Intensity of Photodiode')
df1_Transpose.plot.bar(y="mean", yerr = df1_Transpose["std"])
# plt.xticks(x_axis)
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

