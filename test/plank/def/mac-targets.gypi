{
	'targets': [
		{
			'conditions': [
				[ 
					'OS=="mac"', {
						'xcode_settings': {
							'OTHER_CFLAGS': [
								'-std=c++11', '-stdlib=libc++'
							],
						}#xcode-settings
					} #mac
				],
				[
					'OS=="ios"', {
						'mac_bundle': 1,
						'xcode_settings': {
							'SDKROOT': 'iphoneos',
							'TARGETED_DEVICE_FAMILY': '1,2',
							'CODE_SIGN_IDENTITY': 'iPhone Developer',
							'IPHONEOS_DEPLOYMENT_TARGET': '5.0',
							'ARCHS': '$(ARCHS_STANDARD_32_64_BIT)',
							'CLANG_CXX_LANGUAGE_STANDARD': 'gnu++11',
							'CLANG_CXX_LIBRARY': 'libc++',
							'INFOPLIST_FILE': 'test-Info.plist'
						} #xcode_settings
					} #ios
				],
			] #conditions
        }
	], #targets
}