import serial
import matplotlib.pyplot as plt

plt.ion()
fig = plt.figure()

i = 0
time = list()
values = list()
y = list()
ser = serial.Serial('COM7', 9600)

ser.close()
ser.open()

while True:
    data = ser.readline()
    msg = data.decode()
    x = msg.split("/")
    placeholder = 2000
    location = 0
    for channel in x:
        if channel.startswith('Channel_'):
            stuff = channel.split("_")
            print(stuff)
            if placeholder > int(stuff[2]):
                location = int(stuff[1])
                placeholder = int(stuff[2])
            # values.append(stuff[2])
    if placeholder == 1023:
        y.append(90)
    else:
        y.append((location+1)*11.25-5.625)
    time.append(i)
    print(y)
    plt.plot(time[-20:],y[-20:])
    
    i += 1
    plt.show()
    plt.pause(0.0001)