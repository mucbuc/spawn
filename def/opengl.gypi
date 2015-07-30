{
	'target_defaults': {
		'conditions': [
			[ 
				'OS=="mac"', {
					'link_settings': {
				        'libraries': [
				            'AppKit.framework',
				            'Foundation.framework',
				            'OpenGL.framework',
				            'QuartzCore.framework',
				        ]
				    }
				}
			]
		]
	}
}