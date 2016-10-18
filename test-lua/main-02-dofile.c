
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua5.2/lua.h>
#include <lua5.2/lauxlib.h>

#define DEFAULTFILE  "/home/zhaosheng/git/my-lab.git/test-lua/luafile/01-sortarray.lua"

int main(int argc, void *argv[])
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	
	printf("argc = %d\n", argc);
	if (argc != 2)
	{
		printf("need to specify the config name\n");
		printf("will exec the default file\n");
	}

	printf("will dofile: %s\n", argv[1] ? (char *)argv[1] : DEFAULTFILE);
	int r = luaL_dofile(L, argv[1] ? (char *)argv[1] : DEFAULTFILE);
	if (0 != r)
		lua_error(L);

	printf("r=%d\n", r);
}
