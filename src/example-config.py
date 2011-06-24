CLANLIB_INCLUDE = "/usr/include/ClanLib-2.2"
#CLANLIB_LIBPATH = "/home/sebastian/projects/orx-1.3rc0/dew-linux/lib"

def setupEnvironment(env):
	env['CPPPATH'] = CLANLIB_INCLUDE
	env['LIBS'] = 'pthread'
	env.ParseConfig("pkg-config clanCore-2.2 clanApp-2.2 clanDisplay-2.2 clanGL-2.2 --cflags --libs")


