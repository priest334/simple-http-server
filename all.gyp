# Copyright (c) 2011 The TQ Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

{
  'targets': [
    {
      'target_name': 'all',
      'type': 'none',
      'msvs_guid': '95AB4EAA-0442-4F94-A6E2-4D985003532C',
      'includes': [
        'configs.gypi',
        'settings.gypi',
      ],
      'dependencies': [
        'server/server.gyp:*',
		'net/net.gyp:*',
		'log/log.gyp:*',
      ],
    },
  ],
}
