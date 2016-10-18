
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua5.2/lua.h>
#include <lua5.2/lauxlib.h>

int getfield(lua_State *L, const char *key)
{
	printf("in get filed\n");
	int r = 0;
	lua_pushstring(L, key);
	lua_gettable(L, -2);

	r = luaL_checknumber(L, -1);

	lua_pop(L, 1);

	return r;
}

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
		lua_error(L);
//		error(L);

	printf("dofile r=%d\n", r);

	lua_getglobal(L, "background");

	int red   = getfield(L, "r");
	int green = getfield(L, "g");
	int blue  = getfield(L, "b");

	printf("r=%d, g=%d, b=%d\n", red, green, blue);
}
