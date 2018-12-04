--
-- util.lua
--

local util = { _version = "0.1" }

function util.abspath(path)
    local handle = io.popen('echo "`dirname '..dir..'`/`basename '..dir..'`"')
    path = handle:read("a")
    handle:close()
    return path
end

return uti