pin = 3

uart.setup(0,9600,8,0,1)

function position_changed(value)
  print("The position is now"..value)
  post(value)
end

function post(value)
    connout = nil
    connout = net.createConnection(net.TCP, 0)
 
    connout:on("receive", function(connout, payloadout)
        connout:close();
    end)
 
    connout:on("connection", function(connout, payloadout)
        local postval = "POST /api/orientation/"..value.." HTTP/1.1\r\nHost: arcane-stream-18695.herokuapp.com\r\nAccept: */*\r\n\r\n"
        print (postval);
 
        connout:send(postval)
    end)
 
    connout:on("disconnection", function(connout, payloadout)
        print("Connection closed");
        connout:close();
        collectgarbage();
    end)
 
    connout:connect(80,'http://arcane-stream-18695.herokuapp.com')
end

SSID = "VM218344-2G"
PWD  = "uznydbwt"
wifi.setmode(wifi.STATION)
wifi.sta.config(SSID, PWD)
gpio.mode(4,gpio.OUTPUT)

tmr.alarm(0,1000, 1, function() 
  if wifi.sta.getip()==nil then
    print("connecting to AP...")
    gpio.write(4,gpio.HIGH)
  else
    print('ip: ',wifi.sta.getip())
    tmr.stop(0)
    gpio.write(4,gpio.LOW)
    tmr.delay(1000000) 
    gpio.write(4,gpio.HIGH)
    print("Connected to WIFI")
    tmr.delay(1000000) 
  end
end)
