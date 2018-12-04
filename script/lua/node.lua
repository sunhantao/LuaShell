--
-- node.lua
--

args = {...}
print(#args)
os.execute("sleep 3")

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
