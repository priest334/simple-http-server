{
	'targets': [
		{
			'target_name': 'log',
			'type': 'static_library',
			'msvs_guid': '3EC5AAD7-20AA-45E1-89C1-4EA1E807F659',
			'defines': [
				#'USE_POSIX_PTHREAD',
			],
			'includes': [
				'../configs.gypi',
				'../settings.gypi',
			],
			'include_dirs': [
				'..',
			],
			'sources': [
				'severity.h',
				'severity.cpp',
				'service.h',
				'service.cpp',
				'writer.h',
				'writer.cpp',
				'logging.h',
				'logging.cpp',
				'file_writer.h',
				'file_writer.cpp',
				'message.h',
				'message.cpp',
				'log.h',
				'log.cpp',
			],
		},
	],
}