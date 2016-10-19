
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua5.2/lua.h>
#include <lua5.2/lauxlib.h>

int main(int argc, void *argv[])
{
	int x = 5, y = 6, result = 0;

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	
	printf("argc = %d\n", argc);
	if (argc != 2)
	{
		printf("need to specify the lua script name\n");
		exit(1);
	}

	printf("will loadcfg: %s\n", (char *)argv[1]);
	int r = luaL_dofile(L, (char *)argv[1]);
	if (0 != r)
//		lua_error(L);
		error(L);

	lua_getglobal(L, "func");

	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	if (0 != lua_pcall(L, 2, 1, 0))
		lua_error(L);

	result = lua_gettop(L); printf("stacktop is %d\n", result);

	result = luaL_checknumber(L, -1); printf("result=%d\n", result);

	result = lua_gettop(L); printf("stacktop is %d\n", result);
}
