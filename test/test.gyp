{
	'includes':[
		'../spawn.gypi',
	],#includes
	'target_defaults': {
		'target_name': 'test', 
		'type': 'executable',
		'sources': [
			'../test/src/main.cpp'
		], #sources
		'include_dirs': [
			'../test/'
		], #include_dirs		
	}, #target_defaults
}