{
	'target_defaults': {
		'cflags': [ '-std=c++11' ],
		'ldflags': [ '-pthread' ],
	},
	'make_global_settings': [
  		['CC', '/usr/bin/g++'],
  		['CXX', '/usr/bin/g++'],
	],
}