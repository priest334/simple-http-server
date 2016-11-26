{
  'configurations': {
    'Debug': {
      'defines': [
        'DEBUG',
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
                'libcmt.lib',
              ],
            },
          },
        }],
      ],
    },
  },
}
