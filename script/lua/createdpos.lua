--
-- createdpos.lua
--

local rpc = require("rpc")

while running do
    rpc.dealco()
    print("stop", rpc.asynchelp("stop"))
    print("listkey", rpc.asynchelp("listkey"))
    sleep(1000)
end
