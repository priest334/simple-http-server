{
	'targets': [
		{
			'target_name': 'net',
			'type': 'static_library',
			'msvs_guid': '4309DDE0-3365-4CAC-B70E-D547138C2F67',
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
				'socket_handle.h',
				'socket_handle.cpp',
				'socket_helper.h',
				'socket_helper.cpp',
				'socket.h',
			],
		},
	],
}