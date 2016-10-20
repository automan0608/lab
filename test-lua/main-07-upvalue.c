
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua5.2/lua.h>
#include <lua5.2/lauxlib.h>

static int l_counter(lua_State *L)
{
	printf("%s | 1111\n", __FUNCTION__);
//	double val = lua_tonumber(L, lua_upvalueindex(1));
	double val = luaL_checknumber(L, lua_upvalueindex(1));

	printf("%s | 2222\n", __FUNCTION__);
	lua_pushnumber(L, ++val);
	printf("%s | 3333\n", __FUNCTION__);
	lua_pushvalue(L, -1);
	printf("%s | 4444\n", __FUNCTION__);

	lua_replace(L, lua_upvalueindex(1));

	printf("%s | 5555\n", __FUNCTION__);
	printf("%s | val = %lf\n", __FUNCTION__, val);

	return 1;
}

static int l_newCounter(lua_State *L)
{
	printf("%s | 1111\n", __FUNCTION__);
	lua_pushnumber(L, 0);
	printf("%s | 2222\n", __FUNCTION__);
	lua_pushcclosure(L, &l_counter, 1);
	printf("%s | 3333\n", __FUNCTION__);

	return 1;
}

static const struct luaL_Reg counter_lib[] = 
{
	{"new", l_newCounter},
	{"get", l_counter},
	{NULL, NULL},
};

int luaopen_counter_lib(lua_State *L)
{
	luaL_openlib(L, "counter", counter_lib, 0);
	return 1;
}

