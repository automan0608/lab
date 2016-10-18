
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua5.2/lua.h>
#include <lua5.2/lauxlib.h>

int main(int argc, void *argv[])
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	
	printf("argc = %d\n", argc);
	if (argc != 2)
	{
		printf("need to specify the config name\n");
		exit(1);
	}

	printf("will loadcfg: %s\n", (char *)argv[1]);
	int r = luaL_dofile(L, (char *)argv[1]);
	if (0 != r)
//		lua_error(L);
		error(L);

	printf("dofile r=%d\n", r);

	lua_getglobal(L, "width");
	lua_getglobal(L, "height");

	if (!lua_isnumber(L, -2))
		error(L, "'width' should be a number\n");
	if (!lua_isnumber(L, -1))
		error(L, "'height' should be a number\n");

	int width = luaL_checknumber(L, -2);
	int height = luaL_checknumber(L, -1);

	printf("width=%d, height=%d\n", width, height);
}
