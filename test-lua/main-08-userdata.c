
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>

#define printf 

int luaopen_array_lib(lua_State *L);

typedef struct numarray_s
{
	int size;
	double values[0];
}numarray_t;

static int l_newarray(lua_State *L)
{
	printf("%s | 1111\n", __FUNCTION__);
	int n = luaL_checkint(L, 1);
	size_t nbytes = sizeof(numarray_t) + n * sizeof(double);

	printf("%s | 2222\n", __FUNCTION__);
	numarray_t *a = (numarray_t *)lua_newuserdata(L, nbytes);
	a->size = n;
	printf("%s | 3333\n", __FUNCTION__);

	return 1;
}

static int l_setarray(lua_State *L)
{
	printf("%s | 1111\n", __FUNCTION__);
	numarray_t *a = (numarray_t *)lua_touserdata(L, 1);
	printf("%s | 2222\n", __FUNCTION__);
	int index = luaL_checkint(L, 2);
	printf("%s | 3333\n", __FUNCTION__);
	double value = luaL_checknumber(L, 3);
	printf("%s | 4444\n", __FUNCTION__);

	luaL_argcheck(L, a != NULL, 1, "`array` expected");
	printf("%s | 5555\n", __FUNCTION__);

	luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

	printf("%s | 6666\n", __FUNCTION__);
	a->values[index - 1] = value;

	return 0;
}

static int l_getarray(lua_State *L)
{
	numarray_t *a = (numarray_t *)lua_touserdata(L, 1);
	int index = luaL_checkint(L, 2);

	luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

	lua_pushnumber(L, a->values[index - 1]);

	return 1;
}

static int l_getsize(lua_State *L)
{
	numarray_t *a = (numarray_t *)lua_touserdata(L, 1);

	luaL_argcheck(L, a != NULL, 1, "`array` expected");

	lua_pushnumber(L, a->size);
}

static const struct luaL_Reg array_lib[] = 
{
	{"new", l_newarray},
	{"set", l_setarray},
	{"get", l_getarray},
	{"size", l_getsize},
	{NULL, NULL},
};

int luaopen_array_lib(lua_State *L)
{
	luaL_openlib(L, "array", array_lib, 0);
	return 1;
}


