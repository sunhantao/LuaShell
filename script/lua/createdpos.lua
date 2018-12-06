--
-- createdpos.lua
--

local rpc = require("rpc")


function f()
  for i = 1, 9 do
    print("f")
      sendno, senderr = rpc.asynchelp("stop")
      print("stop", coroutine.running(), sendno)
  end
end

function g()
    for i = 1, 9 do
    print("g")
        sendno, senderr = rpc.asynchelp("listkey")
        print("listkey", coroutine.running(), sendno)
    end
end

rpc.asycstart(f)
rpc.asycstart(g)
if running then
    print("123")
    print(rpcasyncwait(1000))
    sleep(1000)
end
