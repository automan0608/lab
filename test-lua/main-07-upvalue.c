
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua5.2/lua.h>
#include <lua5.2/lauxlib.h>

static int counter(lua_State *L)
{
	printf("111\n");
	double val = lua_tonumber(L, lua_upvalueindex(1));

	printf("222\n");
	lua_pushnumber(L, ++val);
	printf("333\n");
	lua_pushvalue(L, -1);
	printf("444\n");

	lua_replace(L, lua_upvalueindex(1));

	printf("555\n");
	printf("%s | val = %lf\n", __FUNCTION__, val);

	return 1;
}

int newCount(lua_State *L)
{
	lua_pushnumber(L, 0);
	lua_pushcclosure(L, &counter, 1);

	return 1;
}

int main()
{
	lua_State *L = luaL_newstate();
	
	int result = newCount(L);

	printf("%s | ", __FUNCTION__);
	counter(L);

	printf("%s | ", __FUNCTION__);
	counter(L);

	printf("%s | ", __FUNCTION__);
	counter(L);

	printf("%s | ", __FUNCTION__);
	counter(L);

}
