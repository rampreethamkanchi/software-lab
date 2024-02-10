# 1. Write a program to load a .csv file as a NumPy 1-D array. Find the maximum and minimum elements in the array. Hint: For the data, use the .csv file “book1.csv”
import numpy as np
# read a csv file into numpy 1-D array using genfromtxt
data = np.genfromtxt('book1.csv', delimiter='\t', skip_header=1, usecols=1, dtype=int)
# find the maximum and minimum elements in the array
max_element = np.max(data)
min_element = np.min(data)
print('Maximum element of book1.csv:', max_element)
print('Minimum element of book1.csv:', min_element)

#2. For the Numpy 1-D array as obtained in Q.1, sort the elements in ascending order.
# sort the elements in ascending order
sorted_data = np.sort(data)

#3. For the sorted Numpy 1-D array as obtained in Q.2, reverse the array and print the reversed array.
# reverse the array and print the reversed array
reversed_data = sorted_data[::-1]
print('Reversed array of book1.csv:', reversed_data)

#4. Write a program to load three .csv files (Book1.csv, Book2.csv, and Book3.csv) as a list of Numpy 1-D arrays. Print the means of all arrays as a list.
# read three csv files into a list of numpy 1-D arrays using genfromtxt
data1 = np.genfromtxt('book1.csv', delimiter='\t', skip_header=1, usecols=1, dtype=int)
data2 = np.genfromtxt('book2.csv', delimiter='\t', skip_header=1, usecols=1, dtype=int)
data3 = np.genfromtxt('book3.csv', delimiter='\t', skip_header=1, usecols=1, dtype=int)
data_list = [data1, data2, data3]

mean_list = []
for data in data_list:
    mean = np.mean(data)
    mean_list.append(mean)

print('Mean of all arrays in order:', mean_list)