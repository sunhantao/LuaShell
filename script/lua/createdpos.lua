--
-- createdpos.lua
--

local rpc = require("rpc")

function f()
  for i = 1, 5 do
      sendno, senderr = rpc.help("stop")
      -- print("stop", coroutine.running(), sendno)
  end
end

if running then
  for i = 1, 20 do
    rpc.asycstart(f)
  end
  print("wait", rpcasyncwait(1000))
end
