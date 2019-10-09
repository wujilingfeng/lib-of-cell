cc=g++
CFLAGS=-g -Wall
CUR_DIR=$(shell pwd)
INCLUDE_DIR=$(CUR_DIR)/../include
ADD_INCLUDE=-I ./ -I /Users/libo/Documents/conformal-map/eigen/Eigen #须设置
TEMP_DIR=$(CUR_DIR)/../temp
#vpath %.o $(CUR_DIR)/temp
#vpath %.a $(CUR_DIR)/lib
vpath %.h $(CUR_DIR)/../include
#VPATH = $(CUR_DIR):$(CUR_DIR)/src
cfiles=$(wildcard *.c)
cppfiles=$(wildcard *.cpp)
cppobjects=$(patsubst %.cpp,%.o,$(cppfiles))

cobjects=$(patsubst %.c,%.o,$(cfiles))
all : $(cppobjects) $(cobjects)
$(cppobjects) : %.o:%.cpp
	$(cc) -c -I $(INCLUDE_DIR) $(ADD_INCLUDE) $(CFLAGS) $< -o $(TEMP_DIR)/$@
$(cobjects) : %.o:%.c
	$(cc) -c -I $(INCLUDE_DIR) $(ADD_INCLUDE) $(CFLAGS) $< -o $(TEMP_DIR)/$@

#$(objects): t1.cpp t2.cpp
#echo $^&& echo $@
#$(objects) : $(wildcard *.cpp)
#$(cc) -c -I $(INCLUDE_DIR) $(CFLAGS) $< -o $(patsubst %.cpp,%.o,$<)&&echo $^&&echo $(objects)
