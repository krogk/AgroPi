# -*- coding: utf-8 -*-
import json
from flask import render_template, session, g, request
from app.common.utils import Logger, Utilities, ApiCalls, Response
from app.common.decorators import login_required, required_params
from app.measurements.controllers import MeasurementsControllers
from app.measurements import measurements_bp


@measurements_bp.before_app_request
def load_user():
    g.user = None
    if 'user_data' in session:
        try:
            g.user = session['user_data']
        except:
            pass


@measurements_bp.route('/measurements', methods=['POST'])
# @login_required
@required_params('type', 'value')
def add_measurement():
    request_id = Utilities.generate_session_id()
    logger = Logger(request_id).event("ADD MEASUREMENT")
    
    params = request.form.to_dict()
    logger.event("request parameters: {}".format(params))

    return MeasurementsControllers(request_id).add_measurement(params)
