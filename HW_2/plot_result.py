import numpy as np
from matplotlib import pyplot as plt
import os
os.chdir(r'C:\Users\Kungtacheng\Desktop\program\C++\DS_and_Graph_theory\HW_2')
data = open('data.txt', 'r')
data_size = []
insertion_time = []
selection_time = []
quick_time = []
merge_time = []
heap_time = []
for line in data.readlines():
    print(line)
    arr = line.split('\t')
    print(arr)
    data_size.append(arr[0])
    insertion_time.append(arr[1])
    selection_time.append(arr[2])
    quick_time.append(arr[3])
    merge_time.append(arr[4])
    heap_time.append(arr[5])
plt.plot(data_size, insertion_time)
plt.plot(data_size, selection_time)
plt.plot(data_size, quick_time)
plt.plot(data_size, merge_time)
plt.plot(data_size, heap_time)
plt.grid()
plt.show()