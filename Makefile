OBJS = $(wildcard code/*.cpp)
OBJ_NAME = main.exe 
COMPILER_FLAGS = -std=c++17 
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
INCLUDE_DIR = -IC:\Users\HP\Desktop\BTL\SDL2-2.26.5\i686-w64-mingw32\include\SDL2 -IC:\Users\HP\Desktop\BTL\SDL2_image-2.6.3\i686-w64-mingw32\include\SDL2 -IC:\Users\HP\Desktop\BTL\SDL2_ttf-2.20.2\i686-w64-mingw32\include\SDL2 -IC:\Users\HP\Desktop\BTL\SDL2_mixer-2.6.3\i686-w64-mingw32\include\SDL2
LIB_DIR = -LC:\Users\HP\Desktop\BTL\SDL2-2.26.5\i686-w64-mingw32\lib -LC:\Users\HP\Desktop\BTL\SDL2_image-2.6.3\i686-w64-mingw32\lib -LC:\Users\HP\Desktop\BTL\SDL2_ttf-2.20.2\i686-w64-mingw32\lib -LC:\Users\HP\Desktop\BTL\SDL2_mixer-2.6.3\i686-w64-mingw32\lib
// thay địa chỉ của include với lib sao cho phù hợp với máy tính của bạn

compile:
	g++ $(COMPILER_FLAGS) $(INCLUDE_DIR) $(LIB_DIR) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
