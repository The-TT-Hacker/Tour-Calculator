cmd_Release/obj.target/tourcalculator.node := g++ -shared -pthread -rdynamic -m64  -Wl,-soname=tourcalculator.node -o Release/obj.target/tourcalculator.node -Wl,--start-group Release/obj.target/tourcalculator/src/tourcalculatoraddon.o Release/obj.target/tourcalculator/src/tourcalculator.o Release/obj.target/tourcalculator/src/tournament.o Release/obj.target/tourcalculator/src/graph.o -Wl,--end-group 
