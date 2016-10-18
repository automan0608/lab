
local a = {}

local i = 1

math.randomseed(os.time(NULL))

for i=1, 4, 1
do
	a[i] = math.random(1, 100)
	print(a[i])
end

print('after sort')
table.sort(a)

for k, v in ipairs(a)
do
	print(k .. ': ' .. v)
end
