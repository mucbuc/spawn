{	
	'includes':[
		'mac-targets.gypi'
	],
    'target_defaults': {
    	'default_configuration': 'Test',
		'configurations':{
	       	'Release': {
	         	'defines': [
	           		'NDEBUG',
	        	],
	       	},
	       	'Debug': {
	       	},
	       	'Test': {
	       		'defines': [
	       			'TARGET_TEST=1'
	       		],
	       	}	
	    },
        'sources': [
			'../src/assert.cpp',
			'../src/assert.h',
			'../src/assert.hxx',
			'../src/test.h',
        ]
    }
}