{
  'conditions': [
    ['OS=="win"', {
      'defines': [
        'WIN32',
		'_MBCS',
      ],
      'msvs_settings': {
        'VCCLCompilerTool': {
          'ExceptionHandling': '1',
        },
        'VCLinkerTool': {
          'GenerateDebugInformation': 'true',
          'LinkIncremental': '1',
          'LinkLibraryDependencies': 'true',
          'SubSystem': '1',
		  'AdditionalDependencies': [
			'%(AdditionalDependencies)',
		  ],
        },
      },
	  'msvs_disabled_warnings': [
	    '4503',
	  ],
    }],# OS!="win"
    ['OS!="win"', {
      
    }],
  ],
}