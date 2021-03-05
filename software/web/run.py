#!/usr/bin/env python
# -*- coding: utf-8 -*-
from app.application import create_app
app = create_app('app.config')
app.run(host='0.0.0.0', port=5050)
