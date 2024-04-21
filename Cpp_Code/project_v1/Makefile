INCLUDES:=./  ./include
SRCS:=$(wildcard *.cc) 
LIBS:=  -lwfrest -lworkflow -lssl -lcrypto
OBJS:=$(patsubst %.cc, %.o, $(SRCS))
SERVER:= CloudiskServer.out

# 目标 : 依赖
$(SERVER): main.o CloudiskServer.o Token.o Hash.o
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g -std=c++11

%.o:%.cc
	g++ -c $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g -std=c++11

HASH:=testHash
TOKEN:=testToken

$(HASH): Hash.o testHash.o
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

$(TOKEN): Token.o testToken.o
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

echo:
	echo $(INCLUDES)
	echo $(SRCS)

clean:
	rm -rf $(OBJS) $(SERVER) $(HASH) $(TOKEN)
