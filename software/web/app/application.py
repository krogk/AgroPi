# -*- coding: utf-8 -*-
# from gevent import monkey
# monkey.patch_all()

from flask import Flask
from flask_mongoengine import MongoEngine
from flask_socketio import SocketIO, emit

# flask mongoengine
db = MongoEngine()

app = Flask(__name__)
app.config.from_object('app.config')

# flask mongoengine init
db.init_app(app)


# import blueprints
from app.auth.views import auth_bp
from app.dashboard.views import dashboard_bp
from app.control.views import control_bp
from app.observations.views import observations_bp
from app.settings.views import settings_bp
from app.measurements import measurements_bp

# register blueprints
app.register_blueprint(auth_bp)
app.register_blueprint(dashboard_bp)
app.register_blueprint(control_bp)
app.register_blueprint(observations_bp)
app.register_blueprint(settings_bp)
app.register_blueprint(measurements_bp)

socketio = SocketIO(app)
