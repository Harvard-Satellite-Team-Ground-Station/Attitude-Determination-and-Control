import serial
import matplotlib.pyplot as plt

plt.ion()
fig = plt.figure()

i = 0
time = list()
values = list()
y = list()
ser = serial.Serial('COM5', 9600)

ser.close()
ser.open()

while True:
    data = ser.readline()
    msg = data.decode()
    x = msg.split("/")
    placeholder = 2000
    location = 0
    
    values = list()
    avg = list()
    for channel in x:
        if channel.startswith('Channel_'):
            stuff = channel.split("_")
            print(stuff)
            values.append(int(stuff[2]))
    avg.append((values[4] + values[5])/2) # left -90 deg
    avg.append((values[2] + values[3])/2) # middle 0 deg
    avg.append((values[0] + values[1])/2) # right 90 deg
    
    # starting between 0 and 90
    angle =((-1)*(1023-avg[0]) + (1023-avg[2])) / 1023 * 90
    y.append(angle)
    time.append(i)
    print(y)
    plt.plot(time[-20:],y[-20:])
    
    i += 1
    plt.show()
    plt.pause(0.0001)