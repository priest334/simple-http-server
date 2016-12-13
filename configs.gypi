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
              'RuntimeLibrary': '1',
            },
            'VCLinkerTool': {
              'IgnoreDefaultLibraryNames': [
                #'libcmtd.lib',
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
