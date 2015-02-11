{
	'includes':[
		'../../def/main.gypi',
	],#inclues
	'target_defaults': {
		'target_name': 'test',
		'type': 'executable',
		'sources': [
			'../src/other.cpp',
		], #sources
		'include_dirs': [
			'../../../src/'
		], #include_dirs		
	}, #target_defaults
}