include Makefile.include

EXE_NAME=main
OBJS=main.o MafiaMember.o MafiaMembersManager.o

#
# Targets
#

all: $(EXE_NAME) $(OBJS)

$(EXE_NAME): $(OBJS)
	$(CC) $(CCFLAGS) -o $(EXE_NAME) $(OBJS)

MafiaMember.o: MafiaMember.cpp MafiaMember.h
	$(CC) $(CCFLAGS) $(INCLUDE_PATH) -c MafiaMember.cpp -o MafiaMember$(OBJ_EXTENSION)

MafiaMembersManager.o: MafiaMembersManager.h MafiaMembersManager.cpp MafiaMember.cpp MafiaMember.h
	$(CC) $(CCFLAGS) $(INCLUDE_PATH) -c MafiaMembersManager.cpp -o MafiaMembersManager$(OBJ_EXTENSION)

main.o: main.cpp $(INCLUDE_DIR)/BinaryTreeNode.h $(INCLUDE_DIR)/BinaryTreeUtils.h
	$(CC) $(CCFLAGS) $(INCLUDE_PATH) -c main.cpp -o main$(OBJ_EXTENSION)

clean:
	$(DELETE_CMD) $(OBJS) $(EXE_NAME)
