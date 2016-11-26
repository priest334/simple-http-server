{
  'conditions': [
    ['OS=="win"', {
      'variables': {
        'sdkdir': 'E:/OpenSources/libevent',
      },
      'include_dirs': [
        '<(sdkdir)/include',
      ],
      'library_dirs': [
        '<(sdkdir)',
      ],
      'link_settings': {
        'libraries': [
          '-lAdvapi32',
		  '-llibevent',
        ]
      },
    }],# OS!="win"
    ['OS!="win"', {
      'link_settings': {
		'libraries': [
			'-levent',
		],
	  },
    }],
  ],
}