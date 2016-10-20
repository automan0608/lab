

local array = require "array_lib"

local a = array.new(10)

print(a)
print('1111') print(array.get(a, 2))
print('2222') print(array.set(a, 2, 10))
print('3333') print(array.get(a, 2))
