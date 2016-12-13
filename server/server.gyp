{
  'target_defaults': {
    'includes': [
      '../configs.gypi',
      '../settings.gypi',
      '../libevent.gypi',
      '../pthread.gypi',
    ],
    'include_dirs': [
      '..',
    ],
  },
  'targets': [
    {
      'target_name': 'server',
      'type': 'static_library',
      'msvs_guid': 'B88713BB-1726-4A73-9923-9F1DC4D8033F',
      'dependencies': [
        '../base/base.gyp:base',
		'../log/log.gyp:log',
      ],
      'sources': [
        'server.h',
		'http/service.h',
		'http/service.cpp',
      ],
    },
    {
      'target_name': 'http_service_test',
      'type': 'executable',
      'msvs_guid': 'CC8A7DB3-C2CD-455B-B93F-1463FF86AC1A',
      'dependencies': [
        'server',
      ],
      'sources': [
        'http/tests.cpp',
      ],
    },
  ],
}