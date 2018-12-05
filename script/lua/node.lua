--
-- node.lua
--

a, b = ...
print('hahaha')
print(a)
print(b)
print('xixixi')

for i = 1, 3 do
    print("rpcasyncalling " .. i)
    rpcasyncall(tostring(i))
    print("rpcasyncalled " .. i)
end

-- local node = { _version = "0.1" }

-- local util = require("util")

-- function create(dir, options)
--     dir = util.abspath(dir)
--     file, err = io.open(dir, "r")
--     if file then
--         file:close()
--         return false
--     end
--     return true
-- end


-- return node
