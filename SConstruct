#import "config.py"
ORX_INCLUDE = '/home/sebastian/projects/orx-1.3rc0/dev-linux/include'
ORX_LIBPATH = '/home/sebastian/projects/orx-1.3rc0/dev-linux/lib'

env = Environment(
	CPPPATH=[ORX_INCLUDE],
	LIBS=['orxd'],
	LIBPATH=[ORX_LIBPATH]
)
env.Program('bin/MagnetoPong', Glob('src/*.cpp'))
