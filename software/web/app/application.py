# -*- coding: utf-8 -*-
# from gevent import monkey
# monkey.patch_all()

from flask import Flask
from flask_mongoengine import MongoEngine
from flask_mail import Mail

# flask mongoengine
db = MongoEngine()

# flask mail
mail = Mail()


# application factory, see: http://flask.pocoo.org/docs/patterns/appfactories/
def create_app(config_filename):
    app = Flask(__name__)
    app.config.from_object(config_filename)

    # flask mongoengine init
    db.init_app(app)

    # flask mail init
    mail.init_app(app)

    # import blueprints
    from app.auth.views import auth_bp
    from app.dashboard.views import dashboard_bp
    from app.control.views import control_bp
    from app.observations.views import observations_bp
    from app.settings.views import settings_bp

    # register blueprints
    app.register_blueprint(auth_bp)
    app.register_blueprint(dashboard_bp)
    app.register_blueprint(control_bp)
    app.register_blueprint(observations_bp)
    app.register_blueprint(settings_bp)

    return app
