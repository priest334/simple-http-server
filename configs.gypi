{
  'configurations': {
    'Debug': {
      'defines': [
        'DEBUG',
		'_DEBUG',
		'_MBCS',
      ],
      'conditions': [
        ['OS!="win"', {
          'cflags': [
            '-g',
          ],
        }],
        ['OS=="win"', {
          'msvs_settings': {
            'VCCLCompilerTool': {
			  'Optimization': '0',
              'RuntimeLibrary': '1',
            },
            'VCLinkerTool': {
              'IgnoreDefaultLibraryNames': [
                'libcmt.lib',
              ],
            },
          },
        }],
      ],
    },
    'Release': {
      'defines': [
        'RELEASE',
		'NDEBUG',
		'_MBCS',
      ],
      'conditions': [
        ['OS!="win"', {
          'cflags': [
            '-g',
          ],
        }],
        ['OS=="win"', {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'RuntimeLibrary': '0',
            },
            'VCLinkerTool': {
              'IgnoreDefaultLibraryNames': [
                #'libcmt.lib',
              ],
            },
          },
        }],
      ],
    },
  },
}
