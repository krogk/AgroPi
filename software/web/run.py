#!/usr/bin/env python
# -*- coding: utf-8 -*-
from app.application import socketio, app
from flask_socketio import SocketIO, emit

# [socketio, app] = create_app('app.config')

# Handler for a message recieved over 'connect' channel
@socketio.on('connect')
def test_connect():
    emit('after_connect',  {'data':'connected!'})

socketio.run(app, host='0.0.0.0', port=5050)
