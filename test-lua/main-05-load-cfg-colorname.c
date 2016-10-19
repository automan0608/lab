
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua5.2/lua.h>
#include <lua5.2/lauxlib.h>

struct color_s {
	char *name;
	int red, green, blue;
} colortable[] = {
	{"BLACK", 255, 255, 255},
	{"RED", 255, 0, 0},
	{"GREEN", 0, 255, 0},
	{"BLUE", 0, 0, 255}, 
	{"WHITE", 0, 0, 0}
};

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
	int red, green, blue;

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

	if (lua_isstring(L, -1))
	{
		printf("get background from lua script is a string\n");

		const char *name = luaL_checkstring(L, -1);
		int i = 0;
		int tablesize = sizeof(colortable) / sizeof(struct color_s);
		for (i = 0; i < tablesize; i++)
		{
			if (!strcmp(colortable[i].name, name))
				break;
		}

		if (i < tablesize)
		{
			red = colortable[i].red;
			green = colortable[i].green;
			blue = colortable[i].blue;
		}
		else
		{
			red = -1;
			green = -1;
			blue = -1;
		}
	}
	else
	{
		printf("get background from lua script is a table\n");

		red   = getfield(L, "r");
		green = getfield(L, "g");
		blue  = getfield(L, "b");
	}

	printf("r=%d, g=%d, b=%d\n", red, green, blue);
}
