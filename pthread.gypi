{
  'conditions': [
    ['OS=="win"', {
      'variables': {
        'sdkdir': 'E:/pthreads-w32-2-9-1-release/Pre-built.2',
      },
      'include_dirs': [
        '<(sdkdir)/include',
      ],
      'library_dirs': [
        '<(sdkdir)/lib/x86',
      ],
      'link_settings': {
        'libraries': [
          '-lpthreadVCE2',
        ],
      },
    }],# OS!="win"
    ['OS!="win"', {
      'link_settings': {
        'libraries': [
          '-lpthread',
        ],
      },
    }],
  ],

}