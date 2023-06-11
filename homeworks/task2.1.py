# Задача 2.1. 

# Создайте две функции maximum и minimum,
# которые получают список целых чисел в качестве входных данных 
# и возвращают наибольшее и наименьшее число в этом списке соответственно.
# Например,
# * [4,6,2,1,9,63,-134,566]         -> max = 566, min = -134
# * [-52, 56, 30, 29, -54, 0, -110] -> min = -110, max = 56
# * [42, 54, 65, 87, 0]             -> min = 0, max = 87
# * [5]                             -> min = 5, max = 5
# функции sorted, max и min использовать нельзя!


arr = [[4,6,2,1,9,63,-134,566],[-52, 56, 30, 29, -54, 0, -110],[42, 54, 65, 87, 0], [5]]

def bubble_for(data):
  for i in range(len(data)- 1):
    for j in range (len(data)-i-1):
      if data[j] > data[j+1]:
        data[j], data[j+1] = data[j+1], data[j]
  return data

def minimum(arr):

    for data in arr:
      print ("Минимальное значение из массива: ", data, bubble_for(data)[0])
   

def maximum(arr):
    
    for data in arr:
      print ("Максимальное значение из массива: ", data, bubble_for(data)[len(data) - 1])
    