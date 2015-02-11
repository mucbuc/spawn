{
	'includes':[
		'../../def/main.gypi',
	],#inclues
	'target_defaults': {
		'target_name': 'test2',
		'type': 'executable',
		'sources': [
			'../src/main.cpp',
		], #sources
		'include_dirs': [
			'../../../src/'
		], #include_dirs		
	}, #target_defaults
}