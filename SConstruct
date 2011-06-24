import config
#ORX_INCLUDE = '/home/sebastian/projects/orx-1.3rc0/dev-linux/include'
#ORX_LIBPATH = '/home/sebastian/projects/orx-1.3rc0/dev-linux/lib'

env = Environment(
	CPPPATH=[config.ORX_INCLUDE],
	LIBS=['orxd'],
	LIBPATH=[config.ORX_LIBPATH]
)
env.Program('bin/MagnetoPong', Glob('src/*.cpp'))
