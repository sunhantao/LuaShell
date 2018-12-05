--
-- node.lua
--

local node = { _version = "0.1" }

local util = require("util")

function createconf(dir, options)
    dir = util.abspath(dir)
    file, err = io.open(dir, "r")
    if file then
        file:close()
        return false
    end
    return true
end

return node
