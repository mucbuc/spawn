{
	'includes':[
		'../spawn.gypi',
		'plank/def/mac-targets.gypi',
		'plank/def/plank.gypi'
	],#includes
	'target_defaults': {
		'target_name': 'test', 
		'type': 'executable',
		'sources': [
			'../test/src/main.cpp'
		], #sources
		'include_dirs': [
			'plank/src/',
			'../test/'
		], #include_dirs		
	}, #target_defaults
}